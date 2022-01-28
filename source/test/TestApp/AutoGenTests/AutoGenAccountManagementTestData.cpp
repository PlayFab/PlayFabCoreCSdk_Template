#include "TestAppPch.h"
#include "TestContext.h"
#include "TestApp.h"
#include "AutoGenAccountManagementTests.h"
#include "XAsyncHelper.h"

namespace PlayFabUnit
{

using namespace PlayFab::Wrappers;

#pragma region AdminBanUsers

void AutoGenAccountManagementTests::FillAdminBanUsersRequest(PFAccountManagementBanUsersRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"Bans\": [ {  \"PlayFabId\": \"1679AF5CD04BD838\",  \"IPAddress\": \"192.168.1.1\",  \"Reason\": \"You cheated!\",  \"DurationInHours\": 7 }, {  \"PlayFabId\": \"2329AF5CD04BF513\",  \"Reason\": \"Caught you using speed hack!\" } ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateAdminBanUsersResponse(PFAccountManagementBanUsersResult* result)
{
    // result.banData = PFAccountManagementBanInfo const* const*;
    // result.banDataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminDeleteMasterPlayerAccount

void AutoGenAccountManagementTests::FillAdminDeleteMasterPlayerAccountRequest(PFAccountManagementDeleteMasterPlayerAccountRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"MetaData\": \"Identifying info\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateAdminDeleteMasterPlayerAccountResponse(PFAccountManagementDeleteMasterPlayerAccountResult* result)
{
    // result.jobReceiptId = const char*;
    // result.titleIds = const char* const*;
    // result.titleIdsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminDeleteMembershipSubscription

void AutoGenAccountManagementTests::FillAdminDeleteMembershipSubscriptionRequest(PFAccountManagementDeleteMembershipSubscriptionRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"MembershipId\": \"ShieldBonusMembership\", \"SubscriptionId\": \"39F6B89A-0F0C-4D96-B12C-BA89543A11A1\", \"PlayFabId\": \"{{PlayFabId}}\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region AdminDeletePlayer

void AutoGenAccountManagementTests::FillAdminDeletePlayerRequest(PFAccountManagementDeletePlayerRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region AdminDeleteTitle


#pragma endregion

#pragma region AdminExportMasterPlayerData

void AutoGenAccountManagementTests::FillAdminExportMasterPlayerDataRequest(PFAccountManagementExportMasterPlayerDataRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateAdminExportMasterPlayerDataResponse(PFAccountManagementExportMasterPlayerDataResult* result)
{
    // result.jobReceiptId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminGetPlayedTitleList

void AutoGenAccountManagementTests::FillAdminGetPlayedTitleListRequest(PFAccountManagementGetPlayedTitleListRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateAdminGetPlayedTitleListResponse(PFAccountManagementGetPlayedTitleListResult* result)
{
    // result.titleIds = const char* const*;
    // result.titleIdsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminGetPlayerIdFromAuthToken

void AutoGenAccountManagementTests::FillAdminGetPlayerIdFromAuthTokenRequest(PFAccountManagementGetPlayerIdFromAuthTokenRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"Token\": \"3F584AD0EF943E2\", \"TokenType\": \"Email\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateAdminGetPlayerIdFromAuthTokenResponse(PFAccountManagementGetPlayerIdFromAuthTokenResult* result)
{
    // result.playFabId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminGetPlayerProfile

void AutoGenAccountManagementTests::FillAdminGetPlayerProfileRequest(PFAccountManagementGetPlayerProfileRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateAdminGetPlayerProfileResponse(PFAccountManagementGetPlayerProfileResult* result)
{
    // result.playerProfile = PFPlayerProfileModel const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminGetUserAccountInfo

void AutoGenAccountManagementTests::FillAdminGetUserAccountInfoRequest(PFAccountManagementLookupUserAccountInfoRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"IgnoreMissingTitleActivation\": false}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateAdminGetUserAccountInfoResponse(PFAccountManagementLookupUserAccountInfoResult* result)
{
    // result.userInfo = PFUserAccountInfo const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminGetUserBans

void AutoGenAccountManagementTests::FillAdminGetUserBansRequest(PFAccountManagementGetUserBansRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateAdminGetUserBansResponse(PFAccountManagementGetUserBansResult* result)
{
    // result.banData = PFAccountManagementBanInfo const* const*;
    // result.banDataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminResetPassword

void AutoGenAccountManagementTests::FillAdminResetPasswordRequest(PFAccountManagementResetPasswordRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"Token\": \"2B584FA1DF645E4\", \"Password\": \"ExampleSecret@r\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region AdminRevokeAllBansForUser

void AutoGenAccountManagementTests::FillAdminRevokeAllBansForUserRequest(PFAccountManagementRevokeAllBansForUserRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateAdminRevokeAllBansForUserResponse(PFAccountManagementRevokeAllBansForUserResult* result)
{
    // result.banData = PFAccountManagementBanInfo const* const*;
    // result.banDataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminRevokeBans

void AutoGenAccountManagementTests::FillAdminRevokeBansRequest(PFAccountManagementRevokeBansRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"BanIds\": [ \"E0B5FF89542D413C\", \"EF43FF89542G1546\" ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateAdminRevokeBansResponse(PFAccountManagementRevokeBansResult* result)
{
    // result.banData = PFAccountManagementBanInfo const* const*;
    // result.banDataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminSendAccountRecoveryEmail

void AutoGenAccountManagementTests::FillAdminSendAccountRecoveryEmailRequest(PFAccountManagementAdminSendAccountRecoveryEmailRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"Email\": \"assignedemail@here.com\", \"EmailTemplateId\": \"D53AB15D8F12E330\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region AdminSetMembershipOverride

void AutoGenAccountManagementTests::FillAdminSetMembershipOverrideRequest(PFAccountManagementSetMembershipOverrideRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"ExpirationTime\": \"2021-12-09T18:14:28.24Z\", \"MembershipId\": \"ShieldBonusMembership\", \"PlayFabId\": \"{{PlayFabId}}\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region AdminUpdateBans

void AutoGenAccountManagementTests::FillAdminUpdateBansRequest(PFAccountManagementUpdateBansRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"Bans\": [ {  \"BanId\": \"E0B5FF89542D413C\",  \"Permanent\": true,  \"Active\": true }, {  \"BanId\": \"EF43FF89542G1546\",  \"Reason\": \"Royal pardon\",  \"Expires\": \"2016-07-04T00:00:00Z\" } ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateAdminUpdateBansResponse(PFAccountManagementUpdateBansResult* result)
{
    // result.banData = PFAccountManagementBanInfo const* const*;
    // result.banDataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminUpdateUserTitleDisplayName

void AutoGenAccountManagementTests::FillAdminUpdateUserTitleDisplayNameRequest(PFAccountManagementAdminUpdateUserTitleDisplayNameRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"DisplayName\": \"New Display Name\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateAdminUpdateUserTitleDisplayNameResponse(PFAccountManagementUpdateUserTitleDisplayNameResult* result)
{
    // result.displayName = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientAddGenericID

void AutoGenAccountManagementTests::FillClientAddGenericIDRequest(PFAccountManagementClientAddGenericIDRequestWrapper<>& request)
{
    // Example Request: "{ \"GenericId\": { \"ServiceName\": \"BigBizSocial\", \"UserId\": \"1234567890\" }}"
    PFAccountManagementGenericServiceIdWrapper<> id;
    id.SetServiceName("TestGenericServiceName");
    id.SetUserId("TestGenericUserId");

    request.SetGenericId(id);
}

#pragma endregion

#pragma region ClientAddOrUpdateContactEmail

void AutoGenAccountManagementTests::FillClientAddOrUpdateContactEmailRequest(PFAccountManagementAddOrUpdateContactEmailRequestWrapper<>& request)
{
    // Example Request: "{ \"EmailAddress\": \"theuser@domain.com\"}"
    request.SetEmailAddress("me@here.com");
}

#pragma endregion

#pragma region ClientAddUsernamePassword

void AutoGenAccountManagementTests::FillClientAddUsernamePasswordRequest(PFAccountManagementAddUsernamePasswordRequestWrapper<>& request)
{
    // Example Request: "{ \"Username\": \"theuser\", \"Email\": \"me@here.com\", \"Password\": \"ExampleSecret\"}"
    request.SetEmail("testemail@here.com");
    request.SetPassword("testpassword");
    request.SetUsername("testusername");
}

HRESULT AutoGenAccountManagementTests::ValidateClientAddUsernamePasswordResponse(PFAccountManagementAddUsernamePasswordResult* result)
{
    // result.username = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientGetAccountInfo

void AutoGenAccountManagementTests::FillClientGetAccountInfoRequest(PFAccountManagementGetAccountInfoRequestWrapper<>& request)
{
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\"}"
    request.SetPlayFabId("462A009489BDCA48");
}

HRESULT AutoGenAccountManagementTests::ValidateClientGetAccountInfoResponse(PFAccountManagementGetAccountInfoResult* result)
{
    // result.accountInfo = PFUserAccountInfo const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientGetPlayerCombinedInfo

void AutoGenAccountManagementTests::FillClientGetPlayerCombinedInfoRequest(PFAccountManagementGetPlayerCombinedInfoRequestWrapper<>& request)
{
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"InfoRequestParameters\": { \"GetUserAccountInfo\": true, \"GetUserInventory\": false, \"GetUserVirtualCurrency\": true, \"GetUserData\": true, \"UserDataKeys\": [  \"preferences\",  \"progress\" ], \"GetUserReadOnlyData\": false, \"GetCharacterInventories\": false, \"GetCharacterList\": false, \"GetTitleData\": false, \"GetPlayerStatistics\": false, \"GetPlayerProfile\": false }}"
    request.SetPlayFabId("462A009489BDCA48");
}

HRESULT AutoGenAccountManagementTests::ValidateClientGetPlayerCombinedInfoResponse(PFAccountManagementGetPlayerCombinedInfoResult* result)
{
    // result.infoResultPayload = PFGetPlayerCombinedInfoResultPayload const*;
    // result.playFabId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientGetPlayerProfile

void AutoGenAccountManagementTests::FillClientGetPlayerProfileRequest(PFAccountManagementGetPlayerProfileRequestWrapper<>& request)
{
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\"}"
    request.SetPlayFabId("462A009489BDCA48");
}

HRESULT AutoGenAccountManagementTests::ValidateClientGetPlayerProfileResponse(PFAccountManagementGetPlayerProfileResult* result)
{
    // result.playerProfile = PFPlayerProfileModel const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientGetPlayFabIDsFromFacebookIDs

void AutoGenAccountManagementTests::FillClientGetPlayFabIDsFromFacebookIDsRequest(PFAccountManagementGetPlayFabIDsFromFacebookIDsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"FacebookIDs\": [ \"857498576495\", \"759374651209\" ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateClientGetPlayFabIDsFromFacebookIDsResponse(PFAccountManagementGetPlayFabIDsFromFacebookIDsResult* result)
{
    // result.data = PFAccountManagementFacebookPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientGetPlayFabIDsFromFacebookInstantGamesIds

void AutoGenAccountManagementTests::FillClientGetPlayFabIDsFromFacebookInstantGamesIdsRequest(PFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"FacebookInstantGamesIds\": [ \"1114685845316172\", \"1114685845316173\" ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateClientGetPlayFabIDsFromFacebookInstantGamesIdsResponse(PFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult* result)
{
    // result.data = PFAccountManagementFacebookInstantGamesPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientGetPlayFabIDsFromGameCenterIDs

void AutoGenAccountManagementTests::FillClientGetPlayFabIDsFromGameCenterIDsRequest(PFAccountManagementGetPlayFabIDsFromGameCenterIDsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"GameCenterIDs\": [ \"857498576495\", \"759374651209\" ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateClientGetPlayFabIDsFromGameCenterIDsResponse(PFAccountManagementGetPlayFabIDsFromGameCenterIDsResult* result)
{
    // result.data = PFAccountManagementGameCenterPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientGetPlayFabIDsFromGenericIDs

void AutoGenAccountManagementTests::FillClientGetPlayFabIDsFromGenericIDsRequest(PFAccountManagementGetPlayFabIDsFromGenericIDsRequestWrapper<>& request)
{
    // Example Request: "{ \"GenericIDs\": [ {  \"ServiceName\": \"BigBizSocial\",  \"UserId\": \"1234567890\" }, {  \"ServiceName\": \"VeeCeeMe\",  \"UserId\": \"og5igh85gf43gf\" } ]}"
    PFAccountManagementGenericServiceIdWrapper<> id;
    id.SetServiceName("TestGenericServiceName");
    id.SetUserId("TestGenericUserId");

    ModelVector<PFAccountManagementGenericServiceIdWrapper<>> ids;
    ids.push_back(id);

    request.SetGenericIDs(ids);
}

HRESULT AutoGenAccountManagementTests::ValidateClientGetPlayFabIDsFromGenericIDsResponse(PFAccountManagementGetPlayFabIDsFromGenericIDsResult* result)
{
    // result.data = PFAccountManagementGenericPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientGetPlayFabIDsFromGoogleIDs

void AutoGenAccountManagementTests::FillClientGetPlayFabIDsFromGoogleIDsRequest(PFAccountManagementGetPlayFabIDsFromGoogleIDsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"GoogleIDs\": [ \"857498576495\", \"759374651209\" ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateClientGetPlayFabIDsFromGoogleIDsResponse(PFAccountManagementGetPlayFabIDsFromGoogleIDsResult* result)
{
    // result.data = PFAccountManagementGooglePlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientGetPlayFabIDsFromKongregateIDs

void AutoGenAccountManagementTests::FillClientGetPlayFabIDsFromKongregateIDsRequest(PFAccountManagementGetPlayFabIDsFromKongregateIDsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"KongregateIDs\": [ \"857498576495\", \"759374651209\" ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateClientGetPlayFabIDsFromKongregateIDsResponse(PFAccountManagementGetPlayFabIDsFromKongregateIDsResult* result)
{
    // result.data = PFAccountManagementKongregatePlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientGetPlayFabIDsFromNintendoSwitchDeviceIds

void AutoGenAccountManagementTests::FillClientGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest(PFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"NintendoSwitchDeviceIds\": [ \"526f79204261747478\", \"526f79204261747479\" ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateClientGetPlayFabIDsFromNintendoSwitchDeviceIdsResponse(PFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult* result)
{
    // result.data = PFAccountManagementNintendoSwitchPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientGetPlayFabIDsFromPSNAccountIDs

void AutoGenAccountManagementTests::FillClientGetPlayFabIDsFromPSNAccountIDsRequest(PFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PSNAccountIDs\": [ \"857498576495\", \"759374651209\" ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateClientGetPlayFabIDsFromPSNAccountIDsResponse(PFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult* result)
{
    // result.data = PFAccountManagementPSNAccountPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientGetPlayFabIDsFromSteamIDs

void AutoGenAccountManagementTests::FillClientGetPlayFabIDsFromSteamIDsRequest(PFAccountManagementGetPlayFabIDsFromSteamIDsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"SteamStringIDs\": [ \"857498576495\", \"759374651209\" ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateClientGetPlayFabIDsFromSteamIDsResponse(PFAccountManagementGetPlayFabIDsFromSteamIDsResult* result)
{
    // result.data = PFAccountManagementSteamPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientGetPlayFabIDsFromTwitchIDs

void AutoGenAccountManagementTests::FillClientGetPlayFabIDsFromTwitchIDsRequest(PFAccountManagementGetPlayFabIDsFromTwitchIDsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"TwitchIds\": [ \"127168541\", \"88315720\" ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateClientGetPlayFabIDsFromTwitchIDsResponse(PFAccountManagementGetPlayFabIDsFromTwitchIDsResult* result)
{
    // result.data = PFAccountManagementTwitchPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientGetPlayFabIDsFromXboxLiveIDs

void AutoGenAccountManagementTests::FillClientGetPlayFabIDsFromXboxLiveIDsRequest(PFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"XboxLiveAccountIDs\": [ \"857498576495\", \"759374651209\" ], \"Sandbox\": \"RETAIL\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateClientGetPlayFabIDsFromXboxLiveIDsResponse(PFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult* result)
{
    // result.data = PFAccountManagementXboxLiveAccountPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientLinkAndroidDeviceID

void AutoGenAccountManagementTests::FillClientLinkAndroidDeviceIDRequest(PFAccountManagementLinkAndroidDeviceIDRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"AndroidDeviceId\": \"526f79204261747479\", \"OS\": \"5.0\", \"AndroidDevice\": \"Nexus 6\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientLinkApple

void AutoGenAccountManagementTests::FillClientLinkAppleRequest(PFAccountManagementLinkAppleRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"IdentityToken\": \"eyJraWQi...\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientLinkCustomID

void AutoGenAccountManagementTests::FillClientLinkCustomIDRequest(PFAccountManagementLinkCustomIDRequestWrapper<>& request)
{
    // Example Request: "{ \"CustomId\": \"67AB-5397-CC54-EA31\"}"
    request.SetCustomId("TestCustomUniqueId");
    request.SetForceLink(true);
}

#pragma endregion

#pragma region ClientLinkFacebookAccount

void AutoGenAccountManagementTests::FillClientLinkFacebookAccountRequest(PFAccountManagementLinkFacebookAccountRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"AccessToken\": \"FaceAccessTokenID\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientLinkFacebookInstantGamesId

void AutoGenAccountManagementTests::FillClientLinkFacebookInstantGamesIdRequest(PFAccountManagementLinkFacebookInstantGamesIdRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"FacebookInstantGamesSignature\": \"abcdef\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientLinkGameCenterAccount

void AutoGenAccountManagementTests::FillClientLinkGameCenterAccountRequest(PFAccountManagementLinkGameCenterAccountRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"GameCenterId\": \"2998h2998f0b000d0993\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientLinkGoogleAccount

void AutoGenAccountManagementTests::FillClientLinkGoogleAccountRequest(PFAccountManagementLinkGoogleAccountRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"AccessToken\": \"ExampleSecret\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientLinkIOSDeviceID

void AutoGenAccountManagementTests::FillClientLinkIOSDeviceIDRequest(PFAccountManagementLinkIOSDeviceIDRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"DeviceId\": \"29848d9bh8900a0b003\", \"OS\": \"7.11\", \"DeviceModel\": \"Iphone 5s\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientLinkKongregate

void AutoGenAccountManagementTests::FillClientLinkKongregateRequest(PFAccountManagementLinkKongregateAccountRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"KongregateId\": \"457332\", \"AuthTicket\": \"{123-456-78931212}\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientLinkNintendoServiceAccount

void AutoGenAccountManagementTests::FillClientLinkNintendoServiceAccountRequest(PFAccountManagementLinkNintendoServiceAccountRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"IdentityToken\": \"eyJraWQi...\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientLinkNintendoSwitchDeviceId

void AutoGenAccountManagementTests::FillClientLinkNintendoSwitchDeviceIdRequest(PFAccountManagementLinkNintendoSwitchDeviceIdRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"NintendoSwitchDeviceId\": \"526f79204261747479\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientLinkOpenIdConnect

void AutoGenAccountManagementTests::FillClientLinkOpenIdConnectRequest(PFAccountManagementLinkOpenIdConnectRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"ConnectionId\": \"exampleprovider\", \"IdToken\": \"eyJraWQi...\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientLinkPSNAccount

void AutoGenAccountManagementTests::FillClientLinkPSNAccountRequest(PFAccountManagementClientLinkPSNAccountRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"AuthCode\": \"LKJDG7DDE\", \"RedirectUri\": \"orbis://games\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientLinkSteamAccount

void AutoGenAccountManagementTests::FillClientLinkSteamAccountRequest(PFAccountManagementLinkSteamAccountRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"SteamTicket\": \"steamTicketID\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientLinkTwitch

void AutoGenAccountManagementTests::FillClientLinkTwitchRequest(PFAccountManagementLinkTwitchAccountRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"AccessToken\": \"TwitchAccessToken\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientLinkXboxAccount

void AutoGenAccountManagementTests::FillClientLinkXboxAccountRequest(PFAccountManagementClientLinkXboxAccountRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"XboxToken\": \"XBL3.0 x=1981989841;akljdlkafdknad\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientRemoveContactEmail

void AutoGenAccountManagementTests::FillClientRemoveContactEmailRequest(PFAccountManagementRemoveContactEmailRequestWrapper<>& request)
{
    // Example Request: "{}"
    UNREFERENCED_PARAMETER(request);
}

#pragma endregion

#pragma region ClientRemoveGenericID

void AutoGenAccountManagementTests::FillClientRemoveGenericIDRequest(PFAccountManagementClientRemoveGenericIDRequestWrapper<>& request)
{
    // Example Request: "{ \"GenericId\": { \"ServiceName\": \"BigBizSocial\", \"UserId\": \"1234567890\" }}"
    PFAccountManagementGenericServiceIdWrapper<> id;
    id.SetServiceName("TestGenericServiceName");
    id.SetUserId("TestGenericUserId");

    request.SetGenericId(id);
}

#pragma endregion

#pragma region ClientReportPlayer

void AutoGenAccountManagementTests::FillClientReportPlayerRequest(PFAccountManagementReportPlayerClientRequestWrapper<>& request)
{
    // Example Request: "{ \"ReporteeId\": \"1a46086aed40f142\", \"Comment\": \"cheating\"}"
    request.SetReporteeId("86F2C0D9890AB609");
    request.SetComment("Testing reporting");
}

HRESULT AutoGenAccountManagementTests::ValidateClientReportPlayerResponse(PFAccountManagementReportPlayerClientResult* result)
{
    // result.submissionsRemaining = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientSendAccountRecoveryEmail

void AutoGenAccountManagementTests::FillClientSendAccountRecoveryEmailRequest(PFAccountManagementClientSendAccountRecoveryEmailRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"Email\": \"Me@here.com\", \"TitleId\": \"{{TitleId}}\", \"EmailTemplateId\": \"D53AB15D8F12E330\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientUnlinkAndroidDeviceID

void AutoGenAccountManagementTests::FillClientUnlinkAndroidDeviceIDRequest(PFAccountManagementUnlinkAndroidDeviceIDRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"AndroidDeviceId\": \"526f79204261747479\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientUnlinkApple

void AutoGenAccountManagementTests::FillClientUnlinkAppleRequest(PFAccountManagementUnlinkAppleRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientUnlinkCustomID

void AutoGenAccountManagementTests::FillClientUnlinkCustomIDRequest(PFAccountManagementUnlinkCustomIDRequestWrapper<>& request)
{
    // Example Request: "{ \"CustomId\": \"67AB-5397-CC54-EA31\"}"
    request.SetCustomId("TestCustomUniqueId");
}

#pragma endregion

#pragma region ClientUnlinkFacebookAccount

void AutoGenAccountManagementTests::FillClientUnlinkFacebookAccountRequest(PFAccountManagementUnlinkFacebookAccountRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientUnlinkFacebookInstantGamesId

void AutoGenAccountManagementTests::FillClientUnlinkFacebookInstantGamesIdRequest(PFAccountManagementUnlinkFacebookInstantGamesIdRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"FacebookInstantGamesId\": \"1114685845316173\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientUnlinkGameCenterAccount

void AutoGenAccountManagementTests::FillClientUnlinkGameCenterAccountRequest(PFAccountManagementUnlinkGameCenterAccountRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientUnlinkGoogleAccount

void AutoGenAccountManagementTests::FillClientUnlinkGoogleAccountRequest(PFAccountManagementUnlinkGoogleAccountRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientUnlinkIOSDeviceID

void AutoGenAccountManagementTests::FillClientUnlinkIOSDeviceIDRequest(PFAccountManagementUnlinkIOSDeviceIDRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"DeviceId\": \"29848d9bh8900a0b003\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientUnlinkKongregate

void AutoGenAccountManagementTests::FillClientUnlinkKongregateRequest(PFAccountManagementUnlinkKongregateAccountRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientUnlinkNintendoServiceAccount

void AutoGenAccountManagementTests::FillClientUnlinkNintendoServiceAccountRequest(PFAccountManagementUnlinkNintendoServiceAccountRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientUnlinkNintendoSwitchDeviceId

void AutoGenAccountManagementTests::FillClientUnlinkNintendoSwitchDeviceIdRequest(PFAccountManagementUnlinkNintendoSwitchDeviceIdRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"NintendoSwitchDeviceId\": \"526f79204261747479\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientUnlinkOpenIdConnect

void AutoGenAccountManagementTests::FillClientUnlinkOpenIdConnectRequest(PFAccountManagementUnlinkOpenIdConnectRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"ConnectionId\": \"exampleprovider\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientUnlinkPSNAccount

void AutoGenAccountManagementTests::FillClientUnlinkPSNAccountRequest(PFAccountManagementClientUnlinkPSNAccountRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientUnlinkSteamAccount

void AutoGenAccountManagementTests::FillClientUnlinkSteamAccountRequest(PFAccountManagementUnlinkSteamAccountRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientUnlinkTwitch

void AutoGenAccountManagementTests::FillClientUnlinkTwitchRequest(PFAccountManagementUnlinkTwitchAccountRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientUnlinkXboxAccount

void AutoGenAccountManagementTests::FillClientUnlinkXboxAccountRequest(PFAccountManagementClientUnlinkXboxAccountRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientUpdateAvatarUrl

void AutoGenAccountManagementTests::FillClientUpdateAvatarUrlRequest(PFAccountManagementClientUpdateAvatarUrlRequestWrapper<>& request)
{
    // Example Request: "{ \"ImageUrl\": \"https://www.gravatar.com/avatar/205e460b479e2e5b48aec07710c08d50\"}"
    request.SetImageUrl("https://www.gravatar.com/avatar/205e460b479e2e5b48aec07710c08d50");
}

#pragma endregion

#pragma region ClientUpdateUserTitleDisplayName

void AutoGenAccountManagementTests::FillClientUpdateUserTitleDisplayNameRequest(PFAccountManagementClientUpdateUserTitleDisplayNameRequestWrapper<>& request)
{
    // Example Request: "{ \"DisplayName\": \"User Title Name\"}"
    request.SetDisplayName("Permanent Group Owner");
}

HRESULT AutoGenAccountManagementTests::ValidateClientUpdateUserTitleDisplayNameResponse(PFAccountManagementUpdateUserTitleDisplayNameResult* result)
{
    // result.displayName = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerAddGenericID

void AutoGenAccountManagementTests::FillServerAddGenericIDRequest(PFAccountManagementServerAddGenericIDRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"GenericId\": { \"ServiceName\": \"BigBizSocial\", \"UserId\": \"1234567890\" }}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ServerBanUsers

void AutoGenAccountManagementTests::FillServerBanUsersRequest(PFAccountManagementBanUsersRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"Bans\": [ {  \"PlayFabId\": \"1679AF5CD04BD838\",  \"IPAddress\": \"192.168.1.1\",  \"Reason\": \"You cheated!\",  \"DurationInHours\": 7 }, {  \"PlayFabId\": \"2329AF5CD04BF513\",  \"Reason\": \"Caught you using speed hack!\" } ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateServerBanUsersResponse(PFAccountManagementBanUsersResult* result)
{
    // result.banData = PFAccountManagementBanInfo const* const*;
    // result.banDataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerDeletePlayer

void AutoGenAccountManagementTests::FillServerDeletePlayerRequest(PFAccountManagementDeletePlayerRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ServerGetPlayerCombinedInfo

void AutoGenAccountManagementTests::FillServerGetPlayerCombinedInfoRequest(PFAccountManagementGetPlayerCombinedInfoRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"InfoRequestParameters\": { \"GetUserAccountInfo\": true, \"GetUserInventory\": false, \"GetUserVirtualCurrency\": true, \"GetUserData\": true, \"UserDataKeys\": [  \"preferences\",  \"progress\" ], \"GetUserReadOnlyData\": false, \"GetCharacterInventories\": false, \"GetCharacterList\": false, \"GetTitleData\": false, \"GetPlayerStatistics\": false, \"GetPlayerProfile\": false }}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateServerGetPlayerCombinedInfoResponse(PFAccountManagementGetPlayerCombinedInfoResult* result)
{
    // result.infoResultPayload = PFGetPlayerCombinedInfoResultPayload const*;
    // result.playFabId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerGetPlayerProfile

void AutoGenAccountManagementTests::FillServerGetPlayerProfileRequest(PFAccountManagementGetPlayerProfileRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateServerGetPlayerProfileResponse(PFAccountManagementGetPlayerProfileResult* result)
{
    // result.playerProfile = PFPlayerProfileModel const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerGetPlayFabIDsFromFacebookIDs

void AutoGenAccountManagementTests::FillServerGetPlayFabIDsFromFacebookIDsRequest(PFAccountManagementGetPlayFabIDsFromFacebookIDsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"FacebookIDs\": [ \"857498576495\", \"759374651209\" ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateServerGetPlayFabIDsFromFacebookIDsResponse(PFAccountManagementGetPlayFabIDsFromFacebookIDsResult* result)
{
    // result.data = PFAccountManagementFacebookPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerGetPlayFabIDsFromFacebookInstantGamesIds

void AutoGenAccountManagementTests::FillServerGetPlayFabIDsFromFacebookInstantGamesIdsRequest(PFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"FacebookInstantGamesIds\": [ \"1114685845316172\", \"1114685845316173\" ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateServerGetPlayFabIDsFromFacebookInstantGamesIdsResponse(PFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult* result)
{
    // result.data = PFAccountManagementFacebookInstantGamesPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerGetPlayFabIDsFromGenericIDs

void AutoGenAccountManagementTests::FillServerGetPlayFabIDsFromGenericIDsRequest(PFAccountManagementGetPlayFabIDsFromGenericIDsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"GenericIDs\": [ {  \"ServiceName\": \"BigBizSocial\",  \"UserId\": \"1234567890\" }, {  \"ServiceName\": \"VeeCeeMe\",  \"UserId\": \"og5igh85gf43gf\" } ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateServerGetPlayFabIDsFromGenericIDsResponse(PFAccountManagementGetPlayFabIDsFromGenericIDsResult* result)
{
    // result.data = PFAccountManagementGenericPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerGetPlayFabIDsFromNintendoSwitchDeviceIds

void AutoGenAccountManagementTests::FillServerGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest(PFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"NintendoSwitchDeviceIds\": [ \"526f79204261747478\", \"526f79204261747479\" ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateServerGetPlayFabIDsFromNintendoSwitchDeviceIdsResponse(PFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult* result)
{
    // result.data = PFAccountManagementNintendoSwitchPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerGetPlayFabIDsFromPSNAccountIDs

void AutoGenAccountManagementTests::FillServerGetPlayFabIDsFromPSNAccountIDsRequest(PFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PSNAccountIDs\": [ \"857498576495\", \"759374651209\" ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateServerGetPlayFabIDsFromPSNAccountIDsResponse(PFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult* result)
{
    // result.data = PFAccountManagementPSNAccountPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerGetPlayFabIDsFromSteamIDs

void AutoGenAccountManagementTests::FillServerGetPlayFabIDsFromSteamIDsRequest(PFAccountManagementGetPlayFabIDsFromSteamIDsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"SteamStringIDs\": [ \"857498576495\", \"759374651209\" ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateServerGetPlayFabIDsFromSteamIDsResponse(PFAccountManagementGetPlayFabIDsFromSteamIDsResult* result)
{
    // result.data = PFAccountManagementSteamPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerGetPlayFabIDsFromXboxLiveIDs

void AutoGenAccountManagementTests::FillServerGetPlayFabIDsFromXboxLiveIDsRequest(PFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"XboxLiveAccountIDs\": [ \"857498576495\", \"759374651209\" ], \"Sandbox\": \"RETAIL\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateServerGetPlayFabIDsFromXboxLiveIDsResponse(PFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult* result)
{
    // result.data = PFAccountManagementXboxLiveAccountPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerGetServerCustomIDsFromPlayFabIDs

void AutoGenAccountManagementTests::FillServerGetServerCustomIDsFromPlayFabIDsRequest(PFAccountManagementGetServerCustomIDsFromPlayFabIDsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabIDs\": [ \"1232421311\" ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateServerGetServerCustomIDsFromPlayFabIDsResponse(PFAccountManagementGetServerCustomIDsFromPlayFabIDsResult* result)
{
    // result.data = PFAccountManagementServerCustomIDPlayFabIDPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerGetUserAccountInfo

void AutoGenAccountManagementTests::FillServerGetUserAccountInfoRequest(PFAccountManagementGetUserAccountInfoRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateServerGetUserAccountInfoResponse(PFAccountManagementGetUserAccountInfoResult* result)
{
    // result.userInfo = PFUserAccountInfo const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerGetUserBans

void AutoGenAccountManagementTests::FillServerGetUserBansRequest(PFAccountManagementGetUserBansRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateServerGetUserBansResponse(PFAccountManagementGetUserBansResult* result)
{
    // result.banData = PFAccountManagementBanInfo const* const*;
    // result.banDataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerLinkPSNAccount

void AutoGenAccountManagementTests::FillServerLinkPSNAccountRequest(PFAccountManagementServerLinkPSNAccountRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"AuthCode\": \"LKJDG7DDE\", \"RedirectUri\": \"orbis://games\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ServerLinkServerCustomId

void AutoGenAccountManagementTests::FillServerLinkServerCustomIdRequest(PFAccountManagementLinkServerCustomIdRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"ServerCustomId\": \"67AB-5397-CC54-EA31\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ServerLinkXboxAccount

void AutoGenAccountManagementTests::FillServerLinkXboxAccountRequest(PFAccountManagementServerLinkXboxAccountRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"XboxToken\": \"XBL3.0 x=1981989841;akljdlkafdknad\", \"PlayFabId\": \"{{PlayFabId}}\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ServerRemoveGenericID

void AutoGenAccountManagementTests::FillServerRemoveGenericIDRequest(PFAccountManagementServerRemoveGenericIDRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"GenericId\": { \"ServiceName\": \"BigBizSocial\", \"UserId\": \"1234567890\" }}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ServerRevokeAllBansForUser

void AutoGenAccountManagementTests::FillServerRevokeAllBansForUserRequest(PFAccountManagementRevokeAllBansForUserRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateServerRevokeAllBansForUserResponse(PFAccountManagementRevokeAllBansForUserResult* result)
{
    // result.banData = PFAccountManagementBanInfo const* const*;
    // result.banDataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerRevokeBans

void AutoGenAccountManagementTests::FillServerRevokeBansRequest(PFAccountManagementRevokeBansRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"BanIds\": [ \"E0B5FF89542D413C\", \"EF43FF89542G1546\" ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateServerRevokeBansResponse(PFAccountManagementRevokeBansResult* result)
{
    // result.banData = PFAccountManagementBanInfo const* const*;
    // result.banDataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerSendCustomAccountRecoveryEmail

void AutoGenAccountManagementTests::FillServerSendCustomAccountRecoveryEmailRequest(PFAccountManagementSendCustomAccountRecoveryEmailRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"EmailTemplateId\": \"D53AB15D8F12E330\", \"Email\": \"Me@here.com\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ServerSendEmailFromTemplate

void AutoGenAccountManagementTests::FillServerSendEmailFromTemplateRequest(PFAccountManagementSendEmailFromTemplateRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"EmailTemplateId\": \"B53CA15D92D2E331\", \"PlayFabId\": \"{{PlayFabId}}\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ServerUnlinkPSNAccount

void AutoGenAccountManagementTests::FillServerUnlinkPSNAccountRequest(PFAccountManagementServerUnlinkPSNAccountRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ServerUnlinkServerCustomId

void AutoGenAccountManagementTests::FillServerUnlinkServerCustomIdRequest(PFAccountManagementUnlinkServerCustomIdRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"ServerCustomId\": \"67AB-5397-CC54-EA31\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ServerUnlinkXboxAccount

void AutoGenAccountManagementTests::FillServerUnlinkXboxAccountRequest(PFAccountManagementServerUnlinkXboxAccountRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ServerUpdateAvatarUrl

void AutoGenAccountManagementTests::FillServerUpdateAvatarUrlRequest(PFAccountManagementServerUpdateAvatarUrlRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"ImageUrl\": \"https://www.gravatar.com/avatar/205e460b479e2e5b48aec07710c08d50\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ServerUpdateBans

void AutoGenAccountManagementTests::FillServerUpdateBansRequest(PFAccountManagementUpdateBansRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"Bans\": [ {  \"BanId\": \"E0B5FF89542D413C\",  \"Permanent\": true,  \"Active\": true }, {  \"BanId\": \"EF43FF89542G1546\",  \"Reason\": \"Royal pardon\",  \"Expires\": \"2016-07-04T00:00:00Z\" } ]}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenAccountManagementTests::ValidateServerUpdateBansResponse(PFAccountManagementUpdateBansResult* result)
{
    // result.banData = PFAccountManagementBanInfo const* const*;
    // result.banDataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion
 

}
