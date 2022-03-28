#include "TestAppPch.h"
#include "TestContext.h"
#include "ApiTests.h"
#include "XAsyncHelper.h"
#include "XAsyncDispatcher.h"
#include "playfab/PFCore.h"

namespace PlayFab
{
namespace Test
{

void CALLBACK AuthenticateWithCustomIdComplete(XAsyncBlock* async)
{
    std::unique_ptr<XAsyncBlock> reclaim{ async };
    TestContext& testContext = *static_cast<TestContext*>(async->context);

    PFTitlePlayerHandle playerHandle{ nullptr };
    HRESULT hr = PFAuthenticationAuthenticateWithCustomIdGetResult(async, &playerHandle);
    if (FAILED(hr))
    {
        testContext.Fail();
    }
    else
    {
        testContext.Pass();
    }

    PFTitlePlayerCloseHandle(playerHandle);
}

void ApiTests::TestAuth(TestContext& testContext)
{
    auto asyncBlock = std::make_unique<XAsyncBlock>();
    asyncBlock->callback = AuthenticateWithCustomIdComplete;
    asyncBlock->context = &testContext;

    PFAuthenticationAuthenticateCustomIdIdentityRequest request{};
    request.customId = "CustomId";

    HRESULT hr = PFAuthenticationAuthenticateWithCustomIdAsync(serviceConfig, &request, asyncBlock.get());

    if (FAILED(hr))
    {
        testContext.Fail();
    }
    else
    {
        asyncBlock.release();
    }
}

void ApiTests::AddTests()
{
    AddTest("TestAuth", &ApiTests::TestAuth);
}

void ApiTests::ClassSetUp()
{
    HRESULT hr = PFInitialize(nullptr);
    assert(SUCCEEDED(hr));
    hr = PFServiceConfigCreateHandle(testTitleData.connectionString.data(), testTitleData.titleId.data(), testTitleData.playerAccountPoolId.data(), &serviceConfig);
    assert(SUCCEEDED(hr));

    UNREFERENCED_PARAMETER(hr);
}

void ApiTests::ClassTearDown()
{
    PFServiceConfigCloseHandle(serviceConfig);

    XAsyncBlock async{};
    HRESULT hr = PFUninitializeAsync(&async);
    assert(SUCCEEDED(hr));

    hr = XAsyncGetStatus(&async, true);
    assert(SUCCEEDED(hr));

    UNREFERENCED_PARAMETER(hr);
}

} // namespace Test
} // namespace PlayFab
