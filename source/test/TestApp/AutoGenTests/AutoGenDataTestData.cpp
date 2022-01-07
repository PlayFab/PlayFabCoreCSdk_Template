#include "TestAppPch.h"
#include "TestContext.h"
#include "TestApp.h"
#include "AutoGenDataTests.h"
#include "XAsyncHelper.h"
#include "JsonUtils.h"

#include <HttpClient.h>
#include <httpClient/httpClient.h>

namespace PlayFabUnit
{

using namespace PlayFab::Wrappers;

HRESULT UploadFileSync(std::string url, PlayFab::JsonValue& requestBody)
{
    HCCallHandle callHandle{ nullptr };

    // Set up HCHttpCallHandle
    RETURN_IF_FAILED(HCHttpCallCreate(&callHandle));
    RETURN_IF_FAILED(HCHttpCallRequestSetUrl(callHandle, "PUT", url.c_str()));

    RETURN_IF_FAILED(HCHttpCallRequestSetHeader(callHandle, "Content-Type", "application/json; charset=utf-8", true));
    
    RETURN_IF_FAILED(HCHttpCallRequestSetRequestBodyString(callHandle, PlayFab::JsonUtils::WriteToString(requestBody).c_str()));

    XAsyncBlock asyncBlock{};
    RETURN_IF_FAILED(HCHttpCallPerformAsync(callHandle, &asyncBlock));

    return XAsyncGetStatus(&asyncBlock, true);
}

#pragma region AbortFileUploads

void AutoGenDataTests::FillAbortFileUploadsPrerequisiteInitiateFileUploadsRequest(PFDataInitiateFileUploadsRequestWrapper<>& request)
{
    // Example request: "{ \"FileNames\": [ \"profile_configuration\", \"game_state\" ], \"Entity\": { \"Id\": \"ID\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetFileNames({ "TestFileAbort" });
    request.SetEntity(PFEntityKey{ "B64BE91E5DBD5597", "title_player_account" });
}

HRESULT AutoGenDataTests::StoreAbortFileUploadsPrerequisiteInitiateFileUploadsResponse(std::shared_ptr<InitiateFileUploadsResponseHolder> result)
{
    testData.m_InitiateFileUploadsResponse = result;
    return S_OK;
}

void AutoGenDataTests::FillAbortFileUploadsRequest(PFDataAbortFileUploadsRequestWrapper<>& request)
{
    // Example Request: "{ \"FileNames\": [ \"avatar\" ], \"Entity\": { \"Id\": \"ID\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetFileNames({ "TestFileAbort" });
    request.SetEntity(PFEntityKey{ "B64BE91E5DBD5597", "title_player_account" });
}

HRESULT AutoGenDataTests::ValidateAbortFileUploadsResponse(PFDataAbortFileUploadsResponse* result)
{
    // result.entity = PFEntityKey const*;
    // result.profileVersion = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region DeleteFiles

void AutoGenDataTests::FillDeleteFilesPrerequisiteInitiateFileUploadsRequest(PFDataInitiateFileUploadsRequestWrapper<>& request)
{
    // Example request: "{ \"FileNames\": [ \"profile_configuration\", \"game_state\" ], \"Entity\": { \"Id\": \"ID\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetFileNames({ "TestFileDelete" });
    request.SetEntity(PFEntityKey{ "B64BE91E5DBD5597", "title_player_account" });
}

HRESULT AutoGenDataTests::StoreDeleteFilesPrerequisiteInitiateFileUploadsResponse(std::shared_ptr<InitiateFileUploadsResponseHolder> result)
{
    testData.m_InitiateFileUploadsResponse = result;

    PlayFab::JsonDocument requestBody;
    requestBody.Parse("{ \"body\": \"Delete Files\" }");
    UploadFileSync(testData.m_InitiateFileUploadsResponse->result->uploadDetails[0]->uploadUrl, requestBody);
    return S_OK;
}

void AutoGenDataTests::FillDeleteFilesPrerequisiteFinalizeFileUploadsRequest(PFDataFinalizeFileUploadsRequestWrapper<>& request)
{
    // Example request: "{ \"ProfileVersion\": 0, \"FileNames\": [ \"profile_configuration\", \"game_state\" ], \"Entity\": { \"Id\": \"ID\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetFileNames({ "TestFileDelete" });
    request.SetEntity(PFEntityKey{ "B64BE91E5DBD5597", "title_player_account" });
}

HRESULT AutoGenDataTests::StoreDeleteFilesPrerequisiteFinalizeFileUploadsResponse(std::shared_ptr<FinalizeFileUploadsResponseHolder> result)
{
    testData.m_FinalizeFileUploadsResponse = result;
    return S_OK;
}

void AutoGenDataTests::FillDeleteFilesRequest(PFDataDeleteFilesRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"FileNames\": [ \"game_state\", \"avatar\" ], \"Entity\": { \"Id\": \"ID\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetFileNames({ "TestFileDelete" });
    request.SetEntity(PFEntityKey{ "B64BE91E5DBD5597", "title_player_account" });
}

HRESULT AutoGenDataTests::ValidateDeleteFilesResponse(PFDataDeleteFilesResponse* result)
{
    // result.entity = PFEntityKey const*;
    // result.profileVersion = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region FinalizeFileUploads

void AutoGenDataTests::FillFinalizeFileUploadsPrerequisiteInitiateFileUploadsRequest(PFDataInitiateFileUploadsRequestWrapper<>& request)
{
    // Example request: "{ \"FileNames\": [ \"profile_configuration\", \"game_state\" ], \"Entity\": { \"Id\": \"ID\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetFileNames({ "TestFileFinalize" });
    request.SetEntity(PFEntityKey{ "B64BE91E5DBD5597", "title_player_account" });
}

HRESULT AutoGenDataTests::StoreFinalizeFileUploadsPrerequisiteInitiateFileUploadsResponse(std::shared_ptr<InitiateFileUploadsResponseHolder> result)
{
    testData.m_InitiateFileUploadsResponse = result;

    PlayFab::JsonDocument requestBody;
    requestBody.Parse("{ \"body\": \"Finalize File Uploads\" }");
    UploadFileSync(testData.m_InitiateFileUploadsResponse->result->uploadDetails[0]->uploadUrl, requestBody);
    return S_OK;
}

void AutoGenDataTests::FillFinalizeFileUploadsRequest(PFDataFinalizeFileUploadsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"ProfileVersion\": 0, \"FileNames\": [ \"profile_configuration\", \"game_state\" ], \"Entity\": { \"Id\": \"ID\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetFileNames({ "TestFileFinalize" });
    request.SetEntity(PFEntityKey{ "B64BE91E5DBD5597", "title_player_account" });
}

HRESULT AutoGenDataTests::ValidateFinalizeFileUploadsResponse(PFDataFinalizeFileUploadsResponse* result)
{
    // result.entity = PFEntityKey const*;
    // result.metadata = struct PFDataGetFileMetadataDictionaryEntry const*;
    // result.metadataCount = uint32_t;
    // result.profileVersion = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenDataTests::FillFinalizeFileUploadsCleanupDeleteFilesRequest(PFDataDeleteFilesRequestWrapper<>& request)
{
    // Example Request: "{ \"FileNames\": [ \"game_state\", \"avatar\" ], \"Entity\": { \"Id\": \"ID\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetFileNames({ "TestFileFinalize" });
    request.SetEntity(PFEntityKey{ "B64BE91E5DBD5597", "title_player_account" });
}

HRESULT AutoGenDataTests::StoreFinalizeFileUploadsCleanupDeleteFilesResponse(std::shared_ptr<DeleteFilesResponseHolder> result)
{
    testData.m_DeleteFilesResponse = result;
    return S_OK;
}

#pragma endregion

#pragma region GetFiles

void AutoGenDataTests::FillGetFilesRequest(PFDataGetFilesRequestWrapper<>& request)
{
    // Example Request: "{ \"Entity\": { \"Id\": \"ID\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetEntity(PFEntityKey{ "B64BE91E5DBD5597", "title_player_account" });
}

HRESULT AutoGenDataTests::ValidateGetFilesResponse(PFDataGetFilesResponse* result)
{
    // result.entity = PFEntityKey const*;
    // result.metadata = struct PFDataGetFileMetadataDictionaryEntry const*;
    // result.metadataCount = uint32_t;
    // result.profileVersion = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region GetObjects

void AutoGenDataTests::FillGetObjectsRequest(PFDataGetObjectsRequestWrapper<>& request)
{
    // Example Request: "{ \"Entity\": { \"Id\": \"ABC90712ABC\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetEntity(PFEntityKey{ "B64BE91E5DBD5597", "title_player_account" });
}

HRESULT AutoGenDataTests::ValidateGetObjectsResponse(PFDataGetObjectsResponse* result)
{
    // result.entity = PFEntityKey const*;
    // result.objects = struct PFDataObjectResultDictionaryEntry const*;
    // result.objectsCount = uint32_t;
    // result.profileVersion = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region InitiateFileUploads

void AutoGenDataTests::FillInitiateFileUploadsRequest(PFDataInitiateFileUploadsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"FileNames\": [ \"profile_configuration\", \"game_state\" ], \"Entity\": { \"Id\": \"ID\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetFileNames({ "TestFileInitiate" });
    request.SetEntity(PFEntityKey{ "B64BE91E5DBD5597", "title_player_account" });
}

HRESULT AutoGenDataTests::ValidateInitiateFileUploadsResponse(PFDataInitiateFileUploadsResponse* result)
{
    // result.entity = PFEntityKey const*;
    // result.profileVersion = int32_t;
    // result.uploadDetails = PFDataInitiateFileUploadMetadata const* const*;
    // result.uploadDetailsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenDataTests::FillInitiateFileUploadsCleanupAbortFileUploadsRequest(PFDataAbortFileUploadsRequestWrapper<>& request)
{
    // Example Request: "{ \"FileNames\": [ \"avatar\" ], \"Entity\": { \"Id\": \"ID\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetFileNames({ "TestFileInitiate" });
    request.SetEntity(PFEntityKey{ "B64BE91E5DBD5597", "title_player_account" });
}

HRESULT AutoGenDataTests::StoreInitiateFileUploadsCleanupAbortFileUploadsResponse(std::shared_ptr<AbortFileUploadsResponseHolder> result)
{
    testData.m_AbortFileUploadsResponse = result;
    return S_OK;
}

#pragma endregion

#pragma region SetObjects

void AutoGenDataTests::FillSetObjectsPrerequisiteSetObjectsRequest(PFDataSetObjectsRequestWrapper<>& request)
{
    // Example request: "{ \"ExpectedProfileVersion\": 5, \"Objects\": [ {  \"ObjectName\": \"SaveSate\",  \"DataObject\": {  \"PlayerDetails\": {   \"LastMissionSuccess\": \"2017-06-15T11:05:19Z\",   \"LastMissionFailure\": \"2017-06-12T11:05:19Z\",   \"MapPosition\": [   22,   37.78   ],   \"IsPaidUpgrade\": true  },  \"GameSettings\": {   \"Screen\": \"FriendsList\",   \"Favorites\": [   \"Place 1\",   \"Place 2\"   ]  }  },  \"SimpleStatements\": {  \"Read\": [   {   \"Friend\": true   }  ],  \"Write\": [   \"Self\"  ]  } } ], \"Entity\": { \"Id\": \"A8140AB9109712B\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    ModelVector<PFDataSetObjectWrapper<>> objects;
    PFDataSetObject pfObject{};
    pfObject.objectName = "TestObjectName";
    pfObject.dataObject.stringValue = "can't be null right now";
    pfObject.escapedDataObject = "\"Test Object Prereq Data\"";
    objects.push_back(pfObject);
    request.SetObjects(std::move(objects));
    request.SetEntity(PFEntityKey{ "33D5E873FB4D8629", "title_player_account" });
}

HRESULT AutoGenDataTests::StoreSetObjectsPrerequisiteSetObjectsResponse(std::shared_ptr<SetObjectsResponseHolder> result)
{
    testData.m_SetObjectsResponse = result;
    return S_OK;
}

void AutoGenDataTests::FillSetObjectsRequest(PFDataSetObjectsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"ExpectedProfileVersion\": 5, \"Objects\": [ {  \"ObjectName\": \"SaveSate\",  \"DataObject\": {  \"PlayerDetails\": {   \"LastMissionSuccess\": \"2017-06-15T11:05:19Z\",   \"LastMissionFailure\": \"2017-06-12T11:05:19Z\",   \"MapPosition\": [   22,   37.78   ],   \"IsPaidUpgrade\": true  },  \"GameSettings\": {   \"Screen\": \"FriendsList\",   \"Favorites\": [   \"Place 1\",   \"Place 2\"   ]  }  },  \"SimpleStatements\": {  \"Read\": [   {   \"Friend\": true   }  ],  \"Write\": [   \"Self\"  ]  } } ], \"Entity\": { \"Id\": \"A8140AB9109712B\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    ModelVector<PFDataSetObjectWrapper<>> objects;
    PFDataSetObject pfObject{};
    pfObject.objectName = "TestObjectName";
    pfObject.dataObject.stringValue = "{ \"Test Object\": \"New Data\" }";
    objects.push_back(pfObject);
    request.SetObjects(std::move(objects));
    request.SetEntity(PFEntityKey{ "33D5E873FB4D8629", "title_player_account" });
}

HRESULT AutoGenDataTests::ValidateSetObjectsResponse(PFDataSetObjectsResponse* result)
{
    // result.profileVersion = int32_t;
    // result.setResults = PFDataSetObjectInfo const* const*;
    // result.setResultsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion
 

}
