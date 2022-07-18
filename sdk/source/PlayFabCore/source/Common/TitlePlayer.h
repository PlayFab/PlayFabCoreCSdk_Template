#pragma once

#include "Entity.h"

namespace PlayFab
{

class TitlePlayer : public Entity
{
public:
    static Result<SharedPtr<TitlePlayer>> Make(
        Authentication::AuthenticateIdentityResult&& authResult,
        SharedPtr<PlayFab::ServiceConfig const> serviceConfig,
        RunContext tokenRefreshContext,
        TokenExpiredHandler&& tokenExpiredHandler
    ) noexcept; 

    TitlePlayer(const TitlePlayer&) = delete;
    TitlePlayer& operator=(const TitlePlayer&) = delete;
    ~TitlePlayer() = default;

public:
    SharedPtr<Entity> LinkedMasterPlayer() const;

private:
    TitlePlayer(
        Authentication::AuthenticateIdentityResult&& authResult,
        SharedPtr<PlayFab::ServiceConfig const> serviceConfig,
        RunContext tokenRefreshContext,
        TokenExpiredHandler&& tokenExpiredHandler
    ) noexcept;

    SharedPtr<Entity> m_linkedMasterPlayer;
};

}
