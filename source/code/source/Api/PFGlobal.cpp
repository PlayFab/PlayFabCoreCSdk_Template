#include "stdafx.h"
#include "GlobalState.h"
#include "BaseModel.h"
#include "ServiceConfig.h"
#include <httpClient/httpClient.h>

using namespace PlayFab;

STDAPI PFMemSetFunctions(
    _In_opt_ PFMemAllocFunction* memAllocFunc,
    _In_opt_ PFMemFreeFunction* memFreeFunc
) noexcept
{
    RETURN_IF_FAILED(PlayFab::Detail::SetMemoryHooks(memAllocFunc, memFreeFunc));

    // Try to set the memory hooks for libHttpClient as well. If it has already be initialized, there is nothing we can do
    HRESULT hr = HCMemSetFunctions([](size_t size, HCMemoryType)
        {
            return PlayFab::Alloc(size);
        },
        [](void* pointer, HCMemoryType)
        {
            return PlayFab::Free(pointer);
        });

    if (FAILED(hr) && hr != E_HC_ALREADY_INITIALISED)
    {
        return hr;
    }

    return S_OK;
}

STDAPI PFMemGetFunctions(
    _Out_ PFMemAllocFunction** memAllocFunc,
    _Out_ PFMemFreeFunction** memFreeFunc
) noexcept
{
    RETURN_HR_INVALIDARG_IF_NULL(memAllocFunc);
    RETURN_HR_INVALIDARG_IF_NULL(memFreeFunc);

    auto& hooks = PlayFab::Detail::GetMemoryHooks();
    *memAllocFunc = hooks.alloc;
    *memFreeFunc = hooks.free;

    return S_OK;
}

HRESULT PFInitialize(
    _In_opt_ XTaskQueueHandle backgroundQueue
) noexcept
{
    return GlobalState::Create(backgroundQueue);
}

HRESULT PFUninitializeAsync(
    _In_ XAsyncBlock* async
) noexcept
{
    return GlobalState::CleanupAsync(async);
}
