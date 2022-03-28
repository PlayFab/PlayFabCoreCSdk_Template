// Token that coordinates cancellation between consumers and implementers of asyncronous operations

#pragma once

namespace PlayFab
{

class CancellationToken;

struct ICancellationListener
{
    // Choosing to not pass the CancellationToken to this callback because there are some edge cases where the token
    // is being destroyed at the same time it is notifying it's listeners that are tricky to handle properly.
    // Additionally, it's not required to unregister from notifications after being notified of cancellation since the 
    // Token always clears its list of listeners after notifying them.
    virtual void OnCancellation() noexcept = 0;

protected:
    ~ICancellationListener() {};
};

class CancellationToken
{
public:
    CancellationToken Derive() const noexcept;

    CancellationToken() noexcept; // Make it more explicit to make a root token
    CancellationToken(CancellationToken const& other) noexcept = default;
    CancellationToken(CancellationToken&& other) noexcept = default;
    CancellationToken& operator=(CancellationToken const& other) noexcept = delete;
    CancellationToken& operator=(CancellationToken&& other) noexcept = delete;
    ~CancellationToken() noexcept = default;

    // returns true if there were listeners that have been cancelled
    bool Cancel() noexcept;

    // Register a cancellation listener. Returns true if cancellation has already happened,
    // and the listener will not be invoked in that case
    bool RegisterForNotificationAndCheck(ICancellationListener& listener) noexcept;
    bool UnregisterForNotificationAndCheck(ICancellationListener& listener) noexcept;

private:
    class SharedState;

    CancellationToken(SharedPtr<SharedState> state) noexcept;

    SharedPtr<SharedState> m_state;
};

}
