#include "stdafx.h"
#include <playfab/PFTitlePlayer.h>
#include "GlobalState.h"
#include "TitlePlayer.h"

using namespace PlayFab;

HRESULT PFTitlePlayerDuplicateHandle(
    _In_ PFTitlePlayerHandle titlePlayerHandle,
    _Out_ PFTitlePlayerHandle* duplicatedHandle
) noexcept
{
    RETURN_HR_INVALIDARG_IF_NULL(duplicatedHandle);

    SharedPtr<GlobalState> state;
    RETURN_IF_FAILED(GlobalState::Get(state));

    auto titlePlayer = state->TitlePlayers().FromHandle(titlePlayerHandle);
    *duplicatedHandle = state->TitlePlayers().MakeHandle(std::move(titlePlayer));

    return S_OK;
}

void PFTitlePlayerCloseHandle(
    _In_ PFTitlePlayerHandle titlePlayerHandle
) noexcept
{
    SharedPtr<GlobalState> state;
    HRESULT hr = GlobalState::Get(state);

    if (SUCCEEDED(hr))
    {
        state->TitlePlayers().CloseHandle(titlePlayerHandle);
    }
}

//HRESULT PFTitlePlayerGetEntityKeySize(
//    _In_ PFTitlePlayerHandle titlePlayerHandle,
//    _Out_ size_t* bufferSize
//) noexcept
//{
//    RETURN_HR_INVALIDARG_IF_NULL(titlePlayerHandle);
//
//    PFEntity entity{ titlePlayerHandle->titlePlayer };
//    return PFEntityGetEntityKeySize(&entity, bufferSize);
//}
//
//HRESULT PFTitlePlayerGetEntityKey(
//    _In_ PFTitlePlayerHandle titlePlayerHandle,
//    _In_ size_t bufferSize,
//    _Out_writes_bytes_to_(bufferSize, *bufferUsed) void* buffer,
//    _Outptr_ const PFEntityKey** entityKey,
//    _Out_opt_ size_t* bufferUsed
//) noexcept
//{
//    RETURN_HR_INVALIDARG_IF_NULL(titlePlayerHandle);
//
//    PFEntity entity{ titlePlayerHandle->titlePlayer };
//    return PFEntityGetEntityKey(&entity, bufferSize, buffer, entityKey, bufferUsed);
//}
//
//HRESULT PFTitlePlayerGetEntityTokenAsync(
//    _In_ PFTitlePlayerHandle titlePlayerHandle,
//    _In_ bool forceRefresh,
//    _Inout_ XAsyncBlock* async
//) noexcept
//{
//    RETURN_HR_INVALIDARG_IF_NULL(titlePlayerHandle);
//
//    PFEntity entity{ titlePlayerHandle->titlePlayer };
//    return PFEntityGetEntityTokenAsync(&entity, forceRefresh, async);
//}
//
//HRESULT PFTitlePlayerGetEntityTokenGetResultSize(
//    _Inout_ XAsyncBlock* async,
//    _Out_ size_t* bufferSize
//) noexcept
//{
//    return PFEntityGetEntityTokenGetResultSize(async, bufferSize);
//}
//
//HRESULT PFTitlePlayerGetEntityTokenGetResult(
//    _Inout_ XAsyncBlock* async,
//    _In_ size_t bufferSize,
//    _Out_writes_bytes_to_(bufferSize, *bufferUsed) void* buffer,
//    _Outptr_ const PFEntityToken** entityToken,
//    _Out_opt_ size_t* bufferUsed
//) noexcept
//{
//    return PFEntityGetEntityTokenGetResult(async, bufferSize, buffer, entityToken, bufferUsed);
//}
