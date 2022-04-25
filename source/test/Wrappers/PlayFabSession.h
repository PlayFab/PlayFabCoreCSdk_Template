// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include <playfab/PFCore.h>
#include <assert.h>

namespace PlayFab
{
namespace Wrappers
{

// RAII wrapper around PlayFabCore initialization
class Session
{
public:
    Session()
    {
        // These probably belong in a test specific spot but this will do for now
        HCSettingsSetTraceLevel(HCTraceLevel::Verbose);
        HCTraceSetTraceToDebugger(true);

        HRESULT hr = PFInitialize(nullptr);
        assert(SUCCEEDED(hr));
        if (FAILED(hr))
        {
            m_uninitializeOnDestruction = false;
        }
    }

    Session(XTaskQueueHandle backgroundQueue)
    {
        HRESULT hr = PFInitialize(backgroundQueue);
        assert(SUCCEEDED(hr));
        if (FAILED(hr))
        {
            m_uninitializeOnDestruction = false;
        }
    }

    Session(Session const&) = delete;
    Session& operator=(Session const&) = delete;

    virtual ~Session()
    {
        if (m_uninitializeOnDestruction)
        {
            XAsyncBlock async{};
            HRESULT hr = PFUninitializeAsync(&async);
            assert(SUCCEEDED(hr));

            hr = XAsyncGetStatus(&async, true);
            assert(SUCCEEDED(hr));
        }
    }

    HRESULT CleanupAsync(XAsyncBlock* async)
    {
        m_uninitializeOnDestruction = false;
        return PFUninitializeAsync(async);
    }

private:
    bool m_uninitializeOnDestruction{ true };
};

}
}
