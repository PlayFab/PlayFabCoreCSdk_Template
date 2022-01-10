#include "TestAppPch.h"
#include "TestContext.h"
#include "EntityTests.h"
#include "XAsyncHelper.h"
#include <playfab/PFAuthentication.h>

namespace PlayFabUnit
{

struct AuthResult : public XAsyncResult
{
    ~AuthResult()
    {
        PFTitlePlayerCloseHandle(titlePlayerHandle);
        PFEntityCloseHandle(entityHandle);
    }

    HRESULT Get(XAsyncBlock* async) override
    {
        RETURN_IF_FAILED(PFAuthenticationClientLoginGetResult(async, &titlePlayerHandle));
        RETURN_IF_FAILED(PFTitlePlayerGetEntityHandle(titlePlayerHandle, &entityHandle));

        return S_OK;
    }

    HRESULT Validate() override
    {
        {
            size_t bufferSize{};
            RETURN_IF_FAILED(PFTitlePlayerGetPlayFabIdSize(titlePlayerHandle, &bufferSize));

            std::string playFabId;
            playFabId.resize(bufferSize);
            RETURN_IF_FAILED(PFTitlePlayerGetPlayFabId(titlePlayerHandle, playFabId.size(), &playFabId[0], nullptr));
        }

        {
            size_t bufferSize{};
            RETURN_IF_FAILED(PFTitlePlayerGetEntityKeySize(titlePlayerHandle, &bufferSize));

            std::vector<char> buffer1(bufferSize);
            PFEntityKey const* entityKeyFromTitlePlayer;
            RETURN_IF_FAILED(PFTitlePlayerGetEntityKey(titlePlayerHandle, buffer1.size(), buffer1.data(), &entityKeyFromTitlePlayer, nullptr));

            RETURN_IF_FAILED(PFEntityGetEntityKeySize(entityHandle, &bufferSize));

            std::vector<char> buffer2(bufferSize);
            PFEntityKey const* entityKeyFromEntity;
            RETURN_IF_FAILED(PFEntityGetEntityKey(entityHandle, buffer2.size(), buffer2.data(), &entityKeyFromEntity, nullptr));

            if (std::strcmp(entityKeyFromTitlePlayer->id, entityKeyFromEntity->id))
            {
                return E_FAIL;
            }

            if (std::strcmp(entityKeyFromTitlePlayer->type, entityKeyFromEntity->type))
            {
                return E_FAIL;
            }

            if (std::strcmp(entityKeyFromTitlePlayer->type, PFTitlePlayerEntityType))
            {
                return E_FAIL;
            }
        }

        {
            size_t bufferSize{};
            RETURN_IF_FAILED(PFTitlePlayerGetCachedEntityTokenSize(titlePlayerHandle, &bufferSize));

            std::vector<char> buffer1(bufferSize);
            const PFEntityToken* entityTokenFromTitlePlayer;
            RETURN_IF_FAILED(PFTitlePlayerGetCachedEntityToken(titlePlayerHandle, buffer1.size(), buffer1.data(), &entityTokenFromTitlePlayer, nullptr));

            RETURN_IF_FAILED(PFEntityGetCachedEntityTokenSize(entityHandle, &bufferSize));

            std::vector<char> buffer2(bufferSize);
            const PFEntityToken* entityTokenFromEntity;
            RETURN_IF_FAILED(PFEntityGetCachedEntityToken(entityHandle, buffer2.size(), buffer2.data(), &entityTokenFromEntity, nullptr));

            if (std::strcmp(entityTokenFromEntity->token, entityTokenFromTitlePlayer->token))
            {
                return E_FAIL;
            }
        }

        {
            size_t sessionTicketSize;
            RETURN_IF_FAILED(PFTitlePlayerGetCachedSessionTicketSize(titlePlayerHandle, &sessionTicketSize));

            std::string sessionTicket;
            sessionTicket.resize(sessionTicketSize);
            RETURN_IF_FAILED(PFTitlePlayerGetCachedSessionTicket(titlePlayerHandle, sessionTicketSize, &sessionTicket[0], nullptr));
        }

        {
            size_t bufferSize;
            RETURN_IF_FAILED(PFTitlePlayerGetPlayerCombinedInfoSize(titlePlayerHandle, &bufferSize));

            if (bufferSize > 0)
            {
                std::vector<char> buffer(bufferSize);
                PFGetPlayerCombinedInfoResultPayload const* playerCombinedInfo;
                RETURN_IF_FAILED(PFTitlePlayerGetPlayerCombinedInfo(titlePlayerHandle, buffer.size(), buffer.data(), &playerCombinedInfo, nullptr));
            }
        }

        {
            time_t lastLoginTime;
            RETURN_IF_FAILED(PFTitlePlayerGetLastLoginTime(titlePlayerHandle, &lastLoginTime));
        }

        {
            PFAuthenticationUserSettings userSettings;
            RETURN_IF_FAILED(PFTitlePlayerGetUserSettings(titlePlayerHandle, &userSettings));
        }

        {
            size_t bufferSize;
            RETURN_IF_FAILED(PFTitlePlayerGetTreatmentAssignmentSize(titlePlayerHandle, &bufferSize));

            if (bufferSize > 0)
            {
                std::vector<char> buffer(bufferSize);
                PFTreatmentAssignment const* treatmentAssignment;
                RETURN_IF_FAILED(PFTitlePlayerGetTreatmentAssignment(titlePlayerHandle, buffer.size(), buffer.data(), &treatmentAssignment, nullptr));
            }
        }

        return S_OK;
    }

