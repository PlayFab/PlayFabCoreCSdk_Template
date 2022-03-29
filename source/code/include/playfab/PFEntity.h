// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include <httpClient/pal.h>
#include <httpClient/async.h>
#include <playfab/PFSharedDataModels.h>
#include <playfab/PFAuthenticationDataModels.h>

extern "C"
{

/// <summary>
/// Handle to an authenticated Entity (TitlePlayer, Title, etc.). Contains the auth tokens needed to make PlayFab service
/// calls. When no longer needed, the Entity handle must be closed with PFEntityCloseHandle.
/// </summary>
typedef struct PFEntity* PFEntityHandle;

/// <summary>
/// PlayFab EntityToken and its expiration time. Used internally to authenticate PlayFab service calls.
/// </summary>
typedef struct PFEntityToken
{
    /// <summary>
    /// The token used to set X-EntityToken for all entity based API calls.
    /// </summary>
    const char* token;

    /// <summary>
    /// (Optional) The time the token will expire, if it is an expiring token, in UTC.
    /// </summary>
    time_t const* expiration;

} PFEntityToken;

///// <summary>
///// Duplicates a PFEntityHandle.
///// </summary>
///// <param name="entityHandle">Entity handle to duplicate.</param>
///// <param name="duplicatedEntityHandle">The duplicated handle.</param>
///// <returns>Result code for this API operation.</returns>
///// <remarks>
///// Both the duplicated handle and the original handle need to be closed with PFEntityCloseHandle when they
///// are no longer needed.
///// </remarks>
//HRESULT PFEntityDuplicateHandle(
//    _In_ PFEntityHandle entityHandle,
//    _Out_ PFEntityHandle* duplicatedEntityHandle
//) noexcept;
//
///// <summary>
///// Closes a PFEntityHandle.
///// </summary>
///// <param name="entityHandle">Entity handle to close.</param>
///// <returns>Result code for this API operation.</returns>
//void PFEntityCloseHandle(
//    _In_ PFEntityHandle entityHandle
//) noexcept;
//
///// <summary>
///// Get the size in bytes needed to store the PFEntityKey for an Entity.
///// </summary>
///// <param name="entityHandle">PFEntityHandle returned from a auth call.</param>
///// <param name="bufferSize">The buffer size in bytes required for the EntityKey.</param>
///// <returns>Result code for this API operation.</returns>
//HRESULT PFEntityGetEntityKeySize(
//    _In_ PFEntityHandle entityHandle,
//    _Out_ size_t* bufferSize
//) noexcept;
//
///// <summary>
///// Get the PFEntityKey for an entity.
///// </summary>
///// <param name="entityHandle">PFEntityHandle returned from a auth call.</param>
///// <param name="bufferSize">The size of the buffer for the PFEntityKey. The required size can be obtained from PFEntityGetEntityKeySize.</param>
///// <param name="buffer">Byte buffer used for the PFEntityKey and its fields.</param>
///// <param name="result">Pointer to the PFEntityKey object.</param>
///// <param name="bufferUsed">The number of bytes in the provided buffer that were used.</param>
///// <returns>Result code for this API operation.</returns>
///// <remarks>
///// entityKey is a pointer within buffer and does not need to be freed separately.
///// </remarks>
//HRESULT PFEntityGetEntityKey(
//    _In_ PFEntityHandle entityHandle,
//    _In_ size_t bufferSize,
//    _Out_writes_bytes_to_(bufferSize, *bufferUsed) void* buffer,
//    _Outptr_ const PFEntityKey** entityKey,
//    _Out_opt_ size_t* bufferUsed
//) noexcept;
//
//HRESULT PFEntityGetEntityTokenAsync(
//    _In_ PFEntityHandle entityHandle,
//    _In_ bool forceRefresh,
//    _Inout_ XAsyncBlock* async
//) noexcept;
//
//HRESULT PFEntityGetEntityTokenGetResultSize(
//    _Inout_ XAsyncBlock* async,
//    _Out_ size_t* bufferSize
//) noexcept;
//
//
//HRESULT PFEntityGetEntityTokenGetResult(
//    _Inout_ XAsyncBlock* async,
//    _In_ size_t bufferSize,
//    _Out_writes_bytes_to_(bufferSize, *bufferUsed) void* buffer,
//    _Outptr_ const PFEntityToken** entityToken,
//    _Out_opt_ size_t* bufferUsed
//) noexcept;

}
