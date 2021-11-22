#pragma once

#include <playfab/PFEntity.h>
#include "CallbackManager.h"
#include "HttpClient.h"
#include "Authentication/AuthenticationDataModels.h"

namespace PlayFab
{

namespace QoS
{
class QoSAPI;
}

class EntityToken : public PFEntityToken
{
public:
    EntityToken(const Authentication::EntityTokenResponse& tokenResponse);
    EntityToken(const Authentication::GetEntityTokenResponse& tokenResponse);
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
class Entity : public std::enable_shared_from_this<Entity>
{
public:
    Entity(SharedPtr<PlayFab::HttpClient const> httpClient, SharedPtr<QoS::QoSAPI const> qosAPI, Authentication::EntityTokenResponse&& entityTokenResponse);
    Entity(SharedPtr<PlayFab::HttpClient const> httpClient, SharedPtr<QoS::QoSAPI const> qosAPI, Authentication::GetEntityTokenResponse&& entityTokenResponse);

    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;
    ~Entity() = default;

public:
    EntityKey const& EntityKey() const;
    SharedPtr<PlayFab::EntityToken const> EntityToken() const;

    // Shared HttpClient
    SharedPtr<HttpClient const> HttpClient() const;

    // Shared QoS API
    SharedPtr<QoS::QoSAPI const> QoSAPI() const;

    // Refreshes the cached Entity token.
    virtual AsyncOp<void> RefreshToken(const TaskQueue& queue);

    // Non-generated implementation for /Authentication/GetEntityToken API call. When GetEntityToken is called by an existing Entity, the service
    // call will be authenticated with the EntityToken. If the Entity Token requested if for the calling Entity (aka just refreshing our token),
    // our cached token will be updated and a SharedPtr to 'this' will be returned. If the token requested is for another entity, a new Entity
    // object will be created and returned.
    AsyncOp<SharedPtr<Entity>> GetEntityToken(const Authentication::GetEntityTokenRequest& request, const TaskQueue& queue);

    // TokenRefreshedCallbacks exist to support PlayFab Party & PlayFab Lobby interfaces which require titles to provide and manually update a raw 
    // entity token. Whenever the Entity token is silently refreshed these callbacks will be invoked.
    using TokenRefreshedCallback = std::function<void(SharedPtr<PlayFab::EntityToken const>)>;

    CallbackManager<TokenRefreshedCallback> TokenRefreshedCallbacks;

private:
    SharedPtr<PlayFab::HttpClient const> m_httpClient;
    SharedPtr<QoS::QoSAPI const> m_qosAPI;

protected:
    SharedPtr<PlayFab::EntityToken> m_entityToken;

private:
    // Entity attributes
    PlayFab::EntityKey const m_key;
};

}

struct PFEntity
{
    PFEntity(PlayFab::SharedPtr<PlayFab::Entity> entity_) : entity{ entity_ } {}
    PFEntity(const PFEntity&) = default;
    ~PFEntity() = default;

    PlayFab::SharedPtr<PlayFab::Entity> entity;
};
