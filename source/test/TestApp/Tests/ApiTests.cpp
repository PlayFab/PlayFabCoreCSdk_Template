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

}

void ApiTests::TestAuth(TestContext& testContext)
{
    auto asyncBlock = std::make_unique<XAsyncBlock>();
    asyncBlock->callback = AuthenticateWithCustomIdComplete;
    asyncBlock->context = &testContext;

    PFAuthenticationAuthenticateCustomIdIdentityRequest request{};
    request.customId = "CustomId";
    request.playerAccountPoolId = "F60133285C706B33";

    HRESULT hr = PFAuthenticationAuthenticateWithCustomIdAsync(stateHandle, &request, asyncBlock.get());

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
    AddTest("TestGetQoSMeasurements", &ApiTests::TestAuth);
}

void ApiTests::ClassSetUp()
{
    HRESULT hr = PFInitialize(testTitleData.titleId.data(), testTitleData.connectionString.data(), nullptr, &stateHandle);
    assert(SUCCEEDED(hr));
    UNREFERENCED_PARAMETER(hr);
}

void ApiTests::ClassTearDown()
{
    XAsyncBlock async{};
    HRESULT hr = PFUninitializeAsync(stateHandle, &async);
    assert(SUCCEEDED(hr));

    hr = XAsyncGetStatus(&async, true);
    assert(SUCCEEDED(hr));

    UNREFERENCED_PARAMETER(hr);
}

} // namespace Test
} // namespace PlayFab
