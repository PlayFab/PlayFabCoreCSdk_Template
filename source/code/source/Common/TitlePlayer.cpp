#include "stdafx.h"
#include "TitlePlayer.h"
#include "JsonUtils.h"

namespace PlayFab
{

using namespace Authentication;

Result<SharedPtr<TitlePlayer>> TitlePlayer::Make(
    SharedPtr<PlayFab::HttpClient const> httpClient,
    TaskQueue backgroundQueue,
    Authentication::AuthenticateIdentityResult&& authResult
)
{
    Allocator<TitlePlayer> a{};
    SharedPtr<TitlePlayer> titlePlayer{ new (a.allocate(1)) TitlePlayer{ std::move(httpClient), std::move(backgroundQueue), std::move(authResult) }, Deleter<TitlePlayer>() };

    return titlePlayer;
}

TitlePlayer::TitlePlayer(SharedPtr<PlayFab::HttpClient const> httpClient, TaskQueue backgroundQueue, Authentication::AuthenticateIdentityResult&& authResult)
    : Entity{ httpClient, std::move(*authResult.titlePlayerAccount) },
    m_backgroundQueue{ std::move(backgroundQueue) },
    m_linkedMasterPlayer{ MakeShared<Entity>(httpClient, std::move(*authResult.masterPlayerAccount)) }
{
}

SharedPtr<Entity> TitlePlayer::LinkedMasterPlayer() const
{
    return m_linkedMasterPlayer;
}

}
