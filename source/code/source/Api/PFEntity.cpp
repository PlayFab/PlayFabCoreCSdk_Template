#include "stdafx.h"
#include <playfab/PFEntity.h>
#include "Entity.h"
#include "ApiAsyncProviders.h"

using namespace PlayFab;

//HRESULT PFEntityDuplicateHandle(
//    _In_ PFEntityHandle entityHandle,
//    _Out_ PFEntityHandle* duplicatedEntityHandle
//) noexcept
//{
//    RETURN_HR_INVALIDARG_IF_NULL(entityHandle);
//    RETURN_HR_INVALIDARG_IF_NULL(duplicatedEntityHandle);
//
//    *duplicatedEntityHandle = MakeUnique<PFEntity>(*entityHandle).release();
//    return S_OK;
//}
//
//void PFEntityCloseHandle(
//    _In_ PFEntityHandle entityHandle
//) noexcept
//{
//    UniquePtr<PFEntity>{ entityHandle };
//}
//
//HRESULT PFEntityGetEntityKeySize(
//    _In_ PFEntityHandle entityHandle,
//    _Out_ size_t* bufferSize
//) noexcept
//{
//    RETURN_HR_INVALIDARG_IF_NULL(entityHandle);
//    RETURN_HR_INVALIDARG_IF_NULL(bufferSize);
//
//    *bufferSize = entityHandle->entity->EntityKey().RequiredBufferSize();
//    return S_OK;
//}
//
//HRESULT PFEntityGetEntityKey(
//    _In_ PFEntityHandle entityHandle,
//    _In_ size_t bufferSize,
//    _Out_writes_bytes_to_(bufferSize, *bufferUsed) void* buffer,
//    _Outptr_ const PFEntityKey** entityKey,
//    _Out_opt_ size_t* bufferUsed
//) noexcept
//{
//    RETURN_HR_INVALIDARG_IF_NULL(entityHandle);
//    RETURN_HR_INVALIDARG_IF_NULL(buffer);
//    RETURN_HR_INVALIDARG_IF_NULL(entityKey);
//
//    ModelBuffer b{ buffer, bufferSize };
//    auto copyResult = entityHandle->entity->EntityKey().Copy(b);
//    RETURN_IF_FAILED(copyResult.hr);
//    *entityKey = copyResult.ExtractPayload();
//    if (bufferUsed)
//    {
//        *bufferUsed = bufferSize - b.RemainingSpace();
//    }
//
//    return S_OK;
//}
//
//HRESULT PFEntityGetEntityTokenAsync(
//    _In_ PFEntityHandle entityHandle,
//    _In_ bool forceRefresh,
//    _Inout_ XAsyncBlock* async
//) noexcept
//{
//    RETURN_HR_INVALIDARG_IF_NULL(entityHandle);
//
//    auto provider = MakeProvider(async, __FUNCTION__, std::bind(&Entity::GetEntityToken, entityHandle->entity.get(), forceRefresh, std::placeholders::_1));
//    return Provider::Run(UniquePtr<Provider>(provider.release()));
//}
//
//HRESULT PFEntityGetEntityTokenGetResultSize(
//    _Inout_ XAsyncBlock* async,
//    _Out_ size_t* bufferSize
//) noexcept
//{
//    return XAsyncGetResultSize(async, bufferSize);
//}
//
//HRESULT PFEntityGetEntityTokenGetResult(
//    _Inout_ XAsyncBlock* async,
//    _In_ size_t bufferSize,
//    _Out_writes_bytes_to_(bufferSize, *bufferUsed) void* buffer,
//    _Outptr_ const PFEntityToken** entityToken,
//    _Out_opt_ size_t* bufferUsed
//) noexcept
//{
//    RETURN_HR_INVALIDARG_IF_NULL(entityToken);
//
//    RETURN_IF_FAILED(XAsyncGetResult(async, nullptr, bufferSize, buffer, bufferUsed));
//    *entityToken = static_cast<PFEntityToken*>(buffer);
//
//    return S_OK;
//}
