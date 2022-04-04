#include "stdafx.h"
#include "TokenExpiredHandler.h"

namespace PlayFab
{

class ClientHandler : public ICancellationListener
{
public:
    ClientHandler(RunContext&& rc, void* context, PFEntityTokenExpiredEventHandler* handler) noexcept;
    ClientHandler(ClientHandler const&) = delete;
    ClientHandler(ClientHandler&&) = delete;
    ClientHandler& operator=(ClientHandler const&) = delete;
    ClientHandler& operator=(ClientHandler&&) = delete;
    ~ClientHandler() noexcept;

    static void Invoke(SharedPtr<ClientHandler> handler, String entityId) noexcept;

    RunContext const& RunContext() const noexcept;

private:
    void OnCancellation() noexcept override;

    using CallbackContext = std::tuple<SharedPtr<ClientHandler const>, String>;

    static void CALLBACK TaskQueueCallback(void* context, bool cancelled) noexcept;

    PlayFab::RunContext m_rc;
    void* const m_context;
    PFEntityTokenExpiredEventHandler* const m_handler;
};

class TokenExpiredHandler::SharedState
{
public:
    SharedState() noexcept;
    SharedState(SharedState const&) = delete;
    SharedState(SharedState&&) = delete;
    SharedState& operator=(SharedState const&) = delete;
    SharedState& operator=(SharedState&&) = delete;
    ~SharedState() noexcept = default;

    HRESULT RegisterClientHandler(
        RunContext&& rc,
        void* context,
        PFEntityTokenExpiredEventHandler* handler,
        PFRegistrationToken* token
    ) noexcept;

    void UnregisterClientHandler(PFRegistrationToken token) noexcept;

    void Invoke(String&& entityId) const noexcept;

private:
    mutable std::recursive_mutex m_mutex; // recursive for unregister

    Map<PFRegistrationToken, SharedPtr<ClientHandler>> m_clientHandlers;
    PFRegistrationToken m_nextToken;
};

ClientHandler::ClientHandler(PlayFab::RunContext&& rc, void* context, PFEntityTokenExpiredEventHandler* handler) noexcept :
    m_rc{ std::move(rc) },
    m_context{ context },
    m_handler{ handler }
{
    auto cancelled = m_rc.CancellationToken().RegisterForNotificationAndCheck(*this);
    if (cancelled)
    {
        OnCancellation();
    }
}

ClientHandler::~ClientHandler() noexcept
{
    m_rc.CancellationToken().UnregisterForNotificationAndCheck(*this);
}

void ClientHandler::Invoke(SharedPtr<ClientHandler> handler, String entityId) noexcept
{
    auto context = MakeUnique<CallbackContext>(handler, std::move(entityId));

    HRESULT hr = handler->m_rc.TaskQueue().ScheduleWork(TaskQueueCallback, context.get(), 0);
    if (FAILED(hr))
    {
        TRACE_ERROR_HR(hr, "Failed to schedule TokenExpiredEventHanler");
    }
    else
    {
        context.release();
    }
}

RunContext const& ClientHandler::RunContext() const noexcept
{
    return m_rc;
}

void ClientHandler::OnCancellation() noexcept
{
    m_rc.TerminateTaskQueue();
}

void CALLBACK ClientHandler::TaskQueueCallback(void* c, bool cancelled) noexcept
{
    TRACE_VERBOSE("%s: cancelled=%u", __FUNCTION__, cancelled);

    UniquePtr<CallbackContext> context{ static_cast<CallbackContext*>(c) };
    if (!cancelled)
    {
        // Could this be racing with Unregister: 
        // 1) SDK calls TokenExpiredHandler::Invoke
        // 2) ClientHandler::TaskQueueCallback scheduled
        // 3) Before TaskQueueCallback runs, client calls TokenExpiredHandler::Unregister
        // 4) TaskQueueCallback runs. Unsure if its possible for cancelled=false here however

        auto& clientHandler{ std::get<0>(*context) };
        clientHandler->m_handler(clientHandler->m_context, std::get<1>(*context).data());
    }
}

namespace Detail
{
// Arbitrary first token thats recognizable when debugging
PFRegistrationToken const kFirstCallbackToken = 0xBAC0000000000000;
}


TokenExpiredHandler::SharedState::SharedState() noexcept :
    m_nextToken{ Detail::kFirstCallbackToken }
{
}

HRESULT TokenExpiredHandler::SharedState::RegisterClientHandler(RunContext&& rc, void* context, PFEntityTokenExpiredEventHandler* handler, PFRegistrationToken* token) noexcept
{
    std::unique_lock<std::recursive_mutex> lock{ m_mutex };

    RETURN_HR_INVALIDARG_IF_NULL(handler);
    RETURN_HR_INVALIDARG_IF_NULL(token);

    *token = m_nextToken++;
    m_clientHandlers.emplace(*token, MakeShared<ClientHandler>(std::move(rc), context, handler));

    return S_OK;
}

void TokenExpiredHandler::SharedState::UnregisterClientHandler(PFRegistrationToken token) noexcept
{
    std::unique_lock<std::recursive_mutex> lock{ m_mutex };

    TRACE_VERBOSE(__FUNCTION__);

    auto it = m_clientHandlers.find(token);
    if (it == m_clientHandlers.end())
    {
        TRACE_WARNING("%s: Attempted to unregister handler with unrecognized token", __FUNCTION__);
        return;
    }

    it->second->RunContext().CancellationToken().Cancel();

    m_clientHandlers.erase(it);
}

void TokenExpiredHandler::SharedState::Invoke(String&& entityId) const noexcept
{
    std::unique_lock<std::recursive_mutex> lock{ m_mutex };
    
    TRACE_VERBOSE(__FUNCTION__);

    for (auto& pair : m_clientHandlers)
    {
        ClientHandler::Invoke(pair.second, entityId);
    }
}

TokenExpiredHandler::TokenExpiredHandler() noexcept :
    m_state{ MakeShared<SharedState>() }
{
}

HRESULT TokenExpiredHandler::RegisterClientHandler(RunContext&& rc, void* context, PFEntityTokenExpiredEventHandler* handler, PFRegistrationToken* token) noexcept
{
    return m_state->RegisterClientHandler(std::move(rc), context, handler, token);
}

void TokenExpiredHandler::UnregisterClientHandler(PFRegistrationToken token) noexcept
{
    m_state->UnregisterClientHandler(token);
}

void TokenExpiredHandler::Invoke(String&& entityId) const noexcept
{
    m_state->Invoke(std::move(entityId));
}

}
