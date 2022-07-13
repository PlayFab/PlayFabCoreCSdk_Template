// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include <playfab/PFPal.h>
#include <playfab/PFServiceConfig.h>
#include <playfab/PFEntity.h>
#include <playfab/PFTitlePlayer.h>
#include <playfab/PFAuthentication.h>

extern "C"
{

/// <summary>
/// Initialize PlayFabCore global state. Custom platform hooks must be configured prior to calling PFInitialize.
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

}
