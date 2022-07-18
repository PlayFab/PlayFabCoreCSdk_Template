// Run context is the context needed to perform and XAsync operation

#pragma once

#include "XTaskQueue.h"
#include "CancellationToken.h"

namespace PlayFab
{

struct ITerminationListener
{
    virtual ~ITerminationListener() = default;

    // When Terminating, ownership of the termination listener should be transferred back to the termination lister
    // as part of invoking the OnTerminated callback. This allows listener object to be destroyed within the OnTerminated callback.
    virtual void OnTerminated(_In_ SharedPtr<ITerminationListener> self, void* context) = 0;
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

// Wrapper to enable submitting arbitrary lambdas to TaskQueues
template<typename TCallback>
class TaskQueueWork : public ITaskQueueWork
{
public:
    TaskQueueWork(TCallback&& callback);

    // ITaskQueueWork
    void Run() override;

private:
    TCallback m_callback;
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
    template<typename TCallback, typename std::enable_if_t<!std::is_assignable_v<SharedPtr<ITaskQueueWork>, TCallback>>* = 0>
    void SubmitWork(TCallback work, uint32_t delayInMs = 0) const noexcept;

    void SubmitCompletion(SharedPtr<ITaskQueueWork> completion) const noexcept;
    template<typename TCallback, typename std::enable_if_t<!std::is_assignable_v<SharedPtr<ITaskQueueWork>, TCallback>>* = 0>
    void SubmitCompletion(TCallback completion) const noexcept;

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

    // RunContext::Terminate should be called exactly once during PFCleanup. Allowing multiple terminations if a single
    // RunContext prevents the RunContext from guaranteeing that it has completely cleaning up its state prior to each
    // TerminationListener being notified of termination.
    void Terminate(_In_ SharedPtr<ITerminationListener> listener, _In_opt_ void* context) noexcept override;

private:
    class State;

    RunContext(SharedPtr<State> state) noexcept;

    SharedPtr<State> m_state;
};

//------------------------------------------------------------------------------
// Template implementations
//------------------------------------------------------------------------------
template<typename TCallback>
TaskQueueWork<TCallback>::TaskQueueWork(TCallback&& callback) : m_callback{ std::move(callback) }
{
}

// ITaskQueueWork
template<typename TCallback>
void TaskQueueWork<TCallback>::Run()
{
    m_callback();
}

template<typename TCallback, typename std::enable_if_t<!std::is_assignable_v<SharedPtr<ITaskQueueWork>, TCallback>>*>
void TaskQueue::SubmitWork(TCallback work, uint32_t delayInMs) const noexcept
{
    SubmitWork(MakeShared<TaskQueueWork<TCallback>>(std::move(work)), delayInMs);
}

template<typename TCallback, typename std::enable_if_t<!std::is_assignable_v<SharedPtr<ITaskQueueWork>, TCallback>>*>
void TaskQueue::SubmitCompletion(TCallback completion) const noexcept
{
    SubmitCompletion(MakeShared<TaskQueueWork<TCallback>>(std::move(completion)));
}

}
