// Copyright (C) Microsoft Corporation. All rights reserved.

#include "TestAppPch.h"
#include <Windows.h>
#include <fstream>
#include "TestApp.h"

namespace PlayFab
{
namespace Test
{

// Partial class implementation of TestApp.
// Each platform gets its own file and implementation of the following methods, since the logic
// is likely to be very different on all of them.
bool TestApp::LoadTitleDataJson(std::shared_ptr<char*>& testDataJson, size_t& testDataJsonLen)
{
    // Read the title data from the file into the output character array.
    std::ifstream titleDataFile;
    titleDataFile.open(PF_TEST_TITLE_DATA_JSON, std::ios::binary | std::ios::in);

    if (!titleDataFile)
    {
        return false;
    }

    std::streampos begin = titleDataFile.tellg();
    titleDataFile.seekg(0, std::ios::end);
    std::streampos end = titleDataFile.tellg();
    testDataJsonLen = static_cast<int>(end - begin);
    testDataJson = std::make_shared<char*>(new char[testDataJsonLen + 1]);

    titleDataFile.seekg(0, std::ios::beg);
    titleDataFile.read(*testDataJson, testDataJsonLen);
    (*testDataJson)[testDataJsonLen] = '\0';

    titleDataFile.close();

    return true;
}

void TestApp::SetTraceLevel(PFTestTraceLevel level)
{
    traceLevel = level;
}

bool TestApp::ShouldTrace(PFTestTraceLevel level)
{
    return (traceLevel > level);
}

void TestApp::LogPut(const char* message)
{
    // Write to STDOUT.
    puts(message);

    // Write to Visual Studio's Output window.
    OutputDebugStringA(message);
}

} // namespace Test
} // namespace PlayFab