// Run context is the context needed to perform and XAsync operation

#pragma once

#include "TaskQueue.h"
#include "CancellationToken.h"

namespace PlayFab
{

class RunContextTracker;

class RunContext
{
public:
    RunContext Derive() const noexcept;
    RunContext DeriveOnQueue(XTaskQueueHandle queueHandle) const noexcept;

    RunContext(RunContext const&) noexcept = delete;
    RunContext(RunContext&&) noexcept;
    RunContext& operator=(RunContext const&) noexcept = delete;
    RunContext& operator=(RunContext&&) noexcept = delete;
    virtual ~RunContext() noexcept;

    PlayFab::TaskQueue const& TaskQueue() const noexcept;
    PlayFab::CancellationToken CancellationToken() const noexcept;

protected:
    RunContext(PlayFab::TaskQueue&& q, PlayFab::CancellationToken&& ct, SharedPtr<RunContextTracker> tracker) noexcept;

private:
    PlayFab::TaskQueue m_queue;
    PlayFab::CancellationToken m_cancellationToken;

protected:
    SharedPtr<RunContextTracker> m_tracker;
};

using TerminationCallback = void CALLBACK(void* context);

class RootRunContext : public RunContext
{
public:
    RootRunContext(XTaskQueueHandle backgroundQueue) noexcept;

    // TODO figure out best signature here. Since this will be called during clean up, we need strong
    // guarantees that SDK allocations are freed before the callback is fired.
    // Might also want to allow specification of of queue on which the callback will be fired
    void Terminate(TerminationCallback* callback, void* context) noexcept;
};

}
