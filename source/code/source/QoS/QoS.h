#pragma once

#include "QoSDataModels.h"
#include "Entity.h"
#include "TaskQueue.h"

namespace PlayFab
{

namespace QoS
{

class QoSAPI
{
public:
    QoSAPI() = default;
    QoSAPI(const QoSAPI&) = delete;
    ~QoSAPI() = default;

    AsyncOp<Measurements> GetMeasurements(SharedPtr<Entity> entity, uint32_t pingIterations, uint32_t timeoutMs, const TaskQueue& queue) const;

private:
    AsyncOp<void> GetServers(SharedPtr<Entity> entity, const TaskQueue& queue) const;
    AsyncOp<Measurements> PingServers(uint32_t pingIterations, uint32_t timeoutMs, const TaskQueue& queue) const;

private:
    // Cached QoS servers
    mutable Vector<Server> m_servers;
};

} // namespace QoS
} // namespace PlayFab
