// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include <playfab/PFPal.h>
#include <playfab/PFTitlePlayer.h>

extern "C"
{

typedef struct PFTelemetryPipeline* PFTelemetryPipelineHandle;

const uint32_t PFTelemetryMaxEventsPerBatchDefault = 5; // What is goal here? Why would uploading more than this in a single call ever be an issue?
const uint32_t PFTelemetryMaxWaitTimeInSecondsDefault = 3;
const uint32_t PFTelemetryMaxBatchesInFlightDefault = 16; // What is the goal of this? If we are trying to throttle service load maybe this shouldn't be configurable by client
const uint32_t PFTelemetryPollDelayInMsDefault = 10;

PF_API PFTelemetryPipelineCreateHandle(
    _In_ PFTitlePlayerHandle player, // This should probably be any Entity (ex. "Title" Entity could upload telemetry)
    _In_opt_ XTaskQueueHandle queue,
    _In_opt_ uint32_t* maxWaitTimeInSeconds,
    _In_opt_ uint32_t* pollDelayInMs,
    _Out_ PFTelemetryPipelineHandle* handle
) noexcept;

PF_API PFTelemetryPipelineDuplicateHandle(
    PFTelemetryPipelineHandle handle,
    PFTelemetryPipelineHandle* duplicatedHandle
) noexcept;

PF_API_(void) PFTelemetryPipelineCloseHandle(
    PFTelemetryPipelineHandle handle
) noexcept;

PF_API PFTelemetryPipelineEmitEvent(
    _In_ PFTelemetryPipelineHandle telemetryPipeline,
    _In_z_ const char* eventNamespace,
    _In_z_ const char* eventName,
    _In_z_ const char* eventPayloadJson
) noexcept;

}
