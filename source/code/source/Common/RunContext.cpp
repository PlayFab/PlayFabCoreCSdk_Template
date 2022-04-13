#include "stdafx.h"
#include "RunContext.h"

namespace PlayFab
{

static uint32_t g_nextId{ 0 };

//------------------------------------------------------------------------------
// TaskQueue
//------------------------------------------------------------------------------

class TaskQueue::State : public ITerminable
{
public:
    // The only queues we should use internally should be derived from another Queue. We don't want to directly
    // submit work to a client owned queue because we want to be able to terminate queues during cleanup.
    SharedPtr<State> DeriveWorkQueue() const noexcept;
    static SharedPtr<State> DeriveWorkQueue(XTaskQueueHandle handle) noexcept;

    State(XTaskQueueHandle handle) noexcept;
    State(State const&) = delete;
    State(State&&) = delete;
    State& operator=(State const&) = delete;
    State& operator=(State&&) = delete;
    ~State();

    XTaskQueueHandle Handle() const noexcept;
    void SubmitWork(SharedPtr<ITaskQueueWork> work, uint32_t delayInMs) const noexcept;
    void Terminate(_In_opt_ SharedPtr<ITerminationListener> listener, void* context) override;

private:
    static void CALLBACK TaskQueueCallback(void* context, bool cancelled) noexcept;
    static void CALLBACK TaskQueueTerminated(void* context) noexcept;

    XTaskQueueHandle const m_handle{ nullptr };
};

TaskQueue::State::State(XTaskQueueHandle handle) noexcept :
    m_handle{ handle }
{
    assert(handle);
}

TaskQueue::State::~State()
{
    XTaskQueueCloseHandle(m_handle);
}

SharedPtr<TaskQueue::State> TaskQueue::State::DeriveWorkQueue() const noexcept
{
    return DeriveWorkQueue(m_handle);
}

SharedPtr<TaskQueue::State> TaskQueue::State::DeriveWorkQueue(XTaskQueueHandle handle) noexcept
{
    SharedPtr<State> processQueue{ nullptr };
    if (!handle)
    {
        bool haveProcessQueue = XTaskQueueGetCurrentProcessTaskQueue(&handle);
        if (haveProcessQueue)
        {
            // Wrap process queue handle so that it gets closed
            processQueue = MakeShared<State>(handle);
        }
        else
        {
            TRACE_ERROR("Client provided null XTaskQueueHandle and no default process queue is available");
            assert(false); // handle this
        }
    }

    XTaskQueuePortHandle workPort{ nullptr };
    HRESULT hr = XTaskQueueGetPort(handle, XTaskQueuePort::Work, &workPort);
    if (FAILED(hr))
    {
        TRACE_ERROR_HR(hr, "Failed to get work port from queue");
        assert(false); // handle this
    }

    XTaskQueueHandle derivedHandle{ nullptr };
    hr = XTaskQueueCreateComposite(workPort, workPort, &derivedHandle);
    if (FAILED(hr))
    {
        TRACE_ERROR_HR(hr, "Failed to create composite queue");
        assert(false);
    }

    return MakeShared<State>(derivedHandle);
}

XTaskQueueHandle TaskQueue::State::Handle() const noexcept
{
    return m_handle;
}

using TaskQueueCallbackContext = SharedPtr<ITaskQueueWork>;

void CALLBACK TaskQueue::State::TaskQueueCallback(void* context, bool cancelled) noexcept
{
    assert(context);

    UniquePtr<TaskQueueCallbackContext> callbackContext{ static_cast<TaskQueueCallbackContext*>(context) };
    if (cancelled)
    {
        (*callbackContext)->WorkCancelled();
    }
    else
    {
        (*callbackContext)->Run();
    }
}

void TaskQueue::State::SubmitWork(
    SharedPtr<ITaskQueueWork> work,
    uint32_t delayInMs
) const noexcept
{
    assert(work);
    assert(m_handle);

    UniquePtr<TaskQueueCallbackContext> context = MakeUnique<TaskQueueCallbackContext>(std::move(work));

    HRESULT hr = XTaskQueueSubmitDelayedCallback(m_handle, XTaskQueuePort::Work, delayInMs, context.get(), TaskQueueCallback);
    if (SUCCEEDED(hr))
    {
        // Will be reclaimed in TaskQueueCallback
        context.release();
    }
    else if (hr == E_ABORT)
    {
        // Queue was already terminated
        (*context)->WorkCancelled();
    }
    else
    {
        // Other errors are likely fatal
        TRACE_ERROR_HR(hr, "TaskQueue::SubmitWork failed unexpectedly");
        assert(false);
    }
}

struct XTaskQueueTerminateContext
{
    SharedPtr<ITerminationListener> listener;
    void* listenerContext;
    XTaskQueueHandle handle; // for logging purposes only, not guaranteed to be valid in terminate callback
};

void CALLBACK TaskQueue::State::TaskQueueTerminated(void* ctx) noexcept
{
    UniquePtr<XTaskQueueTerminateContext> context{ static_cast<XTaskQueueTerminateContext*>(ctx) };

    TRACE_VERBOSE("TaskQueue[id=%p] terminated", context->handle);

    if (context->listener)
    {
        ITerminationListener& listener{ *context->listener }; // we are about to move context->listener
        listener.OnTerminated(std::move(context->listener), context->listenerContext);
    }
}

void TaskQueue::State::Terminate(_In_opt_ SharedPtr<ITerminationListener> listener, void* listenerContext)
{
    TRACE_VERBOSE("TaskQueue[id=%p] terminating", m_handle);

    assert(m_handle);

    Allocator<XTaskQueueTerminateContext> a;
    UniquePtr<XTaskQueueTerminateContext> context{ new (a.allocate(1)) XTaskQueueTerminateContext{std::move(listener), listenerContext, m_handle} };

    HRESULT hr = XTaskQueueTerminate(m_handle, false, context.get(), TaskQueueTerminated);
    if (FAILED(hr))
    {
        // This likely indicates a bug, but consider the queue terminated to not block cleanup
        assert(SUCCEEDED(hr));
        TRACE_ERROR_HR(hr, "Failed to terminate queue");

        if (listener)
        {
            ITerminationListener& listenerRef{ *listener }; // we are about to move listener
            listenerRef.OnTerminated(std::move(listener), listenerContext);
        }
    }
    else
    {
        context.release();
    }
}

TaskQueue::TaskQueue(SharedPtr<State> state) noexcept :
    m_state{ std::move(state) }
{
}

TaskQueue TaskQueue::DeriveWorkQueue() const noexcept
{
    return TaskQueue{ m_state->DeriveWorkQueue() };
}

TaskQueue TaskQueue::DeriveWorkQueue(XTaskQueueHandle queueHandle) noexcept
{
    return TaskQueue{ State::DeriveWorkQueue(queueHandle) };
}

XTaskQueueHandle TaskQueue::Handle() const noexcept
{
    return m_state->Handle();
}

void TaskQueue::SubmitWork(SharedPtr<ITaskQueueWork> work, uint32_t delayInMs) const noexcept
{
    return m_state->SubmitWork(std::move(work), delayInMs);
}

void TaskQueue::Terminate(SharedPtr<ITerminationListener> listener, void* context)
{
    return m_state->Terminate(std::move(listener), context);
}

//------------------------------------------------------------------------------
// RunContext
//------------------------------------------------------------------------------

class RunContext::State : public ITerminable, public ITerminationListener, public std::enable_shared_from_this<State>
{
public:
    static SharedPtr<State> Root(XTaskQueueHandle queueHandle) noexcept;

