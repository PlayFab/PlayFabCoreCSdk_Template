#pragma once

#include "Entity.h"

namespace PlayFab
{

// TitlePlayer Entity returned from an Authentication API
class TitlePlayer : public Entity
{
public:
    static Result<SharedPtr<TitlePlayer>> Make(Authentication::AuthenticateIdentityResult&& authResult, SharedPtr<PlayFab::HttpClient const> httpClient, RunContext&& tokenRefreshContext) noexcept; 

    TitlePlayer(const TitlePlayer&) = delete;
    TitlePlayer& operator=(const TitlePlayer&) = delete;
    ~TitlePlayer() = default;

public:
    SharedPtr<Entity> LinkedMasterPlayer() const;

private:
    TitlePlayer(Authentication::AuthenticateIdentityResult&& authResult, SharedPtr<PlayFab::HttpClient const> httpClient, RunContext&& tokenRefreshContext);

    SharedPtr<Entity> m_linkedMasterPlayer;
};

}
