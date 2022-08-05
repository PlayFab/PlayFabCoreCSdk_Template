#include "stdafx.h"
#include "Entity.h"
#include "Authentication/Authentication.h"

#if HC_PLATFORM == HC_PLATFORM_GDK
#include <XGameRuntimeFeature.h>
#include <XNetworking.h>
#include <appnotify.h>
#endif

namespace PlayFab
{

using Wrappers::SafeString;

class TokenRefreshWorker : public ITaskQueueWork, public std::enable_shared_from_this<TokenRefreshWorker>
{
public:
    static SharedPtr<TokenRefreshWorker> MakeAndStart(SharedPtr<Entity> const& entity, RunContext&& rc, TokenExpiredHandler tokenExpiredHandler);

    ~TokenRefreshWorker();

private:
    TokenRefreshWorker(SharedPtr<Entity> const& entity, RunContext&& rc, TokenExpiredHandler tokenExpiredHandler);

    // ITaskQueueWork
    void Run() override;

    // Check validity of token and refresh if needed. Handles all errors and invokes TokenExpiredHandler as needed
    void CheckAndRefreshToken(SharedPtr<Entity> entity) noexcept;

    static bool CheckRefreshRequired(EntityToken const& token) noexcept;

    std::mutex m_mutex;
    WeakPtr<Entity> m_weakEntity;
    PlayFab::RunContext m_rc;
    TokenExpiredHandler m_tokenExpiredHandler;

#if HC_PLATFORM == HC_PLATFORM_GDK
    static void CALLBACK NetworkConnectivityChangedCallback(void* context, const XNetworkingConnectivityHint* hint);
    static void CALLBACK AppStateChangedCallback(BOOLEAN isSuspended, void* context);

    bool m_resumeTokenCheckPending{ false };
    bool m_isSuspended{ false };

    XTaskQueueRegistrationToken m_networkConnectivityChangedToken{};
    PAPPSTATE_REGISTRATION m_appStateChangedToken{ nullptr };
#endif

