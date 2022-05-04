#include "stdafx.h"
#include "playfab/PFTelemetry.h"
#include "Telemetry/TelemetryPipeline.h"
#include "ApiHelpers.h"

using namespace PlayFab;

PF_API PFTelemetryPipelineCreateHandle(
    _In_ PFTitlePlayerHandle playerHandle,
    _In_opt_ XTaskQueueHandle queue,
    _In_opt_ uint32_t* maxWaitTimeInSeconds,
    _In_opt_ uint32_t* pollDelayInMs,
    _Out_ PFTelemetryPipelineHandle* handle
) noexcept
{
    return ApiImpl(API_IDENTITY(PFTelemetryPipelineCreateHandle), [&](GlobalState& state)
    {
        RETURN_HR_INVALIDARG_IF_NULL(handle);

        SharedPtr<TitlePlayer> titlePlayer;
        RETURN_IF_FAILED(state.TitlePlayers().FromHandle(playerHandle, titlePlayer));

        SharedPtr<TelemetryPipeline> pipeline = MakeShared<TelemetryPipeline>(
            state.RunContext().DeriveOnQueue(queue),
            titlePlayer,
            maxWaitTimeInSeconds ? *maxWaitTimeInSeconds : PFTelemetryMaxWaitTimeInSecondsDefault,
            pollDelayInMs ? *pollDelayInMs : PFTelemetryPollDelayInMsDefault
        );

        return state.ClientTelemetryPipelines().MakeHandle(std::move(pipeline), *handle);
    });
}

PF_API PFTelemetryPipelineDuplicateHandle(
    PFTelemetryPipelineHandle handle,
    PFTelemetryPipelineHandle* duplicatedHandle
) noexcept
{
    return ApiImpl(API_IDENTITY(PFTelemetryPipelineDuplicateHandle), [&](GlobalState& state)
    {
        RETURN_HR_INVALIDARG_IF_NULL(duplicatedHandle);

        SharedPtr<TelemetryPipeline> pipeline;
        RETURN_IF_FAILED(state.ClientTelemetryPipelines().FromHandle(handle, pipeline));
        return state.ClientTelemetryPipelines().MakeHandle(std::move(pipeline), *duplicatedHandle);
    });
}

PF_API_(void) PFTelemetryPipelineCloseHandle(
    PFTelemetryPipelineHandle handle
) noexcept
{
    ApiImpl(API_IDENTITY(PFTelemetryPipelineCloseHandle), [&](GlobalState& state)
    {
        state.ClientTelemetryPipelines().CloseHandle(handle);
        return S_OK;
    });
}

PF_API PFTelemetryPipelineEmitEvent(
    _In_ PFTelemetryPipelineHandle handle,
    _In_z_ const char* eventNamespace,
    _In_z_ const char* eventName,
    _In_z_ const char* eventPayloadJson
) noexcept
{
    return ApiImpl(API_IDENTITY(PFTelemetryPipelineEmitEvent), [&](GlobalState& state)
    {
        SharedPtr<TelemetryPipeline> pipeline;
        RETURN_IF_FAILED(state.ClientTelemetryPipelines().FromHandle(handle, pipeline));
        return pipeline->EmitEvent(eventNamespace, eventName, eventPayloadJson);
    });
}
