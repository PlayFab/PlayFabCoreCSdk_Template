#include "stdafx.h"
#include "HttpClient.h"
#include "Entity.h"
#include "TitlePlayer.h"
#include "SdkVersion.h"
#include "JsonUtils.h"

namespace PlayFab
{

constexpr char kEntityTokenHeaderName[]{ "X-EntityToken" };
constexpr char kPostMethod[]{ "POST" };

HttpClient::HttpClient(String&& connectionString) :
    m_connectionString{ std::move(connectionString) }
{
}

String HttpClient::GetUrl(const char* path) const
{
    Stringstream fullUrl;
    fullUrl << m_connectionString;

    // Append path
    fullUrl << path;

    // Add sdk version param (used by service for telemetry)
    fullUrl << "?sdk=" << versionString;

    return fullUrl.str();
}

AsyncOp<ServiceResponse> HttpClient::MakePostRequest(
    const char* path,
    UnorderedMap<String, String>&& headers,
    const JsonValue& requestBody,
    RunContext&& runContext
) const
{
    headers["X-PlayFabSDK"] = versionString;

    return XAsyncOperation<ServiceResponse>::Run(MakeUnique<HCHttpCall>(kPostMethod, GetUrl(path), std::move(headers), JsonUtils::WriteToString(requestBody), std::move(runContext)));
}

AsyncOp<ServiceResponse> HttpClient::MakeEntityRequest(
    SharedPtr<Entity> entity,
    const char* path,
    UnorderedMap<String, String>&& headers,
    const JsonValue& requestBody,
    RunContext&& runContext
) const
{
    headers["X-PlayFabSDK"] = versionString;
    auto httpRequest = MakeUnique<HCHttpCall>(kPostMethod, GetUrl(path), std::move(headers), JsonUtils::WriteToString(requestBody), runContext);

    return entity->GetEntityToken(false, runContext.Derive()).Then(
        [
            httpRequest{ std::move(httpRequest) }
        ]
    (Result<EntityToken> result) mutable -> AsyncOp<ServiceResponse>
    {
        RETURN_IF_FAILED(result.hr);
        httpRequest->SetHeader(kEntityTokenHeaderName, result.ExtractPayload().token);
        return XAsyncOperation<ServiceResponse>::Run(std::move(httpRequest));
    });
}

String const& HttpClient::ConnectionString() const noexcept
{
    return m_connectionString;
}

}
