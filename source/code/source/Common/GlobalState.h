#pragma once

#include <playfab/PFGlobal.h>
#include <playfab/PFServiceConfig.h>
#include <playfab/PFTitlePlayer.h>
#include "ServiceConfig.h"
#include "TitlePlayer.h"
#include "HandleTable.h"
#include "TokenExpiredHandler.h"

namespace PlayFab
{

using ServiceConfigHandleTable = HandleTable<PFServiceConfigHandle, ServiceConfig>;
using TitlePlayerHandleTable = HandleTable<PFTitlePlayerHandle, TitlePlayer>;

// GlobalState singleton
class GlobalState : public ITerminationListener
{
public:
    ~GlobalState() noexcept;

    static HRESULT Create(XTaskQueueHandle backgroundQueue) noexcept;
    static HRESULT Get(SharedPtr<GlobalState>& state) noexcept;
    static HRESULT CleanupAsync(XAsyncBlock* async) noexcept;

    RunContext RunContext() const noexcept;
    ServiceConfigHandleTable& ServiceConfigs() noexcept;
    TitlePlayerHandleTable& TitlePlayers() noexcept;
    TokenExpiredHandler TokenExpiredHandler() const noexcept;

private:
    GlobalState(XTaskQueueHandle backgroundQueue) noexcept;

    void OnTerminated(SharedPtr<ITerminationListener>&& self, void* context) noexcept override;
    static HRESULT CALLBACK CleanupAsyncProvider(XAsyncOp op, XAsyncProviderData const* data);

    PlayFab::RunContext m_runContext;
    ServiceConfigHandleTable m_serviceConfigs;
    TitlePlayerHandleTable m_titlePlayers;
    PlayFab::TokenExpiredHandler m_tokenExpiredHandler;

    friend struct GlobalStateBootstrapper;
};

}
