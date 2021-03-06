// Copyright (C) Microsoft Corporation. All rights reserved.

#include "TestAppPch.h"
#include "TestContext.h"
#include "TestUtils.h"


namespace PlayFab
{
namespace Test
{

void TestContext::EndTest(TestFinishState state, const std::string& resultMsg)
{
    if (finishState == TestFinishState::PENDING) // This means that we finish successfully
    {
        endTime = GetMilliTicks();
        testResultMsg = resultMsg;
        finishState = state;
        activeState = TestActiveState::READY;

        // Interrim message if relevant
        if (testResultMsg.empty() && state == TestFinishState::TIMEDOUT)
            testResultMsg = interrimMsg;

        return;
    }

    if (!testResultMsg.empty())
    {
        testResultMsg += "\n";
    }
    testResultMsg += TestFinishStateToString[static_cast<int>(finishState)] + std::string("->") + TestFinishStateToString[static_cast<int>(state)] + " - Cannot declare test finished twice.";
    if (!resultMsg.empty())
        testResultMsg += "\n: " + resultMsg;
    finishState = TestFinishState::FAILED;
}

void TestContext::Pass(const std::string& message)
{
    EndTest(TestFinishState::PASSED, message);
}

void TestContext::Fail(const std::string& message)
{
    EndTest(TestFinishState::FAILED, message.empty() ? "fail" : message);
    // TODO: Throw "assert" exception
}

void TestContext::Fail(const char* failedApi, HRESULT hr)
{
    std::stringstream message;
    message << "SDK call \"" << failedApi << "\" failed with hr=" << std::hex << hr;
    Fail(message.str());
}

void TestContext::Skip(const std::string& message)
{
    EndTest(TestFinishState::SKIPPED, message);
    // TODO: Throw "test skipped" exception
}

void TestContext::SetInterrimMessage(const std::string& message)
{
    interrimMsg = message;
    // printf("Interrim: %s\n", message.c_str());
}

} // namespace Test
} // namespace PlayFab
