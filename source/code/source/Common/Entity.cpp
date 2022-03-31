#include "stdafx.h"
#include "Entity.h"

namespace PlayFab
{

uint32_t Entity::s_tokenPulseIntervalMs{ 1000 * 60 * 30 }; // 30 Minuntes

using Wrappers::SafeString;

Entity::Entity(Authentication::EntityTokenResponse&& response, SharedPtr<PlayFab::HttpClient const> httpClient, RunContext&& tokenRefreshContext) noexcept :
    m_key{ *response.entity },
    m_entityToken{ response },
    m_httpClient{ std::move(httpClient) },
    m_runContext{ std::move(tokenRefreshContext) }
{
}

Entity::~Entity() noexcept
{
    // Cancel TokenPulse
    m_runContext.CancellationToken().Cancel();
}

SharedPtr<PlayFab::HttpClient const> Entity::HttpClient() const
{
    return m_httpClient;
}

PlayFab::EntityKey const& Entity::EntityKey() const
{
    return m_key;
}

AsyncOp<EntityToken> Entity::GetEntityToken(bool forceRefresh, RunContext&& runContext)
{
    if (forceRefresh)
    {
        // API to refresh EntityToken doesn't exist yet
        UNREFERENCED_PARAMETER(runContext);
        return E_FAIL;
    }

    if (m_entityToken.expiration && *m_entityToken.expiration < GetTimeTNow())
    {
        return E_PF_NOENTITYTOKEN;
    }

    return Result<EntityToken>{ EntityToken{ m_entityToken } };
}

class TokenPulseContext : public ICancellationListener
{
public:
    TokenPulseContext(SharedPtr<Entity> entity, RunContext&& rc) : weakEntity{ entity }, runContext{ std::move(rc) }
    {
        bool cancelled = runContext.CancellationToken().RegisterForNotificationAndCheck(*this);
        if (cancelled)
        {
            OnCancellation();
        }
    }

    ~TokenPulseContext()
    {
        runContext.CancellationToken().UnregisterForNotificationAndCheck(*this);
    }

    WeakPtr<Entity> const weakEntity;
    RunContext runContext;

private:
    void OnCancellation() noexcept override
    {
        // TODO is there a race between cancellation and rescheduling work to the queue in TokenPulseCallback?
        // I think we should be ok since the TaskQueue::ScheduleWork call would fail or the callback will be invoked

        // The only way to Cancel work scheduled to a task queue is to terminate that queue
        HRESULT hr = runContext.TaskQueue().Terminate(false, nullptr, nullptr);
        if (FAILED(hr))
        {
            assert(false); 
            TRACE_VERBOSE("Failed to terminated TokenPulse queue");
        }
    }
};

HRESULT Entity::StartTokenRefreshPulseForEntity(SharedPtr<Entity> entity)
{
    auto context = MakeUnique<TokenPulseContext>(entity, entity->m_runContext.Derive());
    RETURN_IF_FAILED(context->runContext.TaskQueue().ScheduleWork(TokenPulseCallback, context.get(), s_tokenPulseIntervalMs));
    context.release();
    return S_OK;
}

void CALLBACK Entity::TokenPulseCallback(void* c, bool cancelled) noexcept
{
    UniquePtr<TokenPulseContext> context{ static_cast<TokenPulseContext*>(c) };
    SharedPtr<Entity> entity{ context->weakEntity.lock() };

    if (cancelled || !entity)
    {
        return;
    }

    std::unique_lock<std::mutex> lock{ entity->m_mutex };

    // Refresh if < 1 hour left until expiration. Possible we could improve this logic to better insulate against suspend scenarios
    time_t const* expiration{ entity->m_entityToken.expiration };
    if (expiration && (uint64_t)(expiration - time(nullptr)) < 60 * 60)
    {
        // Should we use Entity::m_runContext or TokenPulseContext::runContext? Probably either one is fine
        entity->RefreshToken(entity->m_runContext.Derive()).Finally([](Result<void>) {}); // TODO handle errors here
    }

    // Regardless of whether a token refresh was needed, schedule the next callback
    HRESULT hr = context->runContext.TaskQueue().ScheduleWork(TokenPulseCallback, context.get(), s_tokenPulseIntervalMs);
    if (FAILED(hr))
    {
        // This should only fail if the queue has been terminated
        //TRACE_VERBOSE("")
    }
    else
    {
        context.release();
    }
}

AsyncOp<void> Entity::RefreshToken(RunContext&& /*rc*/)
{
    // TODO Service API to refresh token doesn't yet exist
    // TODO It might make sense to have this as an auto generated API outside this class
    return S_OK;
}

EntityToken::EntityToken(const Authentication::EntityTokenResponse& tokenResponse) :
    PFEntityToken{},
    m_token{ tokenResponse.entityToken },
    m_expiration{ tokenResponse.tokenExpiration }
{
    token = m_token.empty() ? nullptr : m_token.data();
    expiration = m_expiration ? m_expiration.operator->() : nullptr;
}

EntityToken::EntityToken(const EntityToken& src) :
    m_token{ src.m_token },
    m_expiration{ src.m_expiration }
{
    token = m_token.empty() ? nullptr : m_token.data();
    expiration = m_expiration ? m_expiration.operator->() : nullptr;
}

EntityToken::EntityToken(EntityToken&& src) :
    PFEntityToken{ src },
    m_token{ std::move(src.m_token) },
    m_expiration{ src.m_expiration }
{
    expiration = m_expiration ? m_expiration.operator->() : nullptr;
}

size_t EntityToken::RequiredBufferSize() const
{
    size_t requiredSize{ alignof(EntityToken) + sizeof(EntityToken) };
    if (token)
    {
        requiredSize += (std::strlen(token) + 1);
    }
    if (expiration)
    {
        requiredSize += (alignof(time_t) + sizeof(time_t));
    }
    return requiredSize;
}

Result<PFEntityToken const*> EntityToken::Copy(ModelBuffer& buffer) const
{
    // Alloc
    auto allocResult = buffer.Alloc<PFEntityToken>(1);
    RETURN_IF_FAILED(allocResult.hr);
    // Copy
    auto outputPtr = allocResult.ExtractPayload();
    {
        auto tokenCopyResult = buffer.CopyTo(this->token);
        RETURN_IF_FAILED(tokenCopyResult.hr);
        outputPtr->token = tokenCopyResult.ExtractPayload();
    }
    {
        auto expirationCopyResult = buffer.CopyTo(this->expiration);
        RETURN_IF_FAILED(expirationCopyResult.hr);
        outputPtr->expiration = expirationCopyResult.ExtractPayload();
    }
    return outputPtr;
}

}
