#include "stdafx.h"
#include "HttpClient.h"
#include "JsonUtils.h"
#include "Entity.h"
#include "TitlePlayer.h"
#include "SdkVersion.h"

namespace PlayFab
{

constexpr char kEntityTokenHeaderName[]{ "X-EntityToken" };
constexpr char kProductionEnvironmentURL[]{ ".playfabapi.com" };

// RAII wrapper around HCCallHandle.
class HCHttpCall : public ICancellationListener
{
public:
    static AsyncOp<ServiceResponse> Perform(
        const char* url,
        const UnorderedMap<String, String>& headers,
        const JsonValue& requestBody,
        RunContext&& runContext
    );

    virtual ~HCHttpCall() noexcept;

private:
    HCHttpCall(RunContext&& runContext);
    HCHttpCall(const HCHttpCall& other) = delete;
    HCHttpCall& operator=(HCHttpCall other) = delete;

    // ICancellationListener
    void OnCancellation() noexcept override;

    HRESULT InitializeCall(const char* url, const UnorderedMap<String, String>& headers, const JsonValue& requestBody) noexcept;;
    AsyncOp<ServiceResponse> CompleteAsync(Result<ServiceResponse>&& result) noexcept;

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
    RunContext const m_runContext;
    HCCallHandle m_callHandle{ nullptr };
    XAsyncBlock m_asyncBlock{};
    SharedPtr<AsyncOpContext<ServiceResponse>> m_asyncContext;
};

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
    const UnorderedMap<String, String>& headers,
    const JsonValue& requestBody,
    RunContext&& runContext
) const
{
    return HCHttpCall::Perform(GetUrl(path).data(), headers, requestBody, std::move(runContext));
}

AsyncOp<ServiceResponse> HttpClient::MakeEntityRequest(
    SharedPtr<Entity> entity,
    const char* path,
    UnorderedMap<String, String>&& headers,
    JsonValue&& requestBody,
    RunContext&& runContext
) const
{
    return entity->GetEntityToken(false, runContext.Derive()).Then(
        [
            url = GetUrl(path),
            headers = std::move(headers),
            body = std::move(requestBody),
            runContext{ runContext.Derive() }
        ]
    (Result<EntityToken> result) mutable -> AsyncOp<ServiceResponse>
    {
        RETURN_IF_FAILED(result.hr);
        headers[kEntityTokenHeaderName] = result.ExtractPayload().token;

        return HCHttpCall::Perform(url.data(), headers, body, std::move(runContext));
    });
}

String const& HttpClient::ConnectionString() const noexcept
{
    return m_connectionString;
}

HCHttpCall::HCHttpCall(RunContext&& runContext) :
    m_runContext{ std::move(runContext) },
    m_asyncContext{ MakeShared<AsyncOpContext<ServiceResponse>>() }
{
}

HCHttpCall::~HCHttpCall() noexcept
{
    if (m_callHandle)
    {
        HCHttpCallCloseHandle(m_callHandle);
    }

    m_runContext.CancellationToken().UnregisterForNotificationAndCheck(*this);
}

AsyncOp<ServiceResponse> HCHttpCall::Perform(
    const char* url,
    const UnorderedMap<String, String>& headers,
    const JsonValue& requestBody,
    RunContext&& context
)
{
    UniquePtr<HCHttpCall> call{ new (Allocator<HCHttpCall>{}.allocate(1)) HCHttpCall(std::move(context)) };

    bool alreadyCancelled = call->m_runContext.CancellationToken().RegisterForNotificationAndCheck(*call);
    if (alreadyCancelled)
    {
        return call->CompleteAsync(E_ABORT);
    }

    HRESULT hr = call->InitializeCall(url, headers, requestBody);
    if (FAILED(hr))
    {
        return call->CompleteAsync(hr);
    }

    call->m_asyncBlock.callback = HCPerformComplete;
    call->m_asyncBlock.context = call.get();
    call->m_asyncBlock.queue = call->m_runContext.TaskQueue().Handle();

    hr = HCHttpCallPerformAsync(call->m_callHandle, &call->m_asyncBlock);
    if (FAILED(hr))
    {
        return call->CompleteAsync(hr);
    }

    auto asyncOp = AsyncOp<ServiceResponse>{ call->m_asyncContext };

    // At this point HCPerfromComplete will be called. Release call and reclaim
    // ownership in callback.
    call.release();

    return asyncOp;
}

