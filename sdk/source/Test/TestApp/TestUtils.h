// Copyright (C) Microsoft Corporation. All rights reserved.

#pragma once

#include "TestDataTypes.h"
#include <ctime>
#include <chrono>

namespace PlayFab
{
namespace Test
{
const char* ToString(TestActiveState state);
const char* ToString(TestFinishState state);

inline int64_t GetMilliTicks()
{
    auto msClock = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());
    return msClock.time_since_epoch().count();
}

}
}
