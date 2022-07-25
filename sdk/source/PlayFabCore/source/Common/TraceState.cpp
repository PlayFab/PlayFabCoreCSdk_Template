#include "stdafx.h"
#include "TraceState.h"
#include "JsonUtils.h"
#include "Platform/LocalStorage.h"
#include "LocalStorageTraceOutput.h"

namespace PlayFab
{

TraceSettings& GetTraceSettings()
{
    static TraceSettings s_settings;
    return s_settings;
}

enum class AccessMode
{
    Initialize,
    Get,
    Cleanup
};

HRESULT AccessTraceState(AccessMode mode, SharedPtr<TraceState>& traceState)
{
    struct TraceStateHolder
    {
        SharedPtr<TraceState> const state;
    };

    static std::atomic<TraceStateHolder*> s_traceStateHolder{ nullptr };
    assert(s_traceStateHolder.is_lock_free());

    switch (mode)
    {
    case AccessMode::Initialize:
    {
        RETURN_HR_IF(E_PF_ALREADY_INITIALIZED, s_traceStateHolder);
        RETURN_HR_INVALIDARG_IF_NULL(traceState);

        TraceStateHolder* traceStateHolder = new (Allocator<TraceStateHolder>{}.allocate(1)) TraceStateHolder{ traceState }; // Reclaimed in cleanup
        s_traceStateHolder.store(traceStateHolder);

        return S_OK;
    }
    case AccessMode::Get:
    {
        TraceStateHolder* traceStateHolder = s_traceStateHolder.load();

        RETURN_HR_IF(E_PF_NOT_INITIALIZED, !traceStateHolder);
        assert(traceStateHolder->state);
        traceState = traceStateHolder->state;

        return S_OK;
    }
    case AccessMode::Cleanup:
    {
        UniquePtr<TraceStateHolder> traceStateHolder{ s_traceStateHolder.exchange(nullptr) };

        RETURN_HR_IF(E_PF_NOT_INITIALIZED, !traceStateHolder);
        traceState = traceStateHolder->state;

        return S_OK;
    }
    default:
    {
        assert(false);
        return E_UNEXPECTED;
    }
    }
}

TraceState::TraceState(RunContext&& runContext, Vector<UniquePtr<TraceOutput>>&& outputs) noexcept :
    m_runContext{ std::move(runContext) },
    m_outputs{ std::move(outputs) }
{
    HCTraceInit();  
#ifdef _DEBUG
    HCTraceSetTraceToDebugger(true);
    HCSettingsSetTraceLevel(HCTraceLevel::Verbose);
#endif
    HCTraceSetClientCallback(TraceCallback);
}

TraceState::~TraceState() noexcept
{
    HCTraceSetClientCallback(nullptr);
    HCTraceCleanup();
}

HRESULT TraceState::Create(RunContext&& runContext, LocalStorage localStorage) noexcept
{
    TraceSettings& settings = GetTraceSettings();

    // Synchronously load trace settings. TraceSettings loaded from file override those configured via API
    // TODO document location, name, and format of TraceSettings file. It should just be a Json serialized
    // version of the TraceSettings struct:
    // {
    //   "enableTraceToFile": true,
    //   "traceFileDirectory": ""
    // }
    Result<Vector<uint8_t>> readResult = localStorage.Read(s_configFile, runContext).Wait();
    if (SUCCEEDED(readResult.hr))
    {
        auto fileData{ readResult.ExtractPayload() };

        JsonDocument fileJson{ &JsonUtils::allocator };
        fileJson.Parse(reinterpret_cast<char*>(fileData.data()), fileData.size());
        if (!fileJson.HasParseError())
        {
            JsonUtils::ObjectGetMember(fileJson, "enableTraceToFile", settings.enableTraceToFile);
            String traceFileDirectory;
            JsonUtils::ObjectGetMember(fileJson, "traceFileDirectory", traceFileDirectory);
            strcpy_s(settings.traceFileDirectory, traceFileDirectory.data());
        }
    }

    Vector<UniquePtr<TraceOutput>> outputs;
    if (settings.enableTraceToFile)
    {
        outputs.emplace_back(MakeUnique<LocalStorageTraceOutput>(runContext.Derive(), localStorage, settings.traceFileDirectory).release());
    }

    SharedPtr<TraceState> traceState{ new (Allocator<TraceState>{}.allocate(1)) TraceState{ std::move(runContext), std::move(outputs) }, Deleter<TraceState>{} };

    return AccessTraceState(AccessMode::Initialize, traceState);
}

HRESULT TraceState::Get(SharedPtr<TraceState>& state) noexcept
{
    return AccessTraceState(AccessMode::Get, state);
}

struct CleanupContext
{
    SharedPtr<TraceState> traceState;
    XAsyncBlock* asyncBlock;
};

HRESULT TraceState::CleanupAsync(XAsyncBlock* async) noexcept
{
    try
    {
        UniquePtr<CleanupContext> context = MakeUnique<CleanupContext>();
        RETURN_IF_FAILED(XAsyncBegin(async, context.get(), __FUNCTION__, __FUNCTION__, CleanupAsyncProvider));
        context.release();
        return S_OK;
    }
    catch (...)
    {
        return CurrentExceptionToHR();
    }
}

HRESULT CALLBACK TraceState::CleanupAsyncProvider(XAsyncOp op, XAsyncProviderData const* data) noexcept
{
    static constexpr uint32_t s_pollDelayMs{ 10 };
    CleanupContext* context{ static_cast<CleanupContext*>(data->context) };

    switch (op)
    {
    case XAsyncOp::Begin:
    {
        // After this no other thread will be able to access TraceState if they don't already have a reference to it
        RETURN_IF_FAILED(AccessTraceState(AccessMode::Cleanup, context->traceState));
        context->asyncBlock = data->async;

        return XAsyncSchedule(data->async, 0);
    }
    case XAsyncOp::DoWork:
    {
        // If there aren't any other remaining reference to TraceState, Terminate the RunContext and destroy it. Otherwise
        // wait until we have the last remaining reference
        if (context->traceState.use_count() > 1)
        {
            RETURN_IF_FAILED(XAsyncSchedule(data->async, s_pollDelayMs));
            return E_PENDING;
        }

        // Give TraceOutputs a chance to finish naturally before terminating RunContext. Terminating RunContext immediately may lead to 
        // lost trace messages in some cases
        for (auto& output : context->traceState->m_outputs)
        {
            output->Stop();
        }

        // Forcibily terminate any remaining work
        context->traceState->m_runContext.Terminate(*context->traceState, context);
        return E_PENDING;
    }
    default:
    {
        return S_OK;
    }
    }
}

void TraceState::OnTerminated(void* c) noexcept
{
    UniquePtr<CleanupContext> context{ static_cast<CleanupContext*>(c) };
    XAsyncBlock* asyncBlock{ context->asyncBlock }; // Keep copy of asyncBlock pointer to complete after cleaning up context

    // Cleanup context. TraceState will be destroyed here
    context.reset();

    // TraceState fully cleaned up!
    XAsyncComplete(asyncBlock, S_OK, 0);
}

// Trace helpers
template<size_t SIZE>
int stprintf_s(char(&buffer)[SIZE], _Printf_format_string_ char const* format ...) noexcept
{
    va_list varArgs{};
    va_start(varArgs, format);
    auto result = vsnprintf(buffer, SIZE, format, varArgs);
    va_end(varArgs);
    return result;
}

int stprintf_s(char* buffer, size_t size, _Printf_format_string_ char const* format ...) noexcept
{
    va_list varArgs{};
    va_start(varArgs, format);
    auto result = vsnprintf(buffer, size, format, varArgs);
    va_end(varArgs);
    return result;
}

template<size_t SIZE>
int vstprintf_s(char(&buffer)[SIZE], _Printf_format_string_ char const* format, va_list varArgs) noexcept
{
    return vsnprintf(buffer, SIZE, format, varArgs);
}

void CALLBACK TraceState::TraceCallback(
    _In_z_ const char* areaName,
    _In_ HCTraceLevel level,
    _In_ uint64_t threadId,
    _In_ uint64_t timestamp,
    _In_z_ const char* message
) noexcept
{
    SharedPtr<TraceState> state;
    TraceState::Get(state);
    if (!state)
    {
        return;
    }
    else if (state->m_outputs.empty())
    {
        // Early out if we have no outputs
        return;
    }


    // Needs to match the HCTraceLevel enum
    static char const* traceLevelNames[] =
    {
        "Off",
        "E",
        "W",
        "P",
        "I",
        "V",
    };

    static size_t const BUFFER_SIZE = 4096;

    std::time_t timeTInSec = static_cast<std::time_t>(timestamp / 1000);
    uint32_t fractionMSec = static_cast<uint32_t>(timestamp % 1000);
    std::tm fmtTime = {};

#if HC_PLATFORM_IS_MICROSOFT
    localtime_s(&fmtTime, &timeTInSec);
#else
    localtime_r(&timeTInSec, &fmtTime);
#endif

    char formattedMessage[BUFFER_SIZE] = {};
    // [threadId][level][time][area] message
    auto written = stprintf_s(formattedMessage, "[%04llX][%s][%02d:%02d:%02d.%03u][%s] %s",
        threadId,
        traceLevelNames[static_cast<size_t>(level)],
        fmtTime.tm_hour,
        fmtTime.tm_min,
        fmtTime.tm_sec,
        fractionMSec,
        areaName,
        message
    );

    if (written <= 0)
    {
        return;
    }

    // Make sure there is room for the \r \n and \0
    written = std::min(written, static_cast<int>(BUFFER_SIZE - 3));
    auto remaining = BUFFER_SIZE - written;

    // Print new line
    auto written2 = stprintf_s(formattedMessage + written, remaining, "\r\n");
    if (written2 <= 0)
    {
        return;
    }

    for (auto& output : state->m_outputs)
    {
        output->TraceMessage(formattedMessage);
    }
}

}
