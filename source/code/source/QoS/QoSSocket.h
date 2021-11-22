#pragma once

#include "Socket.h"
#include "AsyncOp.h"

namespace PlayFab
{
namespace QoS
{

// A wrapper on top of the Socket class to abstract out the logic for pinging the Azure QoS servers.
class QoSSocket
{
public:
    // Make and configure a QoSSocket with appriate port and timeout
    static Result<SharedPtr<QoSSocket>> MakeAndConfigure(uint32_t timeoutMs);

    QoSSocket(const QoSSocket&) = delete;
    QoSSocket& operator=(const QoSSocket&) = delete;
    ~QoSSocket() = default;

    // Get the ping relay latency for the QoS server with the specified server
    Result<uint32_t> PingServer(const char* serverAddress);

private:
    QoSSocket(SharedPtr<Socket> socket, uint32_t timeoutMs);

    // Length of the message send and received
    static const int BUFLEN = 512;

    // Header of the message send over UDP. The message must start with 2 bytes of all bits set to 1
    static const unsigned int MSGHEADER = 255;

    SharedPtr<Socket> m_socket;
    uint32_t const m_timeout;

    // Message sent. Should start with 2 bytes set to 255 each (all bits set to 1)
    const char m_message[BUFLEN]{ static_cast<char>(MSGHEADER), static_cast<char>(MSGHEADER) };
    char m_buf[BUFLEN];
};

} // namespace QoS
} // namespace PlayFab
