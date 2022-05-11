// Copyright (C) Microsoft Corporation. All rights reserved.

#pragma once

#include <condition_variable>
#include <memory>
#include <mutex>
#include <string>

#include "TestReport.h"

enum class PFTestTraceLevel : uint32_t
{
    Off = 0,
    Error = 1,
    Warning = 2,
    Important = 3,
    Information = 4,
    Verbose = 5,
};

namespace PlayFab
{
namespace Test
{

class TestApp
{
public:
    int Main();
    static void LogInit();
    static void Log(const char* format, ...);
    static void LogPut(const char* message);
    static void SetTraceLevel(PFTestTraceLevel level);
    static bool ShouldTrace(PFTestTraceLevel level);

private:
    static PFTestTraceLevel traceLevel;

    static constexpr char s_logfileName[] = "TestClientApp.log";

    // Utility
    static bool LoadTitleData(TestTitleData& titleData);

    // Partial class methods
    // Each platform gets its own file and implementation of the following methods, since the logic
    // is likely to be very different on all of them.
    static bool LoadTitleDataJson(std::shared_ptr<char*>& testDataJsonPtr, size_t& testDataJsonLen);
};

} // namespace Test
} // namespace PlayFab
