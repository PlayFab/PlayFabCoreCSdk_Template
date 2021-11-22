// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include <PFEntity.h>
#include <httpClient/async.h>

extern "C"
{

/// <summary>
/// Handle to a PlayFabEventManagerEvent. Create events using PlayFabEventManagerEventCreate and write them to PlayFab
/// with PlayFabEventManagerWriteEventAsync. When an event is no longer needed, call PlayFabEventManagerEventCloseHandle
/// to release the event object.
/// </summary>
typedef struct PlayFabEventManagerEvent* PlayFabEventManagerEventHandle;

/// <summary>
/// PlayFab Event types
/// </summary>
enum class PlayFabEventManagerEventType : uint32_t
{
    /// <summary>
    /// Default event type (set in global configuration).
    /// </summary>
    Default,

    /// <summary>
    /// Lightweight event. Will be sent to WriteTelemetryEvents endpoint.
    /// </summary>
    Lightweight,

    /// <summary>
    /// Lightweight event. Will be sent to WriteEvents endpoint.
    /// </summary>
    Heavyweight
};

/// <summary>
/// PlayFab EventPipeline types
/// </summary>
enum class PlayFabEventManagerPipelineType : uint32_t
{
    /// <summary>
    /// PlayStream event pipeline
    /// </summary>
    PlayStream = 0x1,

    /// <summary>
    /// PlayFab telemetry pipeline (bypasses PlayStream)
    /// </summary>
    Telemetry = 0x2,

    /// <summary>
    /// All pipelines. Passed to PlayFabEventManagerCustomizeEventPipelineSettings to configure settings for all pipelines at once.
    /// </summary>
    All = 0x3
};

DEFINE_ENUM_FLAG_OPERATORS(PlayFabEventManagerPipelineType);

// TODO consider fire and forget style (auto retry etc.)
/// <summary>
/// Callback routine that is invoked when an event is uploaded to PlayFab.
/// </summary>
/// <param name='context'>A context pointer that was passed during PlayFabEventManagerWriteEventAsync.</param>
/// <param name='result'>A result value indicating whether the upload was successful.</param>
/// <param name='assignedEventId'>Unique identifier assigned to the event by the server. Will be null if no ID is assigned.</param>
/// <seealso cref='PlayFabEventManagerWriteEventAsync' />
typedef void CALLBACK PlayFabEventManagerWriteEventCompletionCallback(_In_opt_ void* context, _In_ HRESULT result, _In_opt_ const char* assignedEventId);

/// <summary>
/// A callback that is invoked when EventManger termination completes.
/// </summary>
/// <param name='context'>A context pointer that was passed during PlayFabEventManagerTerminate.</param>
/// <seealso cref='PlayFabEventManagerTerminate' />
typedef void CALLBACK PlayFabEventManagerTerminatedCallback(_In_opt_ void* context);

/// <summary>
/// Creates a PlayFab Event to upload with EventManager.
/// </summary>
/// <param name="eventType">The type of event.</param>
/// <param name="eventName">The name of the event.</param>
/// <param name="eventNamespace">Optional namespace. The namespace of the Event must be 'custom' or start with 'custom'. 'custom' will be used if no namespace is provided</param>
/// <param name="entityId">Optional entity ID for entity associated with the event. If not provided, the event will apply to the entity that writes it.</param>
/// <param name="entityType">Optional entity type for entity associated with the event. If not provided, the event will apply to the entity that writes it.</param>
/// <param name="eventHandle">Returned PlayFabEventManagerEventHandle.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// The returned eventHandle must be closed with PlayFabEventManagerEventCloseHandle when it is no longer needed.
/// </remarks>
HRESULT PlayFabEventManagerEventCreate(
    _In_ PlayFabEventManagerEventType eventType,
    _In_ const char* eventName,
    _In_opt_ const char* eventNamespace,
    _In_opt_ const char* entityId,
    _In_opt_ const char* entityType,
    _Out_ PlayFabEventManagerEventHandle* eventHandle
) noexcept;

/// <summary>
/// Duplicates a PlayFabEventManagerEventHandle.
/// </summary>
/// <param name="eventHandle">Event handle to duplicate.</param>
/// <param name="duplicatedEventHandle">The duplicated handle.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// Both the duplicated handle and the original handle need to be closed with PlayFabEventManagerEventCloseHandle when they
/// are no longer needed.
/// </remarks>
HRESULT PlayFabEventManagerEventDuplicateHandle(
    _In_ PlayFabEventManagerEventHandle eventHandle,
    _Out_ PlayFabEventManagerEventHandle* duplicatedEventHandle
) noexcept;

/// <summary>
/// Closes a PlayFabEventManagerEventHandle.
/// </summary>
/// <param name="eventHandle">Event handle to close.</param>
/// <returns>Result code for this API operation.</returns>
void PlayFabEventManagerEventCloseHandle(
    _In_ PlayFabEventManagerEventHandle eventHandle
) noexcept;

/// <summary>
/// Set the namespace for the event.
/// </summary>
/// <param name="eventHandle">Event to modify.</param>
/// <param name="eventNamespace">Event namespace. The namespace of the Event must be 'custom' or start with 'custom'.</param>
/// <returns>Result code for this API operation.</returns>
HRESULT PlayFabEventManagerEventSetNamespace(
    _In_ PlayFabEventManagerEventHandle eventHandle,
    _In_ const char* eventNamespace
) noexcept;

/// <summary>
/// Set the Entity associated with the event. If not set, the event will apply to the entity that writes it.
/// </summary>
/// <param name="eventHandle">Event to modify.</param>
/// <param name="entityId">Unique ID of the entity.</param>
/// <param name="entityType">(Optional) Entity type. See https://docs.microsoft.com/gaming/playfab/features/data/entities/available-built-in-entity-types. </param>
/// <returns>Result code for this API operation.</returns>
HRESULT PlayFabEventManagerEventSetEntity(
    _In_ PlayFabEventManagerEventHandle eventHandle,
    _In_ const char* entityId,
    _In_opt_ const char* entityType
) noexcept;

/// <summary>
/// Set a property associated with the event. Properties are arbitrary key/value pairs that will be added to a JSON payload.
/// </summary>
/// <param name="eventHandle">Event to modify.</param>
/// <param name="key">Property key.</param>
/// <param name="value">Property value.</param>
/// <returns>Result code for this API operation.</returns>
HRESULT PlayFabEventManagerEventSetStringProperty(
    _In_ PlayFabEventManagerEventHandle eventHandle,
    _In_ const char* key,
    _In_ const char* value
) noexcept;

/// <summary>
/// Set a property associated with the event. Properties are arbitrary key/value pairs that will be added to a JSON payload.
/// </summary>
/// <param name="eventHandle">Event to modify.</param>
/// <param name="key">Property key.</param>
/// <param name="value">Property value.</param>
/// <returns>Result code for this API operation.</returns>
HRESULT PlayFabEventManagerEventSetBooleanProperty(
    _In_ PlayFabEventManagerEventHandle eventHandle,
    _In_ const char* key,
    _In_ bool value
) noexcept;

/// <summary>
/// Set a property associated with the event. Properties are arbitrary key/value pairs that will be added to a JSON payload.
/// </summary>
/// <param name="eventHandle">Event to modify.</param>
/// <param name="key">Property key.</param>
/// <param name="value">Property value.</param>
/// <returns>Result code for this API operation.</returns>
HRESULT PlayFabEventManagerEventSetIntProperty(
    _In_ PlayFabEventManagerEventHandle eventHandle,
    _In_ const char* key,
    _In_ int64_t value
) noexcept;

/// <summary>
/// Set a property associated with the event. Properties are arbitrary key/value pairs that will be added to a JSON payload.
/// </summary>
/// <param name="eventHandle">Event to modify.</param>
/// <param name="key">Property key.</param>
/// <param name="value">Property value.</param>
/// <returns>Result code for this API operation.</returns>
HRESULT PlayFabEventManagerEventSetUintProperty(
    _In_ PlayFabEventManagerEventHandle eventHandle,
    _In_ const char* key,
    _In_ uint64_t value
) noexcept;

/// <summary>
/// Set a property associated with the event. Properties are arbitrary key/value pairs that will be added to a JSON payload.
/// </summary>
/// <param name="eventHandle">Event to modify.</param>
/// <param name="key">Property key.</param>
/// <param name="value">Property value.</param>
/// <returns>Result code for this API operation.</returns>
HRESULT PlayFabEventManagerEventSetDoubleProperty(
    _In_ PlayFabEventManagerEventHandle eventHandle,
    _In_ const char* key,
    _In_ double value
) noexcept;

/// <summary>
/// Default values for event pipeline settings.
/// </summary>
/// <seealso cref='PlayFabEventManagerCustomizeEventPipelineSettings' />
const size_t PlayFabEventManagerBufferSizeBytesDefault = 256;
const uint32_t PlayFabEventManagerMaxItemsInBatchDefault = 5;
const uint32_t PlayFabEventManagerMaxBatchWaitTimeInSecondsDefault = 3;
const uint32_t PlayFabEventManagerMaxBatchesInFlightDefault = 16;
const uint32_t PlayFabEventManagerPollDelayInMsDefault = 10;

/// <summary>
/// Optional API set set custom event pipeline settings. Pipeline settings apply to a single entity and must be they must be configured
/// prior to calling PlayFabEventManagerWriteEventAsync. If values are not provided PlayFabEventManagerCustomizeEventPipelineSettings
/// is never called) the above defaults will be used.
/// </summary>
/// <param name="entityHandle">PFEntityHandle to customize settings for.</param>
/// <param name="pipeline">The event pipeline the provided settings will be applied to. Pass PlayFabEventManagerPipelineType::All to configure settings for all event pipelines.</param>
/// <param name="queue">XTaskQueue where background work will be scheduled. If not default value is "null" (process default queue will be used).</param>
/// <param name="minimumBufferSizeBytes">The minimum size of the event buffer, in bytes. The actually allocated size will be a power of 2 that is equal or greater than this value.</param>
/// <param name="maxItemsInBatch">The max number of items (events) a batch can hold before it is sent out.</param>
/// <param name="maxBatchWaitTimeInSeconds">The max wait time before a batch must be sent out even if it's still incomplete, in seconds.</param>
/// <param name="maxBatchesInFlight">The max number of batches currently "in flight" (sent to PlayFab service but pending response).</param>
/// <param name="pollDelayInMs">The delay between each time the background operation will poll the event buffer and evaluate if events should be uploaded.</param>
/// <returns>Result code for this API operation.</returns>
HRESULT PlayFabEventManagerCustomizeEventPipelineSettings(
    _In_ PFEntityHandle entityHandle,
    _In_ PlayFabEventManagerPipelineType pipeline,
    _In_opt_ XTaskQueueHandle queue,
    _In_opt_ size_t* minimumBufferSizeBytes,
    _In_opt_ size_t* maxItemsInBatch,
    _In_opt_ uint32_t* maxBatchWaitTimeInSeconds,
    _In_opt_ size_t* maxBatchesInFlight,
    _In_opt_ uint32_t* pollDelayInMs
) noexcept;

/// <summary>
/// Write an event to PlayFab server. Events will be buffered, batched, and uploaded in the background.
/// Prior to shutdown, PlayFabEventManagerTerminate should be called to ensure any pending events
/// get written to the service.
/// </summary>
/// <param name="entityHandle">PFEntityHandle returned from a auth call.</param>
/// <param name="eventHandle">Event to upload.</param>
/// <param name="callbackContext">Optional context pointer to pass to the callback.</param>
/// <param name="callback">Optional callback to be called when the event upload (attempt) completes.</param>
/// <returns>Result code for this API operation.</returns>
HRESULT PlayFabEventManagerWriteEventAsync(
    _In_ PFEntityHandle entityHandle,
    _In_ PlayFabEventManagerEventHandle eventHandle,
    _In_opt_ void* callbackContext,
    _In_opt_ PlayFabEventManagerWriteEventCompletionCallback* callback
) noexcept;

/// <summary>
/// Terminate event pipelines prior to shutdown. Ensures pending events are written and in-flight write requests complete.
/// If the entityHandle is closed without calling PlayFabEventManagerTerminate, some buffered
/// events may be lost. Note that the write result for each event will still be delivered normally via the
/// callback provided to PlayFabEventManagerWriteEventAsync.
/// </summary>
/// <param name="entityHandle">PFEntityHandle returned from a auth call.</param>
/// <param name='wait'>True to synchronously wait for the termination to complete.</param>
/// <param name="callbackContext">Optional context pointer to pass to the callback.</param>
/// <param name="callback">An optional callback that will be called when termination completes.</param>
/// <returns>Result code for this API operation.</returns>
HRESULT PlayFabEventManagerTerminate(
    _In_ PFEntityHandle entityHandle,
    _In_ bool wait,
    _In_opt_ void* callbackContext,
    _In_opt_ PlayFabEventManagerTerminatedCallback* callback
) noexcept;

}
