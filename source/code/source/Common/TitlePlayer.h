#pragma once

#include "Entity.h"

namespace PlayFab
{

using TokenExpiredCallback = std::function<void(SharedPtr<class TitlePlayer>)>;

// TitlePlayer Entity returned from an Authentication API
class TitlePlayer : public Entity
{
public:
    static Result<SharedPtr<TitlePlayer>> Make(
        SharedPtr<PlayFab::HttpClient const> httpClient,
        TaskQueue backgroundQueue,
        Authentication::AuthenticateIdentityResult&& authResult
    ); 

    TitlePlayer(const TitlePlayer&) = delete;
    TitlePlayer& operator=(const TitlePlayer&) = delete;
    ~TitlePlayer() = default;

public:
    SharedPtr<Entity> LinkedMasterPlayer() const;

private:
    TitlePlayer(SharedPtr<PlayFab::HttpClient const> httpClient, TaskQueue backgroundQueue, Authentication::AuthenticateIdentityResult&& authResult);

    TaskQueue m_backgroundQueue;
    SharedPtr<Entity> m_linkedMasterPlayer;
};

}

struct PFTitlePlayer
{
    PFTitlePlayer(PlayFab::SharedPtr<PlayFab::TitlePlayer> titlePlayer_) : titlePlayer{ titlePlayer_ } {}
    PFTitlePlayer(const PFTitlePlayer&) = default;
    ~PFTitlePlayer() = default;

    PlayFab::SharedPtr<PlayFab::TitlePlayer> titlePlayer;
};
