#include "stdafx.h"
#include "TestIncludes.h"
#include "RunContext.h"
#include "ApiXAsyncProvider.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PlayFab
{
namespace UnitTests
{

class CancellableOperation : public ITaskQueueWork, public ICancellationListener
{
public:
    static void Run(RunContext&& rc, Event& completionEvent, uint64_t timeout)
    {
        std::shared_ptr<CancellableOperation> op{ new CancellableOperation(std::move(rc), completionEvent) };
        op->m_rc.TaskQueue().SubmitWork(op, (uint32_t)timeout);
    }

    ~CancellableOperation()
    {
        m_rc.CancellationToken().UnregisterForNotificationAndCheck(*this);
    }

private:
    CancellableOperation(RunContext&& rc, Event& completionEvent) : m_rc{ std::move(rc) }, m_completionEvent{ completionEvent }
    {
        bool cancelled = m_rc.CancellationToken().RegisterForNotificationAndCheck(*this);
        Assert::IsFalse(cancelled);
    }

    void Run() override
    {
        m_completionEvent.Set();
    }

    void WorkCancelled() 
    {
        m_completionEvent.Set();
    } 

    void OnCancellation() noexcept override
    {
        m_rc.TaskQueue().Terminate(nullptr, nullptr);
    }

    RunContext m_rc;
    Event& m_completionEvent;
};

class NonCancellableOperation : public ITaskQueueWork
{
public:
    static void Run(RunContext&& rc, Event& completionEvent, uint64_t timeout)
    {
        std::shared_ptr<NonCancellableOperation> op{ new NonCancellableOperation(std::move(rc), completionEvent) };
        op->m_rc.TaskQueue().SubmitWork(op, (uint32_t)timeout);
    }

    ~NonCancellableOperation()
    {
    }

private:
    NonCancellableOperation(RunContext&& rc, Event& completionEvent) : m_rc{ std::move(rc) }, m_completionEvent{ completionEvent } {}

    void Run() override
    {
        m_completionEvent.Set();
    }

    void WorkCancelled()
    {
        m_completionEvent.Set();
    }

    RunContext m_rc;
    Event& m_completionEvent;
};

struct RunContextTerminationHelper : public ITerminationListener
{
    Event terminationComplete;

    void OnTerminated(SharedPtr<ITerminationListener> self, void* context) override
    {
        terminationComplete.Set();
    }
};

class TestProvider : public XAsyncProviderBase
{
public:
    TestProvider(RunContext&& rc, XAsyncBlock* async, uint32_t result) :
        XAsyncProviderBase{ std::move(rc), async },
        m_result{ result }
    {
    }

    ~TestProvider()
    {
    }

    HRESULT Begin(RunContext rc) override
    {
        rc.TaskQueue().SubmitWork(std::shared_ptr<Work>{new Work{ *this }}, 50000);
        return S_OK;
    }

    HRESULT GetResult(void* buffer, size_t bufferSize)
    {
        assert(bufferSize == sizeof(uint32_t));
        uint32_t* resultPtr = static_cast<uint32_t*>(buffer);
        *resultPtr = m_result;
        return S_OK;
    }

private:
    struct Work : public ITaskQueueWork
    {
        Work(TestProvider& p) : provider{ p } {}
        void Run() override
        {
            provider.Complete(sizeof(uint32_t));
        }
        void WorkCancelled() override
        {
            provider.Fail(E_ABORT);
        }
        TestProvider& provider;
    };

    uint32_t m_result;
};


TEST_CLASS(RunContextTests)
{
public:
    // Allow a 1 second grace period for tasks to cancel
    static constexpr uint32_t kTerminationTimeoutMs = 1000;

    TEST_METHOD(TerminateSimple)
    {
        RunContext root = RunContext::Root(nullptr);
        auto terminationHelper = std::make_shared<RunContextTerminationHelper>();

        root.Terminate(terminationHelper, nullptr);
        Assert::IsTrue(terminationHelper->terminationComplete.Wait(kTerminationTimeoutMs));
    }

    TEST_METHOD(TestCancellableOperation)
    {
        Event completionEvent;
        RunContext root = RunContext::Root(nullptr);

        uint64_t start = GetMilliTicks();
        uint64_t timeout{ 5000 };
        CancellableOperation::Run(root.Derive(), completionEvent, timeout);

        root.CancellationToken().Cancel();
        Assert::IsTrue(completionEvent.Wait(kTerminationTimeoutMs));
    }

    TEST_METHOD(TestNonCancellableOperation)
    {
        Event completionEvent;
        RunContext root = RunContext::Root(nullptr);      

        uint64_t start = GetMilliTicks();
        uint64_t timeout{ 1000 };
        NonCancellableOperation::Run(root.DeriveOnQueue(nullptr), completionEvent, timeout);

        root.CancellationToken().Cancel();

        // Operation is not cancellable, so it should run until completion
        Assert::IsTrue(completionEvent.Wait((DWORD)(kTerminationTimeoutMs + timeout)));

        uint64_t end = GetMilliTicks();
        Assert::IsTrue(end - timeout >= start);
    }

    TEST_METHOD(TerminateWithNonCancellableOperation)
    {
        Event completionEvent;
        RunContext root = RunContext::Root(nullptr);
        auto terminationHelper = std::make_shared<RunContextTerminationHelper>();

        uint64_t start = GetMilliTicks();
        uint64_t timeout{ 1000 };
        NonCancellableOperation::Run(root.DeriveOnQueue(nullptr), completionEvent, timeout);

        root.Terminate(terminationHelper, nullptr);

        Assert::IsTrue(completionEvent.Wait((DWORD)(kTerminationTimeoutMs)));
        Assert::IsTrue(terminationHelper->terminationComplete.Wait((DWORD)kTerminationTimeoutMs));
    }

    //TEST_METHOD(TestProviderCompletion)
    //{
    //    // TODO this test demonstrates that we aren't guaranteed XAsync Providers to be cleaned up before rc.Terminate
    //    // completes. 

    //    RunContext rc = RunContext::Root(nullptr);

    //    struct AsyncContext 
    //    {
    //        uint32_t const expectedResult{ 1337 }; // arbitrary

    //        static void CALLBACK CompletionCallback(XAsyncBlock* async)
    //        {
    //            uint32_t result{};
    //            HRESULT hr = XAsyncGetResult(async, nullptr, sizeof(uint32_t), &result, nullptr);
    //            VERIFY_SUCCEEDED(hr);
    //        }
    //    } context;
    //    
    //    XAsyncBlock async{ nullptr, &context, AsyncContext::CompletionCallback, 0 };
    //    auto provider = std::make_unique<TestProvider>(rc.DeriveOnQueue(nullptr), &async, context.expectedResult);
    //    VERIFY_SUCCEEDED(Provider::Run(UniquePtr<Provider>(provider.release())));

    //    auto terminationHelper = std::make_shared<RunContextTerminationHelper>();
    //    rc.Terminate(terminationHelper, nullptr);
    //    Assert::IsTrue(terminationHelper->terminationComplete.Wait(kTerminationTimeoutMs));
    //}
};

} // UnitTests
} // PlayFab
