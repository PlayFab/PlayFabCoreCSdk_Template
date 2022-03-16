#include "stdafx.h"
#include "Entity.h"

namespace PlayFab
{

using Wrappers::SafeString;

Entity::Entity(SharedPtr<PlayFab::HttpClient const> httpClient, Authentication::EntityTokenResponse&& result) :
    m_httpClient{ std::move(httpClient) },
    m_key{ *result.entity },
    m_entityToken{ result }
{
}

SharedPtr<PlayFab::HttpClient const> Entity::HttpClient() const
{
    return m_httpClient;
}

PlayFab::EntityKey const& Entity::EntityKey() const
{
    return m_key;
}

AsyncOp<EntityToken> Entity::GetEntityToken(bool forceRefresh, const TaskQueue& queue)
{
    if (forceRefresh)
    {
        // API to refresh EntityToken doesn't exist yet
        return E_FAIL;
    }

    // No async logic needed currently
    UNREFERENCED_PARAMETER(queue);

    if (m_entityToken.expiration && *m_entityToken.expiration < GetTimeTNow())
    {
        return E_PF_NOENTITYTOKEN;
    }

    return Result<EntityToken>{ EntityToken{ m_entityToken } };
}

EntityToken::EntityToken(const Authentication::EntityTokenResponse& tokenResponse) :
    PFEntityToken{},
    m_token{ tokenResponse.entityToken },
    m_expiration{ tokenResponse.tokenExpiration }
{
    token = m_token.empty() ? nullptr : m_token.data();
    expiration = m_expiration ? m_expiration.operator->() : nullptr;
}

EntityToken::EntityToken(const EntityToken& src) :
    m_token{ src.m_token },
    m_expiration{ src.m_expiration }
{
    token = m_token.empty() ? nullptr : m_token.data();
    expiration = m_expiration ? m_expiration.operator->() : nullptr;
}

EntityToken::EntityToken(EntityToken&& src) :
    PFEntityToken{ src },
    m_token{ std::move(src.m_token) },
    m_expiration{ src.m_expiration }
{
    expiration = m_expiration ? m_expiration.operator->() : nullptr;
}

size_t EntityToken::RequiredBufferSize() const
{
    size_t requiredSize{ alignof(EntityToken) + sizeof(EntityToken) };
    if (token)
    {
        requiredSize += (std::strlen(token) + 1);
    }
    if (expiration)
    {
        requiredSize += (alignof(time_t) + sizeof(time_t));
    }
    return requiredSize;
}

Result<PFEntityToken const*> EntityToken::Copy(ModelBuffer& buffer) const
{
    // Alloc
    auto allocResult = buffer.Alloc<PFEntityToken>(1);
    RETURN_IF_FAILED(allocResult.hr);
    // Copy
    auto outputPtr = allocResult.ExtractPayload();
    {
        auto tokenCopyResult = buffer.CopyTo(this->token);
        RETURN_IF_FAILED(tokenCopyResult.hr);
        outputPtr->token = tokenCopyResult.ExtractPayload();
    }
    {
        auto expirationCopyResult = buffer.CopyTo(this->expiration);
        RETURN_IF_FAILED(expirationCopyResult.hr);
        outputPtr->expiration = expirationCopyResult.ExtractPayload();
    }
    return outputPtr;
}

}
