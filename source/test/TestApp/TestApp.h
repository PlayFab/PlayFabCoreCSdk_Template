// Copyright (C) Microsoft Corporation. All rights reserved.

#pragma once

#include <condition_variable>
#include <memory>
#include <mutex>
#include <string>

#include "TestReport.h"

namespace PlayFab
{
    class PlayFabClientInstanceAPI;
    struct PlayFabError;

    namespace ClientModels
    {
        struct LoginResult;
        struct ExecuteCloudScriptResult;
    }
}

enum class PFTestTraceLevel : uint32_t
{
    Off = 0,
    Error = 1,
    Warning = 2,
    Important = 3,
    Information = 4,
    Verbose = 5,
};

namespace PlayFabUnit
{
    class TestApp
    {
    public:
        int Main();
        static void Log(const char* format, ...);
        static void LogPut(const char* message);
        static void SetTraceLevel(PFTestTraceLevel level);
        static bool ShouldTrace(PFTestTraceLevel level);

    private:
        static PFTestTraceLevel traceLevel;

#if !defined(DISABLE_PLAYFABCLIENT_API)
        // Cloud Report
        std::string cloudResponse = "";
        std::string cloudPlayFabId = "";
        std::mutex cloudResponseMutex;
        std::condition_variable cloudResponseConditionVar;

        std::shared_ptr<PlayFab::PlayFabClientInstanceAPI> clientApi;
        void OnPostReportLogin(const PlayFab::ClientModels::LoginResult& result, TestReport& testReport);
        void OnPostReportComplete(const PlayFab::ClientModels::ExecuteCloudScriptResult& result);
        void OnPostReportError(const PlayFab::PlayFabError& error);
#endif

        // Utility
        static bool LoadTitleData(TestTitleData& titleData);

        // Partial class methods
        // Each platform gets its own file and implementation of the following methods, since the logic
        // is likely to be very different on all of them.
        static bool LoadTitleDataJson(std::shared_ptr<char*>& testDataJsonPtr, size_t& testDataJsonLen);
    };
}
