#include "TestAppPch.h"
#include "TestContext.h"
#include "TestApp.h"
#include "AutoGenClientTests.h"
#include "XAsyncHelper.h"
#include <playfab/PlayFabClientAuthApi.h>
#include <playfab/PlayFabClientApi.h>
#include <playfab/PlayFabProfilesApi.h>
#include <playfab/PlayFabAdminApi.h>
#include <playfab/PlayFabAuthenticationAuthApi.h>
#include <playfab/PlayFabClientDataModels.h>

namespace PlayFabUnit
{

void AutoGenClientTests::FillPlayFabClientAcceptTradeRequest( PlayFab::ClientModels::AcceptTradeRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"OfferingPlayerId\": \"CD803BF233CE76CC\", \"TradeId\": \"D819CEC225EA9948C351\", \"AcceptedInventoryInstanceIds\": [ \"95C1797ADDAC24DC0383\", \"0F7793DF55CCEAF21B84\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientAcceptTradeResponse( PlayFabClientAcceptTradeResponse* result )
{
    // result.trade = PlayFabClientTradeInfo const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientAddFriendRequest( PlayFab::ClientModels::AddFriendRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"FriendPlayFabId\": \"29837799\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientAddFriendResult( PlayFabClientAddFriendResult* result )
{
    // result.created = bool;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientAddGenericIDRequest( PlayFab::ClientModels::AddGenericIDRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"GenericId\": { \"ServiceName\": \"BigBizSocial\", \"UserId\": \"1234567890\" }}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientAddOrUpdateContactEmailRequest( PlayFab::ClientModels::AddOrUpdateContactEmailRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"EmailAddress\": \"theuser@domain.com\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientAddSharedGroupMembersRequest( PlayFab::ClientModels::AddSharedGroupMembersRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SharedGroupId\": \"Clan Data\", \"PlayFabIds\": [ \"D984A64B832\", \"F74A523E1562\" ]}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientAddUsernamePasswordRequest( PlayFab::ClientModels::AddUsernamePasswordRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Username\": \"theuser\", \"Email\": \"me@here.com\", \"Password\": \"thepassword\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientAddUsernamePasswordResult( PlayFabClientAddUsernamePasswordResult* result )
{
    // result.username = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientAddUserVirtualCurrencyRequest( PlayFab::ClientModels::AddUserVirtualCurrencyRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"VirtualCurrency\": \"GC\", \"Amount\": 100}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientModifyUserVirtualCurrencyResult( PlayFabClientModifyUserVirtualCurrencyResult* result )
{
    // result.balance = int32_t;
    // result.balanceChange = int32_t;
    // result.playFabId = const char*;
    // result.virtualCurrency = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientAndroidDevicePushNotificationRegistrationRequest( PlayFab::ClientModels::AndroidDevicePushNotificationRegistrationRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"DeviceToken\": \"59872d98fa632brn8hg3770\", \"SendPushNotificationConfirmation\": true, \"ConfirmationMessage\": \"Welcome to PlayFab!\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientAttributeInstallRequest( PlayFab::ClientModels::AttributeInstallRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Idfa\": \"11098810\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientCancelTradeRequest( PlayFab::ClientModels::CancelTradeRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"TradeId\": \"D819CEC225EA9948C351\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientCancelTradeResponse( PlayFabClientCancelTradeResponse* result )
{
    // result.trade = PlayFabClientTradeInfo const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientConfirmPurchaseRequest( PlayFab::ClientModels::ConfirmPurchaseRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"OrderId\": \"8853591446005860822\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientConfirmPurchaseResult( PlayFabClientConfirmPurchaseResult* result )
{
    // result.items = PlayFabItemInstance const* const*;
    // result.itemsCount = uint32_t;
    // result.orderId = const char*;
    // result.purchaseDate = time_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientConsumeItemRequest( PlayFab::ClientModels::ConsumeItemRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ItemInstanceId\": \"94585729\", \"ConsumeCount\": 1}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientConsumeItemResult( PlayFabClientConsumeItemResult* result )
{
    // result.itemInstanceId = const char*;
    // result.remainingUses = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientConsumeMicrosoftStoreEntitlementsRequest( PlayFab::ClientModels::ConsumeMicrosoftStoreEntitlementsRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"MarketplaceSpecificData\": { \"XboxToken\": \"XBL3.0 x=1981989841;akljdlkafdknad\", \"userId\": \"46239871\", \"collectionsMsIdKey\": \"MicrosoftStoreIdKey\" }, \"CatalogVersion\": \"{{PrimaryCatalogName}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientConsumeMicrosoftStoreEntitlementsResponse( PlayFabClientConsumeMicrosoftStoreEntitlementsResponse* result )
{
    // result.items = PlayFabItemInstance const* const*;
    // result.itemsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientConsumePS5EntitlementsRequest( PlayFab::ClientModels::ConsumePS5EntitlementsRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"MarketplaceSpecificData\": { \"ServiceLabel\": \"1\" }, \"CatalogVersion\": \"{{PrimaryCatalogName}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientConsumePS5EntitlementsResult( PlayFabClientConsumePS5EntitlementsResult* result )
{
    // result.items = PlayFabItemInstance const* const*;
    // result.itemsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientConsumePSNEntitlementsRequest( PlayFab::ClientModels::ConsumePSNEntitlementsRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ServiceLabel\": 1}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientConsumePSNEntitlementsResult( PlayFabClientConsumePSNEntitlementsResult* result )
{
    // result.itemsGranted = PlayFabItemInstance const* const*;
    // result.itemsGrantedCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientConsumeXboxEntitlementsRequest( PlayFab::ClientModels::ConsumeXboxEntitlementsRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"XboxToken\": \"XBL3.0 x=1981989841;akljdlkafdknad\", \"CatalogVersion\": \"{{PrimaryCatalogName}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientConsumeXboxEntitlementsResult( PlayFabClientConsumeXboxEntitlementsResult* result )
{
    // result.items = PlayFabItemInstance const* const*;
    // result.itemsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientCreateSharedGroupRequest( PlayFab::ClientModels::CreateSharedGroupRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SharedGroupId\": \"Clan Data\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientCreateSharedGroupResult( PlayFabClientCreateSharedGroupResult* result )
{
    // result.sharedGroupId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientExecuteCloudScriptRequest( PlayFab::ClientModels::ExecuteCloudScriptRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"FunctionName\": \"levelCompleted\", \"FunctionParameter\": { \"level\": 3, \"points\": 400 }, \"RevisionSelection\": \"Live\", \"GeneratePlayStreamEvent\": true}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientExecuteCloudScriptResult( PlayFabClientExecuteCloudScriptResult* result )
{
    // result.aPIRequestsIssued = int32_t;
    // result.error = PlayFabClientScriptExecutionError const*;
    // result.executionTimeSeconds = double;
    // result.functionName = const char*;
    // result.functionResult = PlayFabJsonObject;
    // result.functionResultTooLarge = bool const*;
    // result.httpRequestsIssued = int32_t;
    // result.logs = PlayFabClientLogStatement const* const*;
    // result.logsCount = uint32_t;
    // result.logsTooLarge = bool const*;
    // result.memoryConsumedBytes = uint32_t;
    // result.processorTimeSeconds = double;
    // result.revision = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetAccountInfoRequest( PlayFab::ClientModels::GetAccountInfoRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetAccountInfoResult( PlayFabClientGetAccountInfoResult* result )
{
    // result.accountInfo = PlayFabUserAccountInfo const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetAdPlacementsRequest( PlayFab::ClientModels::GetAdPlacementsRequest* request )
{
    // TODO: debug PassingButNoData test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"AppId\": \"A12784B\", \"Identifier\": { \"Name\": \"PowerBonusInterstitial\" }}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetAdPlacementsResult( PlayFabClientGetAdPlacementsResult* result )
{
    // result.adPlacements = PlayFabClientAdPlacementDetails const* const*;
    // result.adPlacementsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientListUsersCharactersRequest( PlayFab::ClientModels::ListUsersCharactersRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientListUsersCharactersResult( PlayFabClientListUsersCharactersResult* result )
{
    // result.characters = PlayFabCharacterResult const* const*;
    // result.charactersCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetCatalogItemsRequest( PlayFab::ClientModels::GetCatalogItemsRequest* request )
{
    // TODO: debug PassingButNoData test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"CatalogVersion\": \"{{PrimaryCatalogName}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetCatalogItemsResult( PlayFabClientGetCatalogItemsResult* result )
{
    // result.catalog = PlayFabClientCatalogItem const* const*;
    // result.catalogCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetCharacterDataRequest( PlayFab::ClientModels::GetCharacterDataRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"CharacterId\": \"{{CharacterId}}\", \"Keys\": [ \"preferences\", \"progress\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetCharacterDataResult( PlayFabClientGetCharacterDataResult* result )
{
    // result.characterId = const char*;
    // result.data = struct PlayFabUserDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetCharacterInventoryRequest( PlayFab::ClientModels::GetCharacterInventoryRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"CharacterId\": \"{{CharacterId}}\", \"CatalogVersion\": \"{{PrimaryCatalogName}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetCharacterInventoryResult( PlayFabClientGetCharacterInventoryResult* result )
{
    // result.characterId = const char*;
    // result.inventory = PlayFabItemInstance const* const*;
    // result.inventoryCount = uint32_t;
    // result.virtualCurrency = struct PlayFabInt32DictionaryEntry const*;
    // result.virtualCurrencyCount = uint32_t;
    // result.virtualCurrencyRechargeTimes = struct PlayFabVirtualCurrencyRechargeTimeDictionaryEntry const*;
    // result.virtualCurrencyRechargeTimesCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetCharacterLeaderboardRequest( PlayFab::ClientModels::GetCharacterLeaderboardRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"CharacterType\": \"blue_warrior\", \"StatisticName\": \"Kills\", \"StartPosition\": 0, \"MaxResultsCount\": 20}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetCharacterLeaderboardResult( PlayFabClientGetCharacterLeaderboardResult* result )
{
    // result.leaderboard = PlayFabClientCharacterLeaderboardEntry const* const*;
    // result.leaderboardCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetCharacterStatisticsRequest( PlayFab::ClientModels::GetCharacterStatisticsRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"CharacterId\": \"{{CharacterId}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetCharacterStatisticsResult( PlayFabClientGetCharacterStatisticsResult* result )
{
    // result.characterStatistics = struct PlayFabInt32DictionaryEntry const*;
    // result.characterStatisticsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetContentDownloadUrlRequest( PlayFab::ClientModels::GetContentDownloadUrlRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Key\": \"images/sword_icon.png\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetContentDownloadUrlResult( PlayFabClientGetContentDownloadUrlResult* result )
{
    // result.uRL = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientCurrentGamesRequest( PlayFab::ClientModels::CurrentGamesRequest* request )
{
    // TODO: debug PassingButNoData test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Region\": \"USCentral\", \"BuildVersion\": \"5.0.1\", \"GameMode\": \"CaptureTheFlag\", \"StatisticName\": \"level\", \"TagFilter\": { \"Includes\": [  {  \"Data\": {   \"level_cap\": \"0\"  }  } ], \"Excludes\": [  {  \"Data\": {   \"newbie\": \"0\"  }  } ] }}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientCurrentGamesResult( PlayFabClientCurrentGamesResult* result )
{
    // result.gameCount = int32_t;
    // result.games = PlayFabClientGameInfo const* const*;
    // result.gamesCount = uint32_t;
    // result.playerCount = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetFriendLeaderboardRequest( PlayFab::ClientModels::GetFriendLeaderboardRequest* request )
{
    // TODO: debug PassingButNoData test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StatisticName\": \"Kills\", \"StartPosition\": 1258, \"MaxResultsCount\": 20, \"IncludeSteamFriends\": false}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetLeaderboardResult( PlayFabClientGetLeaderboardResult* result )
{
    // result.leaderboard = PlayFabClientPlayerLeaderboardEntry const* const*;
    // result.leaderboardCount = uint32_t;
    // result.nextReset = time_t const*;
    // result.version = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetFriendLeaderboardAroundPlayerRequest( PlayFab::ClientModels::GetFriendLeaderboardAroundPlayerRequest* request )
{
    // TODO: debug PassingButNoData test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StatisticName\": \"Kills\", \"MaxResultsCount\": 20}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetFriendLeaderboardAroundPlayerResult( PlayFabClientGetFriendLeaderboardAroundPlayerResult* result )
{
    // result.leaderboard = PlayFabClientPlayerLeaderboardEntry const* const*;
    // result.leaderboardCount = uint32_t;
    // result.nextReset = time_t const*;
    // result.version = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetFriendsListRequest( PlayFab::ClientModels::GetFriendsListRequest* request )
{
    // TODO: debug PassingButNoData test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"IncludeSteamFriends\": true}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetFriendsListResult( PlayFabClientGetFriendsListResult* result )
{
    // result.friends = PlayFabClientFriendInfo const* const*;
    // result.friendsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGameServerRegionsRequest( PlayFab::ClientModels::GameServerRegionsRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildVersion\": \"5.0.1\", \"TitleId\": \"{{TitleId}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGameServerRegionsResult( PlayFabClientGameServerRegionsResult* result )
{
    // result.regions = PlayFabClientRegionInfo const* const*;
    // result.regionsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetLeaderboardRequest( PlayFab::ClientModels::GetLeaderboardRequest* request )
{
    // TODO: debug PassingButNoData test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StatisticName\": \"Kills\", \"StartPosition\": 0, \"MaxResultsCount\": 20}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientGetLeaderboardAroundCharacterRequest( PlayFab::ClientModels::GetLeaderboardAroundCharacterRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StatisticName\": \"Kills\", \"CharacterId\": \"{{CharacterId}}\", \"MaxResultsCount\": 20}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetLeaderboardAroundCharacterResult( PlayFabClientGetLeaderboardAroundCharacterResult* result )
{
    // result.leaderboard = PlayFabClientCharacterLeaderboardEntry const* const*;
    // result.leaderboardCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetLeaderboardAroundPlayerRequest( PlayFab::ClientModels::GetLeaderboardAroundPlayerRequest* request )
{
    // TODO: debug PassingButNoData test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StatisticName\": \"Kills\", \"MaxResultsCount\": 20}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetLeaderboardAroundPlayerResult( PlayFabClientGetLeaderboardAroundPlayerResult* result )
{
    // result.leaderboard = PlayFabClientPlayerLeaderboardEntry const* const*;
    // result.leaderboardCount = uint32_t;
    // result.nextReset = time_t const*;
    // result.version = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetLeaderboardForUsersCharactersRequest( PlayFab::ClientModels::GetLeaderboardForUsersCharactersRequest* request )
{
    // TODO: debug PassingButNoData test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StatisticName\": \"Kills\", \"MaxResultsCount\": 20}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetLeaderboardForUsersCharactersResult( PlayFabClientGetLeaderboardForUsersCharactersResult* result )
{
    // result.leaderboard = PlayFabClientCharacterLeaderboardEntry const* const*;
    // result.leaderboardCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetPaymentTokenRequest( PlayFab::ClientModels::GetPaymentTokenRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"TokenProvider\": \"xsolla\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetPaymentTokenResult( PlayFabClientGetPaymentTokenResult* result )
{
    // result.orderId = const char*;
    // result.providerToken = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetPhotonAuthenticationTokenRequest( PlayFab::ClientModels::GetPhotonAuthenticationTokenRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PhotonApplicationId\": \"acaa26f3-fcdb-4af4-8c76-3a3d4dd3066f\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetPhotonAuthenticationTokenResult( PlayFabClientGetPhotonAuthenticationTokenResult* result )
{
    // result.photonCustomAuthenticationToken = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetPlayerCombinedInfoRequest( PlayFab::ClientModels::GetPlayerCombinedInfoRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"InfoRequestParameters\": { \"GetUserAccountInfo\": true, \"GetUserInventory\": false, \"GetUserVirtualCurrency\": true, \"GetUserData\": true, \"UserDataKeys\": [  \"preferences\",  \"progress\" ], \"GetUserReadOnlyData\": false, \"GetCharacterInventories\": false, \"GetCharacterList\": false, \"GetTitleData\": false, \"GetPlayerStatistics\": false, \"GetPlayerProfile\": false }}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetPlayerCombinedInfoResult( PlayFabClientGetPlayerCombinedInfoResult* result )
{
    // result.infoResultPayload = PlayFabGetPlayerCombinedInfoResultPayload const*;
    // result.playFabId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetPlayerProfileRequest( PlayFab::ClientModels::GetPlayerProfileRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetPlayerProfileResult( PlayFabClientGetPlayerProfileResult* result )
{
    // result.playerProfile = PlayFabPlayerProfileModel const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetPlayerSegmentsResult( PlayFabClientGetPlayerSegmentsResult* result )
{
    // result.segments = PlayFabClientGetSegmentResult const* const*;
    // result.segmentsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetPlayerStatisticsRequest( PlayFab::ClientModels::GetPlayerStatisticsRequest* request )
{
    // TODO: debug PassingButNoData test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StatisticNames\": [ \"Points\", \"Wins\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetPlayerStatisticsResult( PlayFabClientGetPlayerStatisticsResult* result )
{
    // result.statistics = PlayFabStatisticValue const* const*;
    // result.statisticsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetPlayerStatisticVersionsRequest( PlayFab::ClientModels::GetPlayerStatisticVersionsRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StatisticName\": \"headshots\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetPlayerStatisticVersionsResult( PlayFabClientGetPlayerStatisticVersionsResult* result )
{
    // result.statisticVersions = PlayFabClientPlayerStatisticVersion const* const*;
    // result.statisticVersionsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetPlayerTagsRequest( PlayFab::ClientModels::GetPlayerTagsRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Namespace\": \"title.AAA\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetPlayerTagsResult( PlayFabClientGetPlayerTagsResult* result )
{
    // result.playFabId = const char*;
    // result.tags = const char* const*;
    // result.tagsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetPlayerTradesRequest( PlayFab::ClientModels::GetPlayerTradesRequest* request )
{
    // TODO: debug PassingButNoData test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StatusFilter\": \"Filled\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetPlayerTradesResponse( PlayFabClientGetPlayerTradesResponse* result )
{
    // result.acceptedTrades = PlayFabClientTradeInfo const* const*;
    // result.acceptedTradesCount = uint32_t;
    // result.openedTrades = PlayFabClientTradeInfo const* const*;
    // result.openedTradesCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetPlayFabIDsFromFacebookIDsRequest( PlayFab::ClientModels::GetPlayFabIDsFromFacebookIDsRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"FacebookIDs\": [ \"857498576495\", \"759374651209\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetPlayFabIDsFromFacebookIDsResult( PlayFabClientGetPlayFabIDsFromFacebookIDsResult* result )
{
    // result.data = PlayFabClientFacebookPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetPlayFabIDsFromFacebookInstantGamesIdsRequest( PlayFab::ClientModels::GetPlayFabIDsFromFacebookInstantGamesIdsRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"FacebookInstantGamesIds\": [ \"1114685845316172\", \"1114685845316173\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetPlayFabIDsFromFacebookInstantGamesIdsResult( PlayFabClientGetPlayFabIDsFromFacebookInstantGamesIdsResult* result )
{
    // result.data = PlayFabClientFacebookInstantGamesPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetPlayFabIDsFromGameCenterIDsRequest( PlayFab::ClientModels::GetPlayFabIDsFromGameCenterIDsRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"GameCenterIDs\": [ \"857498576495\", \"759374651209\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetPlayFabIDsFromGameCenterIDsResult( PlayFabClientGetPlayFabIDsFromGameCenterIDsResult* result )
{
    // result.data = PlayFabClientGameCenterPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetPlayFabIDsFromGenericIDsRequest( PlayFab::ClientModels::GetPlayFabIDsFromGenericIDsRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"GenericIDs\": [ {  \"ServiceName\": \"BigBizSocial\",  \"UserId\": \"1234567890\" }, {  \"ServiceName\": \"VeeCeeMe\",  \"UserId\": \"og5igh85gf43gf\" } ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetPlayFabIDsFromGenericIDsResult( PlayFabClientGetPlayFabIDsFromGenericIDsResult* result )
{
    // result.data = PlayFabClientGenericPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetPlayFabIDsFromGoogleIDsRequest( PlayFab::ClientModels::GetPlayFabIDsFromGoogleIDsRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"GoogleIDs\": [ \"857498576495\", \"759374651209\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetPlayFabIDsFromGoogleIDsResult( PlayFabClientGetPlayFabIDsFromGoogleIDsResult* result )
{
    // result.data = PlayFabClientGooglePlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetPlayFabIDsFromKongregateIDsRequest( PlayFab::ClientModels::GetPlayFabIDsFromKongregateIDsRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"KongregateIDs\": [ \"857498576495\", \"759374651209\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetPlayFabIDsFromKongregateIDsResult( PlayFabClientGetPlayFabIDsFromKongregateIDsResult* result )
{
    // result.data = PlayFabClientKongregatePlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest( PlayFab::ClientModels::GetPlayFabIDsFromNintendoSwitchDeviceIdsRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"NintendoSwitchDeviceIds\": [ \"526f79204261747478\", \"526f79204261747479\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetPlayFabIDsFromNintendoSwitchDeviceIdsResult( PlayFabClientGetPlayFabIDsFromNintendoSwitchDeviceIdsResult* result )
{
    // result.data = PlayFabClientNintendoSwitchPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetPlayFabIDsFromPSNAccountIDsRequest( PlayFab::ClientModels::GetPlayFabIDsFromPSNAccountIDsRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PSNAccountIDs\": [ \"857498576495\", \"759374651209\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetPlayFabIDsFromPSNAccountIDsResult( PlayFabClientGetPlayFabIDsFromPSNAccountIDsResult* result )
{
    // result.data = PlayFabClientPSNAccountPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetPlayFabIDsFromSteamIDsRequest( PlayFab::ClientModels::GetPlayFabIDsFromSteamIDsRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SteamStringIDs\": [ \"857498576495\", \"759374651209\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetPlayFabIDsFromSteamIDsResult( PlayFabClientGetPlayFabIDsFromSteamIDsResult* result )
{
    // result.data = PlayFabClientSteamPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetPlayFabIDsFromTwitchIDsRequest( PlayFab::ClientModels::GetPlayFabIDsFromTwitchIDsRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"TwitchIds\": [ \"127168541\", \"88315720\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetPlayFabIDsFromTwitchIDsResult( PlayFabClientGetPlayFabIDsFromTwitchIDsResult* result )
{
    // result.data = PlayFabClientTwitchPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetPlayFabIDsFromXboxLiveIDsRequest( PlayFab::ClientModels::GetPlayFabIDsFromXboxLiveIDsRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"XboxLiveAccountIDs\": [ \"857498576495\", \"759374651209\" ], \"Sandbox\": \"RETAIL\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetPlayFabIDsFromXboxLiveIDsResult( PlayFabClientGetPlayFabIDsFromXboxLiveIDsResult* result )
{
    // result.data = PlayFabClientXboxLiveAccountPlayFabIdPair const* const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetPublisherDataRequest( PlayFab::ClientModels::GetPublisherDataRequest* request )
{
    // TODO: debug PassingButNoData test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Keys\": [ \"color\", \"propertyA\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetPublisherDataResult( PlayFabClientGetPublisherDataResult* result )
{
    // result.data = struct PlayFabStringDictionaryEntry const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetPurchaseRequest( PlayFab::ClientModels::GetPurchaseRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"OrderId\": \"8853591446005860822\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetPurchaseResult( PlayFabClientGetPurchaseResult* result )
{
    // result.orderId = const char*;
    // result.paymentProvider = const char*;
    // result.purchaseDate = time_t;
    // result.transactionId = const char*;
    // result.transactionStatus = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetSharedGroupDataRequest( PlayFab::ClientModels::GetSharedGroupDataRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SharedGroupId\": \"Clan Data\", \"Keys\": [ \"ClanKills\", \"LastClanUpdate\" ], \"GetMembers\": true}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetSharedGroupDataResult( PlayFabClientGetSharedGroupDataResult* result )
{
    // result.data = struct PlayFabClientSharedGroupDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.members = const char* const*;
    // result.membersCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetStoreItemsRequest( PlayFab::ClientModels::GetStoreItemsRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StoreId\": \"BonusStore\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetStoreItemsResult( PlayFabClientGetStoreItemsResult* result )
{
    // result.catalogVersion = const char*;
    // result.marketingData = PlayFabClientStoreMarketingModel const*;
    // result.source = PlayFabClientSourceType const*;
    // result.store = PlayFabClientStoreItem const* const*;
    // result.storeCount = uint32_t;
    // result.storeId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetTimeResult( PlayFabClientGetTimeResult* result )
{
    // result.time = time_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetTitleDataRequest( PlayFab::ClientModels::GetTitleDataRequest* request )
{
    // TODO: debug PassingButNoData test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Keys\": [ \"color\", \"propertyA\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetTitleDataResult( PlayFabClientGetTitleDataResult* result )
{
    // result.data = struct PlayFabStringDictionaryEntry const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetTitleNewsRequest( PlayFab::ClientModels::GetTitleNewsRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Count\": 25}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetTitleNewsResult( PlayFabClientGetTitleNewsResult* result )
{
    // result.news = PlayFabClientTitleNewsItem const* const*;
    // result.newsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetTitlePublicKeyRequest( PlayFab::ClientModels::GetTitlePublicKeyRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"TitleId\": \"{{TitleId}}\", \"TitleSharedSecret\": \"123456789\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetTitlePublicKeyResult( PlayFabClientGetTitlePublicKeyResult* result )
{
    // result.rSAPublicKey = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetTradeStatusRequest( PlayFab::ClientModels::GetTradeStatusRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"OfferingPlayerId\": \"CD803BF233CE76CC\", \"TradeId\": \"D819CEC225EA9948C351\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetTradeStatusResponse( PlayFabClientGetTradeStatusResponse* result )
{
    // result.trade = PlayFabClientTradeInfo const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetUserDataRequest( PlayFab::ClientModels::GetUserDataRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Keys\": [ \"preferences\", \"progress\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetUserDataResult( PlayFabClientGetUserDataResult* result )
{
    // result.data = struct PlayFabUserDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGetUserInventoryRequest( PlayFab::ClientModels::GetUserInventoryRequest* request )
{
    // TODO: debug PassingButNoData test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGetUserInventoryResult( PlayFabClientGetUserInventoryResult* result )
{
    // result.inventory = PlayFabItemInstance const* const*;
    // result.inventoryCount = uint32_t;
    // result.virtualCurrency = struct PlayFabInt32DictionaryEntry const*;
    // result.virtualCurrencyCount = uint32_t;
    // result.virtualCurrencyRechargeTimes = struct PlayFabVirtualCurrencyRechargeTimeDictionaryEntry const*;
    // result.virtualCurrencyRechargeTimesCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientGrantCharacterToUserRequest( PlayFab::ClientModels::GrantCharacterToUserRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"CatalogVersion\": \"{{PrimaryCatalogName}}\", \"ItemId\": \"Blue Warrior\", \"CharacterName\": \"FighterDude\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientGrantCharacterToUserResult( PlayFabClientGrantCharacterToUserResult* result )
{
    // result.characterId = const char*;
    // result.characterType = const char*;
    // result.result = bool;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientLinkAndroidDeviceIDRequest( PlayFab::ClientModels::LinkAndroidDeviceIDRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"AndroidDeviceId\": \"526f79204261747479\", \"OS\": \"5.0\", \"AndroidDevice\": \"Nexus 6\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientLinkAppleRequest( PlayFab::ClientModels::LinkAppleRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"IdentityToken\": \"eyJraWQi...\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientLinkCustomIDRequest( PlayFab::ClientModels::LinkCustomIDRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"CustomId\": \"67AB-5397-CC54-EA31\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientLinkFacebookAccountRequest( PlayFab::ClientModels::LinkFacebookAccountRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"AccessToken\": \"FaceAccessTokenID\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientLinkFacebookInstantGamesIdRequest( PlayFab::ClientModels::LinkFacebookInstantGamesIdRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"FacebookInstantGamesSignature\": \"abcdef\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientLinkGameCenterAccountRequest( PlayFab::ClientModels::LinkGameCenterAccountRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"GameCenterId\": \"2998h2998f0b000d0993\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientLinkGoogleAccountRequest( PlayFab::ClientModels::LinkGoogleAccountRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"AccessToken\": \"BInn23arRiCepodeRQ\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientLinkIOSDeviceIDRequest( PlayFab::ClientModels::LinkIOSDeviceIDRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"DeviceId\": \"29848d9bh8900a0b003\", \"OS\": \"7.11\", \"DeviceModel\": \"Iphone 5s\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientLinkKongregateAccountRequest( PlayFab::ClientModels::LinkKongregateAccountRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"KongregateId\": \"457332\", \"AuthTicket\": \"{123-456-78931212}\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientLinkNintendoServiceAccountRequest( PlayFab::ClientModels::LinkNintendoServiceAccountRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"IdentityToken\": \"eyJraWQi...\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientLinkNintendoSwitchDeviceIdRequest( PlayFab::ClientModels::LinkNintendoSwitchDeviceIdRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"NintendoSwitchDeviceId\": \"526f79204261747479\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientLinkOpenIdConnectRequest( PlayFab::ClientModels::LinkOpenIdConnectRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ConnectionId\": \"exampleprovider\", \"IdToken\": \"eyJraWQi...\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientLinkPSNAccountRequest( PlayFab::ClientModels::LinkPSNAccountRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"AuthCode\": \"LKJDG7DDE\", \"RedirectUri\": \"orbis://games\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientLinkSteamAccountRequest( PlayFab::ClientModels::LinkSteamAccountRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SteamTicket\": \"steamTicketID\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientLinkTwitchAccountRequest( PlayFab::ClientModels::LinkTwitchAccountRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"AccessToken\": \"TwitchAccessToken\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientLinkXboxAccountRequest( PlayFab::ClientModels::LinkXboxAccountRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"XboxToken\": \"XBL3.0 x=1981989841;akljdlkafdknad\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientMatchmakeRequest( PlayFab::ClientModels::MatchmakeRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildVersion\": \"5.01\", \"Region\": \"USCentral\", \"GameMode\": \"0\", \"TagFilter\": { \"Includes\": [  {  \"Data\": {   \"level_cap\": \"0\"  }  } ], \"Excludes\": [  {  \"Data\": {   \"newbie\": \"0\"  }  } ] }}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientMatchmakeResult( PlayFabClientMatchmakeResult* result )
{
    // result.expires = const char*;
    // result.lobbyID = const char*;
    // result.pollWaitTimeMS = int32_t const*;
    // result.serverIPV4Address = const char*;
    // result.serverIPV6Address = const char*;
    // result.serverPort = int32_t const*;
    // result.serverPublicDNSName = const char*;
    // result.status = PlayFabClientMatchmakeStatus const*;
    // result.ticket = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientOpenTradeRequest( PlayFab::ClientModels::OpenTradeRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"OfferedInventoryInstanceIds\": [ \"1359447\", \"635691\" ], \"RequestedCatalogItemIds\": [ \"rare_hat_7\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientOpenTradeResponse( PlayFabClientOpenTradeResponse* result )
{
    // result.trade = PlayFabClientTradeInfo const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientPayForPurchaseRequest( PlayFab::ClientModels::PayForPurchaseRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"OrderId\": \"8853591446005860822\", \"ProviderName\": \"PayPal\", \"Currency\": \"RM\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientPayForPurchaseResult( PlayFabClientPayForPurchaseResult* result )
{
    // result.creditApplied = uint32_t;
    // result.orderId = const char*;
    // result.providerData = const char*;
    // result.providerToken = const char*;
    // result.purchaseConfirmationPageURL = const char*;
    // result.purchaseCurrency = const char*;
    // result.purchasePrice = uint32_t;
    // result.status = PlayFabClientTransactionStatus const*;
    // result.vCAmount = struct PlayFabInt32DictionaryEntry const*;
    // result.vCAmountCount = uint32_t;
    // result.virtualCurrency = struct PlayFabInt32DictionaryEntry const*;
    // result.virtualCurrencyCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientPurchaseItemRequest( PlayFab::ClientModels::PurchaseItemRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ItemId\": \"shield_level_5\", \"VirtualCurrency\": \"GV\", \"Price\": 25}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientPurchaseItemResult( PlayFabClientPurchaseItemResult* result )
{
    // result.items = PlayFabItemInstance const* const*;
    // result.itemsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientRedeemCouponRequest( PlayFab::ClientModels::RedeemCouponRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"CouponCode\": \"123-1234-123\", \"CatalogVersion\": \"{{PrimaryCatalogName}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientRedeemCouponResult( PlayFabClientRedeemCouponResult* result )
{
    // result.grantedItems = PlayFabItemInstance const* const*;
    // result.grantedItemsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientRefreshPSNAuthTokenRequest( PlayFab::ClientModels::RefreshPSNAuthTokenRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"AuthCode\": \"LKJDG7DDE\", \"RedirectUri\": \"orbis://games\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientRegisterForIOSPushNotificationRequest( PlayFab::ClientModels::RegisterForIOSPushNotificationRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"DeviceToken\": \"39872f98eb882brn8hg3889\", \"SendPushNotificationConfirmation\": true, \"ConfirmationMessage\": \"Welcome to PlayFab\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientRemoveContactEmailRequest( PlayFab::ClientModels::RemoveContactEmailRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientRemoveFriendRequest( PlayFab::ClientModels::RemoveFriendRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"FriendPlayFabId\": \"29837799\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientRemoveGenericIDRequest( PlayFab::ClientModels::RemoveGenericIDRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"GenericId\": { \"ServiceName\": \"BigBizSocial\", \"UserId\": \"1234567890\" }}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientRemoveSharedGroupMembersRequest( PlayFab::ClientModels::RemoveSharedGroupMembersRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SharedGroupId\": \"Clan Data\", \"PlayFabIds\": [ \"D984A64B832\", \"F74A523E1562\" ]}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientReportAdActivityRequest( PlayFab::ClientModels::ReportAdActivityRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlacementId\": \"A124572382B\", \"RewardId\": \"B2674981A\", \"Activity\": \"End\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientDeviceInfoRequest( PlayFab::ClientModels::DeviceInfoRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Info\": { \"UserAgent\": \"Some Browser\", \"ScreenResolution\": \"640x480\", \"processorCount\": \"2\" }}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientReportPlayerClientRequest( PlayFab::ClientModels::ReportPlayerClientRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ReporteeId\": \"1a46086aed40f142\", \"Comment\": \"cheating\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientReportPlayerClientResult( PlayFabClientReportPlayerClientResult* result )
{
    // result.submissionsRemaining = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientRestoreIOSPurchasesRequest( PlayFab::ClientModels::RestoreIOSPurchasesRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ReceiptData\": \"F00000000000000000000\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientRestoreIOSPurchasesResult( PlayFabClientRestoreIOSPurchasesResult* result )
{
    // result.fulfillments = PlayFabClientPurchaseReceiptFulfillment const* const*;
    // result.fulfillmentsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientRewardAdActivityRequest( PlayFab::ClientModels::RewardAdActivityRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlacementId\": \"A124572382B\", \"RewardId\": \"B2674981A\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientRewardAdActivityResult( PlayFabClientRewardAdActivityResult* result )
{
    // result.adActivityEventId = const char*;
    // result.debugResults = const char* const*;
    // result.debugResultsCount = uint32_t;
    // result.placementId = const char*;
    // result.placementName = const char*;
    // result.placementViewsRemaining = int32_t const*;
    // result.placementViewsResetMinutes = double const*;
    // result.rewardResults = PlayFabClientAdRewardResults const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientSendAccountRecoveryEmailRequest( PlayFab::ClientModels::SendAccountRecoveryEmailRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Email\": \"Me@here.com\", \"TitleId\": \"{{TitleId}}\", \"EmailTemplateId\": \"D53AB15D8F12E330\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientSetFriendTagsRequest( PlayFab::ClientModels::SetFriendTagsRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"FriendPlayFabId\": \"29837799\", \"Tags\": [ \"great sniper\", \"no good at melee\" ]}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientSetPlayerSecretRequest( PlayFab::ClientModels::SetPlayerSecretRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayerSecret\": \"A cryptographically strong string\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientStartGameRequest( PlayFab::ClientModels::StartGameRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildVersion\": \"5.01\", \"Region\": \"EUWest\", \"GameMode\": \"0\", \"CustomCommandLineData\": \"custom_gameserver_commandline_parameter\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientStartGameResult( PlayFabClientStartGameResult* result )
{
    // result.expires = const char*;
    // result.lobbyID = const char*;
    // result.password = const char*;
    // result.serverIPV4Address = const char*;
    // result.serverIPV6Address = const char*;
    // result.serverPort = int32_t const*;
    // result.serverPublicDNSName = const char*;
    // result.ticket = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientStartPurchaseRequest( PlayFab::ClientModels::StartPurchaseRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"CatalogVersion\": \"{{PrimaryCatalogName}}\", \"StoreId\": \"BonusStore\", \"Items\": [ {  \"ItemId\": \"something\",  \"Quantity\": 1,  \"Annotation\": \"totally buying something\" } ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientStartPurchaseResult( PlayFabClientStartPurchaseResult* result )
{
    // result.contents = PlayFabClientCartItem const* const*;
    // result.contentsCount = uint32_t;
    // result.orderId = const char*;
    // result.paymentOptions = PlayFabClientPaymentOption const* const*;
    // result.paymentOptionsCount = uint32_t;
    // result.virtualCurrencyBalances = struct PlayFabInt32DictionaryEntry const*;
    // result.virtualCurrencyBalancesCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientSubtractUserVirtualCurrencyRequest( PlayFab::ClientModels::SubtractUserVirtualCurrencyRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"VirtualCurrency\": \"GC\", \"Amount\": 100}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientUnlinkAndroidDeviceIDRequest( PlayFab::ClientModels::UnlinkAndroidDeviceIDRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"AndroidDeviceId\": \"526f79204261747479\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientUnlinkAppleRequest( PlayFab::ClientModels::UnlinkAppleRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientUnlinkCustomIDRequest( PlayFab::ClientModels::UnlinkCustomIDRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"CustomId\": \"67AB-5397-CC54-EA31\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientUnlinkFacebookAccountRequest( PlayFab::ClientModels::UnlinkFacebookAccountRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientUnlinkFacebookInstantGamesIdRequest( PlayFab::ClientModels::UnlinkFacebookInstantGamesIdRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"FacebookInstantGamesId\": \"1114685845316173\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientUnlinkGameCenterAccountRequest( PlayFab::ClientModels::UnlinkGameCenterAccountRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientUnlinkGoogleAccountRequest( PlayFab::ClientModels::UnlinkGoogleAccountRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientUnlinkIOSDeviceIDRequest( PlayFab::ClientModels::UnlinkIOSDeviceIDRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"DeviceId\": \"29848d9bh8900a0b003\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientUnlinkKongregateAccountRequest( PlayFab::ClientModels::UnlinkKongregateAccountRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientUnlinkNintendoServiceAccountRequest( PlayFab::ClientModels::UnlinkNintendoServiceAccountRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientUnlinkNintendoSwitchDeviceIdRequest( PlayFab::ClientModels::UnlinkNintendoSwitchDeviceIdRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"NintendoSwitchDeviceId\": \"526f79204261747479\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientUnlinkOpenIdConnectRequest( PlayFab::ClientModels::UnlinkOpenIdConnectRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ConnectionId\": \"exampleprovider\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientUnlinkPSNAccountRequest( PlayFab::ClientModels::UnlinkPSNAccountRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientUnlinkSteamAccountRequest( PlayFab::ClientModels::UnlinkSteamAccountRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientUnlinkTwitchAccountRequest( PlayFab::ClientModels::UnlinkTwitchAccountRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientUnlinkXboxAccountRequest( PlayFab::ClientModels::UnlinkXboxAccountRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientUnlockContainerInstanceRequest( PlayFab::ClientModels::UnlockContainerInstanceRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ContainerItemInstanceId\": \"123456788\", \"KeyItemInstanceId\": \"123456789\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientUnlockContainerItemResult( PlayFabClientUnlockContainerItemResult* result )
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

void AutoGenClientTests::FillPlayFabClientUnlockContainerItemRequest( PlayFab::ClientModels::UnlockContainerItemRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ContainerItemId\": \"crate block 1\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientUpdateAvatarUrlRequest( PlayFab::ClientModels::UpdateAvatarUrlRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ImageUrl\": \"https://www.gravatar.com/avatar/205e460b479e2e5b48aec07710c08d50\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientUpdateCharacterDataRequest( PlayFab::ClientModels::UpdateCharacterDataRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"CharacterId\": \"{{CharacterId}}\", \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }, \"Permission\": \"Public\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientUpdateCharacterDataResult( PlayFabClientUpdateCharacterDataResult* result )
{
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientUpdateCharacterStatisticsRequest( PlayFab::ClientModels::UpdateCharacterStatisticsRequest* request )
{
    // TODO: bad char id
    PlayFab::JsonDocument inputJson;
    inputJson.Parse("{ \"CharacterId\" : \"1234\", \"CharacterStatistics\" : { \"Points\" : 600, \"Wins\" : 32 } }");
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientUpdatePlayerStatisticsRequest( PlayFab::ClientModels::UpdatePlayerStatisticsRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse("{ \"Statistics\": [ {  \"StatisticName\": \"Points\", \"Value\": 600 }, {  \"StatisticName\": \"Wins\", \"Value\": 16 } ]}");
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientUpdateSharedGroupDataRequest( PlayFab::ClientModels::UpdateSharedGroupDataRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SharedGroupId\": \"Clan Data\", \"Data\": { \"ClanKills\": \"34\", \"LastClanUpdate\": \"2014-10-03T09:21:14Z\" }, \"Permission\": \"Public\"}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientUpdateUserDataRequest( PlayFab::ClientModels::UpdateUserDataRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }, \"Permission\": \"Public\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientUpdateUserDataResult( PlayFabClientUpdateUserDataResult* result )
{
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientUpdateUserTitleDisplayNameRequest( PlayFab::ClientModels::UpdateUserTitleDisplayNameRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"DisplayName\": \"User Title Name\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientUpdateUserTitleDisplayNameResult( PlayFabClientUpdateUserTitleDisplayNameResult* result )
{
    // result.displayName = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientValidateAmazonReceiptRequest( PlayFab::ClientModels::ValidateAmazonReceiptRequest* request )
{
    // TODO: debug failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse("{ \"CatalogVersion\": \"Test1\", \"CurrencyCode\": \"Test2\", \"CustomTags\": [ \"Test3\" ], \"PurchasePrice\": 123, \"ReceiptId\": \"q1YqVbJSyjH28DGPKChw9c0o8nd3vSstssQtzSkrzM8tCk43K6z0d_HOTcwwN8vxCrVV0lEqBmpJzs_VK8hJrExLTNLLTCzQK8_MSUnJTy8LSpcoWRnoKKUAFRmaGBtZmBqCCFMzpVoA\", \"UserId\": \"l3HL7XppEMhrOGDgur9-ulvqomrSg6qyODKmah72lJU=\" }");
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientValidateAmazonReceiptResult( PlayFabClientValidateAmazonReceiptResult* result )
{
    // result.fulfillments = PlayFabClientPurchaseReceiptFulfillment const* const*;
    // result.fulfillmentsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientValidateGooglePlayPurchaseRequest( PlayFab::ClientModels::ValidateGooglePlayPurchaseRequest* request )
{
    // TODO: debug failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse("{ \"CatalogVersion\": \"String\", \"CurrencyCode\": \"String\", \"CustomTags\": \"String\", \"PurchasePrice\": 123, \"ReceiptJson\": \"String\", \"Signature\": \"String\"}");
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientValidateGooglePlayPurchaseResult( PlayFabClientValidateGooglePlayPurchaseResult* result )
{
    // result.fulfillments = PlayFabClientPurchaseReceiptFulfillment const* const*;
    // result.fulfillmentsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientValidateIOSReceiptRequest( PlayFab::ClientModels::ValidateIOSReceiptRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ReceiptData\": \"MTExMTExMTExMTENCjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMg0KMzMzMzMzMzMzMzMzMzMzMzMNCjQ0NDQ0NDQ0NDQ0NDQNCjU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NQ0KNjY2NjY2NjY2NjY2Ng0KNzc3Nzc3Nzc3Nzc3NzcNCjg4DQo5OTk5OTk5OTk5OTkNCjAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMA0KMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTENCjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjINCjMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMw0KNDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0DQo1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1DQo2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2Ng0KNzc3Nzc3Nzc3NzcNCjg4ODg4ODg4ODg4ODg4ODg4ODg4ODg4ODg4ODg4ODg4DQo5DQpBcHBsZSBJbmMuIFdvcmxkd2lkZSBEZXZlbG9wZXIgUmVsYXRpb25zIENlcnRpZmljYXRpb24gQXV0aG9yaXR5IChub3QgcmVhbGx5IC0gZmFrZSBQbGF5RmFiIGV4YW1wbGUsIGJ1dCBjb25ncmF0cyBvbiB0aGlua2luZyB0byBkZWNvZGUgdGhpcyEpDQowMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwDQoxMTExMTExMTExMQ0KMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyDQozMzMzMzMzMzMzMzMzMzMzMw0KNDQ0NDQ0NDQ0NDQ0NA0KNTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1DQo2NjY2NjY2NjY2NjY2DQo3Nzc3Nzc3Nzc3Nzc3Nw0KODgNCjk5OTk5OTk5OTk5OQ0KMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwDQoxMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMQ0KMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMg0KMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzDQo0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQNCjU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTUNCjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2DQo3Nzc3Nzc3Nzc3Nw0KODg4ODg4ODg4ODg4ODg4ODg4ODg4ODg4ODg4ODg4ODgNCjkNCkFwcGxlIEluYy4gV29ybGR3aWRlIERldmVsb3BlciBSZWxhdGlvbnMgQ2VydGlmaWNhdGlvbiBBdXRob3JpdHkgKG5vdCByZWFsbHkgLSBmYWtlIFBsYXlGYWIgZXhhbXBsZSwgYnV0IGNvbmdyYXRzIG9uIHRoaW5raW5nIHRvIGRlY29kZSB0aGlzISkNCjAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDANCjExMTExMTExMTExDQoyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjINCjMzMzMzMzMzMzMzMzMzMzMzDQo0NDQ0NDQ0NDQ0NDQ0DQo1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTUNCjY2NjY2NjY2NjY2NjYNCjc3Nzc3Nzc3Nzc3Nzc3DQo4OA0KOTk5OTk5OTk5OTk5DQowMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDANCjExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExDQoyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyDQozMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMNCjQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NA0KNTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NQ0KNjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjYNCjc3Nzc3Nzc3Nzc3DQo4ODg4ODg4ODg4ODg4ODg4ODg4ODg4ODg4ODg4ODg4OA0KOQ0KQXBwbGUgSW5jLiBXb3JsZHdpZGUgRGV2ZWxvcGVyIFJlbGF0aW9ucyBDZXJ0aWZpY2F0aW9uIEF1dGhvcml0eSAobm90IHJlYWxseSAtIGZha2UgUGxheUZhYiBleGFtcGxlLCBidXQgY29uZ3JhdHMgb24gdGhpbmtpbmcgdG8gZGVjb2RlIHRoaXMhKQ0KMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMA0KMTExMTExMTExMTENCjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMg0KMzMzMzMzMzMzMzMzMzMzMzMNCjQ0NDQ0NDQ0NDQ0NDQNCjU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NQ0KNjY2NjY2NjY2NjY2Ng0KNzc3Nzc3Nzc3Nzc3NzcNCjg4DQo5OTk5OTk5OTk5OTkNCjAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMA0KMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTExMTENCjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjINCjMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMw0KNDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0DQo1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1NTU1DQo2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2NjY2Ng0KNzc3Nzc3Nzc3NzcNCjg4ODg4ODg4ODg4ODg4ODg4ODg4ODg4ODg4ODg4ODg4DQo5DQpBcHBsZSBJbmMuIFdvcmxkd2lkZSBEZXZlbG9wZXIgUmVsYXRpb25zIENlcnRpZmljYXRpb24gQXV0aG9yaXR5IChub3QgcmVhbGx5IC0gZmFrZSBQbGF5RmFiIGV4YW1wbGUsIGJ1dCBjb25ncmF0cyBvbiB0aGlua2luZyB0byBkZWNvZGUgdGhpcyEpDQowMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAw\", \"CurrencyCode\": \"GBP\", \"PurchasePrice\": 199}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientValidateIOSReceiptResult( PlayFabClientValidateIOSReceiptResult* result )
{
    // result.fulfillments = PlayFabClientPurchaseReceiptFulfillment const* const*;
    // result.fulfillmentsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientValidateWindowsReceiptRequest( PlayFab::ClientModels::ValidateWindowsReceiptRequest* request )
{
    // TODO: debug failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse("{ \"CatalogVersion\": \"String\", \"CurrencyCode\": \"String\", \"CustomTags\": \"String\", \"PurchasePrice\": 123, \"Receipt\": \"String\"}");
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientValidateWindowsReceiptResult( PlayFabClientValidateWindowsReceiptResult* result )
{
    // result.fulfillments = PlayFabClientPurchaseReceiptFulfillment const* const*;
    // result.fulfillmentsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientWriteClientCharacterEventRequest( PlayFab::ClientModels::WriteClientCharacterEventRequest* request )
{
    // TODO: debug Failing test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"CharacterId\": \"{{CharacterId}}\", \"EventName\": \"character_defeated_enemy\", \"Timestamp\": \"2016-03-07T00:00:00Z\", \"Body\": { \"Enemy\": \"guardian\", \"Damage\": 5, \"Coordinates\": {  \"X\": 123.4,  \"Y\": 543.2 } }}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenClientTests::ValidatePlayFabClientWriteEventResponse( PlayFabClientWriteEventResponse* result )
{
    // result.eventId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenClientTests::FillPlayFabClientWriteClientPlayerEventRequest( PlayFab::ClientModels::WriteClientPlayerEventRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"EventName\": \"player_defeated_enemy\", \"Timestamp\": \"2014-03-07T00:00:00Z\", \"Body\": { \"Enemy\": \"guardian\", \"Damage\": 5, \"Coordinates\": {  \"X\": 123.4,  \"Y\": 543.2 } }}" );
    request->FromJson(inputJson);
}

void AutoGenClientTests::FillPlayFabClientWriteTitleEventRequest( PlayFab::ClientModels::WriteTitleEventRequest* request )
{
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"EventName\": \"client_update_submitted\", \"Timestamp\": \"2016-03-07T00:00:00Z\", \"Body\": { \"Version\": \"1.4.50\" }}" );
    request->FromJson(inputJson);
}

 

}