    PFTitlePlayerHandle titlePlayerHandle{ nullptr };
    PFEntityHandle entityHandle{ nullptr };
};

void EntityTests::TestClientLogin(TestContext& testContext)
{
    auto async = std::make_unique<XAsyncHelper<AuthResult>>(testContext);

    PFAuthenticationLoginWithCustomIDRequest request{};
    request.customId = "CustomId";
    request.createAccount = true;

    PFGetPlayerCombinedInfoRequestParams combinedInfoRequestParams{};
    combinedInfoRequestParams.getPlayerProfile = true;
    combinedInfoRequestParams.getTitleData = true;
    combinedInfoRequestParams.getUserAccountInfo = true;
    combinedInfoRequestParams.getUserData = true;
    request.infoRequestParameters = &combinedInfoRequestParams;

    HRESULT hr = PFAuthenticationClientLoginWithCustomIDAsync(stateHandle, &request, &async->asyncBlock);
    if (FAILED(hr))
    {
        testContext.Fail("PlayFabClientLoginWithCustomIDAsync", hr);
    }
    async.release();
}

void EntityTests::TestManualTokenRefresh(TestContext& testContext)
{
    struct State
    {
        AuthResult authResult;
        TestContext& testContext;
    };
    std::unique_ptr<State> testState{ new State{ AuthResult{}, testContext } };

    {
        XAsyncBlock async{};

        PFAuthenticationLoginWithCustomIDRequest request{};
        request.customId = "CustomId";
        request.createAccount = true;

        HRESULT hr = PFAuthenticationClientLoginWithCustomIDAsync(stateHandle, &request, &async);
        if (FAILED(hr))
        {
            testContext.Fail("PlayFabClientLoginWithCustomIDAsync", hr);
            return;
        }

        XAsyncGetStatus(&async, true);
        hr = PFAuthenticationClientLoginGetResult(&async, &testState->authResult.titlePlayerHandle);

        if (FAILED(hr) || !testState->authResult.titlePlayerHandle)
        {
            testContext.Fail("PlayFabGetAuthResult", hr);
            return;
        }

        PFTitlePlayerGetEntityHandle(testState->authResult.titlePlayerHandle, &testState->authResult.entityHandle);

        size_t bufferSize;
        PFEntityGetCachedEntityTokenSize(testState->authResult.entityHandle, &bufferSize);

        std::vector<char> buffer(bufferSize);
        const PFEntityToken* entityToken;
        PFEntityGetCachedEntityToken(testState->authResult.entityHandle, buffer.size(), buffer.data(), &entityToken, nullptr);
    }

    PFRegistrationToken token{};
    PFEntityRegisterTokenRefreshedCallback(testState->authResult.entityHandle, nullptr, 
        [](_In_ const PFEntityToken* newToken, _In_opt_ void* context)
        {
            std::unique_ptr<State> testState{ static_cast<State*>(context) };

            size_t bufferSize;
            PFEntityGetCachedEntityTokenSize(testState->authResult.entityHandle, &bufferSize);

            std::vector<char> buffer(bufferSize);
            const PFEntityToken* entityToken;
            PFEntityGetCachedEntityToken(testState->authResult.entityHandle, buffer.size(), buffer.data(), &entityToken, nullptr);

            if (std::strcmp(newToken->token, entityToken->token))
            {
                testState->testContext.Fail();
            }
            else
            {
                testState->testContext.Pass();
            }

        }, testState.get(), &token);

    {
        XAsyncBlock async{};

        PFAuthenticationGetEntityTokenRequest request{};
        HRESULT hr = PFEntityGetEntityTokenAsync(testState->authResult.entityHandle, &request, &async);
        if (FAILED(hr))
        {
            testContext.Fail("PFEntityGetEntityTokenAsync", hr);
            return;
        }

        hr = XAsyncGetStatus(&async, true);
        if (SUCCEEDED(hr))
        {
            PFEntityHandle newHandle{};
            PFEntityGetEntityTokenGetResult(&async, &newHandle);
            PFEntityCloseHandle(newHandle);
        }

    }

    testState.release();
}

#if HC_PLATFORM == HC_PLATFORM_GDK

// RAII wrapper of XUserHandle
struct XUserHolder
{
    XUserHolder() = default;
    XUserHolder(const XUserHolder&) = delete;
    ~XUserHolder()
    {
        if (this->handle)
        {
            XUserCloseHandle(this->handle);
        }
    }

