#include "stdafx.h"
#include <playfab/PFTitlePlayer.h>
#include "GlobalState.h"
#include "TitlePlayer.h"
#include "ApiHelpers.h"
#include "ApiAsyncProviders.h"

using namespace PlayFab;

HRESULT PFTitlePlayerDuplicateHandle(
    _In_ PFTitlePlayerHandle titlePlayerHandle,
    _Out_ PFTitlePlayerHandle* duplicatedHandle
) noexcept
{
    return ApiImpl(API_IDENTITY(PFTitlePlayerDuplicateHandle), [&](GlobalState& state)
    {
        RETURN_HR_INVALIDARG_IF_NULL(duplicatedHandle);

        SharedPtr<TitlePlayer> titlePlayer;
        RETURN_IF_FAILED(state.TitlePlayers().FromHandle(titlePlayerHandle, titlePlayer));
        return state.TitlePlayers().MakeHandle(std::move(titlePlayer), *duplicatedHandle);
    });
}

void PFTitlePlayerCloseHandle(
    _In_ PFTitlePlayerHandle titlePlayerHandle
) noexcept
{
    ApiImpl(API_IDENTITY(PFTitlePlayerCloseHandle), [&](GlobalState& state)
    {
        state.TitlePlayers().CloseHandle(titlePlayerHandle);
        return S_OK;
    });
}

HRESULT PFTitlePlayerGetEntityKeySize(
    _In_ PFTitlePlayerHandle titlePlayerHandle,
    _Out_ size_t* bufferSize
) noexcept
{
    return TitlePlayerApiImpl(API_IDENTITY(PFTitlePlayerGetEntityKeySize), titlePlayerHandle, [&](SharedPtr<TitlePlayer>& titlePlayer)
    {
        RETURN_HR_INVALIDARG_IF_NULL(bufferSize);
        *bufferSize = titlePlayer->EntityKey().RequiredBufferSize();
        return S_OK;
    });
}

HRESULT PFTitlePlayerGetEntityKey(
    _In_ PFTitlePlayerHandle titlePlayerHandle,
    _In_ size_t bufferSize,
    _Out_writes_bytes_to_(bufferSize, *bufferUsed) void* buffer,
    _Outptr_ const PFEntityKey** result,
    _Out_opt_ size_t* bufferUsed
) noexcept
{
    return TitlePlayerApiImpl(API_IDENTITY(PFTitlePlayerGetEntityKey), titlePlayerHandle, [&](SharedPtr<TitlePlayer>& titlePlayer)
    {
        RETURN_HR_INVALIDARG_IF_NULL(buffer);
        RETURN_HR_INVALIDARG_IF_NULL(result);

        auto& entityKey = titlePlayer->EntityKey();
        RETURN_HR_IF(E_INVALIDARG, bufferSize < entityKey.RequiredBufferSize());

        ModelBuffer b{ buffer, bufferSize };
        auto copyResult = entityKey.Copy(b);
        if (SUCCEEDED(copyResult.hr))
        {
            *result = copyResult.Payload();
            if (bufferUsed)
            {
                assert(bufferSize - b.RemainingSpace() == entityKey.RequiredBufferSize());
                *bufferUsed = bufferSize - b.RemainingSpace();
            }
        }
        return copyResult.hr;
    });
}

HRESULT PFTitlePlayerGetEntityTokenAsync(
    _In_ PFTitlePlayerHandle titlePlayerHandle,
    _Inout_ XAsyncBlock* async
) noexcept
{
    return TitlePlayerAsyncApiImpl(async, API_IDENTITY(PFTitlePlayerGetEntityTokenAsync), titlePlayerHandle, [&](SharedPtr<TitlePlayer> titlePlayer, RunContext&& rc)
    {
        auto provider = MakeProvider(std::move(rc), async, API_IDENTITY(PFTitlePlayerGetEntityTokenAsync), std::bind(&TitlePlayer::GetEntityToken, std::move(titlePlayer), false, std::placeholders::_1));
        return Provider::Run(UniquePtr<Provider>(provider.release()));
    });
}

HRESULT PFTitlePlayerGetEntityTokenGetResultSize(
    _Inout_ XAsyncBlock* async,
    _Out_ size_t* bufferSize
) noexcept
{
    return XAsyncGetResultSize(async, bufferSize);
}

HRESULT PFTitlePlayerGetEntityTokenGetResult(
    _Inout_ XAsyncBlock* async,
    _In_ size_t bufferSize,
    _Out_writes_bytes_to_(bufferSize, *bufferUsed) void* buffer,
    _Outptr_ const PFEntityToken** entityToken,
    _Out_opt_ size_t* bufferUsed
) noexcept
{
    RETURN_HR_INVALIDARG_IF_NULL(entityToken);

    HRESULT hr =  XAsyncGetResult(async, API_IDENTITY(PFTitlePlayerGetEntityTokenAsync), bufferSize, buffer, bufferUsed);
    if (SUCCEEDED(hr))
    {
        *entityToken = static_cast<PFEntityToken*>(buffer);
    }
    return hr;
}
