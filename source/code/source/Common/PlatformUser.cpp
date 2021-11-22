#include "stdafx.h"
#include "PlatformUser.h"

namespace PlayFab
{

#if HC_PLATFORM == HC_PLATFORM_GDK

XUser::XUser(XUserHandle userHandle) noexcept
    : m_handle{ userHandle }
{
}

XUser::XUser(XUser&& other) noexcept
    : m_handle{ other.m_handle },
    m_id{ other.m_id }
{
    other.m_handle = nullptr;
}

XUser::~XUser() noexcept
{
    if (m_handle)
    {
        XUserCloseHandle(m_handle);
    }
}

Result<XUser> XUser::WrapHandle(XUserHandle userHandle) noexcept
{
    if (userHandle == nullptr)
    {
        return Result<XUser>{ E_INVALIDARG };
    }

    XUserHandle copiedHandle;
    RETURN_IF_FAILED(XUserDuplicateHandle(userHandle, &copiedHandle));

    XUser user{ copiedHandle };
    RETURN_IF_FAILED(user.InitializeUser());

    return Result<XUser>{ std::move(user) };
}

Result<XUser> XUser::Duplicate() const noexcept
{
    XUserHandle copiedHandle;
    RETURN_IF_FAILED(XUserDuplicateHandle(m_handle, &copiedHandle));

    XUser copiedUser{ copiedHandle };
    RETURN_IF_FAILED(copiedUser.InitializeUser());

    return Result<XUser>{ std::move(copiedUser) };
}

HRESULT XUser::InitializeUser() noexcept
{
    RETURN_IF_FAILED(XUserGetId(m_handle, &m_id));
    return S_OK;
}

XUserHandle XUser::Handle() const noexcept
{
    return m_handle;
}

uint64_t XUser::Id() const noexcept
{
    return m_id;
}

AsyncOp<TokenAndSignature> XUser::GetTokenAndSignature(
    XUserGetTokenAndSignatureOptions options,
    const String& httpMethod,
    const String& url,
    const UnorderedMap<String, String>& headers,
    size_t requestBodySize,
    const uint8_t* requestBody,
    const TaskQueue& queue
) const noexcept
{
    class Operation
    {
    public:
        static AsyncOp<TokenAndSignature> Begin(
            XUserHandle userHandle,
            XUserGetTokenAndSignatureOptions options,
            const String& httpMethod,
            const String& url,
            const UnorderedMap<String, String>& headersMap,
            size_t requestBodySize,
            const uint8_t* requestBody,
            const TaskQueue& queue
        )
        {
            UniquePtr<Operation> operation{ new (Allocator<Operation>{}.allocate(1)) Operation(queue) };

            Vector<XUserGetTokenAndSignatureHttpHeader> headers{};
            for (const auto& header : headersMap)
            {
                headers.push_back(XUserGetTokenAndSignatureHttpHeader{ header.first.data(), header.second.data() });
            }

            operation->m_asyncBlock.callback = GetTokenAndSignatureComplete;
            operation->m_asyncBlock.queue = operation->m_queue.GetHandle();
            operation->m_asyncBlock.context = operation.get();

            RETURN_IF_FAILED(XUserGetTokenAndSignatureAsync(userHandle, options, httpMethod.data(), url.data(), headers.size(), headers.empty() ? nullptr : headers.data(), requestBodySize, requestBody, &operation->m_asyncBlock));

            auto asyncOp = AsyncOp<TokenAndSignature>{ operation->m_asyncContext };

            // Operation will be reclaimed in GetTokenAndSignatureComplete
            operation.release();

            return asyncOp;
        }

    private:
        Operation(const TaskQueue& queue) : m_queue{ queue }, m_asyncContext{ MakeShared<AsyncOpContext<TokenAndSignature>>() }
        {
        }

        static void CALLBACK GetTokenAndSignatureComplete(XAsyncBlock* asyncBlock)
        {
            // Retake ownership of Operation
            UniquePtr<Operation> operation{ static_cast<Operation*>(asyncBlock->context) };

            size_t bufferSize{ 0 };
            HRESULT hr = XUserGetTokenAndSignatureResultSize(asyncBlock, &bufferSize);

            TokenAndSignature payload;
            if (SUCCEEDED(hr))
            {
                Vector<uint8_t> buffer(bufferSize, 0);
                XUserGetTokenAndSignatureData* XUserTokenSignatureData{ nullptr };

                hr = XUserGetTokenAndSignatureResult(asyncBlock, bufferSize, buffer.data(), &XUserTokenSignatureData, nullptr);
                if (SUCCEEDED(hr))
                {
                    payload.token = String{ XUserTokenSignatureData->token, XUserTokenSignatureData->tokenSize };
                    payload.signature = String{ XUserTokenSignatureData->signature, XUserTokenSignatureData->signatureSize };
                }
            }

            if (FAILED(hr))
            {
                operation->m_asyncContext->Complete(hr);
            }
            else
            {
                operation->m_asyncContext->Complete(std::move(payload));
            }
        }

        TaskQueue const m_queue;
        XAsyncBlock m_asyncBlock{};
        SharedPtr<AsyncOpContext<TokenAndSignature>> m_asyncContext;
    };

    return Operation::Begin(m_handle, options, httpMethod, url, headers, requestBodySize, requestBody, queue);
}

#endif // HC_PLATFORM_GDK

} // namespace PlayFab