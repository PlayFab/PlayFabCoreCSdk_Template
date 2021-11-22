#pragma once

#include "TaskQueue.h"
#include "AsyncOp.h"

#if HC_PLATFORM == HC_PLATFORM_GDK
#include <XUser.h>

namespace PlayFab
{

struct TokenAndSignature
{
    String token;
    String signature;
};

// Minimal RAII wrapper around XUserHandle
class XUser
{
public:
    // XUsers must be copied with XUser::Duplicate
    XUser(const XUser& other) = delete;
    XUser(XUser&& other) noexcept;
    XUser& operator=(XUser&& other) noexcept = default;
    ~XUser() noexcept;

    static Result<XUser> WrapHandle(XUserHandle userHandle) noexcept;
    Result<XUser> Duplicate() const noexcept;

    XUserHandle Handle() const noexcept;
    uint64_t Id() const noexcept;

    AsyncOp<TokenAndSignature> GetTokenAndSignature(
        XUserGetTokenAndSignatureOptions options,
        const String& httpMethod,
        const String& url,
        const UnorderedMap<String, String>& headers,
        size_t requestBodySize,
        const uint8_t* requestBody,
        const TaskQueue& queue
    ) const noexcept;

private:
    XUser() noexcept = default;
    XUser(XUserHandle userHandle) noexcept;

    HRESULT InitializeUser() noexcept;

    XUserHandle m_handle;
    mutable uint64_t m_id{ 0 };
};

using PlatformUser = XUser;

}

#endif // HC_PLATFORM_GDK
