#include "TestAppPch.h"
#include "TestContext.h"
#include "TestApp.h"
#include "AutoGenServerTests.h"
#include "XAsyncHelper.h"
#include <playfab/PlayFabClientAuthApi.h>
#include <playfab/PlayFabClientApi.h>
#include <playfab/PlayFabProfilesApi.h>
#include <playfab/PlayFabAdminApi.h>
#include <playfab/PlayFabAuthenticationAuthApi.h>
#include <playfab/PlayFabClientDataModels.h>

namespace PlayFabUnit
{

void AutoGenServerTests::FillPlayFabServerAddCharacterVirtualCurrencyRequest( PlayFab::ServerModels::AddCharacterVirtualCurrencyRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"CharacterId\": \"{{CharacterId}}\", \"VirtualCurrency\": \"GC\", \"Amount\": 100}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerModifyCharacterVirtualCurrencyResult( PlayFabServerModifyCharacterVirtualCurrencyResult* result )
{
    // result.balance = int32_t;
    // result.virtualCurrency = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerAddFriendRequest( PlayFab::ServerModels::AddFriendRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"FriendPlayFabId\": \"20394883\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerAddGenericIDRequest( PlayFab::ServerModels::AddGenericIDRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"GenericId\": { \"ServiceName\": \"BigBizSocial\", \"UserId\": \"1234567890\" }}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerAddPlayerTagRequest( PlayFab::ServerModels::AddPlayerTagRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"TagName\": \"MostKilled\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerAddSharedGroupMembersRequest( PlayFab::ServerModels::AddSharedGroupMembersRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SharedGroupId\": \"Clan Data\", \"PlayFabIds\": [ \"D984A64B832\", \"F74A523E1562\" ]}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerAddUserVirtualCurrencyRequest( PlayFab::ServerModels::AddUserVirtualCurrencyRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"VirtualCurrency\": \"GC\", \"Amount\": 100}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerModifyUserVirtualCurrencyResult( PlayFabServerModifyUserVirtualCurrencyResult* result )
{
    // result.balance = int32_t;
    // result.balanceChange = int32_t;
    // result.playFabId = const char*;
    // result.virtualCurrency = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerAuthenticateSessionTicketRequest( PlayFab::ServerModels::AuthenticateSessionTicketRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SessionTicket\": \"4D2----8D11F4249A80000-7C64AB0A9F1D8D1A.CD803BF233CE76CC\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerAuthenticateSessionTicketResult( PlayFabServerAuthenticateSessionTicketResult* result )
{
    // result.isSessionTicketExpired = bool const*;
    // result.userInfo = PlayFabUserAccountInfo const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerAwardSteamAchievementRequest( PlayFab::ServerModels::AwardSteamAchievementRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Achievements\": [ {  \"PlayFabId\": \"234974573892\",  \"AchievementName\": \"FinishLevel1\",  \"Result\": false }, {  \"PlayFabId\": \"334353433\",  \"AchievementName\": \"FinishLevel1\",  \"Result\": false } ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerAwardSteamAchievementResult( PlayFabServerAwardSteamAchievementResult* result )
{
    // result.achievementResults = PlayFabServerAwardSteamAchievementItem const* const*;
    // result.achievementResultsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerBanUsersRequest( PlayFab::ServerModels::BanUsersRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Bans\": [ {  \"PlayFabId\": \"1679AF5CD04BD838\",  \"IPAddress\": \"192.168.1.1\",  \"Reason\": \"You cheated!\",  \"DurationInHours\": 7 }, {  \"PlayFabId\": \"2329AF5CD04BF513\",  \"Reason\": \"Caught you using speed hack!\" } ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerBanUsersResult( PlayFabServerBanUsersResult* result )
{
    // result.banData = PlayFabServerBanInfo const* const*;
    // result.banDataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerConsumeItemRequest( PlayFab::ServerModels::ConsumeItemRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ItemInstanceId\": \"94585729\", \"ConsumeCount\": 1}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerConsumeItemResult( PlayFabServerConsumeItemResult* result )
{
    // result.itemInstanceId = const char*;
    // result.remainingUses = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerCreateSharedGroupRequest( PlayFab::ServerModels::CreateSharedGroupRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SharedGroupId\": \"Clan Data\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerCreateSharedGroupResult( PlayFabServerCreateSharedGroupResult* result )
{
    // result.sharedGroupId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerDeleteCharacterFromUserRequest( PlayFab::ServerModels::DeleteCharacterFromUserRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"CharacterId\": \"{{CharacterId}}\", \"SaveCharacterInventory\": false}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerDeletePlayerRequest( PlayFab::ServerModels::DeletePlayerRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerDeletePushNotificationTemplateRequest( PlayFab::ServerModels::DeletePushNotificationTemplateRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PushNotificationTemplateId\": \"6bc7dbf0-075a-46e9-8e84-35737a22c6a4\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerDeleteSharedGroupRequest( PlayFab::ServerModels::DeleteSharedGroupRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SharedGroupId\": \"Clan Data\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerDeregisterGameRequest( PlayFab::ServerModels::DeregisterGameRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"LobbyId\": \"8285313\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerEvaluateRandomResultTableRequest( PlayFab::ServerModels::EvaluateRandomResultTableRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"TableId\": \"RareElementCard\", \"CatalogVersion\": \"{{PrimaryCatalogName}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerEvaluateRandomResultTableResult( PlayFabServerEvaluateRandomResultTableResult* result )
{
    // result.resultItemId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerExecuteCloudScriptServerRequest( PlayFab::ServerModels::ExecuteCloudScriptServerRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"FunctionName\": \"levelCompleted\", \"FunctionParameter\": { \"level\": 3, \"points\": 400 }, \"RevisionSelection\": \"Live\", \"GeneratePlayStreamEvent\": true}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerExecuteCloudScriptResult( PlayFabServerExecuteCloudScriptResult* result )
{
    // result.aPIRequestsIssued = int32_t;
    // result.error = PlayFabServerScriptExecutionError const*;
    // result.executionTimeSeconds = double;
    // result.functionName = const char*;
    // result.functionResult = PlayFabJsonObject;
    // result.functionResultTooLarge = bool const*;
    // result.httpRequestsIssued = int32_t;
    // result.logs = PlayFabServerLogStatement const* const*;
    // result.logsCount = uint32_t;
    // result.logsTooLarge = bool const*;
    // result.memoryConsumedBytes = uint32_t;
    // result.processorTimeSeconds = double;
    // result.revision = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetAllSegmentsResult( PlayFabServerGetAllSegmentsResult* result )
{
    // result.segments = PlayFabServerGetSegmentResult const* const*;
    // result.segmentsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerListUsersCharactersRequest( PlayFab::ServerModels::ListUsersCharactersRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerListUsersCharactersResult( PlayFabServerListUsersCharactersResult* result )
{
    // result.characters = PlayFabCharacterResult const* const*;
    // result.charactersCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetCatalogItemsRequest( PlayFab::ServerModels::GetCatalogItemsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"CatalogVersion\": \"{{PrimaryCatalogName}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetCatalogItemsResult( PlayFabServerGetCatalogItemsResult* result )
{
    // result.catalog = PlayFabServerCatalogItem const* const*;
    // result.catalogCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetCharacterDataRequest( PlayFab::ServerModels::GetCharacterDataRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"CharacterId\": \"{{CharacterId}}\", \"Keys\": [ \"preferences\", \"progress\" ], \"IfChangedFromDataVersion\": 1}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetCharacterDataResult( PlayFabServerGetCharacterDataResult* result )
{
    // result.characterId = const char*;
    // result.data = struct PlayFabUserDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.dataVersion = uint32_t;
    // result.playFabId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetCharacterInventoryRequest( PlayFab::ServerModels::GetCharacterInventoryRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"CharacterId\": \"{{CharacterId}}\", \"CatalogVersion\": \"{{PrimaryCatalogName}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetCharacterInventoryResult( PlayFabServerGetCharacterInventoryResult* result )
{
    // result.characterId = const char*;
    // result.inventory = PlayFabItemInstance const* const*;
    // result.inventoryCount = uint32_t;
    // result.playFabId = const char*;
    // result.virtualCurrency = struct PlayFabInt32DictionaryEntry const*;
    // result.virtualCurrencyCount = uint32_t;
    // result.virtualCurrencyRechargeTimes = struct PlayFabVirtualCurrencyRechargeTimeDictionaryEntry const*;
    // result.virtualCurrencyRechargeTimesCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetCharacterLeaderboardRequest( PlayFab::ServerModels::GetCharacterLeaderboardRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StatisticName\": \"Kills\", \"StartPosition\": 0, \"MaxResultsCount\": 20}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetCharacterLeaderboardResult( PlayFabServerGetCharacterLeaderboardResult* result )
{
    // result.leaderboard = PlayFabServerCharacterLeaderboardEntry const* const*;
    // result.leaderboardCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetCharacterStatisticsRequest( PlayFab::ServerModels::GetCharacterStatisticsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"CharacterId\": \"{{CharacterId}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetCharacterStatisticsResult( PlayFabServerGetCharacterStatisticsResult* result )
{
    // result.characterId = const char*;
    // result.characterStatistics = struct PlayFabInt32DictionaryEntry const*;
    // result.characterStatisticsCount = uint32_t;
    // result.playFabId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetContentDownloadUrlRequest( PlayFab::ServerModels::GetContentDownloadUrlRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Key\": \"images/sword_icon.png\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetContentDownloadUrlResult( PlayFabServerGetContentDownloadUrlResult* result )
{
    // result.uRL = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetFriendLeaderboardRequest( PlayFab::ServerModels::GetFriendLeaderboardRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"StatisticName\": \"Kills\", \"StartPosition\": 1258, \"MaxResultsCount\": 20, \"IncludeSteamFriends\": false}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetLeaderboardResult( PlayFabServerGetLeaderboardResult* result )
{
    // result.leaderboard = PlayFabServerPlayerLeaderboardEntry const* const*;
    // result.leaderboardCount = uint32_t;
    // result.nextReset = time_t const*;
    // result.version = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetFriendsListRequest( PlayFab::ServerModels::GetFriendsListRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"IncludeSteamFriends\": true}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetFriendsListResult( PlayFabServerGetFriendsListResult* result )
{
    // result.friends = PlayFabServerFriendInfo const* const*;
    // result.friendsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetLeaderboardRequest( PlayFab::ServerModels::GetLeaderboardRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StatisticName\": \"Kills\", \"StartPosition\": 0, \"MaxResultsCount\": 20}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerGetLeaderboardAroundCharacterRequest( PlayFab::ServerModels::GetLeaderboardAroundCharacterRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StatisticName\": \"Kills\", \"PlayFabId\": \"{{PlayFabId}}\", \"CharacterId\": \"{{CharacterId}}\", \"MaxResultsCount\": 20}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetLeaderboardAroundCharacterResult( PlayFabServerGetLeaderboardAroundCharacterResult* result )
{
    // result.leaderboard = PlayFabServerCharacterLeaderboardEntry const* const*;
    // result.leaderboardCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetLeaderboardAroundUserRequest( PlayFab::ServerModels::GetLeaderboardAroundUserRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StatisticName\": \"Kills\", \"PlayFabId\": \"{{PlayFabId}}\", \"MaxResultsCount\": 20}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetLeaderboardAroundUserResult( PlayFabServerGetLeaderboardAroundUserResult* result )
{
    // result.leaderboard = PlayFabServerPlayerLeaderboardEntry const* const*;
    // result.leaderboardCount = uint32_t;
    // result.nextReset = time_t const*;
    // result.version = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetLeaderboardForUsersCharactersRequest( PlayFab::ServerModels::GetLeaderboardForUsersCharactersRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StatisticName\": \"Kills\", \"PlayFabId\": \"{{PlayFabId}}\", \"MaxResultsCount\": 20}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetLeaderboardForUsersCharactersResult( PlayFabServerGetLeaderboardForUsersCharactersResult* result )
{
    // result.leaderboard = PlayFabServerCharacterLeaderboardEntry const* const*;
    // result.leaderboardCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetPlayerCombinedInfoRequest( PlayFab::ServerModels::GetPlayerCombinedInfoRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"InfoRequestParameters\": { \"GetUserAccountInfo\": true, \"GetUserInventory\": false, \"GetUserVirtualCurrency\": true, \"GetUserData\": true, \"UserDataKeys\": [  \"preferences\",  \"progress\" ], \"GetUserReadOnlyData\": false, \"GetCharacterInventories\": false, \"GetCharacterList\": false, \"GetTitleData\": false, \"GetPlayerStatistics\": false, \"GetPlayerProfile\": false }}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetPlayerCombinedInfoResult( PlayFabServerGetPlayerCombinedInfoResult* result )
{
    // result.infoResultPayload = PlayFabGetPlayerCombinedInfoResultPayload const*;
    // result.playFabId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetPlayerProfileRequest( PlayFab::ServerModels::GetPlayerProfileRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetPlayerProfileResult( PlayFabServerGetPlayerProfileResult* result )
{
    // result.playerProfile = PlayFabPlayerProfileModel const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetPlayersSegmentsRequest( PlayFab::ServerModels::GetPlayersSegmentsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetPlayerSegmentsResult( PlayFabServerGetPlayerSegmentsResult* result )
{
    // result.segments = PlayFabServerGetSegmentResult const* const*;
    // result.segmentsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetPlayersInSegmentRequest( PlayFab::ServerModels::GetPlayersInSegmentRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SegmentId\": \"1337AA00\", \"SecondsToLive\": 5, \"MaxBatchSize\": 500}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetPlayersInSegmentResult( PlayFabServerGetPlayersInSegmentResult* result )
{
    // result.continuationToken = const char*;
    // result.playerProfiles = PlayFabServerPlayerProfile const* const*;
    // result.playerProfilesCount = uint32_t;
    // result.profilesInSegment = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetPlayerStatisticsRequest( PlayFab::ServerModels::GetPlayerStatisticsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"StatisticNames\": [ \"Points\", \"Wins\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetPlayerStatisticsResult( PlayFabServerGetPlayerStatisticsResult* result )
{
    // result.playFabId = const char*;
    // result.statistics = PlayFabStatisticValue const* const*;
    // result.statisticsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetPlayerStatisticVersionsRequest( PlayFab::ServerModels::GetPlayerStatisticVersionsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StatisticName\": \"headshots\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetPlayerStatisticVersionsResult( PlayFabServerGetPlayerStatisticVersionsResult* result )
{
    // result.statisticVersions = PlayFabServerPlayerStatisticVersion const* const*;
    // result.statisticVersionsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetPlayerTagsRequest( PlayFab::ServerModels::GetPlayerTagsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Namespace\": \"title.AAA\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetPlayerTagsResult( PlayFabServerGetPlayerTagsResult* result )
{
    // result.playFabId = const char*;
    // result.tags = const char* const*;
    // result.tagsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetPlayFabIDsFromFacebookIDsRequest( PlayFab::ServerModels::GetPlayFabIDsFromFacebookIDsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"FacebookIDs\": [ \"857498576495\", \"759374651209\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetPlayFabIDsFromFacebookIDsResult( PlayFabServerGetPlayFabIDsFromFacebookIDsResult* result )
{
    // result.data = PlayFabServerFacebookPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetPlayFabIDsFromFacebookInstantGamesIdsRequest( PlayFab::ServerModels::GetPlayFabIDsFromFacebookInstantGamesIdsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"FacebookInstantGamesIds\": [ \"1114685845316172\", \"1114685845316173\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetPlayFabIDsFromFacebookInstantGamesIdsResult( PlayFabServerGetPlayFabIDsFromFacebookInstantGamesIdsResult* result )
{
    // result.data = PlayFabServerFacebookInstantGamesPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetPlayFabIDsFromGenericIDsRequest( PlayFab::ServerModels::GetPlayFabIDsFromGenericIDsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"GenericIDs\": [ {  \"ServiceName\": \"BigBizSocial\",  \"UserId\": \"1234567890\" }, {  \"ServiceName\": \"VeeCeeMe\",  \"UserId\": \"og5igh85gf43gf\" } ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetPlayFabIDsFromGenericIDsResult( PlayFabServerGetPlayFabIDsFromGenericIDsResult* result )
{
    // result.data = PlayFabServerGenericPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest( PlayFab::ServerModels::GetPlayFabIDsFromNintendoSwitchDeviceIdsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"NintendoSwitchDeviceIds\": [ \"526f79204261747478\", \"526f79204261747479\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetPlayFabIDsFromNintendoSwitchDeviceIdsResult( PlayFabServerGetPlayFabIDsFromNintendoSwitchDeviceIdsResult* result )
{
    // result.data = PlayFabServerNintendoSwitchPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetPlayFabIDsFromPSNAccountIDsRequest( PlayFab::ServerModels::GetPlayFabIDsFromPSNAccountIDsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PSNAccountIDs\": [ \"857498576495\", \"759374651209\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetPlayFabIDsFromPSNAccountIDsResult( PlayFabServerGetPlayFabIDsFromPSNAccountIDsResult* result )
{
    // result.data = PlayFabServerPSNAccountPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetPlayFabIDsFromSteamIDsRequest( PlayFab::ServerModels::GetPlayFabIDsFromSteamIDsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SteamStringIDs\": [ \"857498576495\", \"759374651209\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetPlayFabIDsFromSteamIDsResult( PlayFabServerGetPlayFabIDsFromSteamIDsResult* result )
{
    // result.data = PlayFabServerSteamPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetPlayFabIDsFromXboxLiveIDsRequest( PlayFab::ServerModels::GetPlayFabIDsFromXboxLiveIDsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"XboxLiveAccountIDs\": [ \"857498576495\", \"759374651209\" ], \"Sandbox\": \"RETAIL\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetPlayFabIDsFromXboxLiveIDsResult( PlayFabServerGetPlayFabIDsFromXboxLiveIDsResult* result )
{
    // result.data = PlayFabServerXboxLiveAccountPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetPublisherDataRequest( PlayFab::ServerModels::GetPublisherDataRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Keys\": [ \"color\", \"propertyA\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetPublisherDataResult( PlayFabServerGetPublisherDataResult* result )
{
    // result.data = struct PlayFabStringDictionaryEntry const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetRandomResultTablesRequest( PlayFab::ServerModels::GetRandomResultTablesRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"CatalogVersion\": \"{{PrimaryCatalogName}}\", \"TableIDs\": [ \"CommonElementCard\", \"UncommonElementCard\", \"RareElementCard\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetRandomResultTablesResult( PlayFabServerGetRandomResultTablesResult* result )
{
    // result.tables = struct PlayFabServerRandomResultTableListingDictionaryEntry const*;
    // result.tablesCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetServerCustomIDsFromPlayFabIDsRequest( PlayFab::ServerModels::GetServerCustomIDsFromPlayFabIDsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabIDs\": [ \"1232421311\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetServerCustomIDsFromPlayFabIDsResult( PlayFabServerGetServerCustomIDsFromPlayFabIDsResult* result )
{
    // result.data = PlayFabServerServerCustomIDPlayFabIDPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetSharedGroupDataRequest( PlayFab::ServerModels::GetSharedGroupDataRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SharedGroupId\": \"Clan Data\", \"Keys\": [ \"ClanKills\", \"LastClanUpdate\" ], \"GetMembers\": true}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetSharedGroupDataResult( PlayFabServerGetSharedGroupDataResult* result )
{
    // result.data = struct PlayFabServerSharedGroupDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.members = const char* const*;
    // result.membersCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetStoreItemsServerRequest( PlayFab::ServerModels::GetStoreItemsServerRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StoreId\": \"BonusStore\", \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetStoreItemsResult( PlayFabServerGetStoreItemsResult* result )
{
    // result.catalogVersion = const char*;
    // result.marketingData = PlayFabServerStoreMarketingModel const*;
    // result.source = PlayFabServerSourceType const*;
    // result.store = PlayFabServerStoreItem const* const*;
    // result.storeCount = uint32_t;
    // result.storeId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetTimeResult( PlayFabServerGetTimeResult* result )
{
    // result.time = time_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetTitleDataRequest( PlayFab::ServerModels::GetTitleDataRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Keys\": [ \"color\", \"propertyA\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetTitleDataResult( PlayFabServerGetTitleDataResult* result )
{
    // result.data = struct PlayFabStringDictionaryEntry const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetTitleNewsRequest( PlayFab::ServerModels::GetTitleNewsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Count\": 25}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetTitleNewsResult( PlayFabServerGetTitleNewsResult* result )
{
    // result.news = PlayFabServerTitleNewsItem const* const*;
    // result.newsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetUserAccountInfoRequest( PlayFab::ServerModels::GetUserAccountInfoRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetUserAccountInfoResult( PlayFabServerGetUserAccountInfoResult* result )
{
    // result.userInfo = PlayFabUserAccountInfo const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetUserBansRequest( PlayFab::ServerModels::GetUserBansRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetUserBansResult( PlayFabServerGetUserBansResult* result )
{
    // result.banData = PlayFabServerBanInfo const* const*;
    // result.banDataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetUserDataRequest( PlayFab::ServerModels::GetUserDataRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Keys\": [ \"preferences\", \"progress\" ], \"IfChangedFromDataVersion\": 13}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetUserDataResult( PlayFabServerGetUserDataResult* result )
{
    // result.data = struct PlayFabUserDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.dataVersion = uint32_t;
    // result.playFabId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGetUserInventoryRequest( PlayFab::ServerModels::GetUserInventoryRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGetUserInventoryResult( PlayFabServerGetUserInventoryResult* result )
{
    // result.inventory = PlayFabItemInstance const* const*;
    // result.inventoryCount = uint32_t;
    // result.playFabId = const char*;
    // result.virtualCurrency = struct PlayFabInt32DictionaryEntry const*;
    // result.virtualCurrencyCount = uint32_t;
    // result.virtualCurrencyRechargeTimes = struct PlayFabVirtualCurrencyRechargeTimeDictionaryEntry const*;
    // result.virtualCurrencyRechargeTimesCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGrantCharacterToUserRequest( PlayFab::ServerModels::GrantCharacterToUserRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"CharacterName\": \"FighterDude\", \"CharacterType\": \"Blue Warrior\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGrantCharacterToUserResult( PlayFabServerGrantCharacterToUserResult* result )
{
    // result.characterId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGrantItemsToCharacterRequest( PlayFab::ServerModels::GrantItemsToCharacterRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"CharacterId\": \"{{CharacterId}}\", \"PlayFabId\": \"{{PlayFabId}}\", \"Annotation\": \"Entered Level 2\", \"ItemIds\": [ \"shield_level_5\", \"shield_level_6\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGrantItemsToCharacterResult( PlayFabServerGrantItemsToCharacterResult* result )
{
    // result.itemGrantResults = PlayFabServerGrantedItemInstance const* const*;
    // result.itemGrantResultsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGrantItemsToUserRequest( PlayFab::ServerModels::GrantItemsToUserRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Annotation\": \"Entered Level 2\", \"ItemIds\": [ \"shield_level_3\", \"shield_level_4\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGrantItemsToUserResult( PlayFabServerGrantItemsToUserResult* result )
{
    // result.itemGrantResults = PlayFabServerGrantedItemInstance const* const*;
    // result.itemGrantResultsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerGrantItemsToUsersRequest( PlayFab::ServerModels::GrantItemsToUsersRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"CatalogVersion\": \"{{PrimaryCatalogName}}\", \"ItemGrants\": [ {  \"PlayFabId\": \"20394883\",  \"ItemId\": \"shield_level_1\",  \"Annotation\": \"Entered Level 2\" }, {  \"PlayFabId\": \"20394883\",  \"ItemId\": \"shield_level_2\",  \"Annotation\": \"Entered Level 2\",  \"Data\": {  \"Equipped\": \"True\",  \"Slot\": \"Head\"  } } ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerGrantItemsToUsersResult( PlayFabServerGrantItemsToUsersResult* result )
{
    // result.itemGrantResults = PlayFabServerGrantedItemInstance const* const*;
    // result.itemGrantResultsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerLinkPSNAccountRequest( PlayFab::ServerModels::LinkPSNAccountRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"AuthCode\": \"LKJDG7DDE\", \"RedirectUri\": \"orbis://games\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerLinkServerCustomIdRequest( PlayFab::ServerModels::LinkServerCustomIdRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"ServerCustomId\": \"67AB-5397-CC54-EA31\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerLinkXboxAccountRequest( PlayFab::ServerModels::LinkXboxAccountRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"XboxToken\": \"XBL3.0 x=1981989841;akljdlkafdknad\", \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerModifyItemUsesRequest( PlayFab::ServerModels::ModifyItemUsesRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"ItemInstanceId\": \"94585729\", \"UsesToAdd\": 1}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerModifyItemUsesResult( PlayFabServerModifyItemUsesResult* result )
{
    // result.itemInstanceId = const char*;
    // result.remainingUses = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerMoveItemToCharacterFromCharacterRequest( PlayFab::ServerModels::MoveItemToCharacterFromCharacterRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"GivingCharacterId\": \"98092347523\", \"ReceivingCharacterId\": \"6323489712\", \"ItemInstanceId\": \"701231299999\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerMoveItemToCharacterFromUserRequest( PlayFab::ServerModels::MoveItemToCharacterFromUserRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"CharacterId\": \"{{CharacterId}}\", \"ItemInstanceId\": \"701231299999\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerMoveItemToUserFromCharacterRequest( PlayFab::ServerModels::MoveItemToUserFromCharacterRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"CharacterId\": \"{{CharacterId}}\", \"ItemInstanceId\": \"701231299999\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerNotifyMatchmakerPlayerLeftRequest( PlayFab::ServerModels::NotifyMatchmakerPlayerLeftRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"LobbyId\": \"29439584\", \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerNotifyMatchmakerPlayerLeftResult( PlayFabServerNotifyMatchmakerPlayerLeftResult* result )
{
    // result.playerState = PlayFabServerPlayerConnectionState const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerRedeemCouponRequest( PlayFab::ServerModels::RedeemCouponRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"CouponCode\": \"123-1234-123\", \"CatalogVersion\": \"{{PrimaryCatalogName}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerRedeemCouponResult( PlayFabServerRedeemCouponResult* result )
{
    // result.grantedItems = PlayFabItemInstance const* const*;
    // result.grantedItemsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerRedeemMatchmakerTicketRequest( PlayFab::ServerModels::RedeemMatchmakerTicketRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Ticket\": \"2398349939a03499bc\", \"LobbyId\": \"2353\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerRedeemMatchmakerTicketResult( PlayFabServerRedeemMatchmakerTicketResult* result )
{
    // result.error = const char*;
    // result.ticketIsValid = bool;
    // result.userInfo = PlayFabUserAccountInfo const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerRefreshGameServerInstanceHeartbeatRequest( PlayFab::ServerModels::RefreshGameServerInstanceHeartbeatRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"LobbyId\": \"29439584\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerRegisterGameRequest( PlayFab::ServerModels::RegisterGameRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ServerHost\": \"118.129.31.244\", \"ServerPort\": \"9984\", \"Build\": \"11_034234.13\", \"Region\": \"USEast\", \"GameMode\": \"FreeForAll\", \"Tags\": { \"level_cap\": \"high\", \"no_smoking\": \"1\" }}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerRegisterGameResponse( PlayFabServerRegisterGameResponse* result )
{
    // result.lobbyId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerRemoveFriendRequest( PlayFab::ServerModels::RemoveFriendRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"FriendPlayFabId\": \"29837799\", \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerRemoveGenericIDRequest( PlayFab::ServerModels::RemoveGenericIDRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"GenericId\": { \"ServiceName\": \"BigBizSocial\", \"UserId\": \"1234567890\" }}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerRemovePlayerTagRequest( PlayFab::ServerModels::RemovePlayerTagRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"TagName\": \"MostKilled\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerRemoveSharedGroupMembersRequest( PlayFab::ServerModels::RemoveSharedGroupMembersRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SharedGroupId\": \"Clan Data\", \"PlayFabIds\": [ \"D984A64B832\", \"F74A523E1562\" ]}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerReportPlayerServerRequest( PlayFab::ServerModels::ReportPlayerServerRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ReporterId\": \"9ddafe27d6d445da\", \"ReporteeId\": \"1a46086aed40f142\", \"Comment\": \"cheating\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerReportPlayerServerResult( PlayFabServerReportPlayerServerResult* result )
{
    // result.submissionsRemaining = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerRevokeAllBansForUserRequest( PlayFab::ServerModels::RevokeAllBansForUserRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerRevokeAllBansForUserResult( PlayFabServerRevokeAllBansForUserResult* result )
{
    // result.banData = PlayFabServerBanInfo const* const*;
    // result.banDataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerRevokeBansRequest( PlayFab::ServerModels::RevokeBansRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BanIds\": [ \"E0B5FF89542D413C\", \"EF43FF89542G1546\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerRevokeBansResult( PlayFabServerRevokeBansResult* result )
{
    // result.banData = PlayFabServerBanInfo const* const*;
    // result.banDataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerRevokeInventoryItemRequest( PlayFab::ServerModels::RevokeInventoryItemRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"ItemInstanceId\": \"2048583045\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerRevokeInventoryItemsRequest( PlayFab::ServerModels::RevokeInventoryItemsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Items\": [ {  \"PlayFabId\": \"203945882\",  \"ItemInstanceId\": \"2048583045\" } ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerRevokeInventoryItemsResult( PlayFabServerRevokeInventoryItemsResult* result )
{
    // result.errors = PlayFabServerRevokeItemError const* const*;
    // result.errorsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerSavePushNotificationTemplateRequest( PlayFab::ServerModels::SavePushNotificationTemplateRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"AndroidPayload\": \"String\", \"Id\": \"String\", \"IOSPayload\": \"String\", \"LocalizedPushNotificationTemplates\": \"Object\", \"Name\": \"String\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerSavePushNotificationTemplateResult( PlayFabServerSavePushNotificationTemplateResult* result )
{
    // result.pushNotificationTemplateId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerSendCustomAccountRecoveryEmailRequest( PlayFab::ServerModels::SendCustomAccountRecoveryEmailRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"EmailTemplateId\": \"D53AB15D8F12E330\", \"Email\": \"Me@here.com\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerSendEmailFromTemplateRequest( PlayFab::ServerModels::SendEmailFromTemplateRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"EmailTemplateId\": \"B53CA15D92D2E331\", \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerSendPushNotificationRequest( PlayFab::ServerModels::SendPushNotificationRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Recipient\": \"F8763A987E\", \"Message\": \"You have been attacked! Go defend your base!\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerSendPushNotificationFromTemplateRequest( PlayFab::ServerModels::SendPushNotificationFromTemplateRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Recipient\": \"F8763A987E\", \"PushNotificationTemplateId\": \"6bc7dbf0-075a-46e9-8e84-35737a22c6a4\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerSetFriendTagsRequest( PlayFab::ServerModels::SetFriendTagsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"FriendPlayFabId\": \"298ABC37799\", \"Tags\": [ \"sniper\", \"melee\" ]}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerSetGameServerInstanceDataRequest( PlayFab::ServerModels::SetGameServerInstanceDataRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"GameServerData\": \"String\", \"LobbyId\": \"String\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerSetGameServerInstanceStateRequest( PlayFab::ServerModels::SetGameServerInstanceStateRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"LobbyId\": \"29439584\", \"State\": \"Closed\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerSetGameServerInstanceTagsRequest( PlayFab::ServerModels::SetGameServerInstanceTagsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"LobbyId\": \"29439584\", \"Tags\": { \"TagA\": \"123\", \"TagB\": \"321\" }}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerSetPlayerSecretRequest( PlayFab::ServerModels::SetPlayerSecretRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayerSecret\": \"secretkeyforthisplayer\", \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerSetPublisherDataRequest( PlayFab::ServerModels::SetPublisherDataRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Key\": \"Running Speed\", \"Value\": \"1.03\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerSetTitleDataRequest( PlayFab::ServerModels::SetTitleDataRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Key\": \"Running Speed\", \"Value\": \"1.03\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerSubtractCharacterVirtualCurrencyRequest( PlayFab::ServerModels::SubtractCharacterVirtualCurrencyRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"CharacterId\": \"{{CharacterId}}\", \"VirtualCurrency\": \"GC\", \"Amount\": 100}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerSubtractUserVirtualCurrencyRequest( PlayFab::ServerModels::SubtractUserVirtualCurrencyRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"VirtualCurrency\": \"GC\", \"Amount\": 100}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerUnlinkPSNAccountRequest( PlayFab::ServerModels::UnlinkPSNAccountRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerUnlinkServerCustomIdRequest( PlayFab::ServerModels::UnlinkServerCustomIdRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"ServerCustomId\": \"67AB-5397-CC54-EA31\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerUnlinkXboxAccountRequest( PlayFab::ServerModels::UnlinkXboxAccountRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerUnlockContainerInstanceRequest( PlayFab::ServerModels::UnlockContainerInstanceRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"ContainerItemInstanceId\": \"123456788\", \"KeyItemInstanceId\": \"123456789\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerUnlockContainerItemResult( PlayFabServerUnlockContainerItemResult* result )
{
    // result.grantedItems = PlayFabItemInstance const* const*;
    // result.grantedItemsCount = uint32_t;
    // result.unlockedItemInstanceId = const char*;
    // result.unlockedWithItemInstanceId = const char*;
    // result.virtualCurrency = struct PlayFabUint32DictionaryEntry const*;
    // result.virtualCurrencyCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerUnlockContainerItemRequest( PlayFab::ServerModels::UnlockContainerItemRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"ContainerItemId\": \"crate block 1\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerUpdateAvatarUrlRequest( PlayFab::ServerModels::UpdateAvatarUrlRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"ImageUrl\": \"https://www.gravatar.com/avatar/205e460b479e2e5b48aec07710c08d50\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerUpdateBansRequest( PlayFab::ServerModels::UpdateBansRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Bans\": [ {  \"BanId\": \"E0B5FF89542D413C\",  \"Permanent\": true,  \"Active\": true }, {  \"BanId\": \"EF43FF89542G1546\",  \"Reason\": \"Royal pardon\",  \"Expires\": \"2016-07-04T00:00:00Z\" } ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerUpdateBansResult( PlayFabServerUpdateBansResult* result )
{
    // result.banData = PlayFabServerBanInfo const* const*;
    // result.banDataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerUpdateCharacterDataRequest( PlayFab::ServerModels::UpdateCharacterDataRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"CharacterId\": \"{{CharacterId}}\", \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }, \"Permission\": \"Public\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerUpdateCharacterDataResult( PlayFabServerUpdateCharacterDataResult* result )
{
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerUpdateCharacterStatisticsRequest( PlayFab::ServerModels::UpdateCharacterStatisticsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"CharacterId\": \"{{CharacterId}}\", \"CharacterStatistics\": { \"Headshots\": 18, \"Kills\": 47 }}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerUpdatePlayerStatisticsRequest( PlayFab::ServerModels::UpdatePlayerStatisticsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Statistics\": [ {  \"StatisticName\": \"Points\",  \"Version\": 1,  \"Value\": 600 }, {  \"StatisticName\": \"Wins\",  \"Version\": 2,  \"Value\": 16 }, {  \"StatisticName\": \"Stars\",  \"Value\": 7 } ]}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerUpdateSharedGroupDataRequest( PlayFab::ServerModels::UpdateSharedGroupDataRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SharedGroupId\": \"Clan Data\", \"Data\": { \"ClanKills\": \"34\", \"LastClanUpdate\": \"2014-10-03T09:21:14Z\" }, \"Permission\": \"Public\"}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerUpdateUserDataRequest( PlayFab::ServerModels::UpdateUserDataRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }, \"Permission\": \"Public\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerUpdateUserDataResult( PlayFabServerUpdateUserDataResult* result )
{
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerUpdateUserInternalDataRequest( PlayFab::ServerModels::UpdateUserInternalDataRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerUpdateUserInventoryItemDataRequest( PlayFab::ServerModels::UpdateUserInventoryItemDataRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"CharacterId\": \"{{CharacterId}}\", \"ItemInstanceId\": \"88331144\", \"Data\": { \"Equipped\": \"True\", \"Slot\": \"Head\" }}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerWriteServerCharacterEventRequest( PlayFab::ServerModels::WriteServerCharacterEventRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"CharacterId\": \"{{CharacterId}}\", \"EventName\": \"character_defeated_enemy\", \"Timestamp\": \"2016-03-07T00:00:00Z\", \"Body\": { \"Enemy\": \"guardian\", \"Damage\": 5, \"Coordinates\": {  \"X\": 123.4,  \"Y\": 543.2 } }}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenServerTests::ValidatePlayFabServerWriteEventResponse( PlayFabServerWriteEventResponse* result )
{
    // result.eventId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenServerTests::FillPlayFabServerWriteServerPlayerEventRequest( PlayFab::ServerModels::WriteServerPlayerEventRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"EventName\": \"player_defeated_enemy\", \"Timestamp\": \"2016-03-07T00:00:00Z\", \"Body\": { \"Enemy\": \"guardian\", \"Damage\": 5, \"Coordinates\": {  \"X\": 123.4,  \"Y\": 543.2 } }}" );
    request->FromJson(inputJson);
}

void AutoGenServerTests::FillPlayFabServerWriteTitleEventRequest( PlayFab::ServerModels::WriteTitleEventRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"EventName\": \"client_update_submitted\", \"Timestamp\": \"2016-03-07T00:00:00Z\", \"Body\": { \"Version\": \"1.4.50\" }}" );
    request->FromJson(inputJson);
}

 

}
