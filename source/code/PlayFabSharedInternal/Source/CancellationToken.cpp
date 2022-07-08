#include "pch.h"
#include "CancellationToken.h"

namespace PlayFab
{

class CancellationToken::SharedState : public ICancellationListener, public std::enable_shared_from_this<SharedState>
{
public:
    SharedPtr<SharedState> Derive() noexcept;

    SharedState() = default;
    SharedState(SharedState const&) = delete;
    SharedState(SharedState&&) = delete;
    SharedState& operator=(SharedState const&) = delete;
    SharedState& operator=(SharedState&&) = delete;
    ~SharedState() noexcept;

    bool IsCanceled() const noexcept;

    bool Cancel() noexcept;

    bool RegisterForNotificationAndCheck(ICancellationListener& listener);
    bool UnregisterForNotificationAndCheck(ICancellationListener& listener) noexcept;

private:
    // ICancellationListener
    void OnCancellation() noexcept override;

    mutable std::recursive_mutex m_mutex; // intentionally recursive
    std::atomic<bool> m_cancelled{ false };
    Vector<ICancellationListener*> m_listeners; // non-owning
    SharedPtr<SharedState> m_parent;
};

SharedPtr<CancellationToken::SharedState> CancellationToken::SharedState::Derive() noexcept
{
    SharedPtr<SharedState> child = MakeShared<SharedState>();
    child->m_cancelled = this->RegisterForNotificationAndCheck(*child);

    if (!child->m_cancelled)
    {
        // We only need a reference to parent if we aren't already cancelled
        child->m_parent = shared_from_this();
    }

    return child;
}

CancellationToken::SharedState::~SharedState() noexcept
{
    // We need to read m_parent under a lock as we could be racing with
    // OnCancellation, we must also not hold the lock when calling into
    // UnregisterForNotifications as that would invert the lock order and lead
    // to deadlocks.
    // The parent's lock in UnregisterForNotifications is what ensures that this
    // object (the child) cannot be destroyed while OnCancellation is running.

    SharedPtr<CancellationToken::SharedState> parent;
    {
        std::unique_lock<std::recursive_mutex> lock{ m_mutex };
        std::swap(m_parent, parent);
    }

    if (parent)
    {
        bool wasCanceled = parent->UnregisterForNotificationAndCheck(*this);

        // If the parent returns that is was canceled, we should also be
        // canceled (the reverse is not true, the child could be canceled for
        // its own reasons)
        assert(!wasCanceled || m_cancelled);
        UNREFERENCED_PARAMETER(wasCanceled);
    }
}

bool CancellationToken::SharedState::IsCanceled() const noexcept
{
    std::unique_lock<std::recursive_mutex> lock{ m_mutex };
    return m_cancelled;
}

bool CancellationToken::SharedState::Cancel() noexcept
{
    // Whoever is calling us has a strong reference but we still want to take a
    // strong reference to ourselves just in case they let go of us in the
    // callback
    SharedPtr<SharedState> self{ shared_from_this() };

    std::unique_lock<std::recursive_mutex> lock{ m_mutex };

    // If we've already been cancelled, nothing to do
    if (m_cancelled.exchange(true))
    {
        return false;
    }

    // Intentionally hold the lock while notifying to avoid races with unregister

    // Move the listeners in a local to clear the list
    Vector<ICancellationListener*> listeners{};
    std::swap(listeners, m_listeners);

    for (auto l : listeners)
    {
        // We do not have ownership of l, but we do have an existance guarantee
        // thanks to the mutual exclusion of this method and
        // 'UnregisterForNotificationAndCheck'
        // l could be destroyed after 'OnCancellation' returns
        l->OnCancellation();
    }

    return !listeners.empty();
}

bool CancellationToken::SharedState::RegisterForNotificationAndCheck(ICancellationListener& listener)
{
    std::unique_lock<std::recursive_mutex> lock{ m_mutex };

    // We return the current cancellation state as part of this function so that
    // callers can know if the callbacks will be invoked later or not

    if (m_cancelled)
    {
        return true;
    }

    m_listeners.push_back(&listener);

    return false;
}

bool CancellationToken::SharedState::UnregisterForNotificationAndCheck(ICancellationListener& listener) noexcept
{
    std::unique_lock<std::recursive_mutex> lock{ m_mutex };

    auto it = std::find(m_listeners.begin(), m_listeners.end(), &listener);
    if (it != m_listeners.end())
    {
        m_listeners.erase(it);
    }

    return m_cancelled;
}


void CancellationToken::SharedState::OnCancellation() noexcept
{
    // The parent's lock in UnregisterForNotifications is what ensures that this
    // object (the child) cannot be destroyed while OnCancellation is running.

    {
        std::unique_lock<std::recursive_mutex>{ m_mutex };

        // Automatically unregistered by the parent
        m_parent.reset();
    }

    Cancel();
}

CancellationToken::CancellationToken(SharedPtr<SharedState> state) noexcept :
    m_state{ std::move(state) }
{
}

CancellationToken CancellationToken::Root() noexcept
{
    return CancellationToken{ MakeShared<SharedState>() };
}

CancellationToken CancellationToken::Derive() const noexcept
{
    return CancellationToken{ m_state->SharedState::Derive() };
}

bool CancellationToken::IsCancelled() const noexcept
{
    return m_state->IsCanceled();
}

bool CancellationToken::Cancel() noexcept
{
    return m_state->Cancel();
}

bool CancellationToken::RegisterForNotificationAndCheck(ICancellationListener& listener) noexcept
{
    return m_state->RegisterForNotificationAndCheck(listener);
}

bool CancellationToken::UnregisterForNotificationAndCheck(ICancellationListener& listener) noexcept
{
    return m_state->UnregisterForNotificationAndCheck(listener);
}

}