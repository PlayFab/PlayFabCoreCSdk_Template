#include "TestAppPch.h"
#include "TestContext.h"
#include "TestApp.h"
#include "AutoGenFriendsTests.h"
#include "XAsyncHelper.h"

namespace PlayFabUnit
{

using namespace PlayFab::Wrappers;

#pragma region ClientAddFriend

void AutoGenFriendsTests::FillClientAddFriendRequest(PFFriendsClientAddFriendRequestWrapper<>& request)
{
    // Example Request: "{ \"FriendPlayFabId\": \"29837799\"}"
    request.SetFriendPlayFabId("76D9E1E588B0CFFC");
}

HRESULT AutoGenFriendsTests::ValidateClientAddFriendResponse(PFFriendsAddFriendResult* result)
{
    // result.created = bool;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenFriendsTests::FillClientAddFriendCleanupClientRemoveFriendRequest(PFFriendsClientRemoveFriendRequestWrapper<>& request)
{
    // Example Request: "{ \"FriendPlayFabId\": \"29837799\"}"
    request.SetFriendPlayFabId("76D9E1E588B0CFFC");
}

#pragma endregion

#pragma region ClientGetFriendsList

void AutoGenFriendsTests::FillClientGetFriendsListRequest(PFFriendsClientGetFriendsListRequestWrapper<>& request)
{
    // Example Request: "{ \"IncludeSteamFriends\": true}"
    UNREFERENCED_PARAMETER(request);
}

HRESULT AutoGenFriendsTests::ValidateClientGetFriendsListResponse(PFFriendsGetFriendsListResult* result)
{
    // result.friends = PFFriendsFriendInfo const* const*;
    // result.friendsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientRemoveFriend

void AutoGenFriendsTests::FillClientRemoveFriendPrerequisiteClientAddFriendRequest(PFFriendsClientAddFriendRequestWrapper<>& request)
{
    // Example request: "{ \"FriendPlayFabId\": \"29837799\"}"
    request.SetFriendPlayFabId("76D9E1E588B0CFFC");
}

HRESULT AutoGenFriendsTests::StoreClientRemoveFriendPrerequisiteClientAddFriendResponse(std::shared_ptr<AddFriendResultHolder> result)
{
    testData.m_AddFriendResult = result;
    return S_OK;
}

void AutoGenFriendsTests::FillClientRemoveFriendRequest(PFFriendsClientRemoveFriendRequestWrapper<>& request)
{
    // Example Request: "{ \"FriendPlayFabId\": \"29837799\"}"
    request.SetFriendPlayFabId("76D9E1E588B0CFFC");
}

#pragma endregion

#pragma region ClientSetFriendTags

void AutoGenFriendsTests::FillClientSetFriendTagsRequest(PFFriendsClientSetFriendTagsRequestWrapper<>& request)
{
    // Example Request: "{ \"FriendPlayFabId\": \"29837799\", \"Tags\": [ \"great sniper\", \"no good at melee\" ]}"
    UNREFERENCED_PARAMETER(request);
    request.SetFriendPlayFabId("75DE95A234BF9D97");
    request.SetTags({ "tag1", "tag2" });
}

#pragma endregion

#pragma region ServerAddFriend

void AutoGenFriendsTests::FillServerAddFriendRequest(PFFriendsServerAddFriendRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"FriendPlayFabId\": \"20394883\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ServerGetFriendsList

void AutoGenFriendsTests::FillServerGetFriendsListRequest(PFFriendsServerGetFriendsListRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"IncludeSteamFriends\": true}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenFriendsTests::ValidateServerGetFriendsListResponse(PFFriendsGetFriendsListResult* result)
{
    // result.friends = PFFriendsFriendInfo const* const*;
    // result.friendsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerRemoveFriend

void AutoGenFriendsTests::FillServerRemoveFriendRequest(PFFriendsServerRemoveFriendRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"FriendPlayFabId\": \"29837799\", \"PlayFabId\": \"{{PlayFabId}}\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ServerSetFriendTags

void AutoGenFriendsTests::FillServerSetFriendTagsRequest(PFFriendsServerSetFriendTagsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"FriendPlayFabId\": \"298ABC37799\", \"Tags\": [ \"sniper\", \"melee\" ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion
 

}
