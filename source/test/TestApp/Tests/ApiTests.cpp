#include "TestAppPch.h"
#include "TestContext.h"
#include "ApiTests.h"
#include "XAsyncHelper.h"
#include "XAsyncDispatcher.h"
//#include "playfab/PFLiveOps.h"
//#include "..\..\Wrappers\TitlePlayer.h"

namespace PlayFab
{
//using namespace Wrappers;

namespace Test
{

//void CALLBACK SetObjectsComplete(XAsyncBlock* async)
//{
//    std::unique_ptr<XAsyncBlock> reclaim{ async };
//    TestContext& testContext = *static_cast<TestContext*>(async->context);
//
//    size_t size{ 0 };
//    HRESULT hr = PFDataSetObjectsGetResultSize(async, &size);
//    if (FAILED(hr))
//    {
//        testContext.Fail();
//    }
//    else
//    {
//        std::vector<char> buffer(size);
//        PFDataSetObjectsResponse* response;
//        
//        hr = PFDataSetObjectsGetResult(async, buffer.size(), buffer.data(), &response, nullptr);
//        if (SUCCEEDED(hr))
//        {
//            testContext.Pass();
//        }
//        else
//        {
//            testContext.Fail();
//        }
//    }
//}
//
//void SetObjects(TitlePlayer<> player, TestContext& testContext)
//{
//    PFDataSetObjectsRequest request{};
//    auto entityKey = player.EntityKey();
//    request.entity = &entityKey.Model();
//    
//    auto asyncBlock = std::make_unique<XAsyncBlock>();
//    asyncBlock->callback = SetObjectsComplete;
//    asyncBlock->context = &testContext;
//
//    HRESULT hr = PFDataSetObjectsAsync(player.Handle(), &request, asyncBlock.get());
//    if (FAILED(hr))
//    {
//        testContext.Fail();
//    }
//    else
//    {
//        asyncBlock.release();
//    }
//}

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
        //SetObjects(playerHandle, testContext);
    }
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

    //hr = PFLiveOpsInitialize(serviceConfig);
    assert(SUCCEEDED(hr));

    UNREFERENCED_PARAMETER(hr);
}

void ApiTests::ClassTearDown()
{
    PFServiceConfigCloseHandle(serviceConfig);

    /*{
        XAsyncBlock async{};
        HRESULT hr = PFLiveOpsUninitializeAsync(&async);
        assert(SUCCEEDED(hr));

        hr = XAsyncGetStatus(&async, true);
        assert(SUCCEEDED(hr));

        UNREFERENCED_PARAMETER(hr);
    }*/

    {
        XAsyncBlock async{};
        HRESULT hr = PFUninitializeAsync(&async);
        assert(SUCCEEDED(hr));

        hr = XAsyncGetStatus(&async, true);
        assert(SUCCEEDED(hr));

        UNREFERENCED_PARAMETER(hr);
    }
}

} // namespace Test
} // namespace PlayFab
