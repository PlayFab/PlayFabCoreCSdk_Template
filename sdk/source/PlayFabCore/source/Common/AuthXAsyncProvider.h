#pragma once

#include <XAsyncProviderBase.h>
#include "TitlePlayer.h"
#include "GlobalState.h"

namespace PlayFab
{

// XAsyncProvider for PlayFab auth API calls
template<typename CallT>
class AuthXAsyncProvider : public XAsyncProviderBase
{
private:
    using ResultT = typename Detail::UnwrapAsyncT<typename std::result_of_t<CallT(SharedPtr<GlobalState const>, RunContext)>>;
public:
    static_assert(std::is_assignable_v<SharedPtr<Entity>, ResultT>, "CallT must return a SharedPt<Entity>");

    template<size_t n>
    AuthXAsyncProvider(SharedPtr<GlobalState> state, XAsyncBlock* async, const char(&identityName)[n], CallT authCall)
        : XAsyncProviderBase{ state->RunContext().DeriveOnQueue(async->queue), async, identityName },
        m_state{ std::move(state) },
        m_call{ authCall }
    {
    }

protected:
    // Always kick of the API call during XAsyncOp::Begin so we don't have to worry about lifetime of request
    // and API objects (even though they are hidden as part of a std::bind)
    HRESULT Begin(RunContext runContext) override
    {
        m_call(m_state, std::move(runContext)).Finally([this](Result<SharedPtr<TitlePlayer>> result)
        {
            if (Succeeded(result))
            {
                TRACE_VERBOSE("AuthCallProvider[ID=%s] Call suceeded (hr=0x%08x)", identityName, result.hr);
                HRESULT hr = this->m_state->TitlePlayers().MakeHandle(result.ExtractPayload(), m_titlePlayerHandle);
                if (FAILED(hr))
                {
                    this->Fail(hr);
                }
                else
                {
                    this->Complete(sizeof(PFTitlePlayerHandle));
                }
            }
            else
            {
                TRACE_ERROR("AuthCallProvider[ID=%s] Call failed with message \"%s\" (hr=0x%08x)", identityName, result.errorMessage.data(), result.hr);
                this->Fail(result.hr);
            }
        });

        return S_OK;
    }

    HRESULT GetResult(void* buffer, size_t bufferSize) override
    {
        UNREFERENCED_PARAMETER(bufferSize);
        assert(bufferSize == sizeof(PFTitlePlayerHandle));
        auto titlePlayerHandlePtr = static_cast<PFTitlePlayerHandle*>(buffer);
        *titlePlayerHandlePtr = m_titlePlayerHandle;
        return S_OK;
    }

private:
    SharedPtr<GlobalState> m_state;
    CallT m_call;
    PFTitlePlayerHandle m_titlePlayerHandle{ nullptr };
};

template<typename CallT, size_t n>
UniquePtr<AuthXAsyncProvider<CallT>> MakeAuthProvider(SharedPtr<GlobalState> state, XAsyncBlock* async, const char(&identityName)[n], CallT authCall)
{
    return MakeUnique<AuthXAsyncProvider<CallT>>(std::move(state), async, identityName, std::move(authCall));
}

}
