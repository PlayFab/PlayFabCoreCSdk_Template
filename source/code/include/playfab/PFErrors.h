// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include <httpClient/pal.h>

extern "C"
{

// PlayFab HRESULT error codes (FACILITY_XBOX + 0x5400 + offset)

// Errors returned from any PlayFab service wrapper API.
// It is safe to retry calls that fail with the following errors (with an exponential delay back-off).
#define E_PF_RATELIMITEXCEEDED                     MAKE_E_HC(0x5400L) // 0x89235400
#define E_PF_OVERGAMEMANAGERLIMIT                  MAKE_E_HC(0x5401L) // 0x89235401
#define E_PF_SERVICEUNAVAILABLE                    MAKE_E_HC(0x5402L) // 0x89235402

// If the following errors are returned, the call shouldn't be retried. Without changes, the call will never succeed.
#define E_PF_ACCOUNTBANNED                         MAKE_E_HC(0x5410L) // 0x89235410
#define E_PF_ACCOUNTDELETED                        MAKE_E_HC(0x5411L) // 0x89235411
#define E_PF_ACCOUNTNOTFOUND                       MAKE_E_HC(0x5412L) // 0x89235412
#define E_PF_APIREQUESTSDISABLEDFORTITLE           MAKE_E_HC(0x5413L) // 0x89235413
#define E_PF_INVALIDREQUEST                        MAKE_E_HC(0x5414L) // 0x89235414
#define E_PF_NOTAUTHENTICATED                      MAKE_E_HC(0x5415L) // 0x89235415
#define E_PF_NOTAUTHORIZED                         MAKE_E_HC(0x5416L) // 0x89235416
#define E_PF_PROFILEDOESNOTEXIST                   MAKE_E_HC(0x5417L) // 0x89235417
#define E_PF_TITLEDELETED                          MAKE_E_HC(0x5418L) // 0x89235418
#define E_PF_UNKNOWNERROR                          MAKE_E_HC(0x5419L) // 0x89235419
#define E_PF_SERVICEERROR                          MAKE_E_HC(0x541AL) // 0x8923541A

// Client side auth token check errors. Returned when the required auth token is missing from the provided context handle.
#define E_PF_NOSESSIONTICKET                       MAKE_E_HC(0x5430L) // 0x89235431
#define E_PF_NOENTITYTOKEN                         MAKE_E_HC(0x5431L) // 0x89235432
#define E_PF_NOSECRETKEY                           MAKE_E_HC(0x5432L) // 0x89235433

// Errors returned from PlayFabEventMangager APIs.
#define E_PF_EVENTMANAGERBUFFEROVERFLOW            MAKE_E_HC(0x5440L) // 0x89235440
#define E_PF_EVENTMANAGERINVALIDOPERATION          MAKE_E_HC(0x5441L) // 0x89235441

// E_PF_INTERNAL_* values should never be returned to callers
#define E_PF_INTERNAL_EVENTMANAGERBUFFEREMPTY      MAKE_E_HC(0x5450L) // 0x89235450
#define E_PF_INTERNAL_QOSTIMEOUTEXCEEDED           MAKE_E_HC(0x5451L) // 0x89235451
#define E_PF_INTERNAL_EXPIREDAUTHTOKEN             MAKE_E_HC(0x5452L) // 0x89235452

}
