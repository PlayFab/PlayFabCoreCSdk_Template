#include "stdafx.h"
#include "XAsyncOperation.h"

namespace PlayFab
{

IOperation::IOperation(PlayFab::RunContext&& runContext) noexcept : m_rc{ std::move(runContext) }
{
}

void IOperation::Run(UniquePtr<IOperation> operation) noexcept
{
    operation->OnStarted(std::move(operation));
}

RunContext IOperation::RunContext() const noexcept
{
    return m_rc;
}

XAsyncOperationBase::XAsyncOperationBase(PlayFab::RunContext&& runContext) noexcept :
    IOperation{ std::move(runContext) },
    m_asyncBlock{ RunContext().TaskQueue().Handle(), this, XAsyncCompletionCallback, 0 }
{
}

void XAsyncOperationBase::OnStarted(UniquePtr<IOperation> self) noexcept
{
    HRESULT hr = OnStarted(&m_asyncBlock);
    if (FAILED(hr))
    {
        // XAsyncCompletionCallback won't be called in this case. Operation will be destroyed here
        OnFailed(hr);
    }
    else
    {
        // Release operation. It will be reclaim in XAsyncCompletionCallback
        self.release();
    }
}

void CALLBACK XAsyncOperationBase::XAsyncCompletionCallback(XAsyncBlock* async)
{
    UniquePtr<XAsyncOperationBase> operation{ static_cast<XAsyncOperationBase*>(async->context) };
    operation->OnCompleted(async);
}

}
