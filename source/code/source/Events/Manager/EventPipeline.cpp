#include "stdafx.h"
#include "EventPipeline.h"
#include <Events/EventsApi.h>
#include "Event.h"
#include "AsyncProvider.h"

using namespace PlayFab::EventsModels;

namespace PlayFab
{
namespace EventManager
{

// XAsync provider for a long running background operation that periodically polls and consumes events from
// an EventPipeline's buffer. When an event batch is ready, it is written using the appropriate PlayFab API
// (depending on the EventPipelineType).
//
// The operation will continue to poll until it is explicitly terminated with Terminate or the associated
// EventPipeline is destroyed. If Terminate is called, the provider will write any remaining events, wait for
// in flight batches to complete, and then invoke a TerminationCallback to indicate that it is safe to shutdown
// without events being lost. Note that the write result for each event will still be delivered normally via the
// return AsyncOp even when the Provider is terminated.
class WriteEventsProvider : public Provider
{
public:
    WriteEventsProvider(SharedPtr<EventPipeline> pipeline, SharedPtr<HttpClient const> httpClient, SharedPtr<AuthTokens const> tokens, const TaskQueue& queue);
    WriteEventsProvider(const WriteEventsProvider& source) = delete;
    WriteEventsProvider& operator=(const WriteEventsProvider& source) = delete;
    ~WriteEventsProvider();

    HRESULT Terminate(TerminationCallback callback);

private:
    // Provider overrides
    HRESULT DoWork(TaskQueue&& queue) override;
    HRESULT Cancel(TaskQueue&& queue) override;

private:
    void SendBatch(const TaskQueue& queue);

    WeakPtr<EventPipeline> m_pipeline;
    PlayFabEventManagerPipelineType const m_pipelineType; // redundant with m_pipeline->pipelineType but we need this to write events even if m_pipline is expired

    EventsAPI const m_eventsAPI;

    TaskQueue const m_taskQueue;
    XAsyncBlock m_asyncBlock;
    TerminationCallback m_terminationCallback;

