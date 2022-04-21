// Copyright (C) Microsoft Corporation. All rights reserved.
#include <memory>

#include "TestAppPch.h"
#include "TestReport.h"
#include "TestUtils.h"

using namespace PlayFab;

namespace PlayFab
{
namespace Test
{

TestReport::TestReport(const std::string& className)
{
    internalReport.name = className;
    internalReport.timeStamp = PlayFab::GetMilliTicks();
    internalReport.tests = 0;
    internalReport.failures = 0;
    internalReport.errors = 0;
    internalReport.skipped = 0;
    internalReport.passed = 0;
}

void TestReport::TestStarted()
{
    internalReport.tests += 1;
}

void TestReport::TestComplete(const std::string& testName, TestFinishState testFinishState, int64_t testDurationMs, std::string message)
{
    // Add a new TestCaseReport for the completed test.
    std::shared_ptr<TestCaseReport> testReport = std::make_shared<TestCaseReport>();
    internalReport.testResults.push_back(testReport);

    testReport->classname = internalReport.name;
    testReport->name = testName;
    testReport->time = std::chrono::duration<double>(testDurationMs).count();
    testReport->message = message;
    testReport->finishState = testFinishState;
    testReport->failureText = ToString(testFinishState);

    // Update statistics.
    switch (testFinishState)
    {
    case TestFinishState::PASSED: internalReport.passed += 1; break;
    case TestFinishState::FAILED: internalReport.failures += 1; break;
    case TestFinishState::SKIPPED: internalReport.skipped += 1; break;
    case TestFinishState::PENDING:
        break;
    case TestFinishState::TIMEDOUT:
        break;
    default:
        break;
    }

    // Update overall runtime.
    // TODO: Add hooks for SuiteSetUp and SuiteTearDown, so this can be estimated more accurately
    internalReport.time = (PlayFab::GetMilliTicks() - internalReport.timeStamp) / 1000.0; // For now, update the duration on every test complete - the last one will be essentially correct
}

bool TestReport::AllTestsPassed()
{
    return (internalReport.tests > 0) &&
        ((internalReport.passed + internalReport.skipped) == internalReport.tests) &&
        (0 == internalReport.failures);
}

} // namespace Test
} // namespace PlayFab
