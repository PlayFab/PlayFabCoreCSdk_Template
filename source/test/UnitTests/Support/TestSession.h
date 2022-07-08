#pragma once

#include <playfab/PFCore.h>
#include <playfab/cpp/PlayFabException.h>
#include <httpClient/httpClient.h>

namespace PlayFab
{
namespace Wrappers
{

// RAII wrapper around PlayFabCore initialization
class TestSession
{
public:
    TestSession(XTaskQueueHandle backgroundQueue = nullptr)
    {
        HCSettingsSetTraceLevel(HCTraceLevel::Verbose);
        HCTraceSetTraceToDebugger(true);

        THROW_IF_FAILED(PFInitialize(backgroundQueue));
    }

    TestSession(TestSession const&) = delete;
    TestSession& operator=(TestSession const&) = delete;

    virtual ~TestSession()
    {
        XAsyncBlock async{};
        HRESULT hr = PFUninitializeAsync(&async);
        assert(SUCCEEDED(hr));
        hr = XAsyncGetStatus(&async, true);
        assert(SUCCEEDED(hr));
        UNREFERENCED_PARAMETER(hr);
    }
};

}
}
