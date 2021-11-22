// Copyright (C) Microsoft Corporation. All rights reserved.

#pragma once

#include "TestDataTypes.h"

namespace PlayFabUnit
{
    class TestCase;
    struct TestContext;
    using TestFunc = std::function<void(TestContext&)>;

    struct TestContext
    {
        TestContext(TestCase* testCase, const std::string& name, TestFunc func) :
            testName(name),
            activeState(TestActiveState::PENDING),
            finishState(TestFinishState::PENDING),
            testResultMsg(),
            testFunc(func),
            testCase(testCase)
        {
        };

        const std::string testName;
        TestActiveState activeState;
        TestFinishState finishState;
        std::string testResultMsg;
        std::string interrimMsg;
        TestFunc testFunc;
        TestCase* testCase;
        int64_t startTime;
        int64_t endTime;

        // End this test with the given state and message
        void EndTest(TestFinishState state, const std::string& resultMsg);

        // End this test with PASSED state and optional message
        void Pass(const std::string& message = "");
        // End this test with FAILED state and optional message
        void Fail(const std::string& message = "");
        // End this test with FAILED state. Message will note failed API and HRESULT
        void Fail(const char* failedApi, HRESULT hr);

        // End this test with SKIPPED state and optional message
        void Skip(const std::string& message = "");

        // Set a temporary message, which will display if the test times out
        void SetInterrimMessage(const std::string& message);
    };
}
