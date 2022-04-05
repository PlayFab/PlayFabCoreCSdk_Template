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

HRESULT PFServiceConfigCreateHandle(
    _In_z_ const char* connectionString,
    _In_z_ const char* titleId,
    _In_z_ const char* playerAccountPoolId,
    _Out_ PFServiceConfigHandle* serviceConfigHandle
) noexcept
{
    RETURN_HR_INVALIDARG_IF_NULL(connectionString);
    RETURN_HR_INVALIDARG_IF_NULL(titleId);
    RETURN_HR_INVALIDARG_IF_NULL(playerAccountPoolId);
    RETURN_HR_INVALIDARG_IF_NULL(serviceConfigHandle);

    SharedPtr<GlobalState> state;
    RETURN_IF_FAILED(GlobalState::Get(state));

    auto serviceConfig = MakeShared<PlayFab::ServiceConfig>(connectionString, titleId, playerAccountPoolId);
    return state->ServiceConfigs().MakeHandle(std::move(serviceConfig), *serviceConfigHandle);
}

HRESULT PFServiceConfigDuplicateHandle(
    PFServiceConfigHandle handle,
    PFServiceConfigHandle* duplicatedHandle
) noexcept
{
    RETURN_HR_INVALIDARG_IF_NULL(duplicatedHandle);

    SharedPtr<GlobalState> state;
    RETURN_IF_FAILED(GlobalState::Get(state));

    SharedPtr<ServiceConfig> serviceConfig;
    RETURN_IF_FAILED(state->ServiceConfigs().FromHandle(handle, serviceConfig));
    return state->ServiceConfigs().MakeHandle(std::move(serviceConfig), *duplicatedHandle);
}

void PFServiceConfigCloseHandle(
    PFServiceConfigHandle handle
) noexcept
{
    SharedPtr<GlobalState> state;
    HRESULT hr = GlobalState::Get(state);

    if (SUCCEEDED(hr))
    {
        state->ServiceConfigs().CloseHandle(handle);
    }
}
