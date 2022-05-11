#pragma once

#include <playfab/PFGlobal.h>
#include "RunContext.h"

namespace PlayFab
{

// TODO consider making these templated rather than just for TokenExpiredCallbacks

class TokenExpiredCallback : public ICancellationListener
{
public:
    TokenExpiredCallback(
        RunContext&& rc,
        void* context,
        PFEntityTokenExpiredCallback* callback
    ) noexcept;

    void Invoke(const char* entityId) const noexcept;

private:
    void OnCancellation() noexcept override;

    RunContext const m_rc;
    void* const m_clientContext;
    PFEntityTokenExpiredCallback* const m_clientCallback;
};



// Class to help registering, unregistering, and invoking client callbacks
template<typename CallbackT>
class CallbackManager
{
public:
    CallbackManager();
    CallbackManager(const CallbackManager&) = delete;
    CallbackManager& operator=(const CallbackManager&) = delete;
    ~CallbackManager() = default;

    PFRegistrationToken Register(SharedPtr<ClientCallback<CallbackT>>&& callback);
    void Unregister(PFRegistrationToken token);

    template<typename... Args>
    typename std::enable_if_t<std::is_void_v<std::result_of_t<CallbackT(Args...)>>> Invoke(Args... args) const;

private:
    mutable std::recursive_mutex m_mutex; // recursive to allow unregistration within callback

    Map<PFRegistrationToken, SharedPtr<ClientCallback<CallbackT>> m_callbacks;
    PFRegistrationToken m_nextToken;
};

//------------------------------------------------------------------------------
// Template implementations
//------------------------------------------------------------------------------

namespace Detail
{
// Arbitrary first token thats recognizable when debugging
PFRegistrationToken const kFirstCallbackToken = 0xBAC0000000000000;

}

template<typename CallbackT>
CallbackManager<CallbackT>::CallbackManager() : m_nextToken{ Detail::kFirstCallbackToken }
{
}

template<typename CallbackT>
PFRegistrationToken CallbackManager<CallbackT>::Register(SharedPtr<ClientCallback<CallbackT>>&& callback)
{
    std::unique_lock<std::recursive_mutex> lock{ m_mutex };

    assert(callback);

    PFRegistrationToken token{ m_nextToken++ };

    auto res = m_callbacks.emplace(token, CallbackContext{ std::move(queue), std::move(callback) });
    assert(res.second);
    UNREFERENCED_PARAMETER(res.second);

    return token;
}

template<typename CallbackT>
void CallbackManager<CallbackT>::Unregister(PFRegistrationToken token)
{
    std::unique_lock<std::recursive_mutex> lock{ m_mutex };

    assert(!(token < Detail::kFirstCallbackToken));
    assert(token < m_nextToken);

    m_callbacks.erase(token);
}

template<typename CallbackT> template<typename... Args>
typename std::enable_if_t<std::is_void_v<std::result_of_t<CallbackT(Args...)>>> CallbackManager<CallbackT>::Invoke(Args... args) const
{
    std::unique_lock<std::recursive_mutex> lock{ m_mutex };

    // Copy callbacks so that reentrant unregistration doesn't break iteration
    auto callbacks{ m_callbacks };

    for (auto& pair : callbacks)
    {
        auto& callbackContext{ pair.second };
        callbackContext.queue.RunCompletion([callbackBinder{ std::bind(callbackContext.callback, args...) }]
        {
            callbackBinder();
        });
    }
}

}
