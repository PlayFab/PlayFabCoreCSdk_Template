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

/// <summary>
/// A callback invoked every time a new memory buffer must be dynamically allocated by the library.
/// This callback is optionally installed by calling PFMemSetFunctions()
/// 
/// The callback must allocate and return a pointer to a contiguous block of memory of the 
/// specified size that will remain valid until the app's corresponding PFMemFreeFunction 
/// callback is invoked to release it.
/// 
/// Every non-null pointer returned by this method will be subsequently passed to the corresponding
/// PFMemFreeFunction callback once the memory is no longer needed.
/// </summary>
/// <returns>A pointer to an allocated block of memory of the specified size, or a null 
/// pointer if allocation failed.</returns>
/// <param name="size">The size of the allocation to be made. This value will never be zero.</param>
typedef _Ret_maybenull_ _Post_writable_byte_size_(size) void* STDAPIVCALLTYPE PFMemAllocFunction(
    _In_ size_t size
);

/// <summary>
/// A callback invoked every time a previously allocated memory buffer is no longer needed by 
/// the library and can be freed. This callback is optionally installed by calling PFMemSetFunctions()
///
/// The callback is invoked whenever the library has finished using a memory buffer previously 
/// returned by the app's corresponding PFMemAllocFunction such that the application can free the
/// memory buffer.
/// </summary>
/// <param name="pointer">The pointer to the memory buffer previously allocated. This value will
/// never be a null pointer.</param>
typedef void STDAPIVCALLTYPE PFMemFreeFunction(
    _In_ _Post_invalid_ void* pointer
);

/// <summary>
/// Optionally sets the memory hook functions to allow callers to control route memory 
/// allocations to their own memory manager. This must be called before PFInitialize() 
/// and can not be called again once memory hooks have been set.
///
/// This method allows the application to install custom memory allocation routines in order 
/// to service all requests for new memory buffers instead of using default allocation routines.
/// </summary>
/// <param name="memAllocFunc">A pointer to the custom allocation callback to use.</param>
/// <param name="memFreeFunc">A pointer to the custom freeing callback to use.</param>
/// <returns>HRESULT return code for this API operation.</returns>
PF_API PFMemSetFunctions(
    _In_opt_ PFMemAllocFunction* memAllocFunc,
    _In_opt_ PFMemFreeFunction* memFreeFunc
) noexcept;

/// <summary>
/// Gets the memory hook functions to allow callers to control route memory allocations to their 
/// own memory manager. This method allows the application get the default memory allocation routines.
/// This can be used along with PFMemSetFunctions() to monitor all memory allocations.
/// </summary>
/// <param name="memAllocFunc">Set to the current allocation callback. Returns the default routine 
/// if not previously set</param>
/// <param name="memFreeFunc">Set to the to the current memory free callback. Returns the default 
/// routine if not previously set</param>
/// <returns>HRESULT return code for this API operation.</returns>
PF_API PFMemGetFunctions(
    _Out_ PFMemAllocFunction** memAllocFunc,
    _Out_ PFMemFreeFunction** memFreeFunc
) noexcept;

/// <summary>
/// Enables redirection of PlayFab tracing to a local file. Must be called before PFInitialize.
/// </summary>
/// <param name="traceFileDirectory">Directory where trace file should be stored</param>
/// <returns>HRESULT return code for this API operation.</returns>
PF_API PFTraceEnableTraceToFile(
    _In_z_ const char* traceFileDirectory
) noexcept;

/// <summary>
/// Create PlayFab global state.
/// </summary>
/// <param name="backgroundQueue">An XTaskQueue that should be used for background work. If no queue is a default (threadpool) queue will be used.</param>
/// <returns>Result code for this API operation.</returns>
PF_API PFInitialize(
    _In_opt_ XTaskQueueHandle backgroundQueue
) noexcept;

/// <summary>
/// Cleanup PlayFab global state.
/// </summary>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>Asynchronous result returned via XAsyncGetStatus.</remarks>
PF_API PFUninitializeAsync(
    _In_ XAsyncBlock* async
) noexcept;

/// <summary>
/// A token returned when registering a callback to identify the registration. This token is later used 
/// to unregister the callback.
/// </summary>
typedef uint64_t PFRegistrationToken;

}
