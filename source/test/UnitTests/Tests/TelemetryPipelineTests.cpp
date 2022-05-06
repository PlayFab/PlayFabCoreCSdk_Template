#include "stdafx.h"
#include "TestIncludes.h"
#include "Wrappers/TelemetryPipeline.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PlayFab
{
namespace UnitTests
{

constexpr char* kWriteEventsMockResponseBody =
R"({
  "code": 200,
  "status": "OK",
  "data": {
    "WriteEventsResponse": {
      "AssignedEventIds": []
    }
  }
})";

constexpr char* kTestEventTemplate =
R"({
  "eventId": 0
})";

TEST_CLASS(TelemetryTests)
{
public:
    TEST_METHOD(TestSingleEventDefaultSettings)
    {
        Wrappers::Session session;
        Wrappers::ServiceConfig<> serviceConfig{ "mockConnectionString", "mockTitleId", "mockPlayerAccountPoolId" };

        // Configure Mocks
        std::stringstream authUrl;
        authUrl << serviceConfig.ConnectionString() << "/PlayerIdentity/AuthenticateWith";
        HttpMock authMock{ "POST", authUrl.str().data() };

        rapidjson::Document authResponseBodyJson;
        auto& allocator{ authResponseBodyJson.GetAllocator() };
        authResponseBodyJson.Parse(kMockAuthResponseBody);
        authMock.SetResponseBody(authResponseBodyJson);

        // Synchronously authenticate
        XAsyncBlock async{};
        PFAuthenticationAuthenticateCustomIdIdentityRequest request{};
        VERIFY_SUCCEEDED(PFAuthenticationAuthenticateWithCustomIdAsync(serviceConfig.Handle(), &request, &async));
        VERIFY_SUCCEEDED(XAsyncGetStatus(&async, true));
        PFTitlePlayerHandle titlePlayerHandle{ nullptr };
        VERIFY_SUCCEEDED(PFAuthenticationAuthenticateWithCustomIdGetResult(&async, &titlePlayerHandle));
        auto titlePlayer = Wrappers::TitlePlayer<>::Wrap(titlePlayerHandle);

        Wrappers::TelemetryPipeline pipeline{ titlePlayer.Handle(), nullptr };

        std::stringstream writeEventUrl;
        writeEventUrl << serviceConfig.ConnectionString() << "/Event/WriteEvent";
        HttpMock writeEventMock{ "POST", writeEventUrl.str().data() };
        writeEventMock.SetResponseBody(kWriteEventsMockResponseBody);

        AsyncTestContext tc;
        writeEventMock.SetMockMatchedCallback([&](HttpMock const& mock, std::string url, std::string requestBody)
        {
            rapidjson::Document requestJson;
            requestJson.Parse(requestBody.data());
            rapidjson::Document payloadJson;
            payloadJson.Parse(requestJson["Events"][0]["PayloadJSON"].GetString());
            tc.Assert(payloadJson["eventId"].GetInt() == 0);
            tc.Complete();
        });

        pipeline.EmitEvent(titlePlayer.Handle(), "playfab.core", "testEvent", kTestEventTemplate);

        tc.AwaitResult();
    }

    TEST_METHOD(TestMultipleEvents)
    {
        Wrappers::Session session;
        Wrappers::ServiceConfig<> serviceConfig{ "mockConnectionString", "mockTitleId", "mockPlayerAccountPoolId" };

        // Configure Mocks
        std::stringstream authUrl;
        authUrl << serviceConfig.ConnectionString() << "/PlayerIdentity/AuthenticateWith";
        HttpMock authMock{ "POST", authUrl.str().data() };

        rapidjson::Document authResponseBodyJson;
        auto& allocator{ authResponseBodyJson.GetAllocator() };
        authResponseBodyJson.Parse(kMockAuthResponseBody);
        authMock.SetResponseBody(authResponseBodyJson);

        // Synchronously authenticate
        XAsyncBlock async{};
        PFAuthenticationAuthenticateCustomIdIdentityRequest request{};
        VERIFY_SUCCEEDED(PFAuthenticationAuthenticateWithCustomIdAsync(serviceConfig.Handle(), &request, &async));
        VERIFY_SUCCEEDED(XAsyncGetStatus(&async, true));
        PFTitlePlayerHandle titlePlayerHandle{ nullptr };
        VERIFY_SUCCEEDED(PFAuthenticationAuthenticateWithCustomIdGetResult(&async, &titlePlayerHandle));
        auto titlePlayer = Wrappers::TitlePlayer<>::Wrap(titlePlayerHandle);

        Wrappers::TelemetryPipeline pipeline{ titlePlayer.Handle(), nullptr };

        std::stringstream writeEventUrl;
        writeEventUrl << serviceConfig.ConnectionString() << "/Event/WriteEvent";
        HttpMock writeEventMock{ "POST", writeEventUrl.str().data() };
        writeEventMock.SetResponseBody(kWriteEventsMockResponseBody);

        std::set<int> eventIdsToWrite{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        size_t eventsWritten = 0;

        AsyncTestContext tc;
        writeEventMock.SetMockMatchedCallback([&](HttpMock const& mock, std::string url, std::string requestBody)
        {
            rapidjson::Document requestJson;
            requestJson.Parse(requestBody.data());

            auto& eventsJson = requestJson["Events"];
            for (auto& eventJson : eventsJson.GetArray())
            {
                rapidjson::Document payloadJson;
                payloadJson.Parse(eventJson["PayloadJSON"].GetString());
                tc.Assert(eventIdsToWrite.find(payloadJson["eventId"].GetInt()) != eventIdsToWrite.end());
                ++eventsWritten;
            }

            if (eventsWritten == eventIdsToWrite.size())
            {
                tc.Complete();
            }
        });

        rapidjson::Document eventPayloadJson;
        eventPayloadJson.Parse(kTestEventTemplate);

        for (auto& eventId : eventIdsToWrite)
        {
            eventPayloadJson["eventId"] = eventId;
            
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            eventPayloadJson.Accept(writer);

            pipeline.EmitEvent(titlePlayer.Handle(), "playfab.core", "testEvent", buffer.GetString());
        }

        tc.AwaitResult();
    }
};

}
}