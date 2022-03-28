#include "stdafx.h"
#include "TitlePlayer.h"
#include "JsonUtils.h"

namespace PlayFab
{

using namespace Authentication;

Result<SharedPtr<TitlePlayer>> TitlePlayer::Make(
    SharedPtr<PlayFab::HttpClient const> httpClient,
    RunContext&& tokenRefreshContext,
    Authentication::AuthenticateIdentityResult&& authResult
)
{
    Allocator<TitlePlayer> a{};
    SharedPtr<TitlePlayer> titlePlayer{ new (a.allocate(1)) TitlePlayer{ std::move(httpClient), std::move(tokenRefreshContext), std::move(authResult) }, Deleter<TitlePlayer>() };

    return titlePlayer;
}

TitlePlayer::TitlePlayer(SharedPtr<PlayFab::HttpClient const> httpClient, RunContext&& tokenRefreshContext, Authentication::AuthenticateIdentityResult&& authResult)
    : Entity{ httpClient, std::move(*authResult.titlePlayerAccount) },
    m_tokenRefreshContext{ std::move(tokenRefreshContext) },
    m_linkedMasterPlayer{ MakeShared<Entity>(httpClient, std::move(*authResult.masterPlayerAccount)) }
{
}

SharedPtr<Entity> TitlePlayer::LinkedMasterPlayer() const
{
    return m_linkedMasterPlayer;
}

}
