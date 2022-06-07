#include "stdafx.h"
#include "GlobalState.h"
#include "AsyncProvider.h"
#include <httpClient/httpClient.h>

using namespace PlayFab;

namespace PlayFab
{

class TraceState
{
public:
    static TraceState& Get();

    TraceState(const TraceState&) = delete;
    TraceState& operator=(TraceState) = delete;
    ~TraceState();

    void AddTraceOutput(UniquePtr<TraceOutput> output);
    void ClearTraceOutputs();

private:
    TraceState();

    static void CALLBACK TraceCallback(
        _In_z_ const char* areaName,
        _In_ HCTraceLevel level,
        _In_ uint64_t threadId,
        _In_ uint64_t timestamp,
        _In_z_ const char* message
    ) noexcept;

    static constexpr size_t kMaxTraceOutputs{ 3 };
    std::array<UniquePtr<TraceOutput>, kMaxTraceOutputs> m_traceOutputs;
};

// Clarify/simplify this pattern
struct GlobalStateBootstrapper
{
    enum class AccessMode
    {
        Create,
        Get,
        Cleanup
    };

    struct CreateArgs
    {
        XTaskQueueHandle backgroundQueue;
    };

    static HRESULT StateAccess(AccessMode mode, CreateArgs* createArgs, SharedPtr<GlobalState>& state) noexcept;
};

namespace Detail
{

// Choose arbitrary but recognizable values for handles
uintptr_t const kFirstServiceConfigHandle = 0x10000000;
uintptr_t const kFirstTitlePlayerHandle = 0x20000000;
uintptr_t const kFirstTelemetryPipelineHandle = 0x30000000;

}

GlobalState::GlobalState(XTaskQueueHandle backgroundQueue) noexcept :
    m_runContext{ RunContext::Root(backgroundQueue) },
    m_serviceConfigs{ Detail::kFirstServiceConfigHandle },
    m_titlePlayers{ Detail::kFirstTitlePlayerHandle },
    m_clientTeletryPipelines{ Detail::kFirstTelemetryPipelineHandle }
{
}

GlobalState::~GlobalState() noexcept
{
    TRACE_VERBOSE(__FUNCTION__);
}

HRESULT GlobalState::Create(XTaskQueueHandle backgroundQueue) noexcept
{
    // Add trace outputs before anything else so that tracing works during initialization
    auto& traceSettings = GetTraceSettings();
    if (traceSettings.enableTraceToFile)
    {
        auto traceFileOutput = MakeUnique<TraceFileOutput>(traceSettings.traceFileDirectory);
        TraceState::Get().AddTraceOutput(UniquePtr<TraceOutput>{ traceFileOutput.release() });
    }

    RETURN_IF_FAILED(HCInitialize(nullptr));

    GlobalStateBootstrapper::CreateArgs args{ backgroundQueue };
    SharedPtr<GlobalState> state;
    return GlobalStateBootstrapper::StateAccess(GlobalStateBootstrapper::AccessMode::Create, &args, state);
}

HRESULT GlobalState::Get(SharedPtr<GlobalState>& state) noexcept
{
    return GlobalStateBootstrapper::StateAccess(GlobalStateBootstrapper::AccessMode::Get, nullptr, state);
}

struct CleanupContext
{
    XAsyncBlock lhcCleanupAsync{};
    XAsyncBlock* cleanupAsync{};
};

HRESULT GlobalState::CleanupAsync(XAsyncBlock* async) noexcept
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

HRESULT CALLBACK GlobalState::CleanupAsyncProvider(XAsyncOp op, XAsyncProviderData const* data)
{
    CleanupContext* context{ static_cast<CleanupContext*>(data->context) };

    switch (op)
    {
    case XAsyncOp::Begin:
    try
    {
        SharedPtr<GlobalState> state;
        RETURN_IF_FAILED(GlobalStateBootstrapper::StateAccess(GlobalStateBootstrapper::AccessMode::Cleanup, nullptr, state));
        context->cleanupAsync = data->async;

        state->m_runContext.Terminate(std::move(state), context);
        return S_OK;
    }
    catch (...)
    {
        return CurrentExceptionToHR();
    }
    default:
    {
        return S_OK;
    }
    }
}

void CALLBACK HCCleanupComplete(XAsyncBlock* async)
{
    TRACE_VERBOSE(__FUNCTION__);

    // This is the last step of cleanup, so reclaim the context
    UniquePtr<CleanupContext> context{ static_cast<CleanupContext*>(async->context) };

    HRESULT hr = XAsyncGetStatus(async, false);
    assert(hr != E_PENDING);

    if (hr == E_HC_INTERNAL_STILLINUSE)
    {
        // If something else is still referencing libHttpClient, complete with success
        hr = S_OK;
    }

    // Free context before completing the XAsyncBlock because there isn't a guarantee that Provider::Cleanup is called
    // before the client's callback.
    XAsyncBlock* cleanupAsync{ context->cleanupAsync };
    context.reset();

    // Cleanup TraceOutputs
    TraceState::Get().ClearTraceOutputs();

    XAsyncComplete(cleanupAsync, hr, 0);
}

void GlobalState::OnTerminated(SharedPtr<ITerminationListener>&& self, void* c) noexcept
{
    TRACE_VERBOSE(__FUNCTION__);

    CleanupContext* context{ static_cast<CleanupContext*>(c) };

    // Free GlobalState before calling HCCleanup - 'this' will be destroyed here
    self.reset();

    context->lhcCleanupAsync.callback = HCCleanupComplete;
    context->lhcCleanupAsync.queue = context->cleanupAsync->queue; // Should use derived queue
    context->lhcCleanupAsync.context = context;

    HCCleanupAsync(&context->lhcCleanupAsync);
}

RunContext GlobalState::RunContext() const noexcept
{
    return m_runContext;
}

ServiceConfigHandleTable& GlobalState::ServiceConfigs() noexcept
{
    return m_serviceConfigs;
}

TitlePlayerHandleTable& GlobalState::TitlePlayers() noexcept
{
    return m_titlePlayers;
}

TelemetryPipelineHandleTable& GlobalState::ClientTelemetryPipelines() noexcept
{
    return m_clientTeletryPipelines;
}

TokenExpiredHandler GlobalState::TokenExpiredHandler() const noexcept
{
    return m_tokenExpiredHandler;
}

HRESULT GlobalStateBootstrapper::StateAccess(AccessMode mode, CreateArgs* createArgs, SharedPtr<GlobalState>& state) noexcept
{
    struct StateHolder
    {
        SharedPtr<GlobalState> state;
    };

    // function scope static members so initialization order is defined
    static std::mutex s_mutex;
    static StateHolder* s_stateHolder{ nullptr }; // intentional non-owning pointer

    try
    {
        std::lock_guard<std::mutex> lock{ s_mutex };

        switch (mode)
        {
        case AccessMode::Create:
        {
            // Assuming for now initialization is not ref counted - there should be exactly one call to create
            // and exactly one call to cleanup
            if (s_stateHolder)
            {
                return E_PF_ALREADY_INITIALIZED;
            }

            assert(createArgs);
            state = SharedPtr<GlobalState>{ new (Allocator<GlobalState>{}.allocate(1)) GlobalState{ createArgs->backgroundQueue }, Deleter<GlobalState>() };
            s_stateHolder = MakeUnique<StateHolder>().release(); // will be reclaimed in cleanup
            s_stateHolder->state = std::move(state);

            return S_OK;
        }
        case AccessMode::Get:
        {
            if (!s_stateHolder)
            {
                return E_PF_NOT_INITIALIZED;
            }
            assert(s_stateHolder->state);
            state = s_stateHolder->state;

            return S_OK;
        }
        case AccessMode::Cleanup:
        {
            if (!s_stateHolder)
            {
                return E_PF_NOT_INITIALIZED;
            }

            UniquePtr<StateHolder> stateHolder{ s_stateHolder };
            s_stateHolder = nullptr;
            state = stateHolder->state; // state is the only remaining reference to the GlobalState

            return S_OK;
        }
        default:
        {
            assert(false);
            return E_UNEXPECTED;
        }
        }
    }
    catch (...)
    {
        return CurrentExceptionToHR();
    }
}

TraceState::TraceState()
{
    HCTraceInit();
    HCTraceSetClientCallback(TraceState::TraceCallback);
}

TraceState::~TraceState()
{
    for (auto& output : m_traceOutputs)
    {
        assert(!output);
    }

    HCTraceSetClientCallback(nullptr);
    HCTraceCleanup();
}

TraceState& TraceState::Get()
{
    static TraceState s_state;
    return s_state;
}

void TraceState::AddTraceOutput(UniquePtr<TraceOutput> newOutput)
{
    for (auto& output : m_traceOutputs)
    {
        if (!output)
        {
            output = std::move(newOutput);
        }
    }
}

void TraceState::ClearTraceOutputs()
{
    for (auto& output : m_traceOutputs)
    {
        output.reset();
    }
}

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
    TraceState& state = TraceState::Get();

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

    for (auto& output : state.m_traceOutputs)
    {
        if (output)
        {
            output->TraceMessage(formattedMessage);
        }
    }
}

} // namespace PlayFab
