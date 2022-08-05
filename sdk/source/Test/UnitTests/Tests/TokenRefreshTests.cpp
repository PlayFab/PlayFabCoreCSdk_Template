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
        Wrappers::TestSession session;
        Wrappers::ServiceConfig<> serviceConfig{ "mockConnectionString", "mockTitleId", "mockPlayerAccountPoolId" };

        // Mock AuthenticateWithCustomId
        PlayFabServiceMock authMock{ serviceConfig, "AuthenticateWithCustomId" };

        // Set Token to expire in 1 minute to trigger a refresh
        time_t tokenExpiration = time(nullptr) + 60;
        auto tokenExpirationString = TimeTToIso8601String(tokenExpiration);
        rapidjson::Value tokenExpirationJson{ tokenExpirationString.data(), PlayFabServiceMock::JsonAllocator() };
        authMock.ResponseBodyPayload()["TitlePlayerAccount"].AddMember("TokenExpiration", tokenExpirationJson.Move(), PlayFabServiceMock::JsonAllocator());

        // Mock GetEntityToken 
        const char refreshedToken[] = "RefreshedToken";
        PlayFabServiceMock refreshMock{ serviceConfig, "GetEntityToken" };
        refreshMock.SetCallback([&](PlayFabServiceMock& mock, std::string, std::string)
        {
            mock.ResponseBodyPayload()["EntityToken"] = rapidjson::Value{ refreshedToken };
        });

        // Synchronously authenticate
        PFTitlePlayerHandle titlePlayerHandle{ nullptr };
        {
            XAsyncBlock async{};
            PFAuthenticationAuthenticateCustomIdIdentityRequest request{};
            VERIFY_SUCCEEDED(PFAuthenticationAuthenticateWithCustomIdAsync(serviceConfig.Handle(), &request, &async));
            VERIFY_SUCCEEDED(XAsyncGetStatus(&async, true));
            VERIFY_SUCCEEDED(PFAuthenticationAuthenticateWithCustomIdGetResult(&async, &titlePlayerHandle));
        }
        auto titlePlayer = Wrappers::TitlePlayer<>::Wrap(titlePlayerHandle);

        // Wait for the token to be refreshed. There is currently no convenient public hook to await on here since it
        // happens in the background, so just allow 2 seconds
        Sleep(2000);

        // Check the new EntityToken
        {
            XAsyncBlock async{};
            VERIFY_SUCCEEDED(PFTitlePlayerGetEntityTokenAsync(titlePlayer.Handle(), &async));

            size_t tokenSize;
            VERIFY_SUCCEEDED(PFTitlePlayerGetEntityTokenResultSize(&async, &tokenSize));

            std::vector<char> tokenBuffer(tokenSize);
            PFEntityToken const* token{};
            VERIFY_SUCCEEDED(PFTitlePlayerGetEntityTokenResult(&async, tokenBuffer.size(), tokenBuffer.data(), &token, nullptr));

            Assert::AreEqual(refreshedToken, token->token);
        }
    }

    TEST_METHOD(TestTokenExpiredCallback)
    {
        Wrappers::TestSession session;
        Wrappers::ServiceConfig<> serviceConfig{ "mockConnectionString", "mockTitleId", "mockPlayerAccountPoolId" };

        // Mock AuthenticateWithCustomId with expiring token
        PlayFabServiceMock authMock{ serviceConfig, "AuthenticateWithCustomId" };
        time_t tokenExpiration = time(nullptr) + 60;
        auto tokenExpirationString = TimeTToIso8601String(tokenExpiration);
        rapidjson::Value tokenExpirationJson{ tokenExpirationString.data(), PlayFabServiceMock::JsonAllocator() };
        authMock.ResponseBodyPayload()["TitlePlayerAccount"].AddMember("TokenExpiration", tokenExpirationJson.Move(), PlayFabServiceMock::JsonAllocator());

        // Mock GetEntityToken will failure
        PlayFabServiceMock refreshMock{ serviceConfig, "GetEntityToken" };
        refreshMock.SetCallback([&](PlayFabServiceMock& mock, std::string, std::string)
        {
            mock.ResponseBody().CopyFrom(PlayFabServiceMock::ServiceErrors()["ExpiredAuthToken"], PlayFabServiceMock::JsonAllocator());
        });

        struct TokenExpiredHandlerContext
        {
            Event event;
            std::string entityId;
        } tokenExpiredContext;

        PFRegistrationToken registrationToken{};
        PFEntityRegisterTokenExpiredEventHandler(nullptr, &tokenExpiredContext, [](void* ctx, const char* entityId)
        {
            auto handlerContext = static_cast<TokenExpiredHandlerContext*>(ctx);
            handlerContext->entityId = entityId;
            handlerContext->event.Set();
        }, &registrationToken);

        // Synchronously authenticate
        PFTitlePlayerHandle titlePlayerHandle{ nullptr };
        {
            XAsyncBlock async{};
            PFAuthenticationAuthenticateCustomIdIdentityRequest request{};
            VERIFY_SUCCEEDED(PFAuthenticationAuthenticateWithCustomIdAsync(serviceConfig.Handle(), &request, &async));
            VERIFY_SUCCEEDED(XAsyncGetStatus(&async, true));
            VERIFY_SUCCEEDED(PFAuthenticationAuthenticateWithCustomIdGetResult(&async, &titlePlayerHandle));
        }
        auto titlePlayer = Wrappers::TitlePlayer<>::Wrap(titlePlayerHandle);


        // Wait for token expired event
        tokenExpiredContext.event.Wait();
        Assert::AreEqual(tokenExpiredContext.entityId.data(), titlePlayer.EntityKey().Model().id);

        // Update auth mock with new token
        const char newToken[] = "NewEntityToken";
        authMock.ResponseBodyPayload()["TitlePlayerAccount"].RemoveMember("TokenExpiration");
        authMock.ResponseBodyPayload()["TitlePlayerAccount"]["EntityToken"] = rapidjson::Value{ newToken };

        // Synchronously reauthenticate
        {
            XAsyncBlock async{};
            PFAuthenticationAuthenticateCustomIdIdentityRequest request{};
            VERIFY_SUCCEEDED(PFAuthenticationReAuthenticateWithCustomIdAsync(titlePlayer.Handle(), &request, &async));
            VERIFY_SUCCEEDED(XAsyncGetStatus(&async, true));
        }


        // Check the new EntityToken
        {
            XAsyncBlock async{};
            VERIFY_SUCCEEDED(PFTitlePlayerGetEntityTokenAsync(titlePlayer.Handle(), &async));

            size_t tokenSize;
            VERIFY_SUCCEEDED(PFTitlePlayerGetEntityTokenResultSize(&async, &tokenSize));

            std::vector<char> tokenBuffer(tokenSize);
            PFEntityToken const* token{};
            VERIFY_SUCCEEDED(PFTitlePlayerGetEntityTokenResult(&async, tokenBuffer.size(), tokenBuffer.data(), &token, nullptr));

            Assert::AreEqual(newToken, token->token);
        }
    }

};

}
}
