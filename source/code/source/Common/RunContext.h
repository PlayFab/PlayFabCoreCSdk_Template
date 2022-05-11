// Run context is the context needed to perform and XAsync operation

#pragma once

#include "XTaskQueue.h"
#include "CancellationToken.h"

namespace PlayFab
{

struct ITerminationListener
{
    virtual ~ITerminationListener() = default;

    // This signature looks a bit strange, but is intentional. Termination typically happens during cleanup, so 
    // we need to be very precise about ownership and cleanup timing. When Terminating, shared ownership
    // of the ITerminationListener is given to the ITerminable. When it has finished terminating, it should relinquish
    // that ownership as part of invoking OnTerminated rather than holding onto the reference until after OnTerminated
    // returns. This allows the ITerminationListener to be destroyed within the OnTerminated callback.
    virtual void OnTerminated(_In_ SharedPtr<ITerminationListener>&& self, void* context) = 0;
};

struct ITerminable
{
    virtual ~ITerminable() = default;
    virtual void Terminate(_In_opt_ SharedPtr<ITerminationListener> listener, void* context) = 0;
};

// Interface for work submitted to TaskQueues
struct ITaskQueueWork
{
    virtual void Run() = 0;
    virtual void WorkCancelled() {}
};

// RAII wrapper around XTaskQueueHandle
class TaskQueue : public ITerminable
{
public:
    TaskQueue DeriveWorkQueue() const noexcept;
    static TaskQueue DeriveWorkQueue(XTaskQueueHandle handle) noexcept;

    TaskQueue(const TaskQueue& other) noexcept = default;
    TaskQueue(TaskQueue&& other) noexcept = default;
    TaskQueue& operator=(TaskQueue const& other) noexcept = delete;
    TaskQueue& operator=(TaskQueue&& other) noexcept = delete;
    ~TaskQueue() noexcept = default;

    XTaskQueueHandle Handle() const noexcept;
    void SubmitWork(SharedPtr<ITaskQueueWork> work, uint32_t delayInMs = 0) const noexcept;
    void SubmitCompletion(SharedPtr<ITaskQueueWork> completion) const noexcept;
    void Terminate(_In_opt_ SharedPtr<ITerminationListener> listener, void* context) override;

private:
    class State;

    TaskQueue(SharedPtr<State> state) noexcept;

    SharedPtr<State> m_state;
};

class RunContext : public ITerminable
{
public:
    static RunContext Root(XTaskQueueHandle backgroundQueue) noexcept;
    RunContext Derive() noexcept;
    RunContext DeriveOnQueue(XTaskQueueHandle queueHandle) noexcept;

    RunContext(RunContext const&) noexcept = default;
    RunContext(RunContext&&) noexcept = default;
    RunContext& operator=(RunContext const&) noexcept = delete;
    RunContext& operator=(RunContext&&) noexcept = delete;
    ~RunContext() noexcept = default;

    PlayFab::TaskQueue TaskQueue() const noexcept;
    PlayFab::CancellationToken CancellationToken() const noexcept;
    void Terminate(_In_opt_ SharedPtr<ITerminationListener> listener, void* context) noexcept override;

private:
    class State;

    RunContext(SharedPtr<State> state) noexcept;

    SharedPtr<State> m_state;
};

}