    static constexpr uint32_t s_interval{ 1000 * 60 * 30 }; // 30 Minuntes
};

TokenRefreshWorker::TokenRefreshWorker(SharedPtr<Entity> const& entity, PlayFab::RunContext&& rc, TokenExpiredHandler tokenExpiredHandler) :
    m_weakEntity{ entity },
    m_rc{ std::move(rc) },
    m_tokenExpiredHandler{ std::move(tokenExpiredHandler) }
{
#if HC_PLATFORM == HC_PLATFORM_GDK
    HRESULT hr = XNetworkingRegisterConnectivityHintChanged(m_rc.TaskQueueHandle(), this, TokenRefreshWorker::NetworkConnectivityChangedCallback, &m_networkConnectivityChangedToken);
    if (FAILED(hr))
    {
        TRACE_ERROR_HR(hr, "Failed to register for connectivity changed notifications");
    }

    hr = HRESULT_FROM_WIN32(RegisterAppStateChangeNotification(TokenRefreshWorker::AppStateChangedCallback, this, &m_appStateChangedToken));
    if (FAILED(hr))
    {
        TRACE_ERROR_HR(hr, "Failed to register for app state change notifications");
    }
#endif
}

TokenRefreshWorker::~TokenRefreshWorker()
{
#if HC_PLATFORM == HC_PLATFORM_GDK
    if (m_appStateChangedToken)
    {
        UnregisterAppStateChangeNotification(m_appStateChangedToken);
    }

    if (m_networkConnectivityChangedToken.token)
    {
        XNetworkingUnregisterConnectivityHintChanged(m_networkConnectivityChangedToken, true);
    }
#endif
}

SharedPtr<TokenRefreshWorker> TokenRefreshWorker::MakeAndStart(SharedPtr<Entity> const& entity, RunContext&& rc, TokenExpiredHandler tokenExpiredHandler)
{
    Allocator<TokenRefreshWorker> a;
    SharedPtr<TokenRefreshWorker> worker{ new (a.allocate(1)) TokenRefreshWorker{ entity, std::move(rc), std::move(tokenExpiredHandler) } };

    worker->m_rc.TaskQueueSubmitWork(worker);
    return worker;
}

void TokenRefreshWorker::Run()
{
    SharedPtr<Entity> entity{ m_weakEntity.lock() };
    if (entity)
    {
        CheckAndRefreshToken(std::move(entity));

        // Reschedule ourselves.
        // Note that with this implementation the TokenExpiredHandler will be invoked every s_interval until the token is restored.
        // This may be fine, but we could include some additional logic to avoid that if desired.
        m_rc.TaskQueueSubmitWork(shared_from_this(), s_interval);
    }
}

void TokenRefreshWorker::CheckAndRefreshToken(SharedPtr<Entity> entity) noexcept
{
    entity->GetEntityToken(false, m_rc.Derive()).Finally(
        [
            self{ shared_from_this() },
            entity
        ]
    (Result<EntityToken> getTokenResult) mutable
    {
        if (FAILED(getTokenResult.hr))
        {
            // If we are able to get an entity token for the Entity, invoke the TokenExpired handler.
            TRACE_INFORMATION("TokenRefreshWorker unable to get EntityToken (hr = 0x%08x)");

            self->m_tokenExpiredHandler.Invoke(entity->EntityKey().Model().id);
        }
        else if (CheckRefreshRequired(getTokenResult.Payload()))
        {
            Authentication::AuthenticationAPI::GetEntityToken(entity, Authentication::GetEntityTokenRequest{}, self->m_rc.Derive()).Finally(
                [
                    self,
                    entity
                ]
            (Result<Authentication::GetEntityTokenResponse> result)
            {
                if (FAILED(result.hr))
                {
                    self->m_tokenExpiredHandler.Invoke(entity->EntityKey().Model().id);
                }
                else
                {
                    HRESULT hr = entity->SetEntityToken(result.Payload());
                    assert(SUCCEEDED(hr));

                    TRACE_ERROR_HR(hr, "Entity::SetEntityToken failed unexpectedly");
                }
            });
        }
    });
}

bool TokenRefreshWorker::CheckRefreshRequired(EntityToken const& token) noexcept
{
    // This was just a first crack at a refresh heuristic. We may want to refine this and sync with the
    // service team about recommended refresh policy.
    time_t const* expiration{ token.expiration };
    if (expiration && (int64_t)(expiration - time(nullptr)) < 60 * 60)
    {
        return true;
    }
    return false;
}

#if HC_PLATFORM == HC_PLATFORM_GDK

void TokenRefreshWorker::NetworkConnectivityChangedCallback(void* context, const XNetworkingConnectivityHint* /*hint*/)
{
    assert(context);
    auto worker = static_cast<TokenRefreshWorker*>(context);

    std::unique_lock<std::mutex> lock{ worker->m_mutex };

    // Ignore network connectivity changes if we are suspended
    if (!worker->m_isSuspended)
    {
        // Always requery the latest network connectivity hint rather than relying on the passed parameter in case this is a stale notification
        XNetworkingConnectivityHint hint{};
        HRESULT hr = XNetworkingGetConnectivityHint(&hint);
        if (SUCCEEDED(hr))
        {
            TRACE_VERBOSE("NetworkConnectivityChangedCallback, hint.networkInitialized=%d", hint.networkInitialized);
            if (hint.networkInitialized && worker->m_resumeTokenCheckPending)
            {
                worker->m_resumeTokenCheckPending = false;
                lock.unlock();

                SharedPtr<Entity> entity{ worker->m_weakEntity.lock() };
                if (entity)
                {
                    worker->CheckAndRefreshToken(std::move(entity));
                }
            }
        }
        else
        {
            TRACE_ERROR_HR(hr, "Unable to get NetworkConnectivityHint");
        }
    }
}

void CALLBACK TokenRefreshWorker::AppStateChangedCallback(BOOLEAN isSuspended, void* context)
{
    assert(context);
    auto worker = static_cast<TokenRefreshWorker*>(context);

    std::unique_lock<std::mutex> lock{ worker->m_mutex };

    if (isSuspended)
    {
        worker->m_isSuspended = true;
        worker->m_resumeTokenCheckPending = true;
    }
    else
    {
        assert(worker->m_isSuspended);
        worker->m_isSuspended = false;

        lock.unlock();

        // Force a query of network state since we've ignored notifications during suspend. The EntityToken will
        // also be checked and refresh if needed here
        NetworkConnectivityChangedCallback(worker, nullptr);
    }
}
#endif

Result<SharedPtr<Entity>> Entity::Make(
    Authentication::EntityTokenResponse&& entityTokenResponse,
    SharedPtr<PlayFab::ServiceConfig const> serviceConfig,
    RunContext&& tokenRefreshContext,
    TokenExpiredHandler tokenExpiredHandler
) noexcept
{
    Allocator<Entity> a{};
    SharedPtr<Entity> entity{
        new (a.allocate(1)) Entity{
            std::move(entityTokenResponse),
            serviceConfig,
            tokenRefreshContext.Derive(),
            tokenExpiredHandler
        }, Deleter<Entity>()
    };

    entity->StartTokenRefreshWorker();

    return entity;
}

Entity::Entity(
    Authentication::EntityTokenResponse&& response,
    SharedPtr<PlayFab::ServiceConfig const> serviceConfig,
    RunContext&& tokenRefreshContext,
    TokenExpiredHandler tokenExpiredHandler
) noexcept :
    m_key{ *response.entity },
    m_entityToken{ response },
    m_serviceConfig{ std::move(serviceConfig) },
    m_runContext{ std::move(tokenRefreshContext) },
    m_tokenExpiredHandler{ std::move(tokenExpiredHandler) }
{
}

SharedPtr<PlayFab::ServiceConfig const> Entity::ServiceConfig() const
{
    return m_serviceConfig;
}

PlayFab::EntityKey const& Entity::EntityKey() const
{
    return m_key;
}

AsyncOp<EntityToken> Entity::GetEntityToken(bool forceRefresh, RunContext runContext)
{
    std::unique_lock<std::mutex> lock{ m_mutex };

    if (forceRefresh) // Is there a need for forceRefresh?
    {
        SharedPtr<Entity> self{ shared_from_this() };
        return Authentication::AuthenticationAPI::GetEntityToken(self, Authentication::GetEntityTokenRequest{}, std::move(runContext)).Then([self](Result<Authentication::GetEntityTokenResponse> result) -> Result<EntityToken>
        {
            RETURN_IF_FAILED(result.hr);

            std::unique_lock<std::mutex> lock{ self->m_mutex };
            auto& response{ result.Payload() };

            assert(response.entity.has_value());
            assert(!std::strcmp(response.entity->Model().id, self->m_key.Model().id));

            self->m_entityToken = EntityToken{ response };

            return EntityToken{ response };
        });
    }
    else if (m_entityToken.expiration && *m_entityToken.expiration < GetTimeTNow())
    {
        return E_PF_NOENTITYTOKEN;
    }
    else
    {
        return Result<EntityToken>{ EntityToken{ m_entityToken } };
    }
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

HRESULT Entity::SetEntityToken(Authentication::GetEntityTokenResponse const& entityTokenResponse)
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

void Entity::StartTokenRefreshWorker() noexcept
{
    TokenRefreshWorker::MakeAndStart(shared_from_this(), m_runContext.Derive(), m_tokenExpiredHandler);
}

EntityToken::EntityToken(const Authentication::EntityTokenResponse& tokenResponse) :
    PFEntityToken{},
    m_token{ tokenResponse.entityToken },
    m_expiration{ tokenResponse.tokenExpiration }
{
    token = m_token.empty() ? nullptr : m_token.data();
    expiration = m_expiration ? m_expiration.operator->() : nullptr;
}

EntityToken::EntityToken(const Authentication::GetEntityTokenResponse& tokenResponse) :
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
    m_token{ std::move(src.m_token) },
    m_expiration{ src.m_expiration }
{
    token = m_token.empty() ? nullptr : m_token.data();
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
