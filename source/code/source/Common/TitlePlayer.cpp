#include "stdafx.h"
#include "TitlePlayer.h"
#include "JsonUtils.h"

namespace PlayFab
{

using namespace Authentication;

TitlePlayer::TitlePlayer(SharedPtr<PlayFab::HttpClient const> httpClient, SharedPtr<QoS::QoSAPI const> qosAPI, SharedPtr<LoginContext const> loginContext, LoginResult&& result)
    : Entity{ std::move(httpClient), std::move(qosAPI), std::move(*result.entityToken) },
    m_loginContext{ std::move(loginContext) },
    m_playFabId{ std::move(result.playFabId) },
    m_sessionTicket{ MakeShared<String>(result.sessionTicket) },
    m_playerCombinedInfo{ std::move(result.infoResultPayload) },
    m_lastLoginTime{ std::move(result.lastLoginTime) },
    m_userSettings{ std::move(result.settingsForUser) },
    m_treatmentAssignment{ std::move(result.treatmentAssignment) }
{
}

TitlePlayer::TitlePlayer(SharedPtr<PlayFab::HttpClient const> httpClient, SharedPtr<QoS::QoSAPI const> qosAPI, SharedPtr<LoginContext const> loginContext, ServerLoginResult&& result)
    : Entity{ std::move(httpClient), std::move(qosAPI), std::move(*result.entityToken) },
    m_loginContext{ std::move(loginContext) },
    m_playFabId{ std::move(result.playFabId) },
    m_sessionTicket{ MakeShared<String>(result.sessionTicket) },
    m_playerCombinedInfo{ std::move(result.infoResultPayload) },
    m_lastLoginTime{ std::move(result.lastLoginTime) },
    m_userSettings{ std::move(result.settingsForUser) },
    m_treatmentAssignment{ std::move(result.treatmentAssignment) }
{
}

TitlePlayer::TitlePlayer(SharedPtr<PlayFab::HttpClient const> httpClient, SharedPtr<QoS::QoSAPI const> qosAPI, SharedPtr<LoginContext const> loginContext, RegisterPlayFabUserResult&& result)
    : Entity{ std::move(httpClient), std::move(qosAPI), std::move(*result.entityToken) },
    m_loginContext{ std::move(loginContext) },
    m_playFabId{ std::move(result.playFabId) },
    m_sessionTicket{ MakeShared<String>(result.sessionTicket) },
    m_userSettings{ std::move(result.settingsForUser) }
{
}

AsyncOp<void> TitlePlayer::RefreshToken(const TaskQueue& queue)
{
    SharedPtr<Entity> sharedThis{ shared_from_this() };

    return m_loginContext->GetRequestBody(queue.DeriveWorkerQueue()).Then([sharedThis, this, queue = TaskQueue{ queue }](Result<JsonValue> requestBodyResult)->AsyncOp<ServiceResponse>
    {
        RETURN_IF_FAILED(requestBodyResult.hr);

        return HttpClient()->MakePostRequest(
            m_loginContext->RequestPath(),
            m_loginContext->RequestHeaders(),
            requestBodyResult.Payload(),
            queue
        );

    }).Then([sharedThis, this](Result<ServiceResponse> result)->Result<void>
    {
        RETURN_IF_FAILED(result.hr);

        auto serviceResponse = result.ExtractPayload();
        if (serviceResponse.HttpCode == 200)
        {
            LoginResult loginResult;
            loginResult.FromJson(serviceResponse.Data);

            // Update EntityToken and SessionTicket
            if (loginResult.entityToken)
            {
                m_entityToken = MakeShared<PlayFab::EntityToken>(*loginResult.entityToken);
                TokenRefreshedCallbacks.Invoke(m_entityToken);
            }
            else
            {
                TRACE_ERROR("EntityToken unexpectedly missing from Login response");
                return E_FAIL;
            }

            m_sessionTicket = MakeShared<String>(loginResult.sessionTicket);
        }
        else
        {
            return Result<void>{ ServiceErrorToHR(serviceResponse.ErrorCode), std::move(serviceResponse.ErrorMessage) };
        }
        return S_OK;
    });
}

String const& TitlePlayer::PlayFabId() const
{
    return m_playFabId;
}

SharedPtr<String const> TitlePlayer::SessionTicket() const
{
    return m_sessionTicket;
}

StdExtra::optional<GetPlayerCombinedInfoResultPayload> const& TitlePlayer::PlayerCombinedInfo() const
{
    return m_playerCombinedInfo;
}

StdExtra::optional<time_t const> const& TitlePlayer::LastLoginTime() const
{
    return m_lastLoginTime;
}

StdExtra::optional<UserSettings const> const& TitlePlayer::UserSettings() const
{
    return m_userSettings;
}

StdExtra::optional<TreatmentAssignment> const& TitlePlayer::TreatmentAssignment() const
{
    return m_treatmentAssignment;
}

LoginContext::LoginContext(const char* requestPath)
    : m_path{ requestPath }
{
}

LoginContext::LoginContext(const char* requestPath, JsonValue&& requestBody)
    : m_path{ requestPath },
    m_requestBody{ std::move(requestBody) }
{
}

LoginContext::LoginContext(const char* requestPath, JsonValue&& requestBody, UnorderedMap<String, String> requestHeaders)
    : m_path{ requestPath },
    m_requestBody{ std::move(requestBody) },
    m_requestHeaders{ std::move(requestHeaders) }
{
}

const char* LoginContext::RequestPath() const
{
    return m_path.data();
}

AsyncOp<JsonValue> LoginContext::GetRequestBody(const TaskQueue& queue) const
{
    UNREFERENCED_PARAMETER(queue); // No async work to be done in base LoginContext
    JsonValue requestBodyCopy;
    JsonUtils::FromJson(m_requestBody, requestBodyCopy);
    return Result<JsonValue>{ std::move(requestBodyCopy) };
}

const UnorderedMap<String, String>& LoginContext::RequestHeaders() const
{
    return m_requestHeaders;
}

}