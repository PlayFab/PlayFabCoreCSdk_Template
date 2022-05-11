// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include "httpClient/httpClient.h"

namespace PlayFab
{
namespace UnitTests
{

using HttpHeaders = std::map<std::string, std::string>;

using MockMatchedCallback = std::function<void(class HttpMock const& mock, std::string url, std::string requestBody)>;

// RAII wrapper around HCMockCallHandle
class HttpMock
{
public:
    HttpMock(_In_ const char* httpMethod, _In_ const char* url) noexcept;
    HttpMock(const HttpMock&) = delete;
    HttpMock& operator=(HttpMock) = delete;
    HttpMock(HttpMock&& other);
    HttpMock& operator=(HttpMock&& other) = delete;
    virtual ~HttpMock();

    void SetResponseHttpStatus(uint32_t httpStatus) const noexcept;
    void SetResponseBody(const char* responseBodyString) const noexcept;
    void SetResponseBody(const rapidjson::Value& responseBodyJson) const noexcept;
    void SetResponseBody(const uint8_t* responseBodyBytes, size_t responseBodySize) const noexcept;
    void ClearReponseBody() const noexcept;
    void SetResponseHeaders(const HttpHeaders& responseHeaders) const noexcept;

    void SetMockMatchedCallback(MockMatchedCallback&& callback) noexcept;

private:
    static void CALLBACK MatchedCallback(
        _In_ HCMockCallHandle mockHandle,
        _In_ const char* method,
        _In_ const char* url,
        _In_ const uint8_t* requestBodyBytes,
        _In_ uint32_t requestBodySize,
        _In_ void* context
    );

    HCMockCallHandle m_handle;
    MockMatchedCallback m_callback;
};

}
}
