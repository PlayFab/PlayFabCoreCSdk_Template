#include "TestAppPch.h"
#include "TestContext.h"
#include "EventManagerTests.h"
#include <playfab/PlayFabClientAuthApi.h>

namespace PlayFabUnit
{

class Event
{
public:
    Event(PlayFabEventManagerEventType type, const char* name)
    {
        HRESULT hr = PlayFabEventManagerEventCreate(type, name, nullptr, nullptr, nullptr, &handle);
        assert(SUCCEEDED(hr));
        UNREFERENCED_PARAMETER(hr);
    }

    Event(const Event& other)
    {
        HRESULT hr = PlayFabEventManagerEventDuplicateHandle(other.handle, &handle);
        assert(SUCCEEDED(hr));
        UNREFERENCED_PARAMETER(hr);
    }

    ~Event()
    {
        PlayFabEventManagerEventCloseHandle(handle);
    }

    PlayFabEventManagerEventHandle handle;
};

struct WriteEventContext
{
    TestContext& testContext;
    std::atomic<size_t>& eventsWritten;
    Event event;
};

void CALLBACK WriteEventComplete(void* context, HRESULT result, const char* /*assignedEventId*/)
{
    auto writeEventContext = std::unique_ptr<WriteEventContext>{ static_cast<WriteEventContext*>(context) };

    std::stringstream message;
    if (FAILED(result))
    {
        message << "PlayFabEventManagerWriteEventAsync async result failed hr=" << std::hex << result;
        writeEventContext->testContext.Fail(message.str());
    }
    else
    {
        writeEventContext->eventsWritten.fetch_add(1);
    }
}

void EventManagerTests::TestWriteEvent(TestContext& testContext)
{
    std::atomic<size_t> eventsWritten{ 0 };

    Event event{ PlayFabEventManagerEventType::Lightweight, "TestEvent" };
    PlayFabEventManagerEventSetStringProperty(event.handle, "Key", "Value");

    auto writeContext = std::unique_ptr<WriteEventContext>(new WriteEventContext{ testContext, eventsWritten, event });

    HRESULT hr = PlayFabEventManagerWriteEventAsync(entityHandle, event.handle, writeContext.get(), &WriteEventComplete);
    if (SUCCEEDED(hr))
    {
        writeContext.release();
    }
    else
    {
        testContext.Fail("PlayFabEventManagerWriteEventAsync", hr);
    }

    hr = PlayFabEventManagerTerminate(entityHandle, true, nullptr, nullptr);
    if (FAILED(hr))
    {
        testContext.Fail("PlayFabEventManagerTerminate", hr);
    }
    else if (eventsWritten != 1)
    {
        testContext.Fail("PlayFabEventManagerTerminate returned prior to event being written");
    }
    else
    {
        testContext.Pass();
    }
}

void EventManagerTests::WriteEventsStressTest(TestContext& testContext)
{
    struct Context
    {
        std::atomic<size_t> writeEventCompletionCount;
        TestContext& testContext;
    };

    auto context = std::unique_ptr<Context>(new Context{ 0, testContext });

    PlayFabEventManagerWriteEventCompletionCallback* callback = [](void* c, HRESULT /*result*/, const char* /*assignedEventId*/)
    {
        auto context = static_cast<Context*>(c);
        ++context->writeEventCompletionCount;
    };

    static constexpr size_t lightweightEventCount = 50; // Choose a value that shouldn't exceed default event buffer size
    for (auto i = 0u; i < lightweightEventCount; ++i)
    {
        std::stringstream eventName;
        eventName << "LightweightEvent" << i;
        Event event{ PlayFabEventManagerEventType::Lightweight, eventName.str().data() };
        PlayFabEventManagerEventSetStringProperty(event.handle, "Key", "Value");

        HRESULT hr = PlayFabEventManagerWriteEventAsync(entityHandle, event.handle, context.get(), callback);
        if (FAILED(hr))
        {
            testContext.Fail("PlayFabEventManagerWriteEventAsync", hr);
            break;
        }
    }

    static constexpr size_t heavyweightEventCount = 10;
    for (auto i = 0u; i < heavyweightEventCount; ++i)
    {
        std::stringstream eventName;
        eventName << "HeavyWeightEvent" << i;
        Event event{ PlayFabEventManagerEventType::Heavyweight, eventName.str().data() };
        PlayFabEventManagerEventSetStringProperty(event.handle, "Key", "Value");

        HRESULT hr = PlayFabEventManagerWriteEventAsync(entityHandle, event.handle, context.get(), callback);
        if (FAILED(hr))
        {
            testContext.Fail("PlayFabEventManagerWriteEventAsync", hr);
            break;
        }
    }

    HRESULT hr = PlayFabEventManagerTerminate(entityHandle, false, context.get(),
        [](void* c)
        {
            auto context = std::unique_ptr<Context>(static_cast<Context*>(c));
            if (context->writeEventCompletionCount == heavyweightEventCount + lightweightEventCount)
            {
                context->testContext.Pass();
            }
            else
            {
                context->testContext.Fail("Termination callback invoked before all events were written");
            }
        });

    if (FAILED(hr))
    {
        testContext.Fail("PlayFabEventManagerWriteEventAsync", hr);
    }
    else
    {
        context.release();
    }
}

void EventManagerTests::AddTests()
{
    AddTest("TestWriteEvent", &EventManagerTests::TestWriteEvent);
    AddTest("WriteEventsStressTest", &EventManagerTests::WriteEventsStressTest);
}

void EventManagerTests::ClassSetUp()
{
    PlayFabInitialize(testTitleData.titleId.data(), nullptr, &stateHandle);
}

void EventManagerTests::ClassTearDown()
{
    XAsyncBlock async{};
    HRESULT hr = PlayFabCleanupAsync(stateHandle, &async);
    assert(SUCCEEDED(hr));

    hr = XAsyncGetStatus(&async, true);
    assert(SUCCEEDED(hr));

    UNREFERENCED_PARAMETER(hr);
}

void EventManagerTests::SetUp(TestContext& testContext)
{
    entityHandle = nullptr;

    PlayFabClientLoginWithCustomIDRequest request{};
    request.customId = "CustomId";
    bool createAccount = true;
    request.createAccount = &createAccount;
    request.titleId = testTitleData.titleId.data();

    XAsyncBlock async{};
    HRESULT hr = PlayFabClientLoginWithCustomIDAsync(stateHandle, &request, &async);
    if (SUCCEEDED(hr))
    {
        // Synchronously what for login to complete
        hr = XAsyncGetStatus(&async, true);
        if (SUCCEEDED(hr))
        {
            PFGetAuthResult(&async, &entityHandle);
        }
    }

    if (!entityHandle)
    {
        testContext.Skip("Skipping test unable to login");
    }
}

void EventManagerTests::TearDown(TestContext& /*testContext*/)
{
    PlayFabEntityCloseHandle(entityHandle);
    entityHandle = nullptr;
}

}