#pragma once

#include <playfab/PFEntity.h>
#include "CallbackManager.h"
#include "HttpClient.h"
#include "Authentication/AuthenticationDataModels.h"

namespace PlayFab
{

// Is there an argument for not even exposing the expiration time? If we want to contain refresh logic entirely within the SDK
// it may be cleaner to not expose the expiration.
class EntityToken : public PFEntityToken, public ClientOutputModel<PFEntityToken>
{
public:
    EntityToken(const Authentication::EntityTokenResponse& tokenResponse);
    EntityToken(const EntityToken& src);
    EntityToken(EntityToken&& src);
    ~EntityToken() = default;

    size_t RequiredBufferSize() const;
    Result<PFEntityToken const*> Copy(ModelBuffer& buffer) const;

private:
    String m_token;
    StdExtra::optional<time_t> m_expiration;
};

// An entity authenticated with PlayFab. An entity has a type, an ID, and an EntityToken. For more detail on PlayFab entities see the service
// documentation here: https://docs.microsoft.com/en-us/gaming/playfab/features/data/entities/quickstart.
class Entity
{
public:
    Entity(const Entity&) = delete;
    Entity(Entity&&) = delete;
    Entity& operator=(const Entity&) = delete;
    Entity& operator=(Entity&&) = delete;
    ~Entity() noexcept;

public:
    // Shared HttpClient
    SharedPtr<HttpClient const> HttpClient() const;

    EntityKey const& EntityKey() const;
    AsyncOp<EntityToken> GetEntityToken(bool forceRefresh, RunContext&& runContext);

protected:
    Entity(Authentication::EntityTokenResponse&& entityTokenResponse, SharedPtr<PlayFab::HttpClient const> httpClient, RunContext&& tokenRefreshContext) noexcept;

    static HRESULT StartTokenRefreshPulseForEntity(SharedPtr<Entity> entity);

private:

    // Callback that is scheduled periodically to check Entity Token and refresh as needed.
    static void CALLBACK TokenPulseCallback(void* context, bool cancelled) noexcept;

    AsyncOp<void> RefreshToken(RunContext&& runContext);

    std::mutex m_mutex;
    PlayFab::EntityKey const m_key;
    PlayFab::EntityToken m_entityToken;
    SharedPtr<PlayFab::HttpClient const> m_httpClient;
    RunContext m_runContext;

    static uint32_t s_tokenPulseIntervalMs;
};

}
