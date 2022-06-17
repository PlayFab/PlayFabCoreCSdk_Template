#include "stdafx.h"
#include "playfab/PFPlatform.h"
#include "Platform/Platform.h"
#include "GlobalState.h"

using namespace PlayFab;

PF_API PFPlatformLocalStorageSetHandlers(
    _In_opt_ XTaskQueueHandle queue,
    _In_opt_ void* context,
    _In_ PFPlatformLocalStorageReadAsyncHandler* readHandler,
    _In_ PFPlatformLocalStorageWriteAsyncHandler* writeHandler,
    _In_ PFPlatformLocalStorageClearAsyncHandler* clearHandler
) noexcept
{
    SharedPtr<GlobalState> state;
    GlobalState::Get(state);
    RETURN_HR_IF(E_PF_ALREADY_INITIALIZED, state);

    Detail::LocalStorageHandlers handlers{ queue, context, readHandler, writeHandler, clearHandler };
    return PlayFab::Detail::SetLocalStorageHandlers(handlers);
}
