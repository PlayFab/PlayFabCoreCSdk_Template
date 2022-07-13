#pragma once

#include <playfab/PFEntity.h>
#include "ServiceConfig.h"
#include "Authentication/AuthenticationTypes.h"
#include "TokenExpiredHandler.h"

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
    EntityToken& operator=(const EntityToken& src);
    EntityToken& operator=(EntityToken&& src);
    ~EntityToken() = default;

    size_t RequiredBufferSize() const;
    Result<PFEntityToken const*> Copy(ModelBuffer& buffer) const;

private:
    String m_token;
    StdExtra::optional<time_t> m_expiration;
};

// An entity authenticated with PlayFab. An entity has a type, an ID, and an EntityToken. For more detail on PlayFab entities see the service
// documentation here: https://docs.microsoft.com/en-us/gaming/playfab/features/data/entities/quickstart.
class Entity : public std::enable_shared_from_this<Entity>
{
public:
    static Result<SharedPtr<Entity>> Make(
        Authentication::EntityTokenResponse&& entityTokenResponse,
        SharedPtr<PlayFab::ServiceConfig const> serviceConfig,
        RunContext&& tokenRefreshContext,
        TokenExpiredHandler tokenExpiredHandler
    ) noexcept;

    Entity(const Entity&) = delete;
    Entity(Entity&&) = delete;
    Entity& operator=(const Entity&) = delete;
    Entity& operator=(Entity&&) = delete;
    ~Entity() noexcept;

public:
    SharedPtr<ServiceConfig const> ServiceConfig() const;
    EntityKey const& EntityKey() const;
    AsyncOp<EntityToken> GetEntityToken(bool forceRefresh, RunContext runContext);

    HRESULT SetEntityToken(Authentication::EntityTokenResponse const& entityTokenResponse);

    // Temporary stub for testing. This will eventually be replaced with auto generated service wrapper when that API is available.
    static AsyncOp<Authentication::EntityTokenResponse> RefreshToken(SharedPtr<Entity> entity, RunContext&& runContext);

protected:
    Entity(
        Authentication::EntityTokenResponse&& entityTokenResponse,
        SharedPtr<PlayFab::ServiceConfig const> serviceConfig,
        RunContext&& tokenRefreshContext,
        TokenExpiredHandler tokenExpiredHandler
    ) noexcept;

    // Token refresh pulse must be started outside of constructor so we can use a weak_ptr in the callback context.
    void StartTokenRefreshWorker() noexcept;

private:
    std::mutex m_mutex;
    PlayFab::EntityKey const m_key;
    PlayFab::EntityToken m_entityToken;
    SharedPtr<PlayFab::ServiceConfig const> m_serviceConfig;
    RunContext m_runContext;
    TokenExpiredHandler m_tokenExpiredHandler;
};

}
