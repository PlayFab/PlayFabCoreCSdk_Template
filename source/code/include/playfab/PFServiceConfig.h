// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include <playfab/PFPal.h>

extern "C"
{

typedef struct PFServiceConfig* PFServiceConfigHandle;

/// <summary>
/// Creates a PlayFab service configuration.
/// </summary>
/// <param name="connectionString">String used to connect to a PlayFab Service instance.</param>
/// <param name="playFabTitleId">PlayFab TitleId for the title. Found in the Game Manager for your title on the PlayFab Website.</param>
/// <param name="playAccountPoolId">Player Account Pool Id. TODO</param>
/// <param name="serviceConfigHandle">Pointer to a PFServiceConfigHandle to write.</param>
/// <returns>Result code for this API operation.  Possible values are S_OK, E_PF_NOT_INITIALIZED, or E_INVALIDARG.</returns>
HRESULT PFServiceConfigCreateHandle(
    _In_z_ const char* connectionString,
    _In_z_ const char* playFabTitleId,
    _In_z_ const char* playerAccountPoolId,
    _Out_ PFServiceConfigHandle* serviceConfigHandle
) noexcept;

/// <summary>
/// Duplicates a PFServiceConfigHandle.
/// </summary>
/// <param name="handle">ServiceConfig handle to duplicate.</param>
/// <param name="duplicatedHandle">The duplicated handle.</param>
/// <returns>Result code for this API operation.</returns> 
/// <remarks>
/// Both the duplicated handle and the original handle need to be closed with PFServiceConfigCloseHandle when they
/// are no longer needed.
/// </remarks>
HRESULT PFServiceConfigDuplicateHandle(
    PFServiceConfigHandle handle,
    PFServiceConfigHandle* duplicatedHandle
) noexcept;

/// <summary>
/// Closes a PFServiceConfigHandle.
/// </summary>
/// <param name="handle">ServiceConfig handle to close.</param>
/// <returns>Result code for this API operation.</returns>
void PFServiceConfigCloseHandle(
    PFServiceConfigHandle handle
) noexcept;

// TODO Do any of these fields have capped sizes? Avoiding the double call would be nice

/// <summary>
/// Gets the size of the buffer needed to hold the connection string for a service configuration.
/// </summary>
/// <param name="handle">ServiceConfig handle.</param>
/// <param name="connectionStringSize">Buffer size required for the connection string (including null terminator).</param>
/// <returns>Result code for this API operation.</returns>
HRESULT PFServiceConfigGetConnectionStringSize(
    _In_  PFServiceConfigHandle handle,
    _Out_ size_t* connectionStringSize
) noexcept;

/// <summary>
/// Gets the connection string for a service configuration.
/// </summary>
/// <param name="handle">ServiceConfig handle.</param>
/// <param name="connectionStringSize">Size of the provided buffer. Required size can be obtained via PFServiceConfigGetConnectionStringSize.</param>
/// <param name="connectionString">Buffer the connection string will be written to.</param>
/// <param name="connectionStringUsed">The number of bytes used in the buffer including the null terminator.</param>
/// <returns>Result code for this API operation.</returns>
HRESULT PFServiceConfigGetConnectionString(
    _In_ PFServiceConfigHandle handle,
    _In_ size_t connectionStringSize,
    _Out_writes_(connectionStringSize) char* connectionString,
    _Out_opt_ size_t* connectionStringUsed
) noexcept;

/// <summary>
/// Gets the size of the buffer needed to hold the PlayFab titleId for a service configuration.
/// </summary>
/// <param name="handle">ServiceConfig handle.</param>
/// <param name="titleIdSize">Buffer size required for the titleId (including null terminator).</param>
/// <returns>Result code for this API operation.</returns>
HRESULT PFServiceConfigGetTitleIdSize(
    _In_  PFServiceConfigHandle handle,
    _Out_ size_t* titleIdSize
) noexcept;

/// <summary>
/// Gets the PlayFab titleId for a service configuration.
/// </summary>
/// <param name="handle">ServiceConfig handle.</param>
/// <param name="titleIdSize">Size of the provided buffer. Required size can be obtained via PFServiceConfigGetTitleIdSize.</param>
/// <param name="titleId">Buffer the titleId will be written to.</param>
/// <param name="titleIdUsed">The number of bytes used in the buffer including the null terminator.</param>
/// <returns>Result code for this API operation.</returns>
HRESULT PFServiceConfigGetTitleId(
    _In_ PFServiceConfigHandle handle,
    _In_ size_t titleIdSize,
    _Out_writes_(titleIdSize) char* titleId,
    _Out_opt_ size_t* titleIdUsed
) noexcept;

/// <summary>
/// Gets the size of the buffer needed to hold the player account pool Id for a service configuration.
/// </summary>
/// <param name="handle">ServiceConfig handle.</param>
/// <param name="playerAccountPoolIdSize">Buffer size required for the player account pool Id (including null terminator).</param>
/// <returns>Result code for this API operation.</returns>
HRESULT PFServiceConfigGetPlayerAccountPoolIdSize(
    _In_  PFServiceConfigHandle handle,
    _Out_ size_t* playerAccountPoolIdSize
) noexcept;

/// <summary>
/// Gets the player account pool Id for a service configuration.
/// </summary>
/// <param name="handle">ServiceConfig handle.</param>
/// <param name="playerAccountPoolIdSize">Size of the provided buffer. Required size can be obtained via PFServiceConfigGetPlayerAccountPoolIdSize.</param>
/// <param name="playerAccountPoolId">Buffer the player account pool id will be written to.</param>
/// <param name="playerAccountPoolIdUsed">The number of bytes used in the buffer including the null terminator.</param>
/// <returns>Result code for this API operation.</returns>
HRESULT PFServiceConfigGetPlayerAccountPoolId(
    _In_ PFServiceConfigHandle handle,
    _In_ size_t playerAccountPoolIdSize,
    _Out_writes_(playerAccountPoolIdSize) char* playerAccountPoolId,
    _Out_opt_ size_t* playerAccountPoolIdUsed
) noexcept;

}
