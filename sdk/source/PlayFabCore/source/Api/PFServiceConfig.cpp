#include "stdafx.h"
#include <playfab/core/PFServiceConfig.h>
#include "GlobalState.h"
#include "ServiceConfig.h"
#include "ApiHelpers.h"

using namespace PlayFab;

PF_API PFServiceConfigCreateHandle(
    _In_z_ const char* connectionString,
    _In_z_ const char* titleId,
    _In_z_ const char* playerAccountPoolId,
    _Out_ PFServiceConfigHandle* serviceConfigHandle
) noexcept
{
    return ApiImpl(API_IDENTITY(PFServiceConfigCreateHandle), [&](GlobalState& state)
    {
        RETURN_HR_INVALIDARG_IF_NULL(connectionString);
        RETURN_HR_INVALIDARG_IF_NULL(titleId);
        RETURN_HR_INVALIDARG_IF_NULL(playerAccountPoolId);
        RETURN_HR_INVALIDARG_IF_NULL(serviceConfigHandle);

        auto serviceConfig = MakeShared<PlayFab::ServiceConfig>(connectionString, titleId, playerAccountPoolId);
        return state.ServiceConfigs().MakeHandle(std::move(serviceConfig), *serviceConfigHandle);
    });
}

PF_API PFServiceConfigDuplicateHandle(
    PFServiceConfigHandle handle,
    PFServiceConfigHandle* duplicatedHandle
) noexcept
{
    return ApiImpl(API_IDENTITY(PFServiceConfigDuplicateHandle), [&](GlobalState& state)
    {
        RETURN_HR_INVALIDARG_IF_NULL(duplicatedHandle);

        SharedPtr<ServiceConfig> serviceConfig;
        RETURN_IF_FAILED(state.ServiceConfigs().FromHandle(handle, serviceConfig));
        return state.ServiceConfigs().MakeHandle(std::move(serviceConfig), *duplicatedHandle);
    });
}

PF_API_(void) PFServiceConfigCloseHandle(
    PFServiceConfigHandle handle
) noexcept
{
    ApiImpl(API_IDENTITY(PFServiceConfigCloseHandle), [&](GlobalState& state)
    {
        state.ServiceConfigs().CloseHandle(handle);
        return S_OK;
    });
}

PF_API PFServiceConfigGetConnectionStringSize(
    _In_  PFServiceConfigHandle handle,
    _Out_ size_t* connectionStringSize
) noexcept
{
    return ServiceConfigApiImpl(API_IDENTITY(PFServiceConfigGetConnectionStringSize), handle, [&](SharedPtr<ServiceConfig> serviceConfig)
    {
        RETURN_HR_INVALIDARG_IF_NULL(connectionStringSize);

        *connectionStringSize = serviceConfig->HttpClient()->ConnectionString().size() + 1;
        return S_OK;
    });
}

PF_API PFServiceConfigGetConnectionString(
    _In_ PFServiceConfigHandle handle,
    _In_ size_t connectionStringSize,
    _Out_writes_(connectionStringSize) char* connectionStringBuffer,
    _Out_opt_ size_t* connectionStringUsed
) noexcept
{
    return ServiceConfigApiImpl(API_IDENTITY(PFServiceConfigGetConnectionString), handle, [&](SharedPtr<ServiceConfig> serviceConfig)
    {
        RETURN_HR_INVALIDARG_IF_NULL(connectionStringBuffer);

        String const& connectionString = serviceConfig->HttpClient()->ConnectionString();
        RETURN_HR_IF(E_INVALIDARG, connectionStringSize < connectionString.size() + 1);

        memcpy(connectionStringBuffer, connectionString.data(), connectionString.size() + 1);

        if (connectionStringUsed)
        {
            *connectionStringUsed = connectionString.size() + 1;
        }

        return S_OK;
    });
}

PF_API PFServiceConfigGetTitleIdSize(
    _In_  PFServiceConfigHandle handle,
    _Out_ size_t* titleIdSize
) noexcept
{
    return ServiceConfigApiImpl(API_IDENTITY(PFServiceConfigGetTitleIdSize), handle, [&](SharedPtr<ServiceConfig> serviceConfig)
    {
        RETURN_HR_INVALIDARG_IF_NULL(titleIdSize);

        *titleIdSize = serviceConfig->TitleId().size() + 1;
        return S_OK;
    });
}

PF_API PFServiceConfigGetTitleId(
    _In_ PFServiceConfigHandle handle,
    _In_ size_t titleIdSize,
    _Out_writes_(titleIdSize) char* titleIdBuffer,
    _Out_opt_ size_t* titleIdUsed
) noexcept
{
    return ServiceConfigApiImpl(API_IDENTITY(PFServiceConfigGetTitleId), handle, [&](SharedPtr<ServiceConfig> serviceConfig)
    {
        RETURN_HR_INVALIDARG_IF_NULL(titleIdBuffer);

        String const& titleId = serviceConfig->TitleId();
        RETURN_HR_IF(E_INVALIDARG, titleIdSize < titleId.size() + 1);

        memcpy(titleIdBuffer, titleId.data(), titleId.size() + 1);

        if (titleIdUsed)
        {
            *titleIdUsed = titleId.size() + 1;
        }

        return S_OK;
    });
}

PF_API PFServiceConfigGetPlayerAccountPoolIdSize(
    _In_  PFServiceConfigHandle handle,
    _Out_ size_t* playerAccountPoolIdSize
) noexcept
{
    return ServiceConfigApiImpl(API_IDENTITY(PFServiceConfigGetPlayerAccountPoolIdSize), handle, [&](SharedPtr<ServiceConfig> serviceConfig)
    {
        RETURN_HR_INVALIDARG_IF_NULL(playerAccountPoolIdSize);

        *playerAccountPoolIdSize = serviceConfig->PlayerAccountPoolId().size() + 1;
        return S_OK;
    });
}

PF_API PFServiceConfigGetPlayerAccountPoolId(
    _In_ PFServiceConfigHandle handle,
    _In_ size_t playerAccountPoolIdSize,
    _Out_writes_(playerAccountPoolIdSize) char* playerAccountPoolIdBuffer,
    _Out_opt_ size_t* playerAccountPoolIdUsed
) noexcept
{
    return ServiceConfigApiImpl(API_IDENTITY(PFServiceConfigGetPlayerAccountPoolId), handle, [&](SharedPtr<ServiceConfig> serviceConfig)
    {
        RETURN_HR_INVALIDARG_IF_NULL(playerAccountPoolIdBuffer);

        String const& playerAccountPoolId = serviceConfig->PlayerAccountPoolId();
        RETURN_HR_IF(E_INVALIDARG, playerAccountPoolIdSize < playerAccountPoolId.size() + 1);

        memcpy(playerAccountPoolIdBuffer, playerAccountPoolId.data(), playerAccountPoolId.size() + 1);

        if (playerAccountPoolIdUsed)
        {
            *playerAccountPoolIdUsed = playerAccountPoolId.size() + 1;
        }

        return S_OK;
    });
}
