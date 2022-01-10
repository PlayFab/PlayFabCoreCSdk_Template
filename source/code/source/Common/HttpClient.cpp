#include "stdafx.h"
#include "HttpClient.h"
#include "JsonUtils.h"
#include "Entity.h"
#include "TitlePlayer.h"
#include "SdkVersion.h"

namespace PlayFab
{
constexpr char productionEnvironmentURL[]{ ".playfabapi.com" };

// RAII wrapper around HCCallHandle.
class HCHttpCall
{
public:
    static AsyncOp<ServiceResponse> Perform(
        const char* url,
        const UnorderedMap<String, String>& headers,
        const JsonValue& requestBody,
        const TaskQueue& queue
    );

    virtual ~HCHttpCall() noexcept;

private:
    HCHttpCall(const TaskQueue& queue);
    HCHttpCall(const HCHttpCall& other) = delete;
    HCHttpCall& operator=(HCHttpCall other) = delete;

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

    static void CALLBACK HCPerformComplete(XAsyncBlock* async);

    String m_requestBody;
    Vector<char> m_responseBody;
    TaskQueue const m_queue;
    HCCallHandle m_callHandle{ nullptr };
    XAsyncBlock m_asyncBlock{};
    SharedPtr<AsyncOpContext<ServiceResponse>> m_asyncContext;
};

// Base class for EntityApiRequestOperation and ClassicApiRequestOperation
class RequestWithRetryOperation
{
public:
    virtual ~RequestWithRetryOperation() = default;

protected:
    RequestWithRetryOperation(SharedPtr<Entity> entity, String&& url, UnorderedMap<String, String>&& headers, JsonValue&& body, const TaskQueue& queue);

    static AsyncOp<ServiceResponse> Run(UniquePtr<RequestWithRetryOperation> operation);

    virtual void UpdateAuthHeader() = 0;

    SharedPtr<Entity> m_entity;
    UnorderedMap<String, String> m_headers;

private:
    void MakeRequest(bool retry);
    void Complete(Result<ServiceResponse>&& result);

