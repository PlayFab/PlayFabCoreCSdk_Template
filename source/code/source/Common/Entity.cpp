#include "stdafx.h"
#include "Entity.h"

namespace PlayFab
{

uint32_t Entity::s_tokenPulseIntervalMs{ 1000 * 60 * 30 }; // 30 Minuntes

using Wrappers::SafeString;

Entity::Entity(
    Authentication::EntityTokenResponse&& response,
    SharedPtr<PlayFab::ServiceConfig const> serviceConfig,
    RunContext&& tokenRefreshContext,
    TokenExpiredHandler&& tokenExpiredHandler
) noexcept :
    m_key{ *response.entity },
    m_entityToken{ response },
    m_serviceConfig{ std::move(serviceConfig) },
    m_runContext{ std::move(tokenRefreshContext) },
    m_tokenExpiredHandler{ std::move(tokenExpiredHandler) }
{
    if (m_runContext.CancellationToken().RegisterForNotificationAndCheck(*this))
    {
        OnCancellation();
    }
}

Entity::~Entity() noexcept
{
    if (!m_runContext.CancellationToken().UnregisterForNotificationAndCheck(*this))
    {
        // If it wasn't terminated already, terminate the background queue
        OnCancellation();
    }
}

SharedPtr<PlayFab::ServiceConfig const> Entity::ServiceConfig() const
{
    return m_serviceConfig;
}

PlayFab::EntityKey const& Entity::EntityKey() const
{
    return m_key;
}

AsyncOp<EntityToken> Entity::GetEntityToken(bool forceRefresh, RunContext&& runContext)
{
    std::unique_lock<std::mutex> lock{ m_mutex };

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

HRESULT Entity::SetEntityToken(Authentication::EntityTokenResponse const& entityTokenResponse)
{
    std::unique_lock<std::mutex> lock{ m_mutex };

    RETURN_HR_IF(E_FAIL, !entityTokenResponse.entity.has_value());

    if (std::strcmp(entityTokenResponse.entity->Model().id, m_key.Model().id))
    {
        TRACE_ERROR("%s: attempting to set EntityToken with mismatched entityKey", __FUNCTION__);
        return E_FAIL;
    }

    m_entityToken = EntityToken{ entityTokenResponse };

    return S_OK;
}

void Entity::OnCancellation() noexcept
{
    HRESULT hr = m_runContext.TerminateTaskQueue();
    if (FAILED(hr))
    {
        assert(false);
        TRACE_VERBOSE("Failed to terminate Entity background TaskQueue");
    }
}

struct TokenPulseContext
{
    TokenPulseContext(SharedPtr<Entity> entity) : weakEntity{ entity } {}
    ~TokenPulseContext() = default;

    WeakPtr<Entity> const weakEntity;
};

HRESULT Entity::StartTokenRefreshPulseForEntity(SharedPtr<Entity> entity)
{
    auto context = MakeUnique<TokenPulseContext>(entity);
    RETURN_IF_FAILED(entity->m_runContext.TaskQueue().ScheduleWork(TokenPulseCallback, context.get(), s_tokenPulseIntervalMs));
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
        entity->RefreshToken(entity->m_runContext.Derive()).Finally([entity](Result<void> result)
        {
            if (FAILED(result.hr))
            {
                // Do we need special handling for E_ABORT? maybe don't invoke callback in that case?
                entity->m_tokenExpiredHandler.Invoke(entity->m_key.Model().id);
            }
            else
            {
                // Make sure entity->m_entityToken is updated
            }
        });
    }

    // Regardless of whether a token refresh was needed, schedule the next callback
    HRESULT hr = entity->m_runContext.TaskQueue().ScheduleWork(TokenPulseCallback, context.get(), s_tokenPulseIntervalMs);
    if (FAILED(hr))
    {
        // This should only fail if the queue has been terminated
        assert(hr == E_ABORT);
        //TRACE_VERBOSE("")
    }
    else
    {
        context.release();
    }
}

AsyncOp<void> Entity::RefreshToken(RunContext&& /*rc*/)
{
    return E_NOTIMPL;
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

EntityToken& EntityToken::operator=(const EntityToken& src)
{
    m_token = src.m_token;
    token = m_token.empty() ? nullptr : m_token.data();

    m_expiration = src.m_expiration;
    expiration = m_expiration ? m_expiration.operator->() : nullptr;

    return *this;
}

EntityToken& EntityToken::operator=(EntityToken&& src)
{
    m_token = std::move(src.m_token);
    token = m_token.empty() ? nullptr : m_token.data();

    m_expiration = src.m_expiration;
    expiration = m_expiration ? m_expiration.operator->() : nullptr;

    return *this;
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
