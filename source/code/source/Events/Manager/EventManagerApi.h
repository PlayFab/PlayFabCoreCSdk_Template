#pragma once

#include <Events/EventsDataModels.h>
#include "EventPipeline.h"
#include "HttpClient.h"
#include "TaskQueue.h"

namespace PlayFab
{
class AuthTokens;

namespace EventManager
{

class Event;

// Thick logic for managing and uploading PlayFab events. Events will be batched and uploaded in the background.
// To ensure no events are lost, Terminate should be called prior to destroying the EventManagerAPI.
class EventManagerAPI
{
public:
    EventManagerAPI(SharedPtr<HttpClient const> httpClient, SharedPtr<AuthTokens const> tokens);

    HRESULT CustomizePipelineSettings(PlayFabEventManagerPipelineType pipeline, EventPipelineSettings settings);
    AsyncOp<String> WriteEvent(SharedPtr<Event const> event) const;
    HRESULT Terminate(TerminationCallback callback) const;

private:
    UnorderedMap<PlayFabEventManagerPipelineType, SharedPtr<EventPipeline>> m_pipelines;
};

} // namespace EventManager
} // namespace PlayFab
