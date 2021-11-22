#include "stdafx.h"
#include "EventBuffer.h"

namespace PlayFab
{
namespace EventManager
{
const size_t minimalBufferSize = 4096; // The default minimal m_buffer size in bytes. For performance optimization reasons this ideally should be equal to the memory page size which is 4096 on most popular platforms.

// Finds and returns a minimal power of 2 that covers the specified bufferSize.
// For example, if bufferSize is 4000 then it will return 4096.
static size_t AdjustBufferSize(const size_t bufferSize)
{
    // Calculate nearest page size
    size_t result = minimalBufferSize;
    while (result < bufferSize)
    {
        result *= 2;
    }

    return  result;
}

EventBuffer::EventBuffer(size_t bufferSize) :
    m_buffMask{ AdjustBufferSize(bufferSize) - 1 },
    m_bufferArray(m_buffMask + 1),
    m_buffStart{ (uint64_t)(m_bufferArray.data()) },
    m_buffEnd{ m_buffStart + m_buffMask + 1 },
    m_eventIndex{ MakeShared<std::atomic<uint64_t>>(0) }
{
    uint8_t *buffer = (uint8_t*)m_buffStart;
    memset(buffer, 0, m_buffMask + 1);

    // First event is just a stub which is used only to maintain the initial consistency of m_head/m_tail.
    // It is immediately considered already consumed.
    uint64_t index = m_eventIndex->load(std::memory_order_relaxed);
    EventPacket* firstEvent = CreateEventPacket(buffer, index, EventContext{});

    m_tail = firstEvent;
    m_head.store(firstEvent, std::memory_order_release);
}

EventBuffer::~EventBuffer()
{
    SpinLock lock(m_atomicSpin);

    // delete all remaining events (including the last consumed one)
    EventPacket* event = m_head.load(std::memory_order_acquire);
    EventPacket* nextPacket;
    while (event != nullptr)
    {
        nextPacket = event->next.load(std::memory_order_acquire);
        DeleteEventPacket(event);
        event = nextPacket;
    }
}

Result<void> EventBuffer::TryPut(EventContext&& eventContext)
{
    SpinLock lock{ m_atomicSpin };

    if (m_terminated.load(std::memory_order_consume))
    {
        return E_PLAYFAB_EVENTMANAGERINVALIDOPERATION;
    }

    constexpr uint32_t size = sizeof(EventPacket);

    EventPacket* headPtr = m_head.load(std::memory_order_acquire);
    EventPacket* tailPtr = m_tail;

    // verify if there is enough space
    const uint64_t headVal = reinterpret_cast<uint64_t>(headPtr);
    uint64_t eventStart = reinterpret_cast<uint64_t>((uint8_t*)tailPtr + size);

    // align event start by platform-safe boundary
    if (eventStart % 8 != 0)
    {
        eventStart += 8 - (eventStart % 8);
    }

    const bool wrapping = eventStart + size > m_buffEnd;
    const uint64_t sizeNeeded = !wrapping ? size : size + (m_buffEnd - eventStart);
    const uint64_t sizeLeft = (headVal - eventStart) & m_buffMask;

    if (sizeNeeded > sizeLeft)
    {
        return E_PLAYFAB_EVENTMANAGERBUFFEROVERFLOW;
    }

    if (wrapping)
    {
        eventStart = m_buffStart;
    }

    // create an event packet, set it to the m_tail->next and move the m_tail

    uint64_t currentEventIndex = m_eventIndex->fetch_add(1, std::memory_order_relaxed);
    EventPacket* event = CreateEventPacket(reinterpret_cast<uint8_t*>(eventStart), currentEventIndex, std::move(eventContext));
    tailPtr->next.store(event, std::memory_order_release);
    m_tail = event;

    return S_OK;
}

Result<EventContext> EventBuffer::TryTake()
{
    EventPacket* headPtr = m_head.load(std::memory_order_acquire);
    EventPacket* event = headPtr->next.load(std::memory_order_acquire);

    if (event == nullptr)
    {
        // there are no events available for consumption
        return E_PLAYFAB_INTERNAL_EVENTMANAGERBUFFEREMPTY;
    }

    // event is available; return its values
    auto eventContext = std::move(event->eventContext);

    // set new m_head (new last consumed event)
    m_head.store(event, std::memory_order_release);

    // delete old last consumed event from m_buffer
    DeleteEventPacket(headPtr);

    return eventContext;
}

HRESULT EventBuffer::Terminate()
{
    bool expected{ false };
    if (m_terminated.compare_exchange_strong(expected, true))
    {
        return S_OK;
    }
    else
    {
        return E_PLAYFAB_EVENTMANAGERINVALIDOPERATION;
    }
}

EventPacket* EventBuffer::CreateEventPacket(uint8_t *location, const uint64_t index, EventContext&& eventContext)
{
    // Use placement new to allocate an event packet in the m_buffer
    return new (location) EventPacket(index, std::move(eventContext));
}

void EventBuffer::DeleteEventPacket(EventPacket* event)
{
    // Destroy the event packet object explicitly
    event->~EventPacket();
}

} // namespace EventManager
} // namespace PlayFab