    SharedPtr<State> Derive() noexcept;
    SharedPtr<State> DeriveOnQueue(XTaskQueueHandle queueHandle) noexcept;

    State(PlayFab::TaskQueue&& q, PlayFab::CancellationToken&& ct, SharedPtr<State> parent) noexcept;
    State(State const&) noexcept = delete;
    State(State&&) noexcept = delete;
    State& operator=(State const&) noexcept = delete;
    State& operator=(State&&) noexcept = delete;
    ~State() noexcept;

    PlayFab::TaskQueue TaskQueue() const noexcept;
    PlayFab::CancellationToken CancellationToken() const noexcept;

    void Terminate(_In_opt_ SharedPtr<ITerminationListener> listener, void* context) override;

private:
    void OnTerminated(SharedPtr<ITerminationListener>&& self, void* context) override;

    PlayFab::TaskQueue m_queue;
    PlayFab::CancellationToken m_cancellationToken;

    std::mutex m_mutex;

    enum class Status
    {
        Active,
        Terminating,
        Terminated
    };

    Vector<WeakPtr<ITerminable>> m_terminables;
    size_t m_pendingTerminations{ 0 };
    Vector<std::pair<SharedPtr<ITerminationListener>, void*>> m_terminationListeners;
    SharedPtr<State> m_parent;
    Status m_status{ Status::Active };

