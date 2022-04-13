#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PlayFab
{
namespace UnitTests
{

constexpr char* mockAuthResponseBody =
R"({
  "code": 200,
  "status": "OK",
  "data": {
    "MasterPlayerAccount": {
      "EntityToken": "MasterPlayerMockEntityToken",
      "Entity": {
        "Id": "MasterPlayerId",
        "Type": "master_player_account",
        "TypeString": "master_player_account",
        "IsTitle": false,
        "IsNamespace": false,
        "IsService": false,
        "IsMasterPlayer": true,
        "IsTitlePlayer": false
      }
    },
    "TitlePlayerAccount": {
      "EntityToken": "TitlePlayerMockEntityToken",
      "Entity": {
        "Id": "TitlePlayerId",
        "Type": "title_player_account",
        "TypeString": "title_player_account",
        "IsTitle": false,
        "IsNamespace": false,
        "IsService": false,
        "IsMasterPlayer": false,
        "IsTitlePlayer": true
      }
    }
  }
})";

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
        authResponseBodyJson.Parse(mockAuthResponseBody);

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
        Wrappers::TitlePlayer<>::Wrap(titlePlayerHandle);

        Assert::IsTrue(tokenRefreshedEvent.Wait(1000));
    }

};

}
}