    std::atomic<size_t> m_batchesInFlight{ 0 };
    std::atomic<bool> m_terminated{ false };
    Vector<EventContext> m_batch;
    Clock::time_point m_batchCreationTime;
};

EventPipeline::EventPipeline(PlayFabEventManagerPipelineType type, SharedPtr<HttpClient const> httpClient, SharedPtr<AuthTokens const> tokens) :
    pipelineType{ type },
    m_httpClient{ std::move(httpClient) },
    m_tokens{ std::move(tokens) },
    m_state{ State::Created }
{
}

HRESULT EventPipeline::CustomizeSettings(EventPipelineSettings settings)
{
    switch (m_state)
    {
    case State::Created:
    {
        m_settings = settings;
        return S_OK;
    }
    case State::Active:
    case State::Terminated:
    {
        // Settings cannot be changed after events have already been added to the pipeline
        return E_PLAYFAB_EVENTMANAGERINVALIDOPERATION;
    }
    default:
    {
        assert(false);
        return E_UNEXPECTED;
    }
    }
}

AsyncOp<String> EventPipeline::IntakeEvent(SharedPtr<Event const> event)
{
    switch (m_state)
    {
    case State::Created:
    {
        // Create the EventBuffer and WriteEventsProvider the first time IntakeEvent is called. This will lock the pipeline settings.
        m_state.store(State::Active);

        m_buffer = MakeUnique<EventBuffer>(m_settings.minimumBufferSizeInBytes);

        // EventPipeline has a non-owning pointer to the WriteEventsProvider - it's lifetime is managed automatically
        // by the Provider class. The background operation will run until it's explicitly terminated or the pipeline its consuming
        // events from is destroyed.
        m_writeEventsProvider = MakeUnique<WriteEventsProvider>(shared_from_this(), m_httpClient, m_tokens, m_settings.queue).release();
        Provider::Run(UniquePtr<Provider>{ m_writeEventsProvider });
     
        break;
    }
    case State::Terminated:
    {
        return E_PLAYFAB_EVENTMANAGERINVALIDOPERATION;
    }
    default: break;
    }

    auto eventAsyncContext = MakeShared<AsyncOpContext<String>>();
    EventContext eventContext{ std::move(event), eventAsyncContext };

    auto putBufferResult = m_buffer->TryPut(std::move(eventContext));
    if (Failed(putBufferResult))
    {
        eventAsyncContext->Complete(putBufferResult.hr);
    }

    return eventAsyncContext;
}

HRESULT EventPipeline::Terminate(TerminationCallback callback)
{
    auto state = m_state.exchange(State::Terminated);

    switch (state)
    {
    case State::Created:
    case State::Terminated:
    {
        // Trivially done
        callback();
        return S_OK;
    }
    case State::Active:
    {
        RETURN_IF_FAILED(m_buffer->Terminate());
        return m_writeEventsProvider->Terminate(std::move(callback));
    }
    default:
    {
        assert(false);
        return E_UNEXPECTED;
    }
    }
}

WriteEventsProvider::WriteEventsProvider(SharedPtr<EventPipeline> pipeline, SharedPtr<HttpClient const> httpClient, SharedPtr<AuthTokens const> tokens, const TaskQueue& queue) :
    Provider{ &m_asyncBlock, XASYNC_IDENTITY(WriteEventsProvider) },
    m_pipeline{ pipeline },
    m_pipelineType{ pipeline->pipelineType },
    m_eventsAPI{ std::move(httpClient), std::move(tokens) },
    m_taskQueue{ queue.DeriveWorkerQueue() },
    m_asyncBlock{ m_taskQueue.GetHandle(), nullptr, nullptr }
{
}

WriteEventsProvider::~WriteEventsProvider()
{
    // Invoking m_terminationCallback here rather than in XAsync callback because the provider may be destroyed prior to
    // the XAsync callback being invoked. XAsync framework aggressively cleans up the provider as soon it can, and because the operation
    // has no result payload, cleanup happens immediately after DoWork (prior to the completion callback being invoked in some cases)

    if (m_terminationCallback)
    {
        m_terminationCallback();
    }
}

HRESULT WriteEventsProvider::Terminate(TerminationCallback callback)
{
    if (m_terminated)
    {
        // Calling Terminate twice is not allowed
        return E_PLAYFAB_EVENTMANAGERINVALIDOPERATION;
    }

    m_terminationCallback = std::move(callback);
    XAsyncCancel(&m_asyncBlock);
    return S_OK;
}

HRESULT WriteEventsProvider::DoWork(TaskQueue&& queue)
{
    if (m_terminated)
    {
        // The pipeline was terminated. Awaiting for batches in flight to complete, but no more work to do
        return E_PENDING;
    }

    SharedPtr<EventPipeline> pipeline = m_pipeline.lock();
    if (!pipeline)
    {
        // If the pipeline has been destroyed, cancel the task and return E_PENDING. WriteEventsProvider::Cancel 
        // ensures pending events & batches in flight complete before completing the XAsync operation
        XAsyncCancel(&m_asyncBlock);
        return E_PENDING;
    }

    m_batch.reserve(pipeline->m_settings.maxItemsInBatch);

    if (m_batchesInFlight >= pipeline->m_settings.maxBatchesInFlight)
    {
        // do not take new events from m_buffer if batches currently in flight are at the maximum allowed number
        // and are not sent out (or received an error) yet
        RETURN_IF_FAILED(Schedule(pipeline->m_settings.pollDelayInMs));
        return E_PENDING;
    }

    auto getFromBufferResult = pipeline->m_buffer->TryTake();
    if (Succeeded(getFromBufferResult))
    {
        // Successfully took event from buffer. Add it to current batch
        m_batch.emplace_back(getFromBufferResult.ExtractPayload());

        // If it's the first event in an incomplete batch then set the batch creation time
        if (m_batch.size() == 1)
        {
            m_batchCreationTime = Clock::now();
        }

        // Send batch if its full
        if (m_batch.size() >= pipeline->m_settings.maxItemsInBatch)
        {
            SendBatch(queue);
        }

        RETURN_IF_FAILED(Schedule(0));
        return E_PENDING;
    }

    if (!m_batch.empty())
    {
        // check if the batch wait time expired
        std::chrono::seconds batchAge = std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - m_batchCreationTime);
        if (batchAge.count() >= (int32_t)pipeline->m_settings.maxBatchWaitTimeInSeconds)
        {
            // batch wait time elapsed, send incomplete batch
            SendBatch(queue);
            RETURN_IF_FAILED(Schedule(pipeline->m_settings.pollDelayInMs));
            return E_PENDING;
        }
    }

