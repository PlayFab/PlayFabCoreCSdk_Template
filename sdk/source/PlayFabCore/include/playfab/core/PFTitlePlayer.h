// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include <playfab/core/PFEntity.h>
#include <playfab/core/PFTypes.h>

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
typedef struct PFTitlePlayer* PFTitlePlayerHandle;

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
PF_API PFTitlePlayerDuplicateHandle(
    _In_ PFTitlePlayerHandle titlePlayerHandle,
    _Out_ PFTitlePlayerHandle* duplicatedHandle
) noexcept;

/// <summary>
/// Closes a PFTitlePlayerHandle.
/// </summary>
/// <param name="titlePlayerHandle">TitlePlayer handle to close.</param>
/// <returns>Result code for this API operation.</returns>
PF_API_(void) PFTitlePlayerCloseHandle(
    _In_ PFTitlePlayerHandle titlePlayerHandle
) noexcept;

/// <summary>
/// Get the size in bytes needed to store the PFEntityKey for a TitlePlayer.
/// </summary>
/// <param name="titlePlayerHandle">PFTitlePlayerHandle returned from a login call.</param>
/// <param name="bufferSize">The buffer size in bytes required for the EntityKey.</param>
/// <returns>Result code for this API operation.</returns>
PF_API PFTitlePlayerGetEntityKeySize(
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
PF_API PFTitlePlayerGetEntityKey(
    _In_ PFTitlePlayerHandle titlePlayerHandle,
    _In_ size_t bufferSize,
    _Out_writes_bytes_to_(bufferSize, *bufferUsed) void* buffer,
    _Outptr_ const PFEntityKey** entityKey,
    _Out_opt_ size_t* bufferUsed
) noexcept;

/// <summary>
/// Get the cached PFEntityToken for a TitlePlayer.
/// </summary>
/// <param name="titlePlayerHandle">PFTitlePlayerHandle returned from a login call.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
PF_API PFTitlePlayerGetEntityTokenAsync(
    _In_ PFTitlePlayerHandle titlePlayerHandle,
    _Inout_ XAsyncBlock* async
) noexcept;

/// <summary>
/// Get the size in bytes needed to store the result of a PFTitlePlayerGetEntityTokenAsync call.
/// </summary>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <param name="bufferSize">The buffer size in bytes required for the result.</param>
/// <returns>Result code for this API operation.</returns>
PF_API PFTitlePlayerGetEntityTokenResultSize(
    _Inout_ XAsyncBlock* async,
    _Out_ size_t* bufferSize
) noexcept;

/// <summary>
/// Gets the result of a successful PFTitlePlayerGetEntityTokenAsync call.
/// </summary>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <param name="bufferSize">The size of the buffer for the result object.</param>
/// <param name="buffer">Byte buffer used for the result value and its fields.</param>
/// <param name="entityToken">Pointer to the EntityToken object.</param>
/// <param name="bufferUsed">The number of bytes in the provided buffer that were used.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// entityToken is a pointer within buffer and does not need to be freed separately.
/// </remarks>
PF_API PFTitlePlayerGetEntityTokenResult(
    _Inout_ XAsyncBlock* async,
    _In_ size_t bufferSize,
    _Out_writes_bytes_to_(bufferSize, *bufferUsed) void* buffer,
    _Outptr_ const PFEntityToken** entityToken,
    _Out_opt_ size_t* bufferUsed
) noexcept;

}
