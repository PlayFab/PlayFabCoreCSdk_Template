#include "TestAppPch.h"
#include "TestContext.h"
#include "TestApp.h"
#include "AutoGenSharedGroupsTests.h"
#include "XAsyncHelper.h"

namespace PlayFabUnit
{

using namespace PlayFab::Wrappers;

#pragma region ClientAddSharedGroupMembers

void AutoGenSharedGroupsTests::FillClientAddSharedGroupMembersPrerequisiteCreateSharedGroupRequest(PFSharedGroupsCreateSharedGroupRequestWrapper<>& request)
{
    request.SetSharedGroupId("AddSharedGroupMembers");
}

HRESULT AutoGenSharedGroupsTests::StoreClientAddSharedGroupMembersPrerequisitePFSharedGroupsCreateSharedGroupResult(std::shared_ptr<CreateSharedGroupResultHolder> result)
{
    testData.m_CreateSharedGroupResult = result;
    return S_OK;
}

void AutoGenSharedGroupsTests::FillAddSharedGroupMembersRequest(PFSharedGroupsAddSharedGroupMembersRequestWrapper<>& request)
{
    // Example Request: "{ \"SharedGroupId\": \"Clan Data\", \"PlayFabIds\": [ \"D984A64B832\", \"F74A523E1562\" ]}"
    request.SetSharedGroupId("AddSharedGroupMembers");
    request.SetPlayFabIds({ "6842934CB46C0834" });
}

void AutoGenSharedGroupsTests::FillClientAddSharedGroupMembersCleanupRemoveSharedGroupMembersRequest(PFSharedGroupsRemoveSharedGroupMembersRequestWrapper<>& request)
{
    // Example Request: "{ \"SharedGroupId\": \"Clan Data\", \"PlayFabIds\": [ \"D984A64B832\", \"F74A523E1562\" ]}"
    request.SetSharedGroupId("AddSharedGroupMembers");
    request.SetPlayFabIds({ "6842934CB46C0834" });
}

void AutoGenSharedGroupsTests::FillClientAddSharedGroupMembersCleanupDeleteSharedGroupRequest(PFSharedGroupsDeleteSharedGroupRequestWrapper<>& request)
{
    request.SetSharedGroupId("AddSharedGroupMembers");
}

#pragma endregion

#pragma region ClientCreateSharedGroup

void AutoGenSharedGroupsTests::FillCreateSharedGroupRequest(PFSharedGroupsCreateSharedGroupRequestWrapper<>& request)
{
    // Example Request: "{ \"SharedGroupId\": \"Clan Data\"}"
    request.SetSharedGroupId("CreateSharedGroup");
}

HRESULT AutoGenSharedGroupsTests::ValidatePFSharedGroupsCreateSharedGroupResult(PFSharedGroupsCreateSharedGroupResult* result)
{
    // result.sharedGroupId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenSharedGroupsTests::FillClientCreateSharedGroupCleanupDeleteSharedGroupRequest(PFSharedGroupsDeleteSharedGroupRequestWrapper<>& request)
{
    request.SetSharedGroupId("CreateSharedGroup");
}

#pragma endregion

#pragma region ClientGetSharedGroupData

void AutoGenSharedGroupsTests::FillClientGetSharedGroupDataPrerequisiteCreateSharedGroupRequest(PFSharedGroupsCreateSharedGroupRequestWrapper<>& request)
{
    // Example request: "{ \"SharedGroupId\": \"Clan Data\"}"
    request.SetSharedGroupId("GetSharedGroupData");
}

HRESULT AutoGenSharedGroupsTests::StoreClientGetSharedGroupDataPrerequisitePFSharedGroupsCreateSharedGroupResult(std::shared_ptr<CreateSharedGroupResultHolder> result)
{
    testData.m_CreateSharedGroupResult = result;
    return S_OK;
}

void AutoGenSharedGroupsTests::FillClientGetSharedGroupDataPrerequisiteUpdateSharedGroupDataRequest(PFSharedGroupsUpdateSharedGroupDataRequestWrapper<>& request)
{
    // Example request: "{ \"SharedGroupId\": \"Clan Data\", \"Data\": { \"ClanKills\": \"34\", \"LastClanUpdate\": \"2014-10-03T09:21:14Z\" }, \"Permission\": \"Public\"}"
    request.SetSharedGroupId("GetSharedGroupData");
    StringDictionaryEntryVector<> data{};
    data.insert_or_assign("test client key", "test client value");
    request.SetData(data);
}

void AutoGenSharedGroupsTests::FillGetSharedGroupDataRequest(PFSharedGroupsGetSharedGroupDataRequestWrapper<>& request)
{
    // Example Request: "{ \"SharedGroupId\": \"Clan Data\", \"Keys\": [ \"ClanKills\", \"LastClanUpdate\" ], \"GetMembers\": true}"
    request.SetSharedGroupId("GetSharedGroupData");
    request.SetGetMembers(true);
}

HRESULT AutoGenSharedGroupsTests::ValidatePFSharedGroupsGetSharedGroupDataResult(PFSharedGroupsGetSharedGroupDataResult* result)
{
    // result.data = struct PFSharedGroupsSharedGroupDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.members = const char* const*;
    // result.membersCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenSharedGroupsTests::FillClientGetSharedGroupDataCleanupDeleteSharedGroupRequest(PFSharedGroupsDeleteSharedGroupRequestWrapper<>& request)
{
    // Example Request: "{ \"SharedGroupId\": \"Clan Data\"}"
    request.SetSharedGroupId("GetSharedGroupData");
}

#pragma endregion

#pragma region ClientRemoveSharedGroupMembers

void AutoGenSharedGroupsTests::FillClientRemoveSharedGroupMembersPrerequisiteCreateSharedGroupRequest(PFSharedGroupsCreateSharedGroupRequestWrapper<>& request)
{
    // Example request: "{ \"SharedGroupId\": \"Clan Data\"}"
    request.SetSharedGroupId("RemoveSharedGroupMembers");
}

HRESULT AutoGenSharedGroupsTests::StoreClientRemoveSharedGroupMembersPrerequisitePFSharedGroupsCreateSharedGroupResult(std::shared_ptr<CreateSharedGroupResultHolder> result)
{
    testData.m_CreateSharedGroupResult = result;
    return S_OK;
}

void AutoGenSharedGroupsTests::FillClientRemoveSharedGroupMembersPrerequisiteAddSharedGroupMembersRequest(PFSharedGroupsAddSharedGroupMembersRequestWrapper<>& request)
{
    // Example request: "{ \"SharedGroupId\": \"Clan Data\", \"PlayFabIds\": [ \"D984A64B832\", \"F74A523E1562\" ]}"
    request.SetSharedGroupId("RemoveSharedGroupMembers");
    request.SetPlayFabIds({ "6842934CB46C0834" });
}

void AutoGenSharedGroupsTests::FillRemoveSharedGroupMembersRequest(PFSharedGroupsRemoveSharedGroupMembersRequestWrapper<>& request)
{
    // Example Request: "{ \"SharedGroupId\": \"Clan Data\", \"PlayFabIds\": [ \"D984A64B832\", \"F74A523E1562\" ]}"
    request.SetSharedGroupId("RemoveSharedGroupMembers");
    request.SetPlayFabIds({ "6842934CB46C0834" });
}

void AutoGenSharedGroupsTests::FillClientRemoveSharedGroupMembersCleanupDeleteSharedGroupRequest(PFSharedGroupsDeleteSharedGroupRequestWrapper<>& request)
{
    // Example Request: "{ \"SharedGroupId\": \"Clan Data\"}"
    request.SetSharedGroupId("RemoveSharedGroupMembers");
}

#pragma endregion

#pragma region ClientUpdateSharedGroupData

void AutoGenSharedGroupsTests::FillClientUpdateSharedGroupDataPrerequisiteCreateSharedGroupRequest(PFSharedGroupsCreateSharedGroupRequestWrapper<>& request)
{
    // Example request: "{ \"SharedGroupId\": \"Clan Data\"}"
    request.SetSharedGroupId("UpdateSharedGroupData");
}

HRESULT AutoGenSharedGroupsTests::StoreClientUpdateSharedGroupDataPrerequisitePFSharedGroupsCreateSharedGroupResult(std::shared_ptr<CreateSharedGroupResultHolder> result)
{
    testData.m_CreateSharedGroupResult = result;
    return S_OK;
}

void AutoGenSharedGroupsTests::FillUpdateSharedGroupDataRequest(PFSharedGroupsUpdateSharedGroupDataRequestWrapper<>& request)
{
    // Example Request: "{ \"SharedGroupId\": \"Clan Data\", \"Data\": { \"ClanKills\": \"34\", \"LastClanUpdate\": \"2014-10-03T09:21:14Z\" }, \"Permission\": \"Public\"}"
    request.SetSharedGroupId("UpdateSharedGroupData");
    StringDictionaryEntryVector<> data{};
    data.insert_or_assign("test update key", "test update value");
    request.SetData(data);
}

void AutoGenSharedGroupsTests::FillClientUpdateSharedGroupDataCleanupDeleteSharedGroupRequest(PFSharedGroupsDeleteSharedGroupRequestWrapper<>& request)
{
    // Example Request: "{ \"SharedGroupId\": \"Clan Data\"}"
    request.SetSharedGroupId("UpdateSharedGroupData");
}

#pragma endregion

#pragma region ServerAddSharedGroupMembers

void AutoGenSharedGroupsTests::FillServerAddSharedGroupMembersPrerequisiteCreateSharedGroupRequest(PFSharedGroupsCreateSharedGroupRequestWrapper<>& request)
{
    request.SetSharedGroupId("AddSharedGroupMembers");
}

HRESULT AutoGenSharedGroupsTests::StoreServerAddSharedGroupMembersPrerequisitePFSharedGroupsCreateSharedGroupResult(std::shared_ptr<CreateSharedGroupResultHolder> result)
{
    testData.m_CreateSharedGroupResult = result;
    return S_OK;
}


void AutoGenSharedGroupsTests::FillServerAddSharedGroupMembersCleanupRemoveSharedGroupMembersRequest(PFSharedGroupsRemoveSharedGroupMembersRequestWrapper<>& request)
{
    // Example Request: "{ \"SharedGroupId\": \"Clan Data\", \"PlayFabIds\": [ \"D984A64B832\", \"F74A523E1562\" ]}"
    request.SetSharedGroupId("AddSharedGroupMembers");
    request.SetPlayFabIds({ "6842934CB46C0834" });
}

void AutoGenSharedGroupsTests::FillServerAddSharedGroupMembersCleanupDeleteSharedGroupRequest(PFSharedGroupsDeleteSharedGroupRequestWrapper<>& request)
{
    request.SetSharedGroupId("AddSharedGroupMembers");
}

#pragma endregion

#pragma region ServerCreateSharedGroup


void AutoGenSharedGroupsTests::FillServerCreateSharedGroupCleanupDeleteSharedGroupRequest(PFSharedGroupsDeleteSharedGroupRequestWrapper<>& request)
{
    request.SetSharedGroupId("CreateSharedGroup");
}

#pragma endregion

#pragma region ServerDeleteSharedGroup

void AutoGenSharedGroupsTests::FillServerDeleteSharedGroupPrerequisiteCreateSharedGroupRequest(PFSharedGroupsCreateSharedGroupRequestWrapper<>& request)
{
    // Example request: "{ \"SharedGroupId\": \"Clan Data\"}"
    request.SetSharedGroupId("DeleteSharedGroup");
}

HRESULT AutoGenSharedGroupsTests::StoreServerDeleteSharedGroupPrerequisitePFSharedGroupsCreateSharedGroupResult(std::shared_ptr<CreateSharedGroupResultHolder> result)
{
    testData.m_CreateSharedGroupResult = result;
    return S_OK;
}

void AutoGenSharedGroupsTests::FillDeleteSharedGroupRequest(PFSharedGroupsDeleteSharedGroupRequestWrapper<>& request)
{
    request.SetSharedGroupId("DeleteSharedGroup");
}

#pragma endregion

#pragma region ServerGetSharedGroupData

void AutoGenSharedGroupsTests::FillServerGetSharedGroupDataPrerequisiteCreateSharedGroupRequest(PFSharedGroupsCreateSharedGroupRequestWrapper<>& request)
{
    // Example request: "{ \"SharedGroupId\": \"Clan Data\"}"
    request.SetSharedGroupId("GetSharedGroupData");
}

HRESULT AutoGenSharedGroupsTests::StoreServerGetSharedGroupDataPrerequisitePFSharedGroupsCreateSharedGroupResult(std::shared_ptr<CreateSharedGroupResultHolder> result)
{
    testData.m_CreateSharedGroupResult = result;
    return S_OK;
}

void AutoGenSharedGroupsTests::FillServerGetSharedGroupDataPrerequisiteUpdateSharedGroupDataRequest(PFSharedGroupsUpdateSharedGroupDataRequestWrapper<>& request)
{
    // Example request: "{ \"SharedGroupId\": \"Clan Data\", \"Data\": { \"ClanKills\": \"34\", \"LastClanUpdate\": \"2014-10-03T09:21:14Z\" }, \"Permission\": \"Public\"}"
    request.SetSharedGroupId("GetSharedGroupData");
    StringDictionaryEntryVector<> data{};
    data.insert_or_assign("test server key", "test server value");
    request.SetData(data);
}


void AutoGenSharedGroupsTests::FillServerGetSharedGroupDataCleanupDeleteSharedGroupRequest(PFSharedGroupsDeleteSharedGroupRequestWrapper<>& request)
{
    // Example Request: "{ \"SharedGroupId\": \"Clan Data\"}"
    request.SetSharedGroupId("GetSharedGroupData");
}

#pragma endregion

#pragma region ServerRemoveSharedGroupMembers

void AutoGenSharedGroupsTests::FillServerRemoveSharedGroupMembersPrerequisiteCreateSharedGroupRequest(PFSharedGroupsCreateSharedGroupRequestWrapper<>& request)
{
    // Example request: "{ \"SharedGroupId\": \"Clan Data\"}"
    request.SetSharedGroupId("RemoveSharedGroupMembers");
}

HRESULT AutoGenSharedGroupsTests::StoreServerRemoveSharedGroupMembersPrerequisitePFSharedGroupsCreateSharedGroupResult(std::shared_ptr<CreateSharedGroupResultHolder> result)
{
    testData.m_CreateSharedGroupResult = result;
    return S_OK;
}

void AutoGenSharedGroupsTests::FillServerRemoveSharedGroupMembersPrerequisiteAddSharedGroupMembersRequest(PFSharedGroupsAddSharedGroupMembersRequestWrapper<>& request)
{
    // Example request: "{ \"SharedGroupId\": \"Clan Data\", \"PlayFabIds\": [ \"D984A64B832\", \"F74A523E1562\" ]}"
    request.SetSharedGroupId("RemoveSharedGroupMembers");
    request.SetPlayFabIds({ "6842934CB46C0834" });
}


void AutoGenSharedGroupsTests::FillServerRemoveSharedGroupMembersCleanupDeleteSharedGroupRequest(PFSharedGroupsDeleteSharedGroupRequestWrapper<>& request)
{
    // Example Request: "{ \"SharedGroupId\": \"Clan Data\"}"
    request.SetSharedGroupId("RemoveSharedGroupMembers");
}

#pragma endregion

#pragma region ServerUpdateSharedGroupData

void AutoGenSharedGroupsTests::FillServerUpdateSharedGroupDataPrerequisiteCreateSharedGroupRequest(PFSharedGroupsCreateSharedGroupRequestWrapper<>& request)
{
    // Example request: "{ \"SharedGroupId\": \"Clan Data\"}"
    request.SetSharedGroupId("UpdateSharedGroupData");
}

HRESULT AutoGenSharedGroupsTests::StoreServerUpdateSharedGroupDataPrerequisitePFSharedGroupsCreateSharedGroupResult(std::shared_ptr<CreateSharedGroupResultHolder> result)
{
    testData.m_CreateSharedGroupResult = result;
    return S_OK;
}


void AutoGenSharedGroupsTests::FillServerUpdateSharedGroupDataCleanupDeleteSharedGroupRequest(PFSharedGroupsDeleteSharedGroupRequestWrapper<>& request)
{
    // Example Request: "{ \"SharedGroupId\": \"Clan Data\"}"
    request.SetSharedGroupId("UpdateSharedGroupData");
}

#pragma endregion
 

}
