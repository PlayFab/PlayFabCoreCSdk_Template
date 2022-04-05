#include "stdafx.h"
#include "CancellationToken.h"

namespace PlayFab
{

class CancellationToken::SharedState : public ICancellationListener
{
public:
    static SharedPtr<SharedState> Derive(SharedPtr<SharedState> parent) noexcept;

    SharedState() = default;
    SharedState(SharedState const&) = delete;
    SharedState(SharedState&&) = delete;
    SharedState& operator=(SharedState const&) = delete;
    SharedState& operator=(SharedState&&) = delete;
    ~SharedState() noexcept;

    bool Cancel() noexcept;

    bool RegisterForNotificationAndCheck(ICancellationListener& listener);
    bool UnregisterForNotificationAndCheck(ICancellationListener& listener) noexcept;

private:
    // ICancellationListener
    void OnCancellation() noexcept override;

    std::recursive_mutex m_mutex; // intentionally recursive
    std::atomic<bool> m_cancelled{ false };
    Vector<ICancellationListener*> m_listeners; // non-owning
    Vector<SharedPtr<SharedState>> m_children;
    SharedPtr<SharedState> m_parent;
};

SharedPtr<CancellationToken::SharedState> CancellationToken::SharedState::Derive(SharedPtr<SharedState> parent) noexcept
{
    SharedPtr<SharedState> child = MakeShared<SharedState>();

    child->m_cancelled = parent->RegisterForNotificationAndCheck(*child);
    if (!child->m_cancelled)
    {
        parent->m_children.push_back(child);
        child->m_parent = std::move(parent);
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

bool CancellationToken::SharedState::Cancel() noexcept
{
    // We need to hold a reference to ourselves to handle some edge cases (see
    // below) and we need the reference to be released after the lock to ensure
    // that we don't destroy a locked mutex (or try to unlock a destroyed mutex)
    // so we define the variable here before doing anything else and will fill
    // it in as appropriate later
    
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

    // No longer need reference to children
    m_children.clear();

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

    auto childIt = std::find_if(m_children.begin(), m_children.end(), [&](auto& child) { return child.get() == &listener; });
    if (childIt != m_children.end())
    {
        m_children.erase(childIt);
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

CancellationToken::CancellationToken() noexcept :
    m_state{ MakeShared<SharedState>() }
{
}

CancellationToken::CancellationToken(SharedPtr<SharedState> state) noexcept :
    m_state{ std::move(state) }
{
}

CancellationToken CancellationToken::Derive() const noexcept
{
    return CancellationToken{ SharedState::Derive(m_state) };
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