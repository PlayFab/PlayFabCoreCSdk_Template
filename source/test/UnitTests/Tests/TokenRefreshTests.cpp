#include "stdafx.h"
#include "TestIncludes.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PlayFab
{
namespace UnitTests
{

TEST_CLASS(TokenRefreshTests)
{
public:
    TEST_METHOD(TokenRefreshSimple)
    {
        Wrappers::Session session;
        Wrappers::ServiceConfig<> serviceConfig{ "mockConnectionString", "mockTitleId", "mockPlayerAccountPoolId" };

        // Configure Mocks
        std::stringstream authUrl;
        authUrl << serviceConfig.ConnectionString() << "/PlayerIdentity/AuthenticateWith";
        HttpMock authMock{ "POST", authUrl.str().data() };

        rapidjson::Document authResponseBodyJson;
        auto& allocator{ authResponseBodyJson.GetAllocator() };
        authResponseBodyJson.Parse(kMockAuthResponseBody);

        // Set Token to expire in 1 minute to trigger a refresh
        time_t tokenExpiration = time(nullptr) + 60;
        auto tokenExpirationString = TimeTToIso8601String(tokenExpiration);
        authResponseBodyJson["data"]["TitlePlayerAccount"].AddMember("TokenExpiration", rapidjson::Value{ tokenExpirationString.data(), allocator }, allocator);
        authMock.SetResponseBody(authResponseBodyJson);

        std::stringstream refreshUrl;
        refreshUrl << serviceConfig.ConnectionString() << "/TokenRefreshMockPath";
        HttpMock refreshMock{ "POST", refreshUrl.str().data() };
        Event tokenRefreshedEvent;
        refreshMock.SetMockMatchedCallback([&tokenRefreshedEvent](HttpMock const&, std::string, std::string)
        {
            tokenRefreshedEvent.Set();
        });

        // Synchronously authenticate
        XAsyncBlock async{};
        PFAuthenticationAuthenticateCustomIdIdentityRequest request{};
        VERIFY_SUCCEEDED(PFAuthenticationAuthenticateWithCustomIdAsync(serviceConfig.Handle(), &request, &async));
        VERIFY_SUCCEEDED(XAsyncGetStatus(&async, true));
        PFTitlePlayerHandle titlePlayerHandle{ nullptr };
        VERIFY_SUCCEEDED(PFAuthenticationAuthenticateWithCustomIdGetResult(&async, &titlePlayerHandle));
        auto titlePlayer = Wrappers::TitlePlayer<>::Wrap(titlePlayerHandle);

        Assert::IsTrue(tokenRefreshedEvent.Wait(1000));
    }

};

}
}