    RETURN_IF_FAILED(Schedule(pipeline->m_settings.pollDelayInMs));
    return E_PENDING;
}

HRESULT WriteEventsProvider::Cancel(TaskQueue&& queue)
{
    m_terminated.store(true);

    SharedPtr<EventPipeline> pipeline = m_pipeline.lock();
    if (pipeline)
    {
        // Get any remaining events from buffer before sending final batch. Ignore limits defined by PipelineSettings
        // during termination
        for(;;)
        {
            auto getFromBufferResult = pipeline->m_buffer->TryTake();
            if (Succeeded(getFromBufferResult))
            {
                m_batch.emplace_back(getFromBufferResult.ExtractPayload());
            }
            else
            {
                break;
            }
        }
    }

    if (!m_batch.empty())
    {
        SendBatch(queue);
    }
    else if (m_batchesInFlight == 0)
    {
        // If their are no pending events or in batches in flight, cancellation is trivially complete.
        Provider::Complete(0);
    }
    return S_OK;
}

void WriteEventsProvider::SendBatch(const TaskQueue& queue)
{
    auto batch{ std::move(m_batch) };
    m_batch.clear();

    // create a WriteEvents API request to send the batch
    PlayFabEventsWriteEventsRequest request{};
    Vector<const PlayFabEventsEventContents*> events;
    events.reserve(batch.size());

    for (const auto& eventContext : batch)
    {
        events.push_back(&eventContext.event->EventContents());
    }
    request.events = events.data();
    request.eventsCount = static_cast<uint32_t>(events.size());

    ++m_batchesInFlight;
    AsyncOp<WriteEventsResponse> writeOperation{ nullptr };

    switch (m_pipelineType)
    {
    case PlayFabEventManagerPipelineType::PlayStream:
    {
        // call Events API to send the batch
        writeOperation = m_eventsAPI.WriteEvents(request, queue);
        break;
    }
    case PlayFabEventManagerPipelineType::Telemetry:
    {
        // call Events API to send the batch, bypassing Playstream
        writeOperation = m_eventsAPI.WriteTelemetryEvents(request, queue);
        break;
    }
    default: assert(false); // Unrecogized pipeline type
    }

    writeOperation.Finally([this, batch](Result<WriteEventsResponse> result)
    {
        // Complete asyncOpContexts for each event in the batch
        if (Succeeded(result))
        {
            auto& resultPayload{ result.Payload() };

            // returned "assignedEventIds" order is guaranteed to be in the same order of events written
            for (size_t eventIndex = 0; eventIndex < batch.size(); ++eventIndex)
            {
                if (eventIndex < resultPayload.assignedEventIdsCount)
                {
                    batch[eventIndex].writeEventAsyncOp->Complete(Result<String>{ resultPayload.assignedEventIds[eventIndex] });
                }
                else
                {
                    // No eventId was assigned, complete with empty string
                    batch[eventIndex].writeEventAsyncOp->Complete(String{});
                }
            }
        }
        else
        {
            for (const auto& eventContext : batch)
            {
                eventContext.writeEventAsyncOp->Complete(result.hr);
            }
        }

        if (--m_batchesInFlight == 0 && m_terminated)
        {
            Provider::Complete(0);
        }
    });
}

} // namespace EventManager
} // namespace PlayFab
