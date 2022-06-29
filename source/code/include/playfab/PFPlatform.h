// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include <playfab/PFPal.h>
#include <httpClient/async.h>

extern "C"
{

/// Read from storage event handler. Should implement an <see cref="XAsyncProvider"/>.
/// </summary>
/// <param name="context">Optional pointer to data used by the event handler.</param>
/// <param name="key">Identifies the data being written. Typically a filepath.</param>
/// <param name="async">XAsyncBlock for the operation.</param>
/// <remarks>
/// This event handler will be invoked when PlayFab needs to read data from storage.
/// The XAsyncBlock should be completed with data size (in bytes) that was read.
/// All arguments are owned by the SDK and are guaranteed to be valid until the operation is complete (except context).
/// </remarks>
typedef HRESULT STDAPIVCALLTYPE PFPlatformLocalStorageReadAsyncHandler(
    _In_opt_ void* context,
    _In_z_ const char* key,
    _Inout_ XAsyncBlock* async
);

/// <summary>
/// Write to storage event handler. Should implement an <see cref="XAsyncProvider"/>.
/// </summary>
/// <param name="context">Optional pointer to data used by the event handler.</param>
/// <param name="key">Identifies the data being written. Typically a filepath.</param>
/// <param name="dataSize">The size (in bytes) of the data.</param>
/// <param name="data">The data to write.</param>
/// <param name="async">XAsyncBlock for the operation.</param>
/// <remarks>
/// This event handler will be invoked when PlayFab needs to write data to storage.
/// All arguments are owned by the SDK and are guaranteed to be valid until the operation is complete (except context).
/// </remarks>
typedef HRESULT STDAPIVCALLTYPE PFPlatformLocalStorageWriteAsyncHandler(
    _In_opt_ void* context,
    _In_z_ const char* key,
    _In_ size_t dataSize,
    _In_reads_bytes_(dataSize) void const* data,
    _Inout_ XAsyncBlock* async
);

/// <summary>
/// Write from storage event handler. Should implement an <see cref="XAsyncProvider"/>.
/// </summary>
/// <param name="context">Optional pointer to data used by the event handler.</param>
/// <param name="key">Identifies the data being written. Typically a filepath.</param>
/// <param name="async">XAsyncBlock for the operation.</param>
/// <remarks>
/// This event handler will be invoked when PlayFab needs to clear data from storage.
/// All arguments are owned by the SDK and are guaranteed to be valid until the operation is complete (except context).
/// </remarks>
typedef HRESULT STDAPIVCALLTYPE PFPlatformLocalStorageClearAsyncHandler(
    _In_opt_ void* context,
    _In_z_ const char* key,
    _Inout_ XAsyncBlock* async
);

/// <summary>
/// Sets the storage event handlers. If custom storage handlers are not set, a default implementation
/// based on cstdio and std::fstream objects will be used. 
/// </summary>
/// <param name="queue">The async queue the callbacks should be invoked on.</param>
/// <param name="context">Optional context that will be passed back to handlers.</param>
/// <param name="readHandler">Read from storage handler, <see cref="PFPlatformLocalStorageReadAsyncHandler"/>.</param>
/// <param name="writeHandler">Write to storage handler, <see cref="PFPlatformLocalStorageWriteAsyncHandler"/>.</param>
/// <param name="clearHandler">Clear from storage handler, <see cref="PFPlatformLocalStorageClearAsyncHandler"/>.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// Must be called before PFInitialize.
/// </remarks>
PF_API PFPlatformLocalStorageSetHandlers(
    _In_opt_ XTaskQueueHandle queue,
    _In_opt_ void* context,
    _In_ PFPlatformLocalStorageReadAsyncHandler* readHandler,
    _In_ PFPlatformLocalStorageWriteAsyncHandler* writeHandler,
    _In_ PFPlatformLocalStorageClearAsyncHandler* clearHandler
) noexcept;

}
