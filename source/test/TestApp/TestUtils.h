// Copyright (C) Microsoft Corporation. All rights reserved.

#pragma once

#include "TestDataTypes.h"

namespace PlayFabUnit
{
    const char* ToString(TestActiveState state);
    const char* ToString(TestFinishState state);

    extern PlayFab::JsonAllocator s_jsonAllocator;
}
