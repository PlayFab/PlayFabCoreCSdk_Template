// Copyright (C) Microsoft Corporation. All rights reserved.

#include "TestAppPch.h"

#include <cstdarg>
#include <functional>
#include <thread>
#include <rapidjson/document.h>

#include "TestApp.h"
#include "TestRunner.h"
#include "TestReport.h"
#include "TestUtils.h"

#include <httpClient/httpClient.h>
#include "ApiTests.h" 

namespace PlayFab
{
namespace Test
{
PFTestTraceLevel TestApp::traceLevel = PFTestTraceLevel::Important;

void TestApp::LogInit()
{
    // Delete existing log file if it exists
    std::remove(s_logfileName);
}

#if HC_PLATFORM != HC_PLATFORM_GDK
void TestApp::Log(const char* format, ...)
{
    static char message[1024 * 64];

    va_list args;
    va_start(args, format);
#if defined(PLAYFAB_PLATFORM_PLAYSTATION)
    vsnprintf_s(message, sizeof(message), format, args);
#elif defined(PLAYFAB_PLATFORM_IOS) || defined(PLAYFAB_PLATFORM_ANDROID) || defined(PLAYFAB_PLATFORM_LINUX) || defined(PLAYFAB_PLATFORM_SWITCH)
    vsnprintf(message, sizeof(message), format, args);
#else
    _vsnprintf_s(message, sizeof(message), format, args);
#endif // defined(PLAYFAB_PLATFORM_PLAYSTATION)
    va_end(args);

    // Output the message in a platform-dependent way.
    LogPut(message);
}
#endif

int TestApp::Main()
{
    TestApp::LogInit();

    HCSettingsSetTraceLevel(HCTraceLevel::Verbose);
    HCTraceSetTraceToDebugger(true);

    // Load the TestTitleData
    TestTitleData testTitleData;
    bool loadSuccessful = LoadTitleData(testTitleData);

    // If the title data fails to load, and you want to use custom hard-coded data, you can
    // comment out the return statement and fill out the TestTitleData fields manually.
    if (!loadSuccessful)
    {
        // TODO: POPULATE THIS SECTION WITH REAL INFORMATION (or set up a testTitleData file, and set your PF_TEST_TITLE_DATA_JSON to the path for that file)
        testTitleData.titleId = "65F7E17B"; // The titleId for your title, found in the "Settings" section of PlayFab Game Manager
        testTitleData.playerAccountPoolId = "EC0C51994370202B";
        testTitleData.connectionString = "https://65f7e17b.api.pfint.azureplayfabdev.com/";
    }

    // Initialize the test runner/test data.
    TestRunner testRunner;

    ApiTests apiTests;
    apiTests.SetTitleInfo(testTitleData);
    testRunner.Add(apiTests);

    // Run the tests (blocks until all tests have finished).
    testRunner.Run();

    // Publish the test summary to STDOUT.
    Log("%s\n", testRunner.suiteTestSummary.c_str());

    // Return 0 (success) if all tests passed. Otherwise, return 1 (error).
    return testRunner.AllTestsPassed();
}

bool TestApp::LoadTitleData(TestTitleData& titleData)
{
    // Load JSON string in a platform-dependent way.
    std::shared_ptr<char*> titleJsonPtr;
    size_t size;
    const bool loadedSuccessfully = LoadTitleDataJson(titleJsonPtr, size);

    if (!loadedSuccessfully)
    {
        return false;
    }

    // Parse JSON string into output TestTitleData.
    rapidjson::Document titleDataJson;
    titleDataJson.Parse(*titleJsonPtr);

    if (!titleDataJson.HasParseError())
    {
        titleData.titleId = titleDataJson["titleId"].GetString();
        titleData.playerAccountPoolId = titleDataJson["playerAccountPoolId"].GetString();
        titleData.connectionString = titleDataJson["connectionString"].GetString();
    }

    return !titleDataJson.HasParseError();
}

} // namespace Test
} // namespace PlayFab
