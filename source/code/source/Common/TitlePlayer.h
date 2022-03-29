#pragma once

#include "Entity.h"

namespace PlayFab
{

// TitlePlayer Entity returned from an Authentication API
class TitlePlayer : public Entity
{
public:
    static Result<SharedPtr<TitlePlayer>> Make(
        SharedPtr<PlayFab::HttpClient const> httpClient,
        RunContext&& tokenRefreshContext,
        Authentication::AuthenticateIdentityResult&& authResult
    ); 

    TitlePlayer(const TitlePlayer&) = delete;
    TitlePlayer& operator=(const TitlePlayer&) = delete;
    ~TitlePlayer() = default;

public:
    SharedPtr<Entity> LinkedMasterPlayer() const;

private:
    TitlePlayer(SharedPtr<PlayFab::HttpClient const> httpClient, RunContext&& tokenRefreshContext, Authentication::AuthenticateIdentityResult&& authResult);

    SharedPtr<Entity> m_linkedMasterPlayer;
};

}
