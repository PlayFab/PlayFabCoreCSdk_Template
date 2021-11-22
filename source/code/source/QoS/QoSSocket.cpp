#include "stdafx.h"
#include "QoS.h"
#include "QoSSocket.h"
#include "TaskQueue.h"

namespace PlayFab
{
namespace QoS
{

// Port the QoS server listen on
constexpr int kPort = 3075;
constexpr char kPortString[]{ "3075" };

Result<SharedPtr<QoSSocket>> QoSSocket::MakeAndConfigure(uint32_t timeoutMs)
{
    auto socketResult = Socket::Make();
    if (Failed(socketResult))
    {
        return socketResult.hr;
    }

    auto socket = socketResult.ExtractPayload();

    RETURN_IF_FAILED(socket->SetPort(kPort));
    RETURN_IF_FAILED(socket->SetTimeout(timeoutMs));

    return SharedPtr<QoSSocket>{ new (Allocator<QoSSocket>{}.allocate(1)) QoSSocket{ std::move(socket), timeoutMs } };
}

QoSSocket::QoSSocket(SharedPtr<Socket> socket, uint32_t timeoutMs) :
    m_socket{ std::move(socket) },
    m_timeout{ timeoutMs }
{
}

Result<uint32_t> QoSSocket::PingServer(const char* address)
{
    RETURN_IF_FAILED(m_socket->SetAddress(address, kPortString));

    // Clear the buffer with this value before receiving the reply.
    constexpr char BUFFER_VALUE = '1';
    memset(m_buf, BUFFER_VALUE, BUFLEN);

    // Snap the start time
    auto begin = Clock::now();

    // Send the message & await the reply
    RETURN_IF_FAILED(m_socket->SendMessage(m_message));
    RETURN_IF_FAILED(m_socket->ReceiveReply(m_buf, BUFLEN));

    // Snap the end time
    auto end = Clock::now();

    // Calculate the total time
    auto latencyMs = static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

    // For QoS measurement purposes, consider a timeout an error
    if (latencyMs >= m_timeout)
    {
        return E_PF_INTERNAL_QOSTIMEOUTEXCEEDED;
    }

    // Expected QoS server response should have first two bytes set to 0
    if (m_buf[0] != '\0' || m_buf[1] != '\0')
    {
        TRACE_WARNING("Unexpected response from QoS Server: %.512s", m_buf);
        // Server still responded, and we only really only care about latency, so don't return an error
    }

    return latencyMs;
}

} // namespace QoS
} // namespace PlayFab
