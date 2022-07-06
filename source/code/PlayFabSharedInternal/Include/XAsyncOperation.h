#pragma once

#include "AsyncOp.h"

namespace PlayFab
{

// Generic interface for an operation that can be run
class IOperation
{
public:
    IOperation(RunContext&& runContext) noexcept;
    IOperation(IOperation const&) noexcept = delete;
    IOperation& operator=(IOperation const&) noexcept = delete;
    virtual ~IOperation() noexcept = default;

    // Transfer ownership of the operation and run it. The operation is responsible 
    // for managing its own lifetime from this point on
    static void Run(UniquePtr<IOperation> operation) noexcept;

protected: // Interface to operations
    RunContext RunContext() const noexcept;

private: // Interface to be implemented by operations  
    virtual void OnStarted(UniquePtr<IOperation> self) = 0;

private:
    PlayFab::RunContext m_rc;
};

// Wrapper of an XAsync Operation. No Strongly typed result
class XAsyncOperationBase : public IOperation, public ICancellationListener
{
public:
    XAsyncOperationBase(PlayFab::RunContext&& runContext) noexcept;
    XAsyncOperationBase(XAsyncOperationBase const&) noexcept = delete;
    XAsyncOperationBase& operator=(XAsyncOperationBase const&) noexcept = delete;
    virtual ~XAsyncOperationBase() noexcept;

private: // Interface to be implemented by XAsync wrapper Operations
    virtual HRESULT OnStarted(XAsyncBlock* async) = 0;
    virtual void OnFailed(HRESULT hr) = 0;
    virtual void OnCompleted(XAsyncBlock* async) = 0;

private: // IOperation implementation
    void OnStarted(UniquePtr<IOperation> self) noexcept override final;

private: // ICancellationListener
    void OnCancellation() noexcept override;

private:
    static void CALLBACK XAsyncCompletionCallback(XAsyncBlock* async);

    XAsyncBlock m_asyncBlock;
};

// Wrapper of an XAsyncOperation with a strongly typed result
template<typename T>
class XAsyncOperation : public XAsyncOperationBase
{
public:
    XAsyncOperation(PlayFab::RunContext&& rc) noexcept;
    XAsyncOperation(XAsyncOperation const&) = delete;
    XAsyncOperation& operator=(XAsyncOperation const&) = delete;
    virtual ~XAsyncOperation() noexcept = default;

    static AsyncOp<T> Run(UniquePtr<XAsyncOperation> operation) noexcept;

    AsyncOp<T> AsAsyncOp() const noexcept;

private: // Interface to be implemented by XAsync wrapper Operations
    virtual Result<T> GetResult(XAsyncBlock* async) noexcept;

private: // XAsyncOperationBase implementation
    virtual void OnFailed(HRESULT hr) noexcept override final;
    virtual void OnCompleted(XAsyncBlock* async) noexcept override final;

    SharedPtr<AsyncOpContext<T>> m_asyncContext;
};

template<typename T>
AsyncOp<T> RunOperation(UniquePtr<XAsyncOperation<T>> operation) noexcept
{
    return XAsyncOperation<T>::Run(std::move(operation));
}

//------------------------------------------------------------------------------
// Template implementations
//------------------------------------------------------------------------------

// XAsyncOp<T> Implementation
template<typename T>
XAsyncOperation<T>::XAsyncOperation(PlayFab::RunContext&& rc) noexcept :
    XAsyncOperationBase{ std::move(rc) },
    m_asyncContext{ MakeShared<AsyncOpContext<T>>() }
{
}

template<typename T>
AsyncOp<T> XAsyncOperation<T>::Run(UniquePtr<XAsyncOperation> operation) noexcept
{
    auto asyncOp = operation->AsAsyncOp();
    IOperation::Run(std::move(operation));
    return asyncOp;
}

template<typename T>
AsyncOp<T> XAsyncOperation<T>::AsAsyncOp() const noexcept
{
    return m_asyncContext;
}

template<typename T>
Result<T> XAsyncOperation<T>::GetResult(XAsyncBlock* asyncBlock) noexcept
{
    size_t resultSize{};
    RETURN_IF_FAILED(XAsyncGetResultSize(asyncBlock, &resultSize));
    assert(resultSize == 0); // Should be overriden for XAsync operations with non-empty result payloads
    return S_OK;
}

template<typename T>
void XAsyncOperation<T>::OnFailed(HRESULT hr) noexcept
{
    // Submit synchronous failures to TaskQueue so that completion runs on the correct port
    struct AsyncCompletion : public ITaskQueueWork
    {
        SharedPtr<AsyncOpContext<T>> asyncContext;
        HRESULT hr;

        void Run() noexcept override
        {
            asyncContext->Complete(hr);
        }
        void WorkCancelled() noexcept override
        {
            asyncContext->Complete(hr);
        }
    };

    auto completion = MakeShared<AsyncCompletion>();
    completion->asyncContext = m_asyncContext;
    completion->hr = hr;

    RunContext().TaskQueue().SubmitCompletion(completion);
}

template<typename T>
void XAsyncOperation<T>::OnCompleted(XAsyncBlock* asyncBlock) noexcept
{
    StdExtra::optional<Result<T>> result;
    try
    {
        result.emplace(GetResult(asyncBlock));
        
    }
    catch (...)
    {
        result.emplace(CurrentExceptionToHR());
    }

    assert(result.has_value());
    m_asyncContext->Complete(std::move(*result));
}

}
