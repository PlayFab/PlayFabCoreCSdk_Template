#pragma once

#include <Events/EventsApi.h>
#include "Event.h"
#include "EventBuffer.h"

namespace PlayFab
{
namespace EventManager
{

using TerminationCallback = std::function<void()>;

struct EventPipelineSettings
{
    TaskQueue queue;
    size_t minimumBufferSizeInBytes{ PlayFabEventManagerBufferSizeBytesDefault };
    size_t maxItemsInBatch{ PlayFabEventManagerMaxItemsInBatchDefault };
    uint32_t maxBatchWaitTimeInSeconds{ PlayFabEventManagerMaxBatchWaitTimeInSecondsDefault };
    size_t maxBatchesInFlight{ PlayFabEventManagerMaxBatchesInFlightDefault };
    uint32_t pollDelayInMs{ PlayFabEventManagerPollDelayInMsDefault };
};

// Producer-consumer Event pipeline. Events added by clients via IntakeEvent & consumed and written to PlayFab
// by WriteEventsProvider in the background.
class EventPipeline : public std::enable_shared_from_this<EventPipeline>
{
public:
    EventPipeline(PlayFabEventManagerPipelineType type, SharedPtr<HttpClient const> httpClient, SharedPtr<AuthTokens const> tokens);
    EventPipeline(const EventPipeline& source) = delete;
    EventPipeline& operator=(const EventPipeline& source) = delete;
    ~EventPipeline() = default;

    PlayFabEventManagerPipelineType const pipelineType;

    HRESULT CustomizeSettings(EventPipelineSettings settings);
    AsyncOp<String> IntakeEvent(SharedPtr<Event const> event);
    HRESULT Terminate(TerminationCallback callback);

private:
    SharedPtr<HttpClient const> m_httpClient;
    SharedPtr<AuthTokens const> m_tokens;

    enum class State
    {
        Created,
        Active,
        Terminated
    };

    std::atomic<State> m_state;
    EventPipelineSettings m_settings;
    UniquePtr<EventBuffer> m_buffer;
    class WriteEventsProvider* m_writeEventsProvider; // non-owning pointer

    friend class WriteEventsProvider;
};

} // namespace EventManager
} // namespace PlayFab
