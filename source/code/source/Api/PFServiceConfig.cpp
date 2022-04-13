#include "stdafx.h"
#include <playfab/PFServiceConfig.h>
#include "GlobalState.h"
#include "ServiceConfig.h"

using namespace PlayFab;

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

HRESULT PFServiceConfigGetConnectionString(
    _In_ PFServiceConfigHandle handle,
    _Out_ const char** connectionString
) noexcept
{
    RETURN_HR_INVALIDARG_IF_NULL(connectionString);

    SharedPtr<GlobalState> state;
    RETURN_IF_FAILED(GlobalState::Get(state));

    SharedPtr<ServiceConfig> serviceConfig;
    RETURN_IF_FAILED(state->ServiceConfigs().FromHandle(handle, serviceConfig));
    *connectionString = serviceConfig->HttpClient()->ConnectionString().data();

    return S_OK;
}

HRESULT PFServiceConfigGetTitleId(
    _In_ PFServiceConfigHandle handle,
    _Out_ const char** titleId
) noexcept
{
    RETURN_HR_INVALIDARG_IF_NULL(titleId);

    SharedPtr<GlobalState> state;
    RETURN_IF_FAILED(GlobalState::Get(state));

    SharedPtr<ServiceConfig> serviceConfig;
    RETURN_IF_FAILED(state->ServiceConfigs().FromHandle(handle, serviceConfig));
    *titleId = serviceConfig->TitleId().data();

    return S_OK;
}

HRESULT PFServiceConfigGetPlayerAccountPoolId(
    _In_ PFServiceConfigHandle handle,
    _Out_ const char** playerAccountPoolId
) noexcept
{
    RETURN_HR_INVALIDARG_IF_NULL(playerAccountPoolId);

    SharedPtr<GlobalState> state;
    RETURN_IF_FAILED(GlobalState::Get(state));

    SharedPtr<ServiceConfig> serviceConfig;
    RETURN_IF_FAILED(state->ServiceConfigs().FromHandle(handle, serviceConfig));
    *playerAccountPoolId = serviceConfig->PlayerAccountPoolId().data();

    return S_OK;
}