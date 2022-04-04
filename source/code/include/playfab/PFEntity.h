// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include <httpClient/pal.h>
#include <httpClient/async.h>

extern "C"
{

/// <summary>
/// PlayFab EntityToken and its expiration time. Used to authenticate PlayFab service calls.
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

/// <summary>
/// EntityToken expired event handler. Needed to reauthenticate players in scenarios where the SDK is unable to automatically
/// refresh the cached EntityToken.
/// </summary>
/// <param name="context">Optional context pointer to data used by the event handler.</param>
/// <param name="userId">The Id of the Entity whose EntityToken expired. TODO should this be EntityKey rather than just EntityId?</param>
/// <returns></returns>
typedef void CALLBACK PFEntityTokenExpiredEventHandler(
    _In_ void* context,
    _In_ const char* entityId
);

/// <summary>
/// Register a handler for EntityToken expired events.
/// </summary>
/// <param name="queue">The async queue the callback should be invoked on.</param>
/// <param name="context">Optional pointer to data used by the event handler.</param>
/// <param name="handler">The event handler, <see cref="XalUserChangeEventHandler"/>.</param>
/// <param name="token">The token for unregistering this callback</param>
/// <returns>Result code for this API operation.  Possible values are S_OK, E_PF_NOT_INITIALIZED, or E_FAIL.</returns>
HRESULT PFEntityRegisterTokenExpiredEventHandler(
    _In_opt_ XTaskQueueHandle queue,
    _In_opt_ void* context,
    _In_ PFEntityTokenExpiredEventHandler* handler,
    _Out_ PFRegistrationToken* token
) noexcept;

/// <summary>
/// Unregisters a previously registered callback.
/// </summary>
/// <param name="token">The token returned from PFEntityRegisterTokenExpiredEventHandler.</param>
/// <returns></returns>
void PFEntityUnregisterTokenExpiredEventHandler(
    _In_ PFRegistrationToken token
) noexcept;

}
