#include "TestAppPch.h"
#include "TestContext.h"
#include "TestApp.h"
#include "AutoGenSharedGroupsTests.h"
#include "XAsyncHelper.h"

namespace PlayFabUnit
{

using namespace PlayFab::Wrappers;

#pragma region ClientAddSharedGroupMembers

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

#pragma endregion

#pragma region ClientGetSharedGroupData

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

#pragma endregion

#pragma region ClientRemoveSharedGroupMembers

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

#pragma endregion

#pragma region ClientUpdateSharedGroupData

void AutoGenSharedGroupsTests::FillUpdateSharedGroupDataRequest(PFSharedGroupsUpdateSharedGroupDataRequestWrapper<>& request)
{
    // Example Request: "{ \"SharedGroupId\": \"Clan Data\", \"Data\": { \"ClanKills\": \"34\", \"LastClanUpdate\": \"2014-10-03T09:21:14Z\" }, \"Permission\": \"Public\"}"
    request.SetSharedGroupId("UpdateSharedGroupData");
    StringDictionaryEntryVector<> data{};
    data.insert_or_assign("test update key", "test update value");
    request.SetData(data);
}

#pragma endregion

#pragma region ServerAddSharedGroupMembers


#pragma endregion

#pragma region ServerCreateSharedGroup


#pragma endregion

#pragma region ServerDeleteSharedGroup

void AutoGenSharedGroupsTests::FillDeleteSharedGroupRequest(PFSharedGroupsDeleteSharedGroupRequestWrapper<>& request)
{
    // Example Request: "{ \"SharedGroupId\": \"Clan Data\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ServerGetSharedGroupData


#pragma endregion

#pragma region ServerRemoveSharedGroupMembers


#pragma endregion

#pragma region ServerUpdateSharedGroupData


#pragma endregion
 

}