    String m_url;
    JsonValue m_body;
    TaskQueue m_queue;
    SharedPtr<AsyncOpContext<ServiceResponse>> m_asyncContext;
};

HttpClient::HttpClient(String titleId) :
    m_titleId{ std::move(titleId) }
{
}

HttpClient::HttpClient(String titleId, String connectionString) :
    m_titleId{ std::move(titleId) },
    m_connectionString{ std::move(connectionString) }
{
}

String HttpClient::GetUrl(const char* path) const
{
    Stringstream fullUrl;
    if (m_connectionString.empty())
    {
        // Construct default url using titleId 
        fullUrl << "https://" << m_titleId << productionEnvironmentURL;
    }
    else
    {
        // Construct url from connection string
        fullUrl << m_connectionString;
    }

    // Append path
    fullUrl << path;

    // Add sdk version param (used by service for telemetry)
    fullUrl << "?sdk=" << versionString;

    return fullUrl.str();
}

AsyncOp<ServiceResponse> HttpClient::MakePostRequest(
    const char* path,
    const UnorderedMap<String, String>& headers,
    const JsonValue& requestBody,
    const TaskQueue& queue
) const
{
    return HCHttpCall::Perform(GetUrl(path).data(), headers, requestBody, queue);
}

AsyncOp<ServiceResponse> HttpClient::MakeEntityRequest(
    SharedPtr<Entity> entity,
    const char* path,
    UnorderedMap<String, String>&& headers,
    JsonValue&& requestBody,
    const TaskQueue& queue
) const
{
    class EntityRequestOperation : public RequestWithRetryOperation
    {
    public:
        static AsyncOp<ServiceResponse> Begin(SharedPtr<Entity> entity, String&& url, UnorderedMap<String, String>&& headers, JsonValue&& body, const TaskQueue& queue)
        {
            auto ptr{ Allocator<EntityRequestOperation>{}.allocate(1) };
            new (ptr) EntityRequestOperation{ std::move(entity), std::move(url), std::move(headers), std::move(body), queue };

            return RequestWithRetryOperation::Run(UniquePtr<RequestWithRetryOperation>{ ptr });
        }

    private:
        EntityRequestOperation(SharedPtr<Entity> entity, String&& url, UnorderedMap<String, String>&& headers, JsonValue&& body, const TaskQueue& queue)
            : RequestWithRetryOperation{ entity, std::move(url), std::move(headers), std::move(body), std::move(queue) }
        {
        }

        void UpdateAuthHeader() override
        {
            if (m_headers.find(kEntityTokenHeaderName) != m_headers.end())
            {
                m_headers[kEntityTokenHeaderName] = m_entity->EntityToken()->token;
            }
            else
            {
                assert(false);
                TRACE_ERROR("EntityToken header missing from PlayFab Entity API request");
            }
        }
    };

    return EntityRequestOperation::Begin(std::move(entity), GetUrl(path), std::move(headers), std::move(requestBody), queue);
}

AsyncOp<ServiceResponse> HttpClient::MakeClassicRequest(
    SharedPtr<TitlePlayer> titlePlayer,
    const char* path,
    UnorderedMap<String, String>&& headers,
    JsonValue&& requestBody,
    const TaskQueue& queue
) const
{
    class ClassicRequestOperation : public RequestWithRetryOperation
    {
    public:
        static AsyncOp<ServiceResponse> Begin(SharedPtr<TitlePlayer> titlePlayer, String&& url, UnorderedMap<String, String>&& headers, JsonValue&& body, const TaskQueue& queue)
        {
            auto ptr{ Allocator<ClassicRequestOperation>{}.allocate(1) };
            new (ptr) ClassicRequestOperation{ std::move(titlePlayer), std::move(url), std::move(headers), std::move(body), queue };

            return RequestWithRetryOperation::Run(UniquePtr<RequestWithRetryOperation>{ ptr });
        }

    private:
        ClassicRequestOperation(SharedPtr<TitlePlayer> titlePlayer, String&& url, UnorderedMap<String, String>&& headers, JsonValue&& body, const TaskQueue& queue)
            : RequestWithRetryOperation{ titlePlayer, std::move(url), std::move(headers), std::move(body), std::move(queue) },
            m_titlePlayer{ std::move(titlePlayer) }
        {
        }

        void UpdateAuthHeader() override
        {
            if (m_headers.find(kSessionTicketHeaderName) != m_headers.end())
            {
                m_headers[kSessionTicketHeaderName] = *m_titlePlayer->SessionTicket();
            }
            else
            {
                assert(false);
                TRACE_ERROR("ClientSessionTicket header missing from PlayFab Classic API request");
            }
        }

        SharedPtr<TitlePlayer> m_titlePlayer;
    };

    return ClassicRequestOperation::Begin(std::move(titlePlayer), GetUrl(path), std::move(headers), std::move(requestBody), queue);
}

HCHttpCall::HCHttpCall(const TaskQueue& queue) :
    m_queue{ queue },
    m_asyncContext{ MakeShared<AsyncOpContext<ServiceResponse>>() }
{
}

HCHttpCall::~HCHttpCall() noexcept
{
    if (m_callHandle)
    {
        HCHttpCallCloseHandle(m_callHandle);
    }
}

AsyncOp<ServiceResponse> HCHttpCall::Perform(
    const char* url,
    const UnorderedMap<String, String>& headers,
    const JsonValue& requestBody,
    const TaskQueue& queue
)
{
    UniquePtr<HCHttpCall> call{ new (Allocator<HCHttpCall>{}.allocate(1)) HCHttpCall(queue) };

    // Consider adding a helper to schedule the completion to correct queue port. Currently if failures happen 
    // synchronously, the continuation will be invoked synchronously as well.

    // Set up HCHttpCallHandle
    RETURN_IF_FAILED(HCHttpCallCreate(&call->m_callHandle));
    RETURN_IF_FAILED(HCHttpCallRequestSetUrl(call->m_callHandle, "POST", url));
    RETURN_IF_FAILED(HCHttpCallResponseSetResponseBodyWriteFunction(call->m_callHandle, HCHttpCall::HCResponseBodyWrite, call.get()));

    // Add default PlayFab headers
    RETURN_IF_FAILED(HCHttpCallRequestSetHeader(call->m_callHandle, "Accept", "application/json", true));
    RETURN_IF_FAILED(HCHttpCallRequestSetHeader(call->m_callHandle, "Content-Type", "application/json; charset=utf-8", true));
    RETURN_IF_FAILED(HCHttpCallRequestSetHeader(call->m_callHandle, "X-PlayFabSDK", versionString, true));
    RETURN_IF_FAILED(HCHttpCallRequestSetHeader(call->m_callHandle, "X-ReportErrorAsSuccess", "true", true));

    for (const auto& pair : headers)
    {
        if (!pair.first.empty() && !pair.second.empty())
        {
            RETURN_IF_FAILED(HCHttpCallRequestSetHeader(call->m_callHandle, pair.first.data(), pair.second.data(), true));
        }
    }

    if (!requestBody.IsNull())
    {
        call->m_requestBody = JsonUtils::WriteToString(requestBody);
        RETURN_IF_FAILED(HCHttpCallRequestSetRequestBodyReadFunction(call->m_callHandle, HCHttpCall::HCRequestBodyRead, call->m_requestBody.size(), call.get()));
    }

    call->m_asyncBlock.callback = HCPerformComplete;
    call->m_asyncBlock.context = call.get();
    call->m_asyncBlock.queue = call->m_queue.GetHandle();

    RETURN_IF_FAILED(HCHttpCallPerformAsync(call->m_callHandle, &call->m_asyncBlock));

    auto asyncOp = AsyncOp<ServiceResponse>{ call->m_asyncContext };

    // At this point HCPerfromComplete will be called. Release call and reclaim
    // ownership in callback.
    call.release();

    return asyncOp;
}

HRESULT HCHttpCall::HCRequestBodyRead(
    _In_ HCCallHandle callHandle,
    _In_ size_t offset,
    _In_ size_t bytesAvailable,
    _In_opt_ void* context,
    _Out_writes_bytes_to_(bytesAvailable, *bytesWritten) uint8_t* destination,
    _Out_ size_t* bytesWritten
)
{
    UNREFERENCED_PARAMETER(callHandle);

    assert(destination);
    assert(bytesAvailable > 0);
    assert(bytesWritten);

    auto call{ static_cast<HCHttpCall*>(context) }; // non-owning
    assert(offset < call->m_requestBody.size());

    *bytesWritten = std::min(bytesAvailable, call->m_requestBody.size() - offset);
    std::memcpy(destination, call->m_requestBody.data() + offset, *bytesWritten);

    return S_OK;
}

HRESULT HCHttpCall::HCResponseBodyWrite(
    _In_ HCCallHandle callHandle,
    _In_reads_bytes_(bytesAvailable) const uint8_t* source,
    _In_ size_t bytesAvailable,
    _In_opt_ void* context
)
{
    UNREFERENCED_PARAMETER(callHandle);

    assert(source);
    assert(bytesAvailable > 0);

    auto call{ static_cast<HCHttpCall*>(context) }; // non-owning
    call->m_responseBody.insert(call->m_responseBody.end(), source, source + bytesAvailable);

    return S_OK;
}

void HCHttpCall::HCPerformComplete(XAsyncBlock* async)
{
    // Retake ownership of asyncContext
    UniquePtr<HCHttpCall> call{ static_cast<HCHttpCall*>(async->context) };
    auto& asyncOpContext{ call->m_asyncContext };

    try
    {
        // Try to parse the response body no matter what. PlayFab often returns a response body even
        // on failure and they can provide more details about what went wrong. If we are unable to parse the response
        // body correctly, fall back to returning the Http status code.

        // Ensure response is null terminated before treating as a string
        call->m_responseBody.push_back(0);

        JsonDocument responseJson{ &JsonUtils::allocator };
        responseJson.Parse(call->m_responseBody.data());
        if (responseJson.HasParseError())
        {
            // Couldn't parse response body, fall back to Http status code
            uint32_t httpCode{ 0 };
            HRESULT hr = HCHttpCallResponseGetStatusCode(call->m_callHandle, &httpCode);
            if (FAILED(hr))
            {
                asyncOpContext->Complete(hr);
                return;
            }

            hr = HttpStatusToHR(httpCode);
            if (FAILED(hr))
            {
                asyncOpContext->Complete(hr);
                return;
            }
            
            // This is an unusal case. We weren't able to parse the response body, but the Http status code indicates that the
            // call was successful. Return the Json parse error in this case.
            Stringstream errorMessage;
            errorMessage << "Failed to parse PlayFab service response: " << rapidjson::GetParseError_En(responseJson.GetParseError());
            TRACE_ERROR(errorMessage.str().data());
            asyncOpContext->Complete(Result<ServiceResponse>{ E_FAIL, errorMessage.str() });
            return;
        }

        // Successful response from service (doesn't always indicate the call was successful, just that the service responded successfully)
        ServiceResponse response{};
        response.FromJson(responseJson);

        // Get requestId response header
        const char* requestId;
        HRESULT hr = HCHttpCallResponseGetHeader(call->m_callHandle, "X-RequestId", &requestId);
        if (FAILED(hr))
        {
            asyncOpContext->Complete(hr);
            return;
        }
        else if (requestId)
        {
            response.RequestId = requestId;
        }

        asyncOpContext->Complete(std::move(response));
    }
    catch (...)
    {
        asyncOpContext->Complete(std::current_exception());
    }
}

RequestWithRetryOperation::RequestWithRetryOperation(SharedPtr<Entity> entity, String&& url, UnorderedMap<String, String>&& headers, JsonValue&& body, const TaskQueue& queue) :
    m_entity{ std::move(entity) },
    m_headers{ std::move(headers) },
    m_url{ url },
    m_body{ std::move(body) },
    m_queue{ queue.DeriveWorkerQueue() },
    m_asyncContext{ MakeShared<AsyncOpContext<ServiceResponse>>() }
{
}

AsyncOp<ServiceResponse> RequestWithRetryOperation::Run(UniquePtr<RequestWithRetryOperation> operation)
{
    operation->MakeRequest(true);
    auto asyncContext{ operation->m_asyncContext };

    // Release the operation. Will be cleaned up in RequestWithRetryOperation::Complete.
    operation.release();

    return asyncContext;
}

void RequestWithRetryOperation::MakeRequest(bool retry)
{
    HCHttpCall::Perform(m_url.data(), m_headers, m_body, m_queue).Finally([this, retry](Result<ServiceResponse> result)
    {
        // Check if the result meets conditions for auth retry
        auto hr = Succeeded(result) ? ServiceErrorToHR(result.Payload().ErrorCode) : result.hr;

        if (retry && (hr == HTTP_E_STATUS_DENIED || /* REST error code (401) */
            hr == E_PF_INTERNAL_EXPIREDAUTHTOKEN || /* PlayFab error code for EntityToken expired */
            hr == E_PF_NOTAUTHENTICATED) /* PlayFab error code for SessionTicket expired */)
        {
            m_entity->RefreshToken(m_queue).Finally([this](Result<void> refreshResult)
            {
                if (Failed(refreshResult))
                {
                    TRACE_INFORMATION("Unable to refresh expired auth token. Passing along error to caller");
                    this->Complete(Result<ServiceResponse>{ refreshResult.hr, refreshResult.errorMessage });
                }
                else
                {
                    // Update our auth headers and retry
                    this->UpdateAuthHeader();
                    this->MakeRequest(false);
                }
            });
        }
        else
        {
            // Conditions for retry not met, pass along result
            this->Complete(std::move(result));
        }
    });
}

void RequestWithRetryOperation::Complete(Result<ServiceResponse>&& result)
{
    // Reclaim operation, it will be released after completing AsyncOpContext
    UniquePtr<RequestWithRetryOperation> reclaim{ this };
    m_asyncContext->Complete(std::move(result));
}

ServiceResponse::ServiceResponse(const ServiceResponse& src) :
    HttpCode{ src.HttpCode },
    HttpStatus{ src.HttpStatus },
    ErrorCode{ src.ErrorCode },
    ErrorName{ src.ErrorName },
    ErrorMessage{ src.ErrorMessage },
    RequestId{ src.RequestId }
{
    JsonUtils::FromJson(src.ErrorDetails, ErrorDetails);
    JsonUtils::FromJson(src.Data, Data);
}

ServiceResponse& ServiceResponse::operator=(const ServiceResponse& src)
{
    HttpCode = src.HttpCode;
    HttpStatus = src.HttpStatus;
    ErrorCode = src.ErrorCode;
    ErrorName = src.ErrorName;
    ErrorMessage = src.ErrorMessage;
    JsonUtils::FromJson(src.ErrorDetails, ErrorDetails);
    JsonUtils::FromJson(src.Data, Data);
    RequestId = src.RequestId;
    return *this;
}

void ServiceResponse::FromJson(const JsonValue& input)
{
    JsonUtils::ObjectGetMember(input, "code", HttpCode);
    JsonUtils::ObjectGetMember(input, "status", HttpStatus);
    StdExtra::optional<int64_t> errorCode{};
    JsonUtils::ObjectGetMember(input, "errorCode", errorCode);
    if (errorCode.has_value())
    {
        ErrorCode = static_cast<ServiceErrorCode>(*errorCode);
    }
    else
    {
        ErrorCode = ServiceErrorCode::Success;
    }
    JsonUtils::ObjectGetMember(input, "error", ErrorName);
    JsonUtils::ObjectGetMember(input, "errorMessage", ErrorMessage);
    JsonUtils::ObjectGetMember(input, "errorDetails", ErrorDetails);
    JsonUtils::ObjectGetMember(input, "data", Data);
}

}
