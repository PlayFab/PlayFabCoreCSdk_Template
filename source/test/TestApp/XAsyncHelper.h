#pragma once

#include "TestContext.h"
#include <playfab/PFAuthentication.h>

namespace PlayFabUnit
{

// Helper class to hold, retrieve, and validate the result of a completed XAsync operation. Intentionally
// storing the and validating the result in a different context so that we can make sure the result
// lifetime is maintained correctly
struct XAsyncResult
{
    XAsyncResult() = default;
    XAsyncResult(const XAsyncResult&) = default;
    XAsyncResult(XAsyncResult&&) = default;
    XAsyncResult& operator=(const XAsyncResult&) = default;
    XAsyncResult& operator=(XAsyncResult&&) = default;
    virtual ~XAsyncResult() = default;

    std::vector<char> resultBuffer{};

    virtual HRESULT Get(XAsyncBlock* async)
    {
        return XAsyncGetStatus(async, false);
    };
    virtual HRESULT Validate()
    {
        return S_OK;
    }
};

// Helper class for calling XAsync APIs and validating the result
template<typename ResultT = XAsyncResult>
struct XAsyncHelper
{
public:
    static_assert(std::is_base_of_v<XAsyncResult, ResultT>, "ResultT needs to be an XAsyncResult");

    XAsyncHelper(TestContext& tc) :
        asyncBlock{},
        testContext{ tc },
        asyncResult{ std::make_shared<ResultT>() }
    {
        asyncBlock.context = this;
        asyncBlock.callback = &XAsyncCallback;
    }

    ~XAsyncHelper()
    {
        asyncResult.reset();
    }

    XAsyncBlock asyncBlock;

private:
    static void CALLBACK XAsyncCallback(XAsyncBlock* async)
    {
        std::unique_ptr<XAsyncHelper> context{ static_cast<XAsyncHelper*>(async->context) };
        HRESULT hr = context->asyncResult->Get(async);
        if (FAILED(hr))
        {
            context->testContext.Fail("XAsyncResult::Get", hr);
        }
        else
        {
            // validate asynchronously to ensure result lifetime is maintained
            std::thread validateResultThread([context{ std::move(context) }]
            {
                std::this_thread::sleep_for(std::chrono::milliseconds{ 10 });

                HRESULT hr = context->asyncResult->Validate();
                if (FAILED(hr))
                {
                    context->testContext.Fail("XAsyncResult::Validate", hr);
                }
                else
                {
                    context->testContext.Pass();
                }
            });

            validateResultThread.detach();
        }
    }

    TestContext& testContext;
    std::shared_ptr<ResultT> asyncResult;
};

}