#pragma once

#include <httpClient/httpClient.h>
#include "XAsyncOperation.h"
#include "RunContext.h"

namespace PlayFab
{

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

// Wrapper around HCHttpCallPerformAsync XAsync operation
class HCHttpCall : public XAsyncOperation<ServiceResponse>
{
public:
    HCHttpCall(
        String method,
        String url,
        UnorderedMap<String, String> headers,
        String requestBody,
        PlayFab::RunContext runContext
    ) noexcept;

    HCHttpCall(HCHttpCall const&) = delete;
    HCHttpCall& operator=(HCHttpCall) = delete;
    ~HCHttpCall() noexcept;

    void SetHeader(String headerName, String headerValue) noexcept;

private:
    // XAsyncOperation
    HRESULT OnStarted(XAsyncBlock* async) noexcept override;
    Result<ServiceResponse> GetResult(XAsyncBlock* async) noexcept override;

    static HRESULT CALLBACK HCRequestBodyRead(
        _In_ HCCallHandle callHandle,
        _In_ size_t offset,
        _In_ size_t bytesAvailable,
        _In_opt_ void* context,
        _Out_writes_bytes_to_(bytesAvailable, *bytesWritten) uint8_t* destination,
        _Out_ size_t* bytesWritten
    );

    static HRESULT CALLBACK HCResponseBodyWrite(
        _In_ HCCallHandle callHandle,
        _In_reads_bytes_(bytesAvailable) const uint8_t* source,
        _In_ size_t bytesAvailable,
        _In_opt_ void* context
    );

    String const m_url;
    UnorderedMap<String, String> m_headers;
    String const m_requestBody;
    Vector<char> m_responseBody;
    HCCallHandle m_callHandle{ nullptr };
};

}
