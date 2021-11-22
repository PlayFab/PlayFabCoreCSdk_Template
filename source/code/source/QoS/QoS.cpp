#include "stdafx.h"
#include "QoS.h"
#include "QoSSocket.h"
#include "JsonUtils.h"
#include <MultiplayerServer/MultiplayerServer.h>
#include <PlayStream/PlayStream.h>

namespace PlayFab
{

using namespace PlayStream;
using namespace MultiplayerServer;

namespace QoS
{

AsyncOp<Measurements> QoSAPI::GetMeasurements(SharedPtr<Entity> entity, uint32_t pingIterations, uint32_t timeoutMs, const TaskQueue& queue) const
{
    TaskQueue workerQueue{ queue.DeriveWorkerQueue() };

    return GetServers(entity, workerQueue).Then([this, pingIterations, timeoutMs, workerQueue](Result<void> result) -> AsyncOp<Measurements>
    {
        RETURN_IF_FAILED(result.hr);
        return PingServers(pingIterations, timeoutMs, workerQueue);
    }
    ).Then([this, entity, workerQueue](Result<Measurements> result)
    {
        // Upload result to PlayFab
        JsonValue eventJson{ rapidjson::kObjectType };
        JsonUtils::ObjectAddMember(eventJson, "ErrorCode", static_cast<uint64_t>(result.hr));

        if (Succeeded(result))
        {
            auto& measurements{ result.Payload() };
            JsonValue regionResultsJson{ rapidjson::kArrayType };

            for (auto i = 0u; i < measurements.Model().regionResultsCount; ++i)
            {
                auto& regionResult{ measurements.Model().regionResults[i] };
                JsonValue regionResultJson{ rapidjson::kObjectType };

                JsonUtils::ObjectAddMember(regionResultJson, "Region", regionResult->region);
                JsonUtils::ObjectAddMember(regionResultJson, "LatencyMs", regionResult->averageLatencyMs);
                JsonUtils::ObjectAddMember(regionResultJson, "SuccessfulPingCount", regionResult->successfulPingCount);
                JsonUtils::ObjectAddMember(regionResultJson, "FailedPingCount", regionResult->failedPingCount);
                regionResultsJson.PushBack(regionResultJson, JsonUtils::allocator);
            }

            JsonUtils::ObjectAddMember(eventJson, "RegionResults", std::move(regionResultsJson));
        }

        PFPlayStreamWriteEventsRequest request{};
        PFPlayStreamEventContents event{};
        Vector<PFPlayStreamEventContents*> events{ &event };
        auto eventJsonString = JsonUtils::WriteToString(eventJson);

        event.name = "qos_result";
        event.eventNamespace = "playfab.servers";
        event.payload.stringValue = eventJsonString.data();
        request.events = events.data();
        request.eventsCount = static_cast<uint32_t>(events.size());

        return PlayStreamAPI::WriteTelemetryEvents(entity, request, workerQueue).Then([qosResult = std::move(result) ](Result<WriteEventsResponse> result)
        {
            // Wait for WriteTelemetryEvents to complete prior to returning result to client. Although though they won't 
            // see that result, we don't want to continue work in the background in case they want to close the XTaskQueue
            // or EntityHandle after the QoS API call completes.

            TRACE_ERROR("WriteTelemetryEvents call failed when uploading QoS measurements (hr=0x%08x, message=%hs)", result.hr, result.errorMessage.data());
            return qosResult;
        });
    });
}

AsyncOp<void> QoSAPI::GetServers(SharedPtr<Entity> entity, const TaskQueue& queue) const
{
    if (!m_servers.empty())
    {
        // If we have a cached server list don't retrieve it again
        return S_OK;
    }

    ListQosServersForTitleRequest request{};
    return MultiplayerServerAPI::ListQosServersForTitle(entity, request, queue).Then([this](Result<ListQosServersForTitleResponse> result)
    {
        if (Succeeded(result))
        {
            auto& resultModel{ result.Payload() };
            for (auto i = 0u; i < resultModel.Model().qosServersCount; ++i)
            {
                auto& server = resultModel.Model().qosServers[i];
                m_servers.emplace_back(Server{ server->region, server->serverUrl });
            }
        }
        return Result<void>{ result.hr, result.errorMessage.data() };
    });
}

AsyncOp<Measurements> QoSAPI::PingServers(uint32_t pingIterations, uint32_t timeoutMs, const TaskQueue& queue) const
{
    if (m_servers.empty())
    {
        // This means we've successfully queried the QoS servers but there weren't any. Return an empty set of measurements
        return Result<Measurements>{ Measurements{} };
    }

    struct PingServersContext
    {
        TaskQueue queue;
        std::atomic<size_t> pendingPings;
        std::mutex mutex;
        UnorderedMap<String, RegionResult> regionResults;
        SharedPtr<AsyncOpContext<Measurements>> asyncOpContext;
    };

    auto context = MakeShared<PingServersContext>();
    context->queue = queue;
    context->pendingPings = m_servers.size() * pingIterations;
    context->asyncOpContext = MakeShared<AsyncOpContext<Measurements>>();

    for (auto i = 0u; i < pingIterations; ++i)
    {
        for (const auto& server : m_servers)
        {
            queue.RunWork([timeoutMs, context, server = Server{ server }]
            {
                auto makeSocketResult = QoSSocket::MakeAndConfigure(timeoutMs);
                if (Succeeded(makeSocketResult))
                {
                    auto socket = makeSocketResult.ExtractPayload();
                    auto pingResult = socket->PingServer(server.address.data());

                    std::lock_guard<std::mutex> lock{ context->mutex };
                    auto& regionResult = context->regionResults.try_emplace(server.address, server.address).first->second;
                    regionResult.AddPingResult(std::move(pingResult));
                }
                else
                {
                    std::lock_guard<std::mutex> lock{ context->mutex };
                    auto& regionResult = context->regionResults.try_emplace(server.address, server.address).first->second;

                    // Treat a socket configuration failure the same as a ping failure. Log error, it will never be surfaced to client
                    TRACE_ERROR_HR(makeSocketResult.hr, "Failed to configured QoSSocket");
                    regionResult.AddPingResult(makeSocketResult.hr);
                }

                if (--context->pendingPings == 0)
                {
                    // If this is the last ping, complete the asyncOp
                    context->asyncOpContext->Complete(Measurements{ context->regionResults });
                }
            });
        }
    }

    return context->asyncOpContext;
}

} // namespace QoS
} // namespace PlayFab
