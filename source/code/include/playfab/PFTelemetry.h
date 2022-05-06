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

const uint32_t PFTelemetryMaxEventsPerBatchDefault = 5;
const uint32_t PFTelemetryMaxWaitTimeInSecondsDefault = 3;
const uint32_t PFTelemetryPollDelayInMsDefault = 10;

/// <summary>
/// Creates a pipeline to upload telemetry events.
/// </summary>
/// <param name="entity">The Entity whose token will be used to make the PlayFab service requests in the background.</param>
/// <param name="queue">The async queue where background work will be scheduled.</param>
/// <param name="maxEventsPerBatch">The maximum number events that will be batched before writing them to PlayFab.</param>
/// <param name="maxWaitTimeInSeconds">The maximum time the pipeline will wait before sending out an incomplete batch.</param>
/// <param name="pollDelayInMs">How long the pipeline will wait to read from the event buffer again after emptying it.</param>
/// <param name="handle">Handle to the created pipeline. Needs to be closed with PFTelemetryPipelineCloseHandle when it isn't needed.</param>
/// <returns>Result code for this API operation.  Possible values are S_OK, E_PF_NOT_INITIALIZED, or E_FAIL.</returns>
PF_API PFTelemetryPipelineCreateHandle(
    _In_ PFTitlePlayerHandle entity,
    _In_opt_ XTaskQueueHandle queue,
    _In_opt_ uint32_t* maxEventsPerBatch,
    _In_opt_ uint32_t* maxWaitTimeInSeconds,
    _In_opt_ uint32_t* pollDelayInMs,
    _Out_ PFTelemetryPipelineHandle* handle
) noexcept;


/// <summary>
/// Duplicates a PFTelemetryPipelineHandle.
/// </summary>
/// <param name="handle">TelemetryPipeline handle to duplicate.</param>
/// <param name="duplicatedHandle">The duplicated handle.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// Both the duplicated handle and the original handle need to be closed with PFTelemetryPipelineCloseHandle when they are no longer needed.
/// </remarks>
PF_API PFTelemetryPipelineDuplicateHandle(
    PFTelemetryPipelineHandle handle,
    PFTelemetryPipelineHandle* duplicatedHandle
) noexcept;

/// <summary>
/// Closes a PFTelemetryPipelineHandle.
/// </summary>
/// <param name="handle">TelemetryPipeline handle to close.</param>
/// <returns>Result code for this API operation.</returns>
PF_API_(void) PFTelemetryPipelineCloseHandle(
    PFTelemetryPipelineHandle handle
) noexcept;

/// <summary>
/// Adds a telemetry event to a pipelines buffer to be uploaded. The API will return synchronously and the event
/// will be uploaded in the background based on the pipeline configuration.
/// </summary>
/// <param name="telemetryPipeline">The TelemetryPipeline to submit the event to.</param>
/// <param name="entity">The entity the event is associated with. This can be different that the entity who owns the pipeline.</param>
/// <param name="eventNamespace">The namespace in which the event is defined.</param>
/// <param name="eventName">The name of the event.</param>
/// <param name="eventPayloadJson">Arbitrary JSON data associated with the event.</param>
/// <returns>Result code for this API operation.  Possible values are S_OK, E_PF_NOT_INITIALIZED, or E_FAIL.</returns>
PF_API PFTelemetryPipelineEmitEvent(
    _In_ PFTelemetryPipelineHandle telemetryPipeline,
    _In_ PFTitlePlayerHandle entity,
    _In_z_ const char* eventNamespace,
    _In_z_ const char* eventName,
    _In_z_ const char* eventPayloadJson
) noexcept;

}
