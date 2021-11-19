#pragma once

#include "Entity.h"

namespace PlayFab
{

// Context needed to re-login after auth tokens expire.
// By default, the original auth request will just replayed without modification. For behavior specific to a particular login method, derive
// from this class and override methods as necessary.
class LoginContext
{
public:
    LoginContext(const char* requestPath);
    LoginContext(const char* requestPath, JsonValue&& requestBody);
    LoginContext(const char* requestPath, JsonValue&& requestBody, UnorderedMap<String, String> requestHeaders);

    virtual const char* RequestPath() const;
    virtual AsyncOp<JsonValue> GetRequestBody(const TaskQueue& queue) const;
    virtual const UnorderedMap<String, String>& RequestHeaders() const;

private:
    String m_path;
    JsonValue m_requestBody;
    UnorderedMap<String, String> m_requestHeaders;
};

// TitlePlayer Entity returned from a Login API
class TitlePlayer : public Entity
{
public:
    TitlePlayer(SharedPtr<PlayFab::HttpClient const> httpClient, SharedPtr<QoS::QoSAPI const> qosAPI, SharedPtr<LoginContext const> loginContext, Authentication::LoginResult&& loginResult);
    TitlePlayer(SharedPtr<PlayFab::HttpClient const> httpClient, SharedPtr<QoS::QoSAPI const> qosAPI, SharedPtr<LoginContext const> loginContext, Authentication::ServerLoginResult&& loginResult);
    TitlePlayer(SharedPtr<PlayFab::HttpClient const> httpClient, SharedPtr<QoS::QoSAPI const> qosAPI, SharedPtr<LoginContext const> loginContext, Authentication::RegisterPlayFabUserResult&& registerResult);

    TitlePlayer(const TitlePlayer&) = delete;
    TitlePlayer& operator=(const TitlePlayer&) = delete;
    ~TitlePlayer() = default;

public:
    // Master_Player_Entity Id associated with this TitlePlayer
    String const& PlayFabId() const;

    // Client SessionTicket for "Classic" PlayFab APIs
    SharedPtr<String const> SessionTicket() const;

    // Getter methods to retreive TitlePlayer properties. All data only guaranteed to be accurate at the time of most recent login. 
    StdExtra::optional<GetPlayerCombinedInfoResultPayload> const& PlayerCombinedInfo() const;
    StdExtra::optional<time_t const> const& LastLoginTime() const;
    StdExtra::optional<Authentication::UserSettings const> const& UserSettings() const;
    StdExtra::optional<TreatmentAssignment> const& TreatmentAssignment() const;

    // Refresh the cached Entity token by replaying login request
    AsyncOp<void> RefreshToken(const TaskQueue& queue) override;

private:
    SharedPtr<LoginContext const> m_loginContext;

    String const m_playFabId;
    SharedPtr<String> m_sessionTicket;

    StdExtra::optional<GetPlayerCombinedInfoResultPayload> m_playerCombinedInfo;
    StdExtra::optional<time_t const> m_lastLoginTime;
    StdExtra::optional<Authentication::UserSettings const> m_userSettings;
    StdExtra::optional<PlayFab::TreatmentAssignment> m_treatmentAssignment;
};

}

struct PFTitlePlayer
{
    PFTitlePlayer(PlayFab::SharedPtr<PlayFab::TitlePlayer> titlePlayer_) : titlePlayer{ titlePlayer_ } {}
    PFTitlePlayer(const PFTitlePlayer&) = default;
    ~PFTitlePlayer() = default;

    PlayFab::SharedPtr<PlayFab::TitlePlayer> titlePlayer;
};
