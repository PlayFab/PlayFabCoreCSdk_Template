#pragma once

#include <httpClient/httpClient.h>
#include "TaskQueue.h"
#include "AsyncOp.h"
#include "RunContext.h"

namespace PlayFab
{
class Entity;

struct ServiceResponse;

// An Http client for make PlayFab service requests
class HttpClient
{
public:
    HttpClient(String&& connectionString);
    HttpClient(const HttpClient&) = default;
    ~HttpClient() = default;

    AsyncOp<ServiceResponse> MakePostRequest(
        const char* path,
        const UnorderedMap<String, String>& headers,
        const JsonValue& requestBody,
        RunContext&& runContext
    ) const;

    AsyncOp<ServiceResponse> MakeEntityRequest(
        SharedPtr<Entity> entity,
        const char* path,
        UnorderedMap<String, String>&& headers,
        JsonValue&& requestBody,
        RunContext&& runContext
    ) const;

    String const& ConnectionString() const noexcept;

private:
    String GetUrl(const char* path) const;

    String m_titleId;
    String m_connectionString;
};

// Wrapper around PlayFab service response.
// See https://docs.microsoft.com/en-us/rest/api/playfab/client/authentication/loginwithcustomid?view=playfab-rest#apierrorwrapper for
// more information.
struct ServiceResponse
{
    ServiceResponse() = default;
    ServiceResponse(const ServiceResponse&);
    ServiceResponse(ServiceResponse&&) = default;
    ServiceResponse& operator=(const ServiceResponse&);
    ServiceResponse& operator=(ServiceResponse&&) = default;
    ~ServiceResponse() = default;

    void FromJson(const JsonValue& input);

    // Fields from response body
    int HttpCode;
    String HttpStatus;
    ServiceErrorCode ErrorCode;
    String ErrorName;
    String ErrorMessage;
    JsonValue ErrorDetails;
    JsonValue Data;

    // From response header
    String RequestId;
};

}
