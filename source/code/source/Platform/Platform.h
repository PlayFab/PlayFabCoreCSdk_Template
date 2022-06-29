#pragma once

#include <playfab/PFPlatform.h>

namespace PlayFab
{
namespace Detail
{

struct LocalStorageHandlers
{
    XTaskQueueHandle queueHandle;
    void* context;
    PFPlatformLocalStorageReadAsyncHandler* read;
    PFPlatformLocalStorageWriteAsyncHandler* write;
    PFPlatformLocalStorageClearAsyncHandler* clear;
};

LocalStorageHandlers& GetLocalStorageHandlers();
HRESULT SetLocalStorageHandlers(LocalStorageHandlers& handlers);

}

}
