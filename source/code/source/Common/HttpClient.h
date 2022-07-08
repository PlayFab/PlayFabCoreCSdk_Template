#pragma once

#include <httpClient/httpClient.h>
#include <HttpRequest.h>

namespace PlayFab
{
class Entity;

// An Http client for make PlayFab service requests
class HttpClient
{
public:
    HttpClient(String&& connectionString);
    HttpClient(const HttpClient&) = default;
    ~HttpClient() = default;

    AsyncOp<ServiceResponse> MakePostRequest(
        const char* path,
        UnorderedMap<String, String>&& headers,
        const JsonValue& requestBody,
        RunContext&& runContext
    ) const;

    AsyncOp<ServiceResponse> MakeEntityRequest(
        SharedPtr<Entity> entity,
        const char* path,
        UnorderedMap<String, String>&& headers,
        const JsonValue& requestBody,
        RunContext&& runContext
    ) const;

    String const& ConnectionString() const noexcept;

private:
    String GetUrl(const char* path) const;

    String const m_connectionString;
};

}
