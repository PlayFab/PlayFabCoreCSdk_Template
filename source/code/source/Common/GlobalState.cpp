#include "stdafx.h"
#include "GlobalState.h"
#include "AsyncProvider.h"
#include <httpClient/httpClient.h>

using namespace PlayFab;

namespace PlayFab
{

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
    HCTraceInit();
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

    HCTraceCleanup();

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

} // namespace PlayFab
