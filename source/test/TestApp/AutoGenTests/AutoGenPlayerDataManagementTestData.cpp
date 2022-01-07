#include "TestAppPch.h"
#include "TestContext.h"
#include "TestApp.h"
#include "AutoGenPlayerDataManagementTests.h"
#include "XAsyncHelper.h"

namespace PlayFabUnit
{

using namespace PlayFab::Wrappers;

#pragma region AdminGetDataReport

void AutoGenPlayerDataManagementTests::FillAdminGetDataReportRequest(PFPlayerDataManagementGetDataReportRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"ReportName\": \"PurchaseDataReport\", \"Year\": 2014, \"Month\": 12, \"Day\": 5}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateAdminGetDataReportResponse(PFPlayerDataManagementGetDataReportResult* result)
{
    // result.downloadUrl = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminGetUserData

void AutoGenPlayerDataManagementTests::FillAdminGetUserDataRequest(PFPlayerDataManagementGetUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Keys\": [ \"preferences\", \"progress\" ], \"IfChangedFromDataVersion\": 13}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateAdminGetUserDataResponse(PFPlayerDataManagementAdminGetUserDataResult* result)
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

void AutoGenPlayerDataManagementTests::FillAdminGetUserInternalDataRequest(PFPlayerDataManagementGetUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Keys\": [ \"preferences\", \"progress\" ], \"IfChangedFromDataVersion\": 13}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateAdminGetUserInternalDataResponse(PFPlayerDataManagementAdminGetUserDataResult* result)
{
    // result.data = struct PFUserDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.dataVersion = uint32_t;
    // result.playFabId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminGetUserPublisherData

void AutoGenPlayerDataManagementTests::FillAdminGetUserPublisherDataRequest(PFPlayerDataManagementGetUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Keys\": [ \"preferences\", \"progress\" ], \"IfChangedFromDataVersion\": 13}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateAdminGetUserPublisherDataResponse(PFPlayerDataManagementAdminGetUserDataResult* result)
{
    // result.data = struct PFUserDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.dataVersion = uint32_t;
    // result.playFabId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminGetUserPublisherInternalData

void AutoGenPlayerDataManagementTests::FillAdminGetUserPublisherInternalDataRequest(PFPlayerDataManagementGetUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Keys\": [ \"preferences\", \"progress\" ], \"IfChangedFromDataVersion\": 13}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateAdminGetUserPublisherInternalDataResponse(PFPlayerDataManagementAdminGetUserDataResult* result)
{
    // result.data = struct PFUserDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.dataVersion = uint32_t;
    // result.playFabId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminGetUserPublisherReadOnlyData

void AutoGenPlayerDataManagementTests::FillAdminGetUserPublisherReadOnlyDataRequest(PFPlayerDataManagementGetUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Keys\": [ \"preferences\", \"progress\" ], \"IfChangedFromDataVersion\": 13}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateAdminGetUserPublisherReadOnlyDataResponse(PFPlayerDataManagementAdminGetUserDataResult* result)
{
    // result.data = struct PFUserDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.dataVersion = uint32_t;
    // result.playFabId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminGetUserReadOnlyData

void AutoGenPlayerDataManagementTests::FillAdminGetUserReadOnlyDataRequest(PFPlayerDataManagementGetUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Keys\": [ \"preferences\", \"progress\" ], \"IfChangedFromDataVersion\": 13}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateAdminGetUserReadOnlyDataResponse(PFPlayerDataManagementAdminGetUserDataResult* result)
{
    // result.data = struct PFUserDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.dataVersion = uint32_t;
    // result.playFabId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminUpdateUserData

void AutoGenPlayerDataManagementTests::FillAdminUpdateUserDataRequest(PFPlayerDataManagementAdminUpdateUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }, \"Permission\": \"Public\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateAdminUpdateUserDataResponse(PFPlayerDataManagementUpdateUserDataResult* result)
{
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminUpdateUserInternalData

void AutoGenPlayerDataManagementTests::FillAdminUpdateUserInternalDataRequest(PFPlayerDataManagementUpdateUserInternalDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateAdminUpdateUserInternalDataResponse(PFPlayerDataManagementUpdateUserDataResult* result)
{
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminUpdateUserPublisherData

void AutoGenPlayerDataManagementTests::FillAdminUpdateUserPublisherDataRequest(PFPlayerDataManagementAdminUpdateUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }, \"Permission\": \"Public\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateAdminUpdateUserPublisherDataResponse(PFPlayerDataManagementUpdateUserDataResult* result)
{
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminUpdateUserPublisherInternalData

void AutoGenPlayerDataManagementTests::FillAdminUpdateUserPublisherInternalDataRequest(PFPlayerDataManagementUpdateUserInternalDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateAdminUpdateUserPublisherInternalDataResponse(PFPlayerDataManagementUpdateUserDataResult* result)
{
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminUpdateUserPublisherReadOnlyData

void AutoGenPlayerDataManagementTests::FillAdminUpdateUserPublisherReadOnlyDataRequest(PFPlayerDataManagementAdminUpdateUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }, \"Permission\": \"Public\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateAdminUpdateUserPublisherReadOnlyDataResponse(PFPlayerDataManagementUpdateUserDataResult* result)
{
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminUpdateUserReadOnlyData

void AutoGenPlayerDataManagementTests::FillAdminUpdateUserReadOnlyDataRequest(PFPlayerDataManagementAdminUpdateUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }, \"Permission\": \"Public\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateAdminUpdateUserReadOnlyDataResponse(PFPlayerDataManagementUpdateUserDataResult* result)
{
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientGetUserData

void AutoGenPlayerDataManagementTests::FillClientGetUserDataRequest(PFPlayerDataManagementGetUserDataRequestWrapper<>& request)
{
    // Example Request: "{ \"Keys\": [ \"preferences\", \"progress\" ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateClientGetUserDataResponse(PFPlayerDataManagementClientGetUserDataResult* result)
{
    // result.data = struct PFUserDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientGetUserPublisherData

void AutoGenPlayerDataManagementTests::FillClientGetUserPublisherDataRequest(PFPlayerDataManagementGetUserDataRequestWrapper<>& request)
{
    // Example Request: "{ \"Keys\": [ \"preferences\", \"progress\" ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateClientGetUserPublisherDataResponse(PFPlayerDataManagementClientGetUserDataResult* result)
{
    // result.data = struct PFUserDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientGetUserPublisherReadOnlyData

void AutoGenPlayerDataManagementTests::FillClientGetUserPublisherReadOnlyDataRequest(PFPlayerDataManagementGetUserDataRequestWrapper<>& request)
{
    // Example Request: "{ \"Keys\": [ \"preferences\", \"progress\" ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateClientGetUserPublisherReadOnlyDataResponse(PFPlayerDataManagementClientGetUserDataResult* result)
{
    // result.data = struct PFUserDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientGetUserReadOnlyData

void AutoGenPlayerDataManagementTests::FillClientGetUserReadOnlyDataRequest(PFPlayerDataManagementGetUserDataRequestWrapper<>& request)
{
    // Example Request: "{ \"Keys\": [ \"preferences\", \"progress\" ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateClientGetUserReadOnlyDataResponse(PFPlayerDataManagementClientGetUserDataResult* result)
{
    // result.data = struct PFUserDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientUpdateUserData

void AutoGenPlayerDataManagementTests::FillClientUpdateUserDataRequest(PFPlayerDataManagementClientUpdateUserDataRequestWrapper<>& request)
{
    // Example Request: "{ \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }, \"Permission\": \"Public\"}"
    StringDictionaryEntryVector<> data{};
    data.insert_or_assign({ "TestUserDataKey","TestUserDataValue" });
    request.SetData(data);
}

HRESULT AutoGenPlayerDataManagementTests::ValidateClientUpdateUserDataResponse(PFPlayerDataManagementUpdateUserDataResult* result)
{
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientUpdateUserPublisherData

void AutoGenPlayerDataManagementTests::FillClientUpdateUserPublisherDataRequest(PFPlayerDataManagementClientUpdateUserDataRequestWrapper<>& request)
{
    // Example Request: "{ \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }, \"Permission\": \"Public\"}"
    StringDictionaryEntryVector<> data{};
    data.insert_or_assign({ "TestUserDataKey","TestUserDataValue" });
    request.SetData(data);
}

HRESULT AutoGenPlayerDataManagementTests::ValidateClientUpdateUserPublisherDataResponse(PFPlayerDataManagementUpdateUserDataResult* result)
{
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerGetUserData

void AutoGenPlayerDataManagementTests::FillServerGetUserDataRequest(PFPlayerDataManagementGetUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Keys\": [ \"preferences\", \"progress\" ], \"IfChangedFromDataVersion\": 13}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateServerGetUserDataResponse(PFPlayerDataManagementServerGetUserDataResult* result)
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

void AutoGenPlayerDataManagementTests::FillServerGetUserInternalDataRequest(PFPlayerDataManagementGetUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Keys\": [ \"preferences\", \"progress\" ], \"IfChangedFromDataVersion\": 13}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateServerGetUserInternalDataResponse(PFPlayerDataManagementServerGetUserDataResult* result)
{
    // result.data = struct PFUserDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.dataVersion = uint32_t;
    // result.playFabId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerGetUserPublisherData

void AutoGenPlayerDataManagementTests::FillServerGetUserPublisherDataRequest(PFPlayerDataManagementGetUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Keys\": [ \"preferences\", \"progress\" ], \"IfChangedFromDataVersion\": 13}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateServerGetUserPublisherDataResponse(PFPlayerDataManagementServerGetUserDataResult* result)
{
    // result.data = struct PFUserDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.dataVersion = uint32_t;
    // result.playFabId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerGetUserPublisherInternalData

void AutoGenPlayerDataManagementTests::FillServerGetUserPublisherInternalDataRequest(PFPlayerDataManagementGetUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Keys\": [ \"preferences\", \"progress\" ], \"IfChangedFromDataVersion\": 13}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateServerGetUserPublisherInternalDataResponse(PFPlayerDataManagementServerGetUserDataResult* result)
{
    // result.data = struct PFUserDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.dataVersion = uint32_t;
    // result.playFabId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerGetUserPublisherReadOnlyData

void AutoGenPlayerDataManagementTests::FillServerGetUserPublisherReadOnlyDataRequest(PFPlayerDataManagementGetUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Keys\": [ \"preferences\", \"progress\" ], \"IfChangedFromDataVersion\": 13}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateServerGetUserPublisherReadOnlyDataResponse(PFPlayerDataManagementServerGetUserDataResult* result)
{
    // result.data = struct PFUserDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.dataVersion = uint32_t;
    // result.playFabId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerGetUserReadOnlyData

void AutoGenPlayerDataManagementTests::FillServerGetUserReadOnlyDataRequest(PFPlayerDataManagementGetUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Keys\": [ \"preferences\", \"progress\" ], \"IfChangedFromDataVersion\": 13}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateServerGetUserReadOnlyDataResponse(PFPlayerDataManagementServerGetUserDataResult* result)
{
    // result.data = struct PFUserDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.dataVersion = uint32_t;
    // result.playFabId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerUpdateUserData

void AutoGenPlayerDataManagementTests::FillServerUpdateUserDataRequest(PFPlayerDataManagementServerUpdateUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }, \"Permission\": \"Public\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateServerUpdateUserDataResponse(PFPlayerDataManagementUpdateUserDataResult* result)
{
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerUpdateUserInternalData

void AutoGenPlayerDataManagementTests::FillServerUpdateUserInternalDataRequest(PFPlayerDataManagementUpdateUserInternalDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateServerUpdateUserInternalDataResponse(PFPlayerDataManagementUpdateUserDataResult* result)
{
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerUpdateUserPublisherData

void AutoGenPlayerDataManagementTests::FillServerUpdateUserPublisherDataRequest(PFPlayerDataManagementServerUpdateUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }, \"Permission\": \"Public\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateServerUpdateUserPublisherDataResponse(PFPlayerDataManagementUpdateUserDataResult* result)
{
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerUpdateUserPublisherInternalData

void AutoGenPlayerDataManagementTests::FillServerUpdateUserPublisherInternalDataRequest(PFPlayerDataManagementUpdateUserInternalDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateServerUpdateUserPublisherInternalDataResponse(PFPlayerDataManagementUpdateUserDataResult* result)
{
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerUpdateUserPublisherReadOnlyData

void AutoGenPlayerDataManagementTests::FillServerUpdateUserPublisherReadOnlyDataRequest(PFPlayerDataManagementServerUpdateUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }, \"Permission\": \"Public\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateServerUpdateUserPublisherReadOnlyDataResponse(PFPlayerDataManagementUpdateUserDataResult* result)
{
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerUpdateUserReadOnlyData

void AutoGenPlayerDataManagementTests::FillServerUpdateUserReadOnlyDataRequest(PFPlayerDataManagementServerUpdateUserDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }, \"Permission\": \"Public\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenPlayerDataManagementTests::ValidateServerUpdateUserReadOnlyDataResponse(PFPlayerDataManagementUpdateUserDataResult* result)
{
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion
 

}
