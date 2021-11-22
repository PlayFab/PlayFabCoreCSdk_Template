#pragma once

#include "SpinLock.h"
#include "Event.h"

namespace PlayFab
{

template<typename T>
class AsyncOpContext;

namespace EventManager
{

struct EventContext
{
    SharedPtr<Event const> event;
    SharedPtr<AsyncOpContext<String>> writeEventAsyncOp;
};

#pragma pack(push)
#pragma pack(8) // conservative memory alignment control to provide maximum platform compatibility

// A "packet" (wrapper) for an event request. The packets are internal custom allocations inside the m_buffer.
// Their purpose is to reduce heap churn as additional data about event (e.g. some event metadata) needs to be stored
// so that a wrapper object is not created on the heap for each event.
// The implementation is based on the implementation of FullEvent struct in Microsoft Gaming Cloud CELL library.
struct EventPacket final
{
    EventPacket(const uint64_t index, EventContext&& context) :
        next(nullptr),
        eventIndex(index),
        timestamp(std::time(nullptr)), // current time
        eventContext(std::move(context))
    {
    }
    ~EventPacket() {};

    std::atomic<EventPacket*> next; // a pointer to the next event packet in m_buffer
    uint64_t eventIndex; // the incremental index of an event
    std::time_t timestamp; // the timestamp of event packet creation

    EventContext eventContext;
};
#pragma pack(pop)

// PlayFab event buffer (a spinlock-enforced MPSC queue based on a circular m_buffer).
// The implementation is based on the implementation of CircularBuffer in Microsoft Gaming Cloud CELL library.
class EventBuffer final
{
public:
    EventBuffer(size_t bufferSize);
    EventBuffer(const EventBuffer& source) = delete;
    EventBuffer& operator=(const EventBuffer& source) = delete;
    ~EventBuffer();

    // Attempts to put an event in m_buffer (add to the m_tail). This method must be thread-safe.
    Result<void> TryPut(EventContext&& eventContext);

    // Attempts to take an event from m_buffer (update the m_head).
    Result<EventContext> TryTake();

    // Terminates the buffer. Attempting to add things to the buffer after it has been terminated will result in error.
    HRESULT Terminate();

private:
    // Creates (allocates and calls constructor) an event packet object in the m_buffer
    EventPacket* CreateEventPacket(uint8_t* location, const uint64_t index, EventContext&& eventContext);

    // Deletes (calls destructor) an event packet object from the m_buffer
    void DeleteEventPacket(EventPacket* eventPacket);

    AtomicSpin m_atomicSpin; // Used for spinlock in critical sections
    std::atomic<bool> m_terminated{ false };

    const size_t m_buffMask; // A bit mask that is used for very fast m_buffer pointer arithmetics.
                           // The m_buffer's length is always a power of two and the m_buffer mask is (length - 1).
                           // For example if m_buffer length is 0x100 (256) then m_buffer mask is 0xFF (255)
                           // (or 100000000 and 011111111 in binary form). Performing binary "&" operations
                           // with a mask like that allows for efficient pointer adjustments in a circular m_buffer.

    Vector<uint8_t> m_bufferArray;
    const uint64_t m_buffStart; // A pointer to the beginning of m_buffer (first byte of the m_buffer).
    const uint64_t m_buffEnd; // A pointer to the byte immediately after the last byte of m_buffer, i.e. (m_buffEnd - m_buffStart) gives the length of the m_buffer.

    std::atomic<EventPacket*> m_head; // A pointer to the last consumed event packet. The last consumed event packet must always exist (not destroyed yet) by design,
                                           // as it may be the same event packet pointed to by m_tail (e.g. when there are no events currently in the m_buffer).
                                           // Events are consumed from the m_head (m_head is moving towards m_tail as events are consumed).

    // Variables below are touched only behind the lock:

    EventPacket* m_tail; // A pointer to the last event packet added to the m_buffer.
                              // Newly added events are added to the m_tail (m_tail is growing as new events are added).

    SharedPtr<std::atomic<uint64_t>> m_eventIndex; // The counter of produced events
};

} // namespace EventManager
} // namespace PlayFab
