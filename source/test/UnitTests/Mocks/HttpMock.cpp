#include "pch.h"
#include "HttpMock.h"

namespace PlayFab
{
namespace UnitTests
{

HttpMock::HttpMock(const char* method, const char* url) noexcept
{
    HRESULT hr = HCMockCallCreate(&m_handle);
    assert(SUCCEEDED(hr));

    hr = HCMockAddMock(m_handle, method, url, nullptr, 0);
    assert(SUCCEEDED(hr));

    // Default mock response of 200 with no response headers or body
    SetResponseHttpStatus(200);

    hr = HCMockSetMockMatchedCallback(m_handle, HttpMock::MatchedCallback, this);
    assert(SUCCEEDED(hr));

    UNREFERENCED_PARAMETER(hr);
}

HttpMock::HttpMock(HttpMock&& other) : m_handle{ other.m_handle }
{
    other.m_handle = nullptr;
}

HttpMock::~HttpMock()
{
    if (m_handle)
    {
        // Remove mock also closes handle
        HCMockRemoveMock(m_handle);
    }
}

void HttpMock::SetResponseHttpStatus(uint32_t httpStatus) const noexcept
{
    auto hr = HCMockResponseSetStatusCode(m_handle, httpStatus);
    assert(SUCCEEDED(hr));
    UNREFERENCED_PARAMETER(hr);
}

void HttpMock::SetResponseBody(const std::string& responseBodyString) const noexcept
{
    if (!responseBodyString.empty())
    {
        Vector<uint8_t> bodyBytes{ responseBodyString.begin(), responseBodyString.end() };
        SetResponseBody(bodyBytes.data(), bodyBytes.size());
    }
}

void HttpMock::SetResponseBody(const rapidjson::Value& responseBodyJson) const noexcept
{
    if (!responseBodyJson.IsNull())
    {
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        responseBodyJson.Accept(writer);
        SetResponseBody(buffer.GetString());
    }
}

void HttpMock::SetResponseBody(
    const uint8_t* responseBodyBytes,
    size_t responseBodySize
) const noexcept
{
    if (responseBodyBytes && responseBodySize)
    {
        auto hr = HCMockResponseSetResponseBodyBytes(m_handle, responseBodyBytes, static_cast<uint32_t>(responseBodySize));
        assert(SUCCEEDED(hr));
        UNREFERENCED_PARAMETER(hr);
    }
}

void HttpMock::ClearReponseBody() const noexcept
{
    // libHttpClient doesn't allow setting body with nullptr, but it does allow size = 0
    uint8_t body{};
    SetResponseBody(&body, 0);
}

void HttpMock::SetResponseHeaders(const HttpHeaders& responseHeaders) const noexcept
{
    for (const auto& header : responseHeaders)
    {
        auto hr = HCMockResponseSetHeader(m_handle, header.first.data(), header.second.data());
        assert(SUCCEEDED(hr));
        UNREFERENCED_PARAMETER(hr);
    }
}

void HttpMock::SetMockMatchedCallback(MockMatchedCallback&& callback) noexcept
{
    m_callback = std::move(callback);
}

void CALLBACK HttpMock::MatchedCallback(
    _In_ HCMockCallHandle mockHandle,
    _In_ const char* method,
    _In_ const char* url,
    _In_ const uint8_t* requestBodyBytes,
    _In_ uint32_t requestBodySize,
    _In_ void* context
)
{
    UNREFERENCED_PARAMETER(method);

    auto mock = static_cast<HttpMock*>(context);
    assert(mock->m_handle == mockHandle);

    if (mock->m_callback)
    {
        mock->m_callback(*mock, url, std::string{ requestBodyBytes, requestBodyBytes + requestBodySize });
    }
}

}
}
