#pragma once

#include <playfab/PFGlobal.h>
#include "ServiceConfig.h"
#include "TitlePlayer.h"
#include "RunContext.h"
#include "HandleTable.h"

namespace PlayFab
{

// GlobalState singleton
class GlobalState
{
public:
    ~GlobalState() noexcept;

    static HRESULT Create(XTaskQueueHandle backgroundQueue) noexcept;
    static HRESULT Get(SharedPtr<GlobalState>& state) noexcept;
    static HRESULT CleanupAsync(XAsyncBlock* async) noexcept;

    RunContext const& RunContext() const noexcept;

    HandleTable<ServiceConfig>& ServiceConfigs() noexcept;
    HandleTable<TitlePlayer>& TitlePlayers() noexcept;

private:
    GlobalState(XTaskQueueHandle backgroundQueue) noexcept;

    static HRESULT CALLBACK CleanupAsyncProvider(XAsyncOp op, XAsyncProviderData const* data);

    RootRunContext m_runContext;
    HandleTable<ServiceConfig> m_serviceConfigs;
    HandleTable<TitlePlayer> m_titlePlayers;

    friend struct GlobalStateBootstrapper;
};

}
