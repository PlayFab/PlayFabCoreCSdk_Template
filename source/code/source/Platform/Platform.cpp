#include "stdafx.h"
#include "Platform.h"
#include "LocalStorageHandlers.h"

namespace PlayFab
{
namespace Detail
{

PFLocalStorageHooks& GetLocalStorageHandlers()
{
    static PFLocalStorageHooks s_handlers{ nullptr, DefaultLocalStorageReadAsync, DefaultLocalStorageWriteAsync, DefaultLocalStorageClearAsync, nullptr };
    return s_handlers;
}

HRESULT SetLocalStorageHandlers(PFLocalStorageHooks& newHandlers)
{
    auto& handlers = GetLocalStorageHandlers();

    if (newHandlers.write && newHandlers.read && newHandlers.clear)
    {
        handlers = newHandlers;
    }
    else
    {
        return E_INVALIDARG;
    }
    return S_OK;
}

}
}