void HCHttpCall::OnCancellation() noexcept
{
    // This is safe to call even if HCHttpCallPerformAsync hasn't yet been called (it just won't do anything)
    XAsyncCancel(&m_asyncBlock);
}

HRESULT HCHttpCall::InitializeCall(const char* url, const UnorderedMap<String, String>& headers, const JsonValue& requestBody) noexcept
{
    // Set up HCHttpCallHandle
    RETURN_IF_FAILED(HCHttpCallCreate(&m_callHandle));
    RETURN_IF_FAILED(HCHttpCallRequestSetUrl(m_callHandle, "POST", url));
    RETURN_IF_FAILED(HCHttpCallResponseSetResponseBodyWriteFunction(m_callHandle, HCHttpCall::HCResponseBodyWrite, this));

    // Add default PlayFab headers
    RETURN_IF_FAILED(HCHttpCallRequestSetHeader(m_callHandle, "Accept", "application/json", true));
    RETURN_IF_FAILED(HCHttpCallRequestSetHeader(m_callHandle, "Content-Type", "application/json; charset=utf-8", true));
    RETURN_IF_FAILED(HCHttpCallRequestSetHeader(m_callHandle, "X-PlayFabSDK", versionString, true));
    RETURN_IF_FAILED(HCHttpCallRequestSetHeader(m_callHandle, "X-ReportErrorAsSuccess", "true", true));

    for (const auto& pair : headers)
    {
        if (!pair.first.empty() && !pair.second.empty())
        {
            RETURN_IF_FAILED(HCHttpCallRequestSetHeader(m_callHandle, pair.first.data(), pair.second.data(), true));
        }
    }

    if (!requestBody.IsNull())
    {
        m_requestBody = JsonUtils::WriteToString(requestBody);
        RETURN_IF_FAILED(HCHttpCallRequestSetRequestBodyReadFunction(m_callHandle, HCHttpCall::HCRequestBodyRead, m_requestBody.size(), this));
    }

    return S_OK;
}

AsyncOp<ServiceResponse> HCHttpCall::CompleteAsync(Result<ServiceResponse>&& result) noexcept
{
    // Helper to ensure Http call is always completed on the TaskQueue completion port even when errors occur synchronously.
    // Consider making this the default behavior for AsyncOpContext::Complete if this pattern needs to be repeated elsewhere
    class HttpRequestCompletion : public ITaskQueueWork
    {
    public:
        HttpRequestCompletion(SharedPtr<AsyncOpContext<ServiceResponse>> asyncContext, Result<ServiceResponse>&& result) :
            m_asyncContext{ std::move(asyncContext) },
            m_result{ std::move(result) }
        {
        }

    private:
        void Run() noexcept override
        {
            m_asyncContext->Complete(std::move(m_result));
        }
        void WorkCancelled() noexcept override
        {
            m_asyncContext->Complete(E_ABORT);
        }

        SharedPtr<AsyncOpContext<ServiceResponse>> const m_asyncContext;
        Result<ServiceResponse> m_result;
    };

    m_runContext.TaskQueue().SubmitCompletion(MakeShared<HttpRequestCompletion>(m_asyncContext, std::move(result)));

    return m_asyncContext;
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
                call->CompleteAsync(hr);
                return;
            }

            hr = HttpStatusToHR(httpCode);
            if (FAILED(hr))
            {
                call->CompleteAsync(hr);
                return;
            }
            
            // This is an unusal case. We weren't able to parse the response body, but the Http status code indicates that the
            // call was successful. Return the Json parse error in this case.
            Stringstream errorMessage;
            errorMessage << "Failed to parse PlayFab service response: " << rapidjson::GetParseError_En(responseJson.GetParseError());
            TRACE_ERROR(errorMessage.str().data());
            call->CompleteAsync(Result<ServiceResponse>{ E_FAIL, errorMessage.str() });
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
            call->CompleteAsync(hr);
            return;
        }
        else if (requestId)
        {
            response.RequestId = requestId;
        }

        call->CompleteAsync(std::move(response));
    }
    catch (...)
    {
        call->m_asyncContext->Complete(std::current_exception());
    }
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
