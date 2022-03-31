#include "stdafx.h"
#include "TitlePlayer.h"
#include "JsonUtils.h"

namespace PlayFab
{

using namespace Authentication;

Result<SharedPtr<TitlePlayer>> TitlePlayer::Make(
    Authentication::AuthenticateIdentityResult&& authResult,
    SharedPtr<PlayFab::HttpClient const> httpClient,
    RunContext&& tokenRefreshContext
) noexcept
{
    Allocator<TitlePlayer> a{};
    SharedPtr<TitlePlayer> titlePlayer{ new (a.allocate(1)) TitlePlayer{ std::move(authResult), std::move(httpClient), std::move(tokenRefreshContext)  }, Deleter<TitlePlayer>() };

    RETURN_IF_FAILED(Entity::StartTokenRefreshPulseForEntity(titlePlayer));

    return titlePlayer;
}

TitlePlayer::TitlePlayer(Authentication::AuthenticateIdentityResult&& authResult, SharedPtr<PlayFab::HttpClient const> httpClient, RunContext&& tokenRefreshContext)
    : Entity{ std::move(*authResult.titlePlayerAccount), httpClient, tokenRefreshContext.Derive() } 
{
    // TODO
    //m_linkedMasterPlayer = SharedPtr<Entity>{ new (Allocator<Entity>{}.allocate(1)) Entity{ std::move(*authResult.masterPlayerAccount), httpClient, tokenRefreshContext.Derive() } };
}

SharedPtr<Entity> TitlePlayer::LinkedMasterPlayer() const
{
    return m_linkedMasterPlayer;
}

}
