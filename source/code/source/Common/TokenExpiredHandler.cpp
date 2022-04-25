#include "stdafx.h"
#include "TokenExpiredHandler.h"

namespace PlayFab
{

class ClientHandlerInvocation : public ITaskQueueWork
{
public:
    ClientHandlerInvocation(void* context, PFEntityTokenExpiredEventHandler* handler, String&& entityId) noexcept;

    void Run() override;

private:
    void* const m_context;
    PFEntityTokenExpiredEventHandler* const m_handler;
    String m_entityId;
};

class ClientHandler
{
public:
    ClientHandler(RunContext&& rc, void* context, PFEntityTokenExpiredEventHandler* handler) noexcept;

    RunContext RunContext() const noexcept;
    void Invoke(String entityId) noexcept;

private:
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

ClientHandlerInvocation::ClientHandlerInvocation(void* context, PFEntityTokenExpiredEventHandler* handler, String&& entityId) noexcept :
    m_context{ context },
    m_handler{ handler },
    m_entityId{ std::move(entityId) }
{
}

void ClientHandlerInvocation::Run()
{
    try
    {
        m_handler(m_context, m_entityId.data());
    }
    catch (...)
    {
        TRACE_ERROR("Caught unhandled exception in client TokenExpired handler");
    }
}

ClientHandler::ClientHandler(PlayFab::RunContext&& rc, void* context, PFEntityTokenExpiredEventHandler* handler) noexcept :
    m_rc{ std::move(rc) },
    m_context{ context },
    m_handler{ handler }
{
}

RunContext ClientHandler::RunContext() const noexcept
{
    return m_rc;
}

void ClientHandler::Invoke(String entityId) noexcept
{
    m_rc.TaskQueue().SubmitWork(MakeShared<ClientHandlerInvocation>(m_context, m_handler, std::move(entityId)));
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

    it->second->RunContext().Terminate(nullptr, nullptr);

    m_clientHandlers.erase(it);
}

void TokenExpiredHandler::SharedState::Invoke(String&& entityId) const noexcept
{
    std::unique_lock<std::recursive_mutex> lock{ m_mutex };
    
    TRACE_VERBOSE(__FUNCTION__);

    for (auto& pair : m_clientHandlers)
    {
        pair.second->Invoke(entityId);
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
