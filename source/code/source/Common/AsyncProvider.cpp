// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "stdafx.h"
#include "AsyncProvider.h"
#include "EnumTraits.h"

namespace PlayFab
{

constexpr char defaultProviderIdentity[]{ "UnnamedProvider" };

Provider::Provider(_In_ XAsyncBlock* async) noexcept
    : identityName{ defaultProviderIdentity },
    m_async{ async }
{
}

HRESULT Provider::Run(_In_ UniquePtr<Provider>&& provider) noexcept
{
    RETURN_HR_INVALIDARG_IF_NULL(provider->m_async);
    RETURN_IF_FAILED(XAsyncBegin(provider->m_async, provider.get(), nullptr, provider->identityName, XAsyncProvider));
    provider.release();
    return S_OK;
}

HRESULT Provider::Begin(TaskQueue&&)
{
    return Schedule(0);
}

HRESULT Provider::DoWork(TaskQueue&&)
{
    return E_FAIL;
}

HRESULT Provider::GetResult(void*, size_t)
{
    assert(false);
    return E_UNEXPECTED;
}

HRESULT Provider::Cancel(TaskQueue&&)
{
    // Cancellation not supported by default, let async operation complete
    return S_OK;
}

HRESULT Provider::Schedule(uint32_t delay) const
{
    return XAsyncSchedule(m_async, delay);
}

void Provider::Complete(size_t resultSize)
{
    XAsyncComplete(m_async, S_OK, resultSize);
}

void Provider::Fail(HRESULT hr)
{
    XAsyncComplete(m_async, hr, 0);
}

HRESULT CALLBACK Provider::XAsyncProvider(_In_ XAsyncOp op, _Inout_ const XAsyncProviderData* data) noexcept
{
    auto provider{ static_cast<Provider*>(data->context) };

    TRACE_VERBOSE("Provider[ID=%s] XAsyncOp::%s", provider->identityName, EnumName(op));

    switch (op)
    {
    case XAsyncOp::Begin:
        try
        {
            return provider->Begin(data->async->queue);
        }
        catch (...)
        {
            return CurrentExceptionToHR();
        }
    case XAsyncOp::DoWork:
        try
        {
            return provider->DoWork(data->async->queue);
        }
        catch (...)
        {
            return CurrentExceptionToHR();
        }
    case XAsyncOp::GetResult:
        try
        {
            return provider->GetResult(data->buffer, data->bufferSize);
        }
        catch (...)
        {
            return CurrentExceptionToHR();
        }
    case XAsyncOp::Cancel:
    {
        try
        {
            return provider->Cancel(data->async->queue);
        }
        catch (...)
        {
            return CurrentExceptionToHR();
        }
    }
    case XAsyncOp::Cleanup:
    {
        // Cleanup should only fail in catostrophic cases. Can't pass result to client 
        // at this point so die with exception.

        // Re-take ownership of provider, it will be destroyed here
        UniquePtr<Provider>{ provider };
        return S_OK;
    }
    default:
    {
        assert(false);
        return S_OK;
    }
    }
}

} // PlayFab
