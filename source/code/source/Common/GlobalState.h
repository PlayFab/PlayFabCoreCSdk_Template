#pragma once

#include <playfab/PFGlobal.h>
#include "HttpClient.h"

namespace PlayFab
{

class GlobalState
{
public:
    GlobalState(String&& titleId, _In_opt_z_ const char* secretKey, _In_opt_z_ const char* connectionString, _In_opt_ XTaskQueueHandle backgroundQueue);
    virtual ~GlobalState() = default;

public:
    String const& TitleId() const;
    SharedPtr<HttpClient const> HttpClient() const;
    SharedPtr<String const> SecretKey() const;

private:
    String const m_titleId;
    SharedPtr<PlayFab::HttpClient> m_httpClient;
    SharedPtr<String> m_secretKey;
    TaskQueue m_backgroundQueue;
};

}

struct PFGlobalState
{
    PlayFab::SharedPtr<PlayFab::GlobalState> state;

    static HRESULT Create(
        _In_z_ const char* titleId,
        _In_opt_z_ const char* secretKey,
        _In_opt_z_ const char* connectionString,
        _In_opt_ XTaskQueueHandle backgroundQueue,
        _Outptr_ PFStateHandle* stateHandle
    );

    HRESULT CleanupAsync(XAsyncBlock* async);

private:
    PFGlobalState(_In_z_ const char* titleId, _In_opt_z_ const char* secretKey, _In_opt_z_ const char* connectionString, _In_opt_ XTaskQueueHandle backgroundQueue);
};
