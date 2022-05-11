#include "stdafx.h"
#include "TitlePlayer.h"
#include "JsonUtils.h"

namespace PlayFab
{

using namespace Authentication;

Result<SharedPtr<TitlePlayer>> TitlePlayer::Make(
    Authentication::AuthenticateIdentityResult&& authResult,
    SharedPtr<PlayFab::ServiceConfig const> serviceConfig,
    RunContext tokenRefreshContext,
    TokenExpiredHandler&& tokenExpiredHandler
) noexcept
{
    Allocator<TitlePlayer> a{};
    SharedPtr<TitlePlayer> titlePlayer{ 
        new (a.allocate(1)) TitlePlayer{ 
            std::move(authResult),
            std::move(serviceConfig),
            tokenRefreshContext,
            std::move(tokenExpiredHandler)  
        }, Deleter<TitlePlayer>() 
    };

    titlePlayer->StartTokenRefreshWorker();

    return titlePlayer;
}

TitlePlayer::TitlePlayer(
    Authentication::AuthenticateIdentityResult&& authResult,
    SharedPtr<PlayFab::ServiceConfig const> serviceConfig,
    RunContext tokenRefreshContext,
    TokenExpiredHandler&& tokenExpiredHandler
) noexcept :
    Entity{ std::move(*authResult.titlePlayerAccount), serviceConfig, tokenRefreshContext.Derive(), tokenExpiredHandler }
{
    m_linkedMasterPlayer = Entity::Make(std::move(*authResult.masterPlayerAccount), serviceConfig, tokenRefreshContext.Derive(), tokenExpiredHandler).ExtractPayload();
}

SharedPtr<Entity> TitlePlayer::LinkedMasterPlayer() const
{
    return m_linkedMasterPlayer;
}

}
