#include "stdafx.h"
#include "RunContext.h"

namespace PlayFab
{

class RunContextTracker
{
public:
    RunContextTracker() = default;

    void Register(RunContext const& rc) noexcept;
    void Unregister(RunContext const& rc) noexcept;

    void Terminate(TerminationCallback* callback, void* context) noexcept;

private:
    mutable std::mutex m_mutex;

    Set<RunContext const*> m_trackedContexts; // may not even need to track but could be used for sanity checks/debugging
    TerminationCallback* m_terminationCallback{ nullptr };
    void* m_terminationCallbackContext{ nullptr };
};

void RunContextTracker::Register(RunContext const& rc) noexcept
{
    // TODO do we need to check for termination here?
    std::unique_lock<std::mutex> lock{ m_mutex };
    m_trackedContexts.insert(&rc);
}

void RunContextTracker::Unregister(RunContext const& rc) noexcept
{
    std::unique_lock<std::mutex> lock{ m_mutex };
    m_trackedContexts.erase(&rc);

    // If this was the last RunContext and we've terminated, complete the termination AsyncOp
    if (m_terminationCallback && m_trackedContexts.empty())
    {
        TerminationCallback* callback{ nullptr };
        std::swap(m_terminationCallback, callback);
        lock.unlock();
        callback(m_terminationCallbackContext);
    }
}

void RunContextTracker::Terminate(TerminationCallback* callback, void* context) noexcept
{
    std::unique_lock<std::mutex> lock{ m_mutex };

    assert(!m_terminationCallback);

    if (!m_trackedContexts.empty())
    {
        m_terminationCallback = callback;
        m_terminationCallbackContext = context;
    }
    else
    {
        lock.unlock();
        callback(context);
    }
}

RunContext::RunContext(PlayFab::TaskQueue&& q, PlayFab::CancellationToken&& ct, SharedPtr<RunContextTracker> tracker) noexcept :
    m_queue{ std::move(q) },
    m_cancellationToken{ std::move(ct) },
    m_tracker{ tracker }
{
    tracker->Register(*this);
}

RunContext::RunContext(RunContext&& other) noexcept :
    m_queue{ std::move(other.m_queue) },
    m_cancellationToken{ std::move(other.m_cancellationToken) },
    m_tracker{ other.m_tracker }
{
    m_tracker->Register(*this);
}

RunContext::~RunContext() noexcept
{
    m_tracker->Unregister(*this);
}

RunContext RunContext::Derive() const noexcept
{
    return RunContext{ m_queue.DeriveWorkerQueue(), m_cancellationToken.Derive(), m_tracker };
}

RunContext RunContext::DeriveOnQueue(XTaskQueueHandle queueHandle) const noexcept
{
    return RunContext{ TaskQueue::DeriveWorkerQueue(queueHandle), m_cancellationToken.Derive(), m_tracker };
}

PlayFab::TaskQueue const& RunContext::TaskQueue() const noexcept
{
    return m_queue;
}

PlayFab::CancellationToken RunContext::CancellationToken() const noexcept
{
    return m_cancellationToken;
}

HRESULT RunContext::TerminateTaskQueue() noexcept
{
    // TODO handle failure here? 'this' lifetime not guaranteed
    return m_queue.Terminate(false, [](void* context)
    {
        RunContext& rc{ *static_cast<RunContext*>(context) };
        rc.m_tracker->Unregister(rc);
    }, this);
}

RootRunContext::RootRunContext(XTaskQueueHandle queueHandle) noexcept :
    RunContext{ TaskQueue::DeriveWorkerQueue(queueHandle), PlayFab::CancellationToken{}, MakeShared<RunContextTracker>() }
{
}

void RootRunContext::Terminate(TerminationCallback* callback, void* context) noexcept
{
    // Cancel all operations if they haven't been cancelled already
    CancellationToken().Cancel();

    // Unregister root then wait for all derived RunContexts to be cleaned up
    m_tracker->Unregister(*this);
    m_tracker->Terminate(callback, context);
}

}
