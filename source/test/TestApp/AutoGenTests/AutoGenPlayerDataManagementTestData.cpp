#include "TestAppPch.h"
#include "TestContext.h"
#include "TestApp.h"
#include "AutoGenPlayerDataManagementTests.h"
#include "XAsyncHelper.h"

namespace PlayFabUnit
{

using namespace PlayFab::Wrappers;

#pragma region AdminGetDataReport

void AutoGenPlayerDataManagementTests::FillGetDataReportRequest(PFPlayerDataManagementGetDataReportRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"ReportName\": \"PurchaseDataReport\", \"Year\": 2014, \"Month\": 12, \"Day\": 5}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidatePFPlayerDataManagementGetDataReportResult(PFPlayerDataManagementGetDataReportResult* result)
{
    // result.downloadUrl = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminGetUserData

void AutoGenPlayerDataManagementTests::FillGetUserDataRequest(PFPlayerDataManagementGetUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Keys\": [ \"preferences\", \"progress\" ], \"IfChangedFromDataVersion\": 13}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidatePFPlayerDataManagementAdminGetUserDataResult(PFPlayerDataManagementAdminGetUserDataResult* result)
{
    // result.data = struct PFUserDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.dataVersion = uint32_t;
    // result.playFabId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminGetUserInternalData


#pragma endregion

#pragma region AdminGetUserPublisherData


#pragma endregion

#pragma region AdminGetUserPublisherInternalData


#pragma endregion

#pragma region AdminGetUserPublisherReadOnlyData


#pragma endregion

#pragma region AdminGetUserReadOnlyData


#pragma endregion

#pragma region AdminUpdateUserData

void AutoGenPlayerDataManagementTests::FillAdminUpdateUserDataRequest(PFPlayerDataManagementAdminUpdateUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }, \"Permission\": \"Public\"}"
    UNREFERENCED_PARAMETER(request);
}

HRESULT AutoGenPlayerDataManagementTests::ValidatePFPlayerDataManagementUpdateUserDataResult(PFPlayerDataManagementUpdateUserDataResult* result)
{
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminUpdateUserInternalData

void AutoGenPlayerDataManagementTests::FillUpdateUserInternalDataRequest(PFPlayerDataManagementUpdateUserInternalDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region AdminUpdateUserPublisherData


#pragma endregion

#pragma region AdminUpdateUserPublisherInternalData


#pragma endregion

#pragma region AdminUpdateUserPublisherReadOnlyData


#pragma endregion

#pragma region AdminUpdateUserReadOnlyData


#pragma endregion

#pragma region ClientGetUserData


HRESULT AutoGenPlayerDataManagementTests::ValidatePFPlayerDataManagementClientGetUserDataResult(PFPlayerDataManagementClientGetUserDataResult* result)
{
    // result.data = struct PFUserDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientGetUserPublisherData


#pragma endregion

#pragma region ClientGetUserPublisherReadOnlyData


#pragma endregion

#pragma region ClientGetUserReadOnlyData


#pragma endregion

#pragma region ClientUpdateUserData

void AutoGenPlayerDataManagementTests::FillClientUpdateUserDataRequest(PFPlayerDataManagementClientUpdateUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }, \"Permission\": \"Public\"}"
    StringDictionaryEntryVector<> data{};
    data.insert_or_assign({ "TestUserDataKey","TestUserDataValue" });
    request.SetData(data);
}

#pragma endregion

#pragma region ClientUpdateUserPublisherData


#pragma endregion

#pragma region ServerGetUserData


HRESULT AutoGenPlayerDataManagementTests::ValidatePFPlayerDataManagementServerGetUserDataResult(PFPlayerDataManagementServerGetUserDataResult* result)
{
    // result.data = struct PFUserDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.dataVersion = uint32_t;
    // result.playFabId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerGetUserInternalData


#pragma endregion

#pragma region ServerGetUserPublisherData


#pragma endregion

#pragma region ServerGetUserPublisherInternalData


#pragma endregion

#pragma region ServerGetUserPublisherReadOnlyData


#pragma endregion

#pragma region ServerGetUserReadOnlyData


#pragma endregion

#pragma region ServerUpdateUserData

void AutoGenPlayerDataManagementTests::FillServerUpdateUserDataRequest(PFPlayerDataManagementServerUpdateUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }, \"Permission\": \"Public\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ServerUpdateUserInternalData


#pragma endregion

#pragma region ServerUpdateUserPublisherData


#pragma endregion

#pragma region ServerUpdateUserPublisherInternalData


#pragma endregion

#pragma region ServerUpdateUserPublisherReadOnlyData


#pragma endregion

#pragma region ServerUpdateUserReadOnlyData


#pragma endregion
 

}
