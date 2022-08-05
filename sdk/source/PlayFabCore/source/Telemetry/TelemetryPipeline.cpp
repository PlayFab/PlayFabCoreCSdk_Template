#include "stdafx.h"
#include "TelemetryPipeline.h"
#include "Events/Events.h"

namespace PlayFab
{

struct EventData
{
    SharedPtr<Entity> entity;
    String eventNamespace;
    String eventName;
    String payloadJson;
    time_t emitTime;
};

// Simple, thread-safe EventBuffer based on std::queue.
// Potential for optimization here with either LHC's LocklessQueue or XPlatCpp CELL-adapted EventBuffer
class EventBuffer
{
public:
    EventBuffer() = default;
    EventBuffer(EventBuffer const&) = delete;
    EventBuffer& operator=(EventBuffer const&) = delete;
    ~EventBuffer() = default;

    HRESULT Push(SharedPtr<Entity> entity, const char* eventNamespace, const char* eventName, const char* payloadJson) noexcept;
    bool PopFront(EventData& eventData) noexcept;

private:
    std::mutex m_mutex;
    Queue<EventData> m_queue;
};

class EventUploader : public ITaskQueueWork, public std::enable_shared_from_this<EventUploader>
{
public:
    EventUploader(RunContext rc, SharedPtr<TitlePlayer> uploadingEntity, SharedPtr<EventBuffer> buffer, uint32_t maxEventsPerBatch, uint32_t maxWaitTimeInSeconds, uint32_t pollDelayInMs);

    void Start();
private:
    void Run() noexcept override;

    RunContext m_rc;
    SharedPtr<TitlePlayer> m_entity;
    SharedPtr<EventBuffer> m_buffer;
    uint32_t const m_maxEventsPerBatch;
    uint32_t const m_maxWaitTimeInSeconds;
    uint32_t const m_pollDelayInMs;
    Vector<Events::EventContents> m_pendingPayload;
    time_t m_oldestEventTimeStamp;
    std::mutex m_mutex;
};

TelemetryPipeline::TelemetryPipeline(RunContext rc, SharedPtr<TitlePlayer> uploadingEntity, uint32_t maxEventsPerBatch, uint32_t maxWaitTimeInSeconds, uint32_t pollDelayInMs) noexcept :
    m_buffer{ MakeShared<EventBuffer>() },
    m_uploader{ MakeShared<EventUploader>(std::move(rc), std::move(uploadingEntity), m_buffer, maxEventsPerBatch, maxWaitTimeInSeconds, pollDelayInMs) }
{
    m_uploader->Start();
}

// Should we do client side payload validation?
HRESULT TelemetryPipeline::EmitEvent(SharedPtr<Entity> entity, const char* eventNamespace, const char* eventName, const char* payloadJson) noexcept
{
    return m_buffer->Push(std::move(entity), eventNamespace, eventName, payloadJson);
}

HRESULT EventBuffer::Push(SharedPtr<Entity> entity, const char* eventNamespace, const char* eventName, const char* payloadJson) noexcept
{
    RETURN_HR_INVALIDARG_IF_NULL(eventNamespace);
    RETURN_HR_INVALIDARG_IF_NULL(eventName);
    RETURN_HR_INVALIDARG_IF_NULL(payloadJson);

    // Copy event data outside lock scope
    EventData data{ std::move(entity), eventNamespace, eventName, payloadJson, std::time(nullptr) };

    std::lock_guard<std::mutex> lock{ m_mutex };
    m_queue.push(std::move(data));

    return S_OK;
}

bool EventBuffer::PopFront(EventData& eventData) noexcept
{
    std::lock_guard<std::mutex> lock{ m_mutex };
    if (m_queue.empty())
    {
        return false;
    }

    std::swap(eventData, m_queue.front());
    m_queue.pop();
    return true;
}

EventUploader::EventUploader(RunContext rc, SharedPtr<TitlePlayer> uploadingEntity, SharedPtr<EventBuffer> buffer, uint32_t maxEventsPerBatch, uint32_t maxWaitTimeInSeconds, uint32_t pollDelayInMs) :
    m_rc{ std::move(rc) },
    m_entity{ std::move(uploadingEntity) },
    m_buffer{ std::move(buffer) },
    m_maxEventsPerBatch{ maxEventsPerBatch },
    m_maxWaitTimeInSeconds{ maxWaitTimeInSeconds },
    m_pollDelayInMs{ pollDelayInMs }
{
}

void EventUploader::Start()
{
    TRACE_VERBOSE(__FUNCTION__);
    // Should never be called twice. Make clearer from interface
    m_rc.TaskQueueSubmitWork(shared_from_this(), 0);
}

void EventUploader::Run() noexcept
{
    TRACE_VERBOSE(__FUNCTION__);

    std::unique_lock<std::mutex> lock{ m_mutex };

    for (bool haveEvents = true; haveEvents; )
    {
        EventData eventData;
        haveEvents = m_buffer->PopFront(eventData);

        if (haveEvents)
        {
            Events::EventContents eventContents;
            eventContents.entity = eventData.entity->EntityKey();
            eventContents.eventNamespace = std::move(eventData.eventNamespace);
            eventContents.name = std::move(eventData.eventName);
            eventContents.payloadJSON = std::move(eventData.payloadJson);
            eventContents.originalTimestamp = eventData.emitTime;

            if (m_pendingPayload.empty())
            {
                m_oldestEventTimeStamp = eventData.emitTime;
            }

            m_pendingPayload.push_back(std::move(eventContents));
        }

        if ((!m_pendingPayload.empty() && std::time(nullptr) - m_oldestEventTimeStamp >= m_maxWaitTimeInSeconds) || m_pendingPayload.size() >= m_maxEventsPerBatch)
        {
            Events::WriteEventsRequest request;
            request.events = std::move(m_pendingPayload);

            assert(m_pendingPayload.empty());

            Events::EventsAPI::WriteEvents(m_entity, request, m_rc.Derive()).Finally([](Result<Events::WriteEventsResponse> result)
            {
                // For now, if upload fails due to transient error that telemetry will just be lost. This is at parity with the
                // behavior of the XPlatCpp Event pipeline. If needed, we could requeue those events and add some retry logic similar to XSAPI
                // in proc Event service.

                if (FAILED(result.hr))
                {
                    TRACE_ERROR_HR(result.hr, "TelemetryPipeline EventUploader WriteEvents failed. Telemetry data will be lost.");
                }
            });
        }
    }

    // Release lock before scheduling next poll just in case
    lock.unlock();

    // Using a polling model to check EventBuffer again after we've emptied it. This is the same algorithm used by XPlatCpp Event Pipeline.
    m_rc.TaskQueueSubmitWork(shared_from_this(), m_pollDelayInMs);
}

}
