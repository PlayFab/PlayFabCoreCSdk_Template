#include "stdafx.h"
#include "Platform.h"
#include "LocalStorageHandlers.h"

namespace PlayFab
{
namespace Detail
{

LocalStorageHandlers& GetLocalStorageHandlers()
{
    static LocalStorageHandlers s_handlers{ nullptr, nullptr, DefaultLocalStorageReadAsync, DefaultLocalStorageWriteAsync, DefaultLocalStorageClearAsync};
    return s_handlers;
}

HRESULT SetLocalStorageHandlers(LocalStorageHandlers& newHandlers)
{
    auto& handlers = GetLocalStorageHandlers();

    if (newHandlers.write && newHandlers.read && newHandlers.clear)
    {
        handlers.write = newHandlers.write;
        handlers.read = newHandlers.read;
        handlers.clear = newHandlers.clear;
        handlers.context = newHandlers.context;
    }
    else
    {
        return E_INVALIDARG;
    }
    return S_OK;
}

}
}
