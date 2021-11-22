#pragma once

#if HC_PLATFORM_IS_MICROSOFT
#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#if HC_PLATFORM != HC_PLATFORM_SONY_PLAYSTATION_4
#include <netdb.h>
#endif
constexpr int SOCKET_ERROR = -1;
constexpr int WSAEWOULDBLOCK = 10035;
#endif

namespace PlayFab
{

class Socket
{
public:
    static Result<SharedPtr<Socket>> Make();

    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;
    ~Socket();

    // Set the address the socket would ping
    HRESULT SetAddress(const char* socketAddr, const char* serviceName);

    // Set the port the socket would ping
    HRESULT SetPort(uint32_t port);

    // Set the timeout for an individual socket call
    HRESULT SetTimeout(uint32_t timeoutMs);

    // Send the message and return the error code
    HRESULT SendMessage(const char* message);

    // Receive the reply and return the error code
    HRESULT ReceiveReply(char* buf, const int& buflen);

    // Get last returned error. Varies depending on platform
    int GetLastError() const;

private:
    Socket();

    // Translates a returned error to HRESULT
    HRESULT TranslateError(int error) const;

private:
    struct sockaddr_in m_siOther;
    struct timeval m_timeOutVal;

#if HC_PLATFORM_IS_MICROSOFT
    SOCKET m_socket{ 0 };
    int m_slen;
    WSADATA m_wsa{};
#elif HC_PLATFORM == HC_PLATFORM_ANDROID
    unsigned int m_socket{ 0 };
    socklen_t m_slen;
#else
    unsigned int m_socket{ 0 };
    unsigned int m_slen;
#endif
};

} // namespace PlayFab