    XUserHandle handle{ nullptr };
};

HRESULT AddXUser(XUserHolder& user)
{
    // Synchronously add Platform user
    XAsyncBlock async{};
    RETURN_IF_FAILED(XUserAddAsync(XUserAddOptions::AddDefaultUserAllowingUI, &async));
    RETURN_IF_FAILED(XAsyncGetStatus(&async, true));
    RETURN_IF_FAILED(XUserAddResult(&async, &user.handle));

    // Sanity check
    XUserLocalId localId{};
    RETURN_IF_FAILED(XUserGetLocalId(user.handle, &localId));

    return S_OK;
}

void EntityTests::TestLoginWithXUser(TestContext& testContext)
{
    XUserHolder xUser;
    AuthResult playFabAuthResult;

    HRESULT hr = AddXUser(xUser);
    if (FAILED(hr))
    {
        testContext.Fail();
    }
    else
    {
        auto async = std::make_unique<XAsyncHelper<AuthResult>>(testContext);

        PFAuthenticationLoginWithXUserRequest request{};
        request.createAccount = true;
        request.userHandle = xUser.handle;

        hr = PFAuthenticationLoginWithXUserAsync(stateHandle, &request, &async->asyncBlock);
        if (FAILED(hr))
        {
            testContext.Fail("PFClientLoginWithXUserAsync", hr);
        }
        async.release();
    }
}
#endif

void EntityTests::AddTests()
{
    AddTest("TestClientLogin", &EntityTests::TestClientLogin);
    AddTest("TestManualTokenRefresh", &EntityTests::TestManualTokenRefresh);
#if HC_PLATFORM == HC_PLATFORM_GDK
    AddTest("TestLoginWithXUser", &EntityTests::TestLoginWithXUser);
#endif
}

void EntityTests::ClassSetUp()
{
    HRESULT hr = PFInitialize(testTitleData.titleId.data(), testTitleData.connectionString.data(), nullptr, &stateHandle);
    UNREFERENCED_PARAMETER(hr);
}

void EntityTests::ClassTearDown()
{
    XAsyncBlock async{};
    HRESULT hr = PFUninitializeAsync(stateHandle, &async);
    assert(SUCCEEDED(hr));

    hr = XAsyncGetStatus(&async, true);
    assert(SUCCEEDED(hr));

    UNREFERENCED_PARAMETER(hr);
}

void EntityTests::SetUp(TestContext& testContext)
{
    if (!stateHandle)
    {
        testContext.Skip("Skipping test because stateHandle is null");
    }
}

}