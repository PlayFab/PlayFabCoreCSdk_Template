#include "stdafx.h"
#include <playfab/core/PFCore.h>
#include "GlobalState.h"

using namespace PlayFab;

PF_API PFInitialize(
    _In_opt_ XTaskQueueHandle backgroundQueue
) noexcept
{
    return GlobalState::Create(backgroundQueue);
}

PF_API PFUninitializeAsync(
    _In_ XAsyncBlock* async
) noexcept
{
    return GlobalState::CleanupAsync(async);
}
