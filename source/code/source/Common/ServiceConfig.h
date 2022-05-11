// Configuration of a PlayFab Service connection

#pragma once

#include "HttpClient.h"

namespace PlayFab
{

class ServiceConfig
{
public:
    ServiceConfig(String&& connectionString, String&& titleId, String&& playerAccountPoolId);

    SharedPtr<HttpClient const> HttpClient() const noexcept;
    String const& TitleId() const noexcept;
    String const& PlayerAccountPoolId() const noexcept;

private:
    SharedPtr<PlayFab::HttpClient> m_httpClient;
    String const m_titleId;
    String const m_playerAccountPoolId;
};

}
