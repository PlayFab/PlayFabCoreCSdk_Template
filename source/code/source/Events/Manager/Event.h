#pragma once

#include <Events/EventsDataModels.h>
#include <httpClient/pal.h>
#include <playfab/PlayFabEventManagerApi.h>

namespace PlayFab
{
namespace EventManager
{

class Event
{
public:
    Event(PlayFabEventManagerEventType type, const char* eventName);
    Event(const Event& src);
    Event(Event&& src) = default;
    Event& operator=(const Event&) = delete;
    ~Event() = default;

    PlayFabEventManagerEventType const eventType;
    const PlayFabEventsEventContents& EventContents() const;

    // Modify event contents
    void SetName(const char* eventName);
    void SetNamespace(const char* eventNamespace);
    void SetEntity(const char* entityId, const char* entityType);
    void SetProperty(const char* name, const char* value);
    void SetProperty(const char* name, bool value);
    void SetProperty(const char* name, int8_t value);
    void SetProperty(const char* name, int16_t value);
    void SetProperty(const char* name, int32_t value);
    void SetProperty(const char* name, int64_t value);
    void SetProperty(const char* name, uint8_t value);
    void SetProperty(const char* name, uint16_t value);
    void SetProperty(const char* name, uint32_t value);
    void SetProperty(const char* name, uint64_t value);
    void SetProperty(const char* name, double value);

private:
    mutable PlayFabEventsEventContents m_eventContents; // mutable so we can lazily update m_eventContents.payload when it is requested

    // PlayFabEventsEventContents fields. Omitting optional customTags, originalId, and originalTimestamp fields.
    StdExtra::optional<PlayFabEntityKey> m_entity;
    String m_eventNamespace;
    String m_name;
    JsonValue m_payload;
    mutable String m_payloadString; // mutable so we can lazily update when it is requested

    // m_entity fields
    String m_entityId;
    String m_entityType;
};

} // namespace EventManager
} // namespace PlayFab

struct PlayFabEventManagerEvent
{
    PlayFabEventManagerEvent(PlayFab::SharedPtr<PlayFab::EventManager::Event> _event) : event{ _event } {}
    PlayFabEventManagerEvent(const PlayFabEventManagerEvent&) = default;
    ~PlayFabEventManagerEvent() = default;

    PlayFab::SharedPtr<PlayFab::EventManager::Event> event;
};
