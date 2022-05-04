#pragma once

#include "TitlePlayer.h"

namespace PlayFab
{

class EventBuffer;
class EventUploader;

class TelemetryPipeline
{
public:
    TelemetryPipeline(RunContext rc, SharedPtr<TitlePlayer> uploadingEntity, uint32_t maxWaitTimeInSeconds, uint32_t pollDelayInMs) noexcept;

    HRESULT EmitEvent(const char* eventNamespace, const char* eventName, const char* payloadJson) noexcept;

private:
    SharedPtr<EventBuffer> m_buffer;
    SharedPtr<EventUploader> m_uploader;
};

}
