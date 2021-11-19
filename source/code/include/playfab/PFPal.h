// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include <httpClient/pal.h>

#if !HC_PLATFORM_IS_MICROSOFT
#ifndef _Null_terminated_
#define _Null_terminated_
#endif
#endif // HC_PLATFORM_IS_MICROSOFT