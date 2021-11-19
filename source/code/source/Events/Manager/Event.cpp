#include "stdafx.h"
#include "Event.h"

namespace PlayFab
{
namespace EventManager
{

Event::Event(PlayFabEventManagerEventType type, const char* eventName) :
    eventType{ type },
    m_eventContents{},
    m_payload{ rapidjson::kObjectType }
{
    SetNamespace("custom");
    SetName(eventName);
}

// Don't bother copying m_payloadString - its lazily created from m_payload when requested
Event::Event(const Event& src) :
    eventType{ src.eventType },
    m_eventContents{}
{
    SetEntity(src.m_entityId.data(), src.m_entityType.data());
    SetNamespace(src.m_eventNamespace.data());
    SetName(src.m_name.data());
    JsonUtils::FromJson(src.m_payload, m_payload);
}

const PlayFabEventsEventContents& Event::EventContents() const
{
    // Lazily update m_eventContents.payload when requested
    m_payloadString = JsonUtils::WriteToString(m_payload);
    m_eventContents.payload.stringValue = m_payloadString.data();

    return m_eventContents;
}

void Event::SetName(const char* eventName)
{
    m_name = eventName;
    m_eventContents.name = m_name.data();
}

void Event::SetNamespace(const char* eventNamespace)
{
    m_eventNamespace = eventNamespace;
    m_eventContents.eventNamespace = m_eventNamespace.data();
}

void Event::SetEntity(const char* entityId, const char* entityType)
{
    m_entityId = entityId;
    // entityType is an optional field of PlayFabEventsEntityKey so allow null
    if (entityType)
    {
        m_entityType = entityType;
    }
    m_entity.emplace(PlayFabEntityKey{ m_entityId.data(), m_entityType.empty() ? nullptr : m_entityType.data() });
    m_eventContents.entity = m_entity.operator->();
}

void Event::SetProperty(const char* name, const char* value)
{
    JsonUtils::ObjectSetMember(m_payload, name, value);
}

void Event::SetProperty(const char* name, bool value)
{
    JsonUtils::ObjectSetMember(m_payload, name, value);
}

void Event::SetProperty(const char* name, int8_t value)
{
    JsonUtils::ObjectSetMember(m_payload, name, value);
}

void Event::SetProperty(const char* name, int16_t value)
{
    JsonUtils::ObjectSetMember(m_payload, name, value);
}

void Event::SetProperty(const char* name, int32_t value)
{
    JsonUtils::ObjectSetMember(m_payload, name, value);
}

void Event::SetProperty(const char* name, int64_t value)
{
    JsonUtils::ObjectSetMember(m_payload, name, value);
}

void Event::SetProperty(const char* name, uint8_t value)
{
    JsonUtils::ObjectSetMember(m_payload, name, value);
}

void Event::SetProperty(const char* name, uint16_t value)
{
    JsonUtils::ObjectSetMember(m_payload, name, value);
}

void Event::SetProperty(const char* name, uint32_t value)
{
    JsonUtils::ObjectSetMember(m_payload, name, value);
}

void Event::SetProperty(const char* name, uint64_t value)
{
    JsonUtils::ObjectSetMember(m_payload, name, value);
}

void Event::SetProperty(const char* name, double value)
{
    JsonUtils::ObjectSetMember(m_payload, name, value);
}

} // namespace EventManager
} // namespace PlayFab
