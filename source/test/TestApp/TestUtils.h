// Copyright (C) Microsoft Corporation. All rights reserved.

#pragma once

#include "TestDataTypes.h"

namespace PlayFab
{
namespace Test
{
const char* ToString(TestActiveState state);
const char* ToString(TestFinishState state);

// TODO don't rely on SDK InternalMemory here
extern PlayFab::JsonAllocator s_jsonAllocator;

}
}
