#include "stdafx.h"
#include "EventManagerApi.h"
#include "EventPipeline.h"
#include "Event.h"

namespace PlayFab
{
namespace EventManager
{

EventManagerAPI::EventManagerAPI(SharedPtr<HttpClient const> httpClient, SharedPtr<AuthTokens const> tokens)
{
    m_pipelines.emplace(PlayFabEventManagerPipelineType::PlayStream, MakeShared<EventPipeline>(PlayFabEventManagerPipelineType::PlayStream, httpClient, tokens));
    m_pipelines.emplace(PlayFabEventManagerPipelineType::Telemetry, MakeShared<EventPipeline>(PlayFabEventManagerPipelineType::Telemetry, httpClient, tokens));
}

HRESULT EventManagerAPI::CustomizePipelineSettings(PlayFabEventManagerPipelineType pipeline, EventPipelineSettings settings)
{
    if ((pipeline & PlayFabEventManagerPipelineType::PlayStream) == PlayFabEventManagerPipelineType::PlayStream)
    {
        RETURN_IF_FAILED(m_pipelines[PlayFabEventManagerPipelineType::PlayStream]->CustomizeSettings(settings));
    }
    if ((pipeline & PlayFabEventManagerPipelineType::Telemetry) == PlayFabEventManagerPipelineType::Telemetry)
    {
        RETURN_IF_FAILED(m_pipelines[PlayFabEventManagerPipelineType::Telemetry]->CustomizeSettings(settings));
    }
    return S_OK;
}

AsyncOp<String> EventManagerAPI::WriteEvent(SharedPtr<Event const> event) const
{
    // Route the event to the appropriate pipeline
    PlayFabEventManagerPipelineType pipelineType{};

    switch (event->eventType)
    {
    case PlayFabEventManagerEventType::Default:
    case PlayFabEventManagerEventType::Lightweight:
    {
        // route lightweight (and default) events to PlayFab, bypassing PlayStream
        pipelineType = PlayFabEventManagerPipelineType::Telemetry;
        break;
    }
    case PlayFabEventManagerEventType::Heavyweight:
    {
        pipelineType = PlayFabEventManagerPipelineType::PlayStream;
        break;
    }
    default:
    {
        // Unexpected event type
        return E_UNEXPECTED;
    }
    }

    auto pipelineEntry = m_pipelines.find(pipelineType);
    if (pipelineEntry == m_pipelines.end())
    {
        return E_UNEXPECTED;
    }

    return pipelineEntry->second->IntakeEvent(event);
}

HRESULT EventManagerAPI::Terminate(TerminationCallback callback) const
{
    struct TerminationContext
    {
        std::atomic<size_t> pendingTerminations;
        TerminationCallback callback;
    };

    auto context = MakeShared<TerminationContext>();
    context->pendingTerminations = m_pipelines.size();
    context->callback = std::move(callback);

    for (auto& pipelineEntry : m_pipelines)
    {
        HRESULT hr = pipelineEntry.second->Terminate([context](void)
        {
            if (--context->pendingTerminations == 0 && context->callback != nullptr)
            {
                context->callback();
            }
        });

        RETURN_IF_FAILED(hr);
    }

    return S_OK;
}

} // namespace EventManager
} // namespace PlayFab
