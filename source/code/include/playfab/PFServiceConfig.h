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

HRESULT PFServiceConfigCreateHandle(
    _In_z_ const char* connectionString,
    _In_z_ const char* titleId,
    _In_z_ const char* playerAccountPoolId,
    _Out_ PFServiceConfigHandle* serviceConfigHandle
) noexcept;

HRESULT PFServiceConfigDuplicateHandle(
    PFServiceConfigHandle handle,
    PFServiceConfigHandle* duplicatedHandle
) noexcept;

void PFServiceConfigCloseHandle(
    PFServiceConfigHandle handle
) noexcept;

// TODO these should probably copy to buffers rather than return internal pointers
HRESULT PFServiceConfigGetConnectionString(
    _In_ PFServiceConfigHandle handle,
    _Out_ const char** connectionString
) noexcept;

HRESULT PFServiceConfigGetTitleId(
    _In_ PFServiceConfigHandle handle,
    _Out_ const char** titleId
) noexcept;

HRESULT PFServiceConfigGetPlayerAccountPoolId(
    _In_ PFServiceConfigHandle handle,
    _Out_ const char** playerAccountPoolId
) noexcept;

}
