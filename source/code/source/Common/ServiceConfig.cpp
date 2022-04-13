#include "stdafx.h"
#include "ServiceConfig.h"

namespace PlayFab
{

ServiceConfig::ServiceConfig(String&& connectionString, String&& titleId, String&& playerAccountPoolId)
    : m_httpClient{ MakeShared<PlayFab::HttpClient>(std::move(connectionString)) },
    m_titleId{ std::move(titleId) },
    m_playerAccountPoolId{ std::move(playerAccountPoolId) }
{
}

SharedPtr<HttpClient const> ServiceConfig::HttpClient() const noexcept
{
    return m_httpClient;
}

String const& ServiceConfig::TitleId() const noexcept
{
    return m_titleId;
}

String const& ServiceConfig::PlayerAccountPoolId() const noexcept
{
    return m_playerAccountPoolId;
}

}