    // For debugging purposes only
    uint32_t m_id;
    uint32_t m_depth;
};

RunContext::State::State(PlayFab::TaskQueue&& q, PlayFab::CancellationToken&& ct, SharedPtr<State> parent) noexcept :
    m_queue{ std::move(q) },
    m_cancellationToken{ std::move(ct) },
    m_parent{ std::move(parent) },
    m_id{ g_nextId++ },
    m_depth{ m_parent ? m_parent->m_depth + 1 : 0 }
{
    TRACE_VERBOSE("%s: id[%u] depth[%u]", __FUNCTION__, m_id, m_depth);
}

RunContext::State::~State()
{
    TRACE_VERBOSE("%s: id[%u] depth[%u]", __FUNCTION__, m_id, m_depth);
}

SharedPtr<RunContext::State> RunContext::State::Root(XTaskQueueHandle queueHandle) noexcept
{
    return MakeShared<State>(TaskQueue::DeriveWorkQueue(queueHandle), CancellationToken::Root(), nullptr);
}

SharedPtr<RunContext::State> RunContext::State::Derive() noexcept
{
    SharedPtr<State> derived = MakeShared<State>(m_queue.DeriveWorkQueue(), m_cancellationToken.Derive(), shared_from_this());

    std::unique_lock<std::mutex> lock{ m_mutex };
    m_terminables.push_back(derived);

    return derived;
}

SharedPtr<RunContext::State> RunContext::State::DeriveOnQueue(XTaskQueueHandle queueHandle) noexcept
{
    SharedPtr<State> derived = MakeShared<State>(TaskQueue::DeriveWorkQueue(queueHandle), m_cancellationToken.Derive(), shared_from_this());

    std::unique_lock<std::mutex> lock{ m_mutex };
    m_terminables.push_back(derived);

    return derived;
}

PlayFab::TaskQueue RunContext::State::TaskQueue() const noexcept
{
    return m_queue;
}

PlayFab::CancellationToken RunContext::State::CancellationToken() const noexcept
{
    return m_cancellationToken;
}

void RunContext::State::Terminate(_In_opt_ SharedPtr<ITerminationListener> listener, void* context)
{
    std::unique_lock<std::mutex> lock{ m_mutex };

    // We only needed to keep m_parent for recursive termination. Once we are terminated we can release it
    m_parent.reset();

    switch (m_status)
    {
    case Status::Active:
    {
        m_status = Status::Terminating;
        if (listener)
        {
            m_terminationListeners.emplace_back(std::move(listener), context);
        }

        Vector<SharedPtr<ITerminable>> terminables;
        for (auto& weakTerminable : m_terminables)
        {
            if (auto sharedTerminable = weakTerminable.lock())
            {
                terminables.emplace_back(sharedTerminable);
            }
        }

        assert(!m_pendingTerminations);
        m_pendingTerminations = 1 + terminables.size();

        TRACE_VERBOSE("RunContext[id=%u] terminating with %u child terminables", m_id, m_pendingTerminations);

        lock.unlock();

        m_queue.Terminate(shared_from_this(), nullptr);
        for (auto& terminable : terminables)
        {
            terminable->Terminate(shared_from_this(), nullptr);
        }

        break;
    }
    case Status::Terminating:
    {
        TRACE_VERBOSE("RunContext[id=%u] terminated while termination was already in progress", m_id);

        if (listener)
        {
            m_terminationListeners.emplace_back(std::move(listener), context);
        }
        break;
    }
    case Status::Terminated:
    {
        TRACE_VERBOSE("RunContext[id=%u] already terminated", m_id);

        lock.unlock();
        if (listener)
        {
            ITerminationListener& listenerRef{ *listener }; // we are about to move listener
            listenerRef.OnTerminated(std::move(listener), context);
        }
        break;
    }
    default:
    {
        assert(false);
    }
    }
}

void RunContext::State::OnTerminated(SharedPtr<ITerminationListener>&& self, void* /*context*/)
{
    std::unique_lock<std::mutex> lock{ m_mutex };

    assert(m_pendingTerminations);
    TRACE_VERBOSE("RunContext[id=%u] terminable terminated, %u remaining", m_id, --m_pendingTerminations);

    if (!m_pendingTerminations)
    {
        m_status = Status::Terminated;

        Vector<std::pair<SharedPtr<ITerminationListener>, void*>> terminationListeners;
        std::swap(m_terminationListeners, terminationListeners);

        lock.unlock();

        // Release the reference that was held during termination
        self.reset();

        for (auto& pair : terminationListeners)
        {
            ITerminationListener& terminationListener{ *pair.first }; // we are about to move listener
            terminationListener.OnTerminated(std::move(pair.first), pair.second);
        }
    }
}

RunContext::RunContext(SharedPtr<State> state) noexcept :
    m_state{ std::move(state) }
{
}

RunContext RunContext::Root(XTaskQueueHandle backgroundQueue) noexcept
{
    return RunContext{ State::Root(backgroundQueue) };
}

RunContext RunContext::Derive() noexcept
{
    return RunContext{ m_state->Derive() };
}

RunContext RunContext::DeriveOnQueue(XTaskQueueHandle queueHandle) noexcept
{
    return RunContext{ m_state->DeriveOnQueue(queueHandle) };
}

TaskQueue RunContext::TaskQueue() const noexcept
{
    return m_state->TaskQueue();
}

CancellationToken RunContext::CancellationToken() const noexcept
{
    return m_state->CancellationToken();
}

void RunContext::Terminate(SharedPtr<ITerminationListener> listener, void* context) noexcept
{
    return m_state->Terminate(std::move(listener), context);
}

} // namespace PlayFab
