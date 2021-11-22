#include "stdafx.h"
#include "Socket.h"

#if HC_PLATFORM_IS_MICROSOFT
#include <sys/utime.h>
#else
#include <sys/ioctl.h>
#include <utime.h>
#endif

namespace PlayFab
{

Result<SharedPtr<Socket>> Socket::Make()
{
    SharedPtr<Socket> out{ new (Allocator<Socket>{}.allocate(1)) Socket };

    int errorCode = 0;

#if HC_PLATFORM_IS_MICROSOFT
    // Initializing
    if ((errorCode = WSAStartup(MAKEWORD(2, 2), &out->m_wsa)) != 0)
    {
        return HRESULT_FROM_WIN32(errorCode);
    }
#endif

    // create socket
    out->m_socket = static_cast<decltype(m_socket)>(socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP));
#if HC_PLATFORM_IS_MICROSOFT
    if (out->m_socket == INVALID_SOCKET)
    {
        return HRESULT_FROM_WIN32(WSAGetLastError());
    }
#else
    if (out->m_socket == SOCKET_ERROR)
    {
        return E_FAIL;
    }
#endif

    // setup address structure
    out->m_siOther.sin_family = AF_INET;

    return out;
}

Socket::Socket() :
    m_siOther{},
    m_timeOutVal{},
    m_slen{ sizeof(m_siOther) }
{
}

Socket::~Socket()
{
#if HC_PLATFORM_IS_MICROSOFT
    closesocket(m_socket);
    WSACleanup();
#else
    close(s);
#endif
}

HRESULT Socket::SetAddress(const char* socketAddr, const char* serviceName)
{
    // Cleanup helper for getarrinfo result
    struct GetAddrInfoResult
    {
        ~GetAddrInfoResult()
        {
            if (addrInfo)
            {
                freeaddrinfo(addrInfo);
            }
        }
        addrinfo* addrInfo{ nullptr };
    } result;

    addrinfo hints{};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;

    auto status = getaddrinfo(socketAddr, serviceName, &hints, &result.addrInfo);
    if (status != 0)
    {
#if HC_PLATFORM_IS_MICROSOFT
        return HRESULT_FROM_WIN32(status);
#else
        return E_FAIL;
#endif
    }

    sockaddr_in* addr = reinterpret_cast<sockaddr_in*>(result.addrInfo[0].ai_addr);
    if (addr->sin_addr.S_un.S_addr == 0)
    {
        return E_FAIL;
    }
    m_siOther.sin_addr.S_un.S_addr = addr->sin_addr.S_un.S_addr;

    return S_OK;
}

HRESULT Socket::SetPort(uint32_t port)
{
    m_siOther.sin_port = htons(static_cast<u_short>(port));
    return S_OK;
}

HRESULT Socket::SetTimeout(uint32_t timeoutMs)
{
    // Input timeout is in milliseconds, tv_sec is in seconds
    m_timeOutVal.tv_sec = timeoutMs / 1000;

    // tv_usec takes microseconds, hence convert the input milliseconds to microseconds
    m_timeOutVal.tv_usec = (timeoutMs - m_timeOutVal.tv_sec * 1000) * 1000;
#if HC_PLATFORM_IS_MICROSOFT
    return TranslateError(setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO | SO_SNDTIMEO, reinterpret_cast<const char*>(&timeoutMs), sizeof(timeoutMs)));
#else
    return TranslateError(setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *) &timeOutVal, sizeof(struct timeval)));
#endif
}

HRESULT Socket::SendMessage(const char* message)
{
    return TranslateError(static_cast<int>(sendto(m_socket, message, static_cast<int>(strlen(message)), 0, (struct sockaddr *) &m_siOther, m_slen)));
}

HRESULT Socket::ReceiveReply(char* buf, const int& buflen)
{
    fd_set socketSet;

    FD_ZERO(&socketSet);
    FD_CLR(0, &socketSet);
    FD_SET(m_socket, &socketSet);

    int selectResult = select(static_cast<int>(m_socket) + 1, &socketSet, nullptr, nullptr, &m_timeOutVal);
    RETURN_IF_FAILED(TranslateError(selectResult));

    if (selectResult > 0)
    {
        return TranslateError(static_cast<int>(recvfrom(m_socket, buf, buflen, 0, (struct sockaddr *) &m_siOther, &m_slen)));
    }

    return S_OK;
}

int Socket::GetLastError() const
{
    return h_errno;
}

HRESULT Socket::TranslateError(int error) const
{
    if (error == SOCKET_ERROR)
    {
        TRACE_ERROR("Socket API returned error, code=%u", GetLastError());
#if HC_PLATFORM_IS_MICROSOFT
        return HRESULT_FROM_WIN32(GetLastError());
#else
        return E_FAIL;
#endif
    }
    return S_OK;
}

} // namespace PlayFab
