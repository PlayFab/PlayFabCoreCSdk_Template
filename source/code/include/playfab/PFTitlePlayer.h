// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include <playfab/PFEntity.h>

extern "C"
{

/// <summary>
/// Entity type for all TitlePlayer Entities. This const value can be used to populate PFEntityKeys referrring to TitlePlayer Entities.
/// </summary>
static const char* PFTitlePlayerEntityType = "title_player_account";

/// <summary>
/// Handle to an authenticated TitlePlayer Entity. Returned from one of the PFAuthenticationClientLogin* APIs.
/// When no longer needed, the Entity handle must be closed with PFTitlePlayerCloseHandle.
/// </summary>
typedef PFHandle PFTitlePlayerHandle;

/// <summary>
/// Duplicates a PFTitlePlayerHandle.
/// </summary>
/// <param name="titlePlayerHandle">TitlePlayer handle to duplicate.</param>
/// <param name="duplicatedHandle">The duplicated handle.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// Both the duplicated handle and the original handle need to be closed with PFTitlePlayerCloseHandle when they
/// are no longer needed.
/// </remarks>
HRESULT PFTitlePlayerDuplicateHandle(
    _In_ PFTitlePlayerHandle titlePlayerHandle,
    _Out_ PFTitlePlayerHandle* duplicatedHandle
) noexcept;

/// <summary>
/// Closes a PFTitlePlayerHandle.
/// </summary>
/// <param name="titlePlayerHandle">TitlePlayer handle to close.</param>
/// <returns>Result code for this API operation.</returns>
void PFTitlePlayerCloseHandle(
    _In_ PFTitlePlayerHandle titlePlayerHandle
) noexcept;

/// <summary>
/// Get the size in bytes needed to store the PFEntityKey for a TitlePlayer.
/// </summary>
/// <param name="titlePlayerHandle">PFTitlePlayerHandle returned from a login call.</param>
/// <param name="bufferSize">The buffer size in bytes required for the EntityKey.</param>
/// <returns>Result code for this API operation.</returns>
HRESULT PFTitlePlayerGetEntityKeySize(
    _In_ PFTitlePlayerHandle titlePlayerHandle,
    _Out_ size_t* bufferSize
) noexcept;

/// <summary>
/// Get the PFEntityKey for a TitlePlayer.
/// </summary>
/// <param name="titlePlayerHandle">PFTitlePlayerHandle returned from a login call.</param>
/// <param name="bufferSize">The size of the buffer for the PFEntityKey. The required size can be obtained from PFTitlePlayerGetEntityKeySize.</param>
/// <param name="buffer">Byte buffer used for the PFEntityKey and its fields.</param>
/// <param name="result">Pointer to the PFEntityKey object.</param>
/// <param name="bufferUsed">The number of bytes in the provided buffer that were used.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// entityKey is a pointer within buffer and does not need to be freed separately.
/// </remarks>
HRESULT PFTitlePlayerGetEntityKey(
    _In_ PFTitlePlayerHandle titlePlayerHandle,
    _In_ size_t bufferSize,
    _Out_writes_bytes_to_(bufferSize, *bufferUsed) void* buffer,
    _Outptr_ const PFEntityKey** entityKey,
    _Out_opt_ size_t* bufferUsed
) noexcept;

HRESULT PFTitlePlayerGetEntityTokenAsync(
    _In_ PFTitlePlayerHandle titlePlayerHandle,
    _In_ bool forceRefresh,
    _Inout_ XAsyncBlock* async
) noexcept;

HRESULT PFTitlePlayerGetEntityTokenGetResultSize(
    _Inout_ XAsyncBlock* async,
    _Out_ size_t* bufferSize
) noexcept;


HRESULT PFTitlePlayerGetEntityTokenGetResult(
    _Inout_ XAsyncBlock* async,
    _In_ size_t bufferSize,
    _Out_writes_bytes_to_(bufferSize, *bufferUsed) void* buffer,
    _Outptr_ const PFEntityToken** entityToken,
    _Out_opt_ size_t* bufferUsed
) noexcept;

typedef void CALLBACK PFEntityTokenExpiredCallback(
    void* context,
    PFTitlePlayerHandle player
);

HRESULT PFTitlePlayerRegisterForTokenExpiredEvent(
    PFTitlePlayerHandle player,
    XTaskQueueHandle queue,
    void* context,
    PFEntityTokenExpiredCallback* callback,
    XTaskQueueRegistrationToken* token
) noexcept;

void PFTitlePlayerUnregisterForTokenExpiredEvent(
    PFTitlePlayerHandle player,
    XTaskQueueRegistrationToken token
) noexcept;

}
