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

    static HRESULT StateAccess(AccessMode mode, CreateArgs* createArgs, SharedPtr<GlobalState>& state);
};

GlobalState::GlobalState(XTaskQueueHandle backgroundQueue) noexcept :
    m_runContext{ backgroundQueue },
    m_serviceConfigs{ (HANDLE)0x10000000 }, // TODO choose sensible values here
    m_titlePlayers{ (HANDLE)0x20000000 }
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
    SharedPtr<GlobalState> state;
    XAsyncBlock lhcCleanupAsync{};
    XAsyncBlock* cleanupAsync{};
};

HRESULT GlobalState::CleanupAsync(XAsyncBlock* async) noexcept
{
    UniquePtr<CleanupContext> context = MakeUnique<CleanupContext>();
    RETURN_IF_FAILED(XAsyncBegin(async, context.get(), __FUNCTION__, __FUNCTION__, CleanupAsyncProvider));
    context.release();
    return S_OK;
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

void CALLBACK RunContextTerminated(void* c)
{
    TRACE_VERBOSE(__FUNCTION__);

    CleanupContext* context{ static_cast<CleanupContext*>(c) };

    context->lhcCleanupAsync.callback = HCCleanupComplete;
    context->lhcCleanupAsync.queue = context->cleanupAsync->queue; // Should use derived queue
    context->lhcCleanupAsync.context = context;

    HCCleanupAsync(&context->lhcCleanupAsync);
}

HRESULT CALLBACK GlobalState::CleanupAsyncProvider(XAsyncOp op, XAsyncProviderData const* data)
{
    CleanupContext* context{ static_cast<CleanupContext*>(data->context) };

    switch (op)
    {
    case XAsyncOp::Begin:
    {
        RETURN_IF_FAILED(GlobalStateBootstrapper::StateAccess(GlobalStateBootstrapper::AccessMode::Cleanup, nullptr, context->state));
        context->cleanupAsync = data->async;

        // TODO cleanup all users?

        context->state->m_runContext.Terminate(RunContextTerminated, context);
        return S_OK;
    }
    default:
    {
        return S_OK;
    }
    }
}

RunContext const& GlobalState::RunContext() const noexcept
{
    return m_runContext;
}

HandleTable<ServiceConfig>& GlobalState::ServiceConfigs() noexcept
{
    return m_serviceConfigs;
}

HandleTable<TitlePlayer>& GlobalState::TitlePlayers() noexcept
{
    return m_titlePlayers;
}

HRESULT GlobalStateBootstrapper::StateAccess(AccessMode mode, CreateArgs* createArgs, SharedPtr<GlobalState>& state)
{
    struct StateHolder
    {
        SharedPtr<GlobalState> state;
    };

    // function scope static members so initialization order is defined
    static std::mutex s_mutex;
    static StateHolder* s_stateHolder{ nullptr }; // intentional non-owning pointer

    std::lock_guard<std::mutex> lock{ s_mutex };

    switch (mode)
    {
    case AccessMode::Create:
    {
        // Assuming for now initialization is not ref counted - there should be exactly one call to create
        // and exactly one call to cleanup
        if (s_stateHolder)
        {
            return E_UNEXPECTED; // Should define PF_E_ALREADY_INITIALIZED
        }

        // TODO Lock memory hooks here

        assert(createArgs);
        //state = SharedPtr<GlobalState>{ new (Allocator<GlobalState>{}.allocate(1)) GlobalState{ createArgs->backgroundQueue }, Deleter<GlobalState>() };
        state = SharedPtr<GlobalState>{ new (Allocator<GlobalState>{}.allocate(1)) GlobalState{ createArgs->backgroundQueue } };
        s_stateHolder = MakeUnique<StateHolder>().release(); // will be reclaimed in cleanup
        s_stateHolder->state = std::move(state);

        return S_OK;
    }
    case AccessMode::Get:
    {
        if (!s_stateHolder)
        {
            return E_UNEXPECTED; // Should define PF_E_NOT_INITIALIZED
        }
        assert(s_stateHolder->state);
        state = s_stateHolder->state;

        return S_OK;
    }
    case AccessMode::Cleanup:
    {
        if (!s_stateHolder)
        {
            return E_UNEXPECTED; // Should define PF_E_NOT_INITIALIZED
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

} // namespace PlayFab
