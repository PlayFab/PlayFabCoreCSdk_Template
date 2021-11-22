#include "TestAppPch.h"
#include "TestContext.h"
#include "TestApp.h"
#include "AutoGenAdminTests.h"
#include "XAsyncHelper.h"
#include <playfab/PlayFabClientAuthApi.h>
#include <playfab/PlayFabClientApi.h>
#include <playfab/PlayFabProfilesApi.h>
#include <playfab/PlayFabAdminApi.h>
#include <playfab/PlayFabAuthenticationAuthApi.h>
#include <playfab/PlayFabClientDataModels.h>

namespace PlayFabUnit
{

void AutoGenAdminTests::FillPlayFabAdminAbortTaskInstanceRequest( PlayFab::AdminModels::AbortTaskInstanceRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"TaskInstanceId\": \"E52531B47B1761C7-4\"}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminAddLocalizedNewsRequest( PlayFab::AdminModels::AddLocalizedNewsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"NewsId\": \"74623b12-6c80-ee4b-7c3b-58e638aa62bd\", \"Language\": \"en\", \"Title\": \"News of the Day\", \"Body\": \"<b>We have a new object to buy!</b>\"}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminAddNewsRequest( PlayFab::AdminModels::AddNewsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Timestamp\": \"2014-04-06T00:00:00Z\", \"Title\": \"News of the Day\", \"Body\": \"<b>We have a new object to buy!</b>\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminAddNewsResult( PlayFabAdminAddNewsResult* result )
{
    // result.newsId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminAddPlayerTagRequest( PlayFab::AdminModels::AddPlayerTagRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"TagName\": \"MostKilled\"}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminAddServerBuildRequest( PlayFab::AdminModels::AddServerBuildRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildId\": \"5.0.1\", \"CommandLineTemplate\": \"-game_id=<game_id> -game_build_version=<game_build_version> -game_mode=<game_mode> -server_host_domain=<server_host_domain> -server_host_port=<server_host_port> -server_host_region=<server_host_region> -playfab_api_endpoint=<playfab_api_endpoint> -title_secret_key=<title_secret_key> -custom_data=<custom_data> -log_file_path=<log_file_path> -output_files_directory_path=<output_files_directory_path>\", \"ExecutablePath\": \"\\ShooterGame\\Binaries\\Win64\\ShooterGameServer.exe\", \"ActiveRegions\": [ \"USCentral\", \"EUWest\" ], \"Comment\": \"Testing new IAP methods\", \"MaxGamesPerHost\": 5, \"MinFreeGameSlots\": 1}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminAddServerBuildResult( PlayFabAdminAddServerBuildResult* result )
{
    // result.activeRegions = PlayFabAdminRegion const*;
    // result.activeRegionsCount = uint32_t;
    // result.buildId = const char*;
    // result.commandLineTemplate = const char*;
    // result.comment = const char*;
    // result.executablePath = const char*;
    // result.maxGamesPerHost = int32_t;
    // result.minFreeGameSlots = int32_t;
    // result.status = PlayFabAdminGameBuildStatus const*;
    // result.timestamp = time_t;
    // result.titleId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminAddUserVirtualCurrencyRequest( PlayFab::AdminModels::AddUserVirtualCurrencyRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"VirtualCurrency\": \"GC\", \"Amount\": 100}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminModifyUserVirtualCurrencyResult( PlayFabAdminModifyUserVirtualCurrencyResult* result )
{
    // result.balance = int32_t;
    // result.balanceChange = int32_t;
    // result.playFabId = const char*;
    // result.virtualCurrency = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminAddVirtualCurrencyTypesRequest( PlayFab::AdminModels::AddVirtualCurrencyTypesRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"VirtualCurrencies\": [ {  \"CurrencyCode\": \"CC\",  \"DisplayName\": \"Chump Coins\",  \"InitialDeposit\": 100,  \"RechargeRate\": 1000,  \"RechargeMax\": 1000 }, {  \"CurrencyCode\": \"GC\" } ]}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminBanUsersRequest( PlayFab::AdminModels::BanUsersRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Bans\": [ {  \"PlayFabId\": \"1679AF5CD04BD838\",  \"IPAddress\": \"192.168.1.1\",  \"Reason\": \"You cheated!\",  \"DurationInHours\": 7 }, {  \"PlayFabId\": \"2329AF5CD04BF513\",  \"Reason\": \"Caught you using speed hack!\" } ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminBanUsersResult( PlayFabAdminBanUsersResult* result )
{
    // result.banData = PlayFabAdminBanInfo const* const*;
    // result.banDataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminCheckLimitedEditionItemAvailabilityRequest( PlayFab::AdminModels::CheckLimitedEditionItemAvailabilityRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"CatalogVersion\": \"{{PrimaryCatalogName}}\", \"ItemId\": \"FreeHoodie\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminCheckLimitedEditionItemAvailabilityResult( PlayFabAdminCheckLimitedEditionItemAvailabilityResult* result )
{
    // result.amount = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminCreateActionsOnPlayerSegmentTaskRequest( PlayFab::AdminModels::CreateActionsOnPlayerSegmentTaskRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Name\": \"PushNotificationVIP_Halloween\", \"Description\": \"Send push notification to VIP players about Halloween event\", \"IsActive\": false, \"Parameter\": { \"SegmentId\": \"274828AF93F13472\", \"ActionId\": \"898665F02BF5B41E\" }}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminCreateTaskResult( PlayFabAdminCreateTaskResult* result )
{
    // result.taskId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminCreateCloudScriptTaskRequest( PlayFab::AdminModels::CreateCloudScriptTaskRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Name\": \"EnableWeekdayHappyHour\", \"Description\": \"Turn on special pricing for weekday happy hour.\", \"Schedule\": \"0 17 * * 1-5\", \"IsActive\": false, \"Parameter\": { \"FunctionName\": \"applyStorePreset\", \"Argument\": {  \"preset\": \"WeekdayHappyHour\" } }}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminCreateInsightsScheduledScalingTaskRequest( PlayFab::AdminModels::CreateInsightsScheduledScalingTaskRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Name\": \"EnableWeekdayPerformance\", \"Description\": \"Scale up Insights Performance Units during weekdays.\", \"Schedule\": \"0 0 * * 1-5\", \"IsActive\": false, \"Parameter\": { \"Level\": 3 }}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminCreateOpenIdConnectionRequest( PlayFab::AdminModels::CreateOpenIdConnectionRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ConnectionId\": \"oidconnection1\", \"ClientId\": \"example_id_1\", \"ClientSecret\": \"example_secret_1\", \"IssuerInformation\": { \"Issuer\": \"https://issuer.example.com/\", \"AuthorizationUrl\": \"https://issuer.example.com/authorize\", \"TokenUrl\": \"https://issuer.example.com/oauth2/token\", \"JsonWebKeySet\": {  \"keys\": [  \"...\"  ] } }}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminCreatePlayerSharedSecretRequest( PlayFab::AdminModels::CreatePlayerSharedSecretRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"FriendlyName\": \"iOS Users\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminCreatePlayerSharedSecretResult( PlayFabAdminCreatePlayerSharedSecretResult* result )
{
    // result.secretKey = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminCreatePlayerStatisticDefinitionRequest( PlayFab::AdminModels::CreatePlayerStatisticDefinitionRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StatisticName\": \"headshots\", \"VersionChangeInterval\": \"Never\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminCreatePlayerStatisticDefinitionResult( PlayFabAdminCreatePlayerStatisticDefinitionResult* result )
{
    // result.statistic = PlayFabAdminPlayerStatisticDefinition const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminCreateSegmentRequest( PlayFab::AdminModels::CreateSegmentRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SegmentModel\": \"Object\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminCreateSegmentResponse( PlayFabAdminCreateSegmentResponse* result )
{
    // result.errorMessage = const char*;
    // result.segmentId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminDeleteContentRequest( PlayFab::AdminModels::DeleteContentRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Key\": \"images/sword_icon.png\"}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminDeleteMasterPlayerAccountRequest( PlayFab::AdminModels::DeleteMasterPlayerAccountRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"MetaData\": \"Identifying info\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminDeleteMasterPlayerAccountResult( PlayFabAdminDeleteMasterPlayerAccountResult* result )
{
    // result.jobReceiptId = const char*;
    // result.titleIds = const char* const*;
    // result.titleIdsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminDeleteOpenIdConnectionRequest( PlayFab::AdminModels::DeleteOpenIdConnectionRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ConnectionId\": \"oidconnection1\"}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminDeletePlayerRequest( PlayFab::AdminModels::DeletePlayerRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminDeletePlayerSharedSecretRequest( PlayFab::AdminModels::DeletePlayerSharedSecretRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SecretKey\": \"keysaresecret\"}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminDeleteSegmentRequest( PlayFab::AdminModels::DeleteSegmentRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SegmentId\": \"97EF0E9302CBE996\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminDeleteSegmentsResponse( PlayFabAdminDeleteSegmentsResponse* result )
{
    // result.errorMessage = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminDeleteStoreRequest( PlayFab::AdminModels::DeleteStoreRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StoreId\": \"BonusStore\"}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminDeleteTaskRequest( PlayFab::AdminModels::DeleteTaskRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Identifier\": { \"Id\": \"E1772FD927D8539D\" }}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminDeleteTitleDataOverrideRequest( PlayFab::AdminModels::DeleteTitleDataOverrideRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"OverrideLabel\": \"LaunchData\"}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminExportMasterPlayerDataRequest( PlayFab::AdminModels::ExportMasterPlayerDataRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminExportMasterPlayerDataResult( PlayFabAdminExportMasterPlayerDataResult* result )
{
    // result.jobReceiptId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetTaskInstanceRequest( PlayFab::AdminModels::GetTaskInstanceRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"TaskInstanceId\": \"E52531B47B1761C7-4\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetActionsOnPlayersInSegmentTaskInstanceResult( PlayFabAdminGetActionsOnPlayersInSegmentTaskInstanceResult* result )
{
    // result.parameter = PlayFabAdminActionsOnPlayersInSegmentTaskParameter const*;
    // result.summary = PlayFabAdminActionsOnPlayersInSegmentTaskSummary const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetAllSegmentsResult( PlayFabAdminGetAllSegmentsResult* result )
{
    // result.segments = PlayFabAdminGetSegmentResult const* const*;
    // result.segmentsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetCatalogItemsRequest( PlayFab::AdminModels::GetCatalogItemsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"CatalogVersion\": \"{{PrimaryCatalogName}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetCatalogItemsResult( PlayFabAdminGetCatalogItemsResult* result )
{
    // result.catalog = PlayFabAdminCatalogItem const* const*;
    // result.catalogCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetCloudScriptRevisionRequest( PlayFab::AdminModels::GetCloudScriptRevisionRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Version\": 1, \"Revision\": 3}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetCloudScriptRevisionResult( PlayFabAdminGetCloudScriptRevisionResult* result )
{
    // result.createdAt = time_t;
    // result.files = PlayFabAdminCloudScriptFile const* const*;
    // result.filesCount = uint32_t;
    // result.isPublished = bool;
    // result.revision = int32_t;
    // result.version = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetCloudScriptTaskInstanceResult( PlayFabAdminGetCloudScriptTaskInstanceResult* result )
{
    // result.parameter = PlayFabAdminCloudScriptTaskParameter const*;
    // result.summary = PlayFabAdminCloudScriptTaskSummary const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetCloudScriptVersionsResult( PlayFabAdminGetCloudScriptVersionsResult* result )
{
    // result.versions = PlayFabAdminCloudScriptVersionStatus const* const*;
    // result.versionsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetContentListRequest( PlayFab::AdminModels::GetContentListRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Prefix\": \"2016/1\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetContentListResult( PlayFabAdminGetContentListResult* result )
{
    // result.contents = PlayFabAdminContentInfo const* const*;
    // result.contentsCount = uint32_t;
    // result.itemCount = int32_t;
    // result.totalSize = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetContentUploadUrlRequest( PlayFab::AdminModels::GetContentUploadUrlRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Key\": \"images/sword_icon.png\", \"ContentType\": \"image/png\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetContentUploadUrlResult( PlayFabAdminGetContentUploadUrlResult* result )
{
    // result.uRL = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetDataReportRequest( PlayFab::AdminModels::GetDataReportRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ReportName\": \"PurchaseDataReport\", \"Year\": 2014, \"Month\": 12, \"Day\": 5}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetDataReportResult( PlayFabAdminGetDataReportResult* result )
{
    // result.downloadUrl = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetMatchmakerGameInfoRequest( PlayFab::AdminModels::GetMatchmakerGameInfoRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"LobbyId\": \"2938488\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetMatchmakerGameInfoResult( PlayFabAdminGetMatchmakerGameInfoResult* result )
{
    // result.buildVersion = const char*;
    // result.endTime = time_t const*;
    // result.lobbyId = const char*;
    // result.mode = const char*;
    // result.players = const char* const*;
    // result.playersCount = uint32_t;
    // result.region = PlayFabAdminRegion const*;
    // result.serverIPV4Address = const char*;
    // result.serverIPV6Address = const char*;
    // result.serverPort = uint32_t;
    // result.serverPublicDNSName = const char*;
    // result.startTime = time_t;
    // result.titleId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetMatchmakerGameModesRequest( PlayFab::AdminModels::GetMatchmakerGameModesRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildVersion\": \"5.0.1\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetMatchmakerGameModesResult( PlayFabAdminGetMatchmakerGameModesResult* result )
{
    // result.gameModes = PlayFabAdminGameModeInfo const* const*;
    // result.gameModesCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetPlayedTitleListRequest( PlayFab::AdminModels::GetPlayedTitleListRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetPlayedTitleListResult( PlayFabAdminGetPlayedTitleListResult* result )
{
    // result.titleIds = const char* const*;
    // result.titleIdsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetPlayerIdFromAuthTokenRequest( PlayFab::AdminModels::GetPlayerIdFromAuthTokenRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Token\": \"3F584AD0EF943E2\", \"TokenType\": \"Email\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetPlayerIdFromAuthTokenResult( PlayFabAdminGetPlayerIdFromAuthTokenResult* result )
{
    // result.playFabId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetPlayerProfileRequest( PlayFab::AdminModels::GetPlayerProfileRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetPlayerProfileResult( PlayFabAdminGetPlayerProfileResult* result )
{
    // result.playerProfile = PlayFabPlayerProfileModel const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetPlayersSegmentsRequest( PlayFab::AdminModels::GetPlayersSegmentsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetPlayerSegmentsResult( PlayFabAdminGetPlayerSegmentsResult* result )
{
    // result.segments = PlayFabAdminGetSegmentResult const* const*;
    // result.segmentsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetPlayerSharedSecretsResult( PlayFabAdminGetPlayerSharedSecretsResult* result )
{
    // result.sharedSecrets = PlayFabAdminSharedSecret const* const*;
    // result.sharedSecretsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetPlayersInSegmentRequest( PlayFab::AdminModels::GetPlayersInSegmentRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SegmentId\": \"1337AA00\", \"SecondsToLive\": 5, \"MaxBatchSize\": 500}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetPlayersInSegmentResult( PlayFabAdminGetPlayersInSegmentResult* result )
{
    // result.continuationToken = const char*;
    // result.playerProfiles = PlayFabAdminPlayerProfile const* const*;
    // result.playerProfilesCount = uint32_t;
    // result.profilesInSegment = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetPlayerStatisticDefinitionsResult( PlayFabAdminGetPlayerStatisticDefinitionsResult* result )
{
    // result.statistics = PlayFabAdminPlayerStatisticDefinition const* const*;
    // result.statisticsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetPlayerStatisticVersionsRequest( PlayFab::AdminModels::GetPlayerStatisticVersionsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StatisticName\": \"headshots\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetPlayerStatisticVersionsResult( PlayFabAdminGetPlayerStatisticVersionsResult* result )
{
    // result.statisticVersions = PlayFabAdminPlayerStatisticVersion const* const*;
    // result.statisticVersionsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetPlayerTagsRequest( PlayFab::AdminModels::GetPlayerTagsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Namespace\": \"title.AAA\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetPlayerTagsResult( PlayFabAdminGetPlayerTagsResult* result )
{
    // result.playFabId = const char*;
    // result.tags = const char* const*;
    // result.tagsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetPolicyRequest( PlayFab::AdminModels::GetPolicyRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PolicyName\": \"ApiPolicy\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetPolicyResponse( PlayFabAdminGetPolicyResponse* result )
{
    // result.policyName = const char*;
    // result.policyVersion = int32_t;
    // result.statements = PlayFabAdminPermissionStatement const* const*;
    // result.statementsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetPublisherDataRequest( PlayFab::AdminModels::GetPublisherDataRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Keys\": [ \"color\", \"propertyA\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetPublisherDataResult( PlayFabAdminGetPublisherDataResult* result )
{
    // result.data = struct PlayFabStringDictionaryEntry const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetRandomResultTablesRequest( PlayFab::AdminModels::GetRandomResultTablesRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetRandomResultTablesResult( PlayFabAdminGetRandomResultTablesResult* result )
{
    // result.tables = struct PlayFabAdminRandomResultTableListingDictionaryEntry const*;
    // result.tablesCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetSegmentsRequest( PlayFab::AdminModels::GetSegmentsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SegmentIds\": [ \"B05FC8CB558A6570\", \"97EF0E9302CBE996\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetSegmentsResponse( PlayFabAdminGetSegmentsResponse* result )
{
    // result.errorMessage = const char*;
    // result.segments = PlayFabAdminSegmentModel const* const*;
    // result.segmentsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetServerBuildInfoRequest( PlayFab::AdminModels::GetServerBuildInfoRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildId\": \"5.0.1\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetServerBuildInfoResult( PlayFabAdminGetServerBuildInfoResult* result )
{
    // result.activeRegions = PlayFabAdminRegion const*;
    // result.activeRegionsCount = uint32_t;
    // result.buildId = const char*;
    // result.comment = const char*;
    // result.errorMessage = const char*;
    // result.maxGamesPerHost = int32_t;
    // result.minFreeGameSlots = int32_t;
    // result.status = PlayFabAdminGameBuildStatus const*;
    // result.timestamp = time_t;
    // result.titleId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetServerBuildUploadURLRequest( PlayFab::AdminModels::GetServerBuildUploadURLRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildId\": \"5.0.1\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetServerBuildUploadURLResult( PlayFabAdminGetServerBuildUploadURLResult* result )
{
    // result.uRL = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetStoreItemsRequest( PlayFab::AdminModels::GetStoreItemsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StoreId\": \"BonusStore\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetStoreItemsResult( PlayFabAdminGetStoreItemsResult* result )
{
    // result.catalogVersion = const char*;
    // result.marketingData = PlayFabAdminStoreMarketingModel const*;
    // result.source = PlayFabAdminSourceType const*;
    // result.store = PlayFabAdminStoreItem const* const*;
    // result.storeCount = uint32_t;
    // result.storeId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetTaskInstancesRequest( PlayFab::AdminModels::GetTaskInstancesRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StatusFilter\": \"Failed\", \"StartedAtRangeFrom\": \"2016-08-23T11:00:00Z\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetTaskInstancesResult( PlayFabAdminGetTaskInstancesResult* result )
{
    // result.summaries = PlayFabAdminTaskInstanceBasicSummary const* const*;
    // result.summariesCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetTasksRequest( PlayFab::AdminModels::GetTasksRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Identifier\": { \"Name\": \"EnableDailyHappyHour\" }}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetTasksResult( PlayFabAdminGetTasksResult* result )
{
    // result.tasks = PlayFabAdminScheduledTask const* const*;
    // result.tasksCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetTitleDataRequest( PlayFab::AdminModels::GetTitleDataRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Keys\": [ \"color\", \"propertyA\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetTitleDataResult( PlayFabAdminGetTitleDataResult* result )
{
    // result.data = struct PlayFabStringDictionaryEntry const*;
    // result.dataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminLookupUserAccountInfoRequest( PlayFab::AdminModels::LookupUserAccountInfoRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"IgnoreMissingTitleActivation\": false}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminLookupUserAccountInfoResult( PlayFabAdminLookupUserAccountInfoResult* result )
{
    // result.userInfo = PlayFabUserAccountInfo const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetUserBansRequest( PlayFab::AdminModels::GetUserBansRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetUserBansResult( PlayFabAdminGetUserBansResult* result )
{
    // result.banData = PlayFabAdminBanInfo const* const*;
    // result.banDataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetUserDataRequest( PlayFab::AdminModels::GetUserDataRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Keys\": [ \"preferences\", \"progress\" ], \"IfChangedFromDataVersion\": 13}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetUserDataResult( PlayFabAdminGetUserDataResult* result )
{
    // result.data = struct PlayFabUserDataRecordDictionaryEntry const*;
    // result.dataCount = uint32_t;
    // result.dataVersion = uint32_t;
    // result.playFabId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminGetUserInventoryRequest( PlayFab::AdminModels::GetUserInventoryRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGetUserInventoryResult( PlayFabAdminGetUserInventoryResult* result )
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

void AutoGenAdminTests::FillPlayFabAdminGrantItemsToUsersRequest( PlayFab::AdminModels::GrantItemsToUsersRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"CatalogVersion\": \"{{PrimaryCatalogName}}\", \"ItemGrants\": [ {  \"PlayFabId\": \"20394883\",  \"ItemId\": \"shield_level_1\",  \"Annotation\": \"Entered Level 2\" }, {  \"PlayFabId\": \"20394883\",  \"ItemId\": \"shield_level_2\",  \"Annotation\": \"Entered Level 2\",  \"Data\": {  \"Equipped\": \"True\",  \"Slot\": \"Head\"  } } ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminGrantItemsToUsersResult( PlayFabAdminGrantItemsToUsersResult* result )
{
    // result.itemGrantResults = PlayFabAdminGrantedItemInstance const* const*;
    // result.itemGrantResultsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminIncrementLimitedEditionItemAvailabilityRequest( PlayFab::AdminModels::IncrementLimitedEditionItemAvailabilityRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"CatalogVersion\": \"{{PrimaryCatalogName}}\", \"ItemId\": \"FreeHoodie\", \"Amount\": 50}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminIncrementPlayerStatisticVersionRequest( PlayFab::AdminModels::IncrementPlayerStatisticVersionRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StatisticName\": \"headshots\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminIncrementPlayerStatisticVersionResult( PlayFabAdminIncrementPlayerStatisticVersionResult* result )
{
    // result.statisticVersion = PlayFabAdminPlayerStatisticVersion const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminListOpenIdConnectionResponse( PlayFabAdminListOpenIdConnectionResponse* result )
{
    // result.connections = PlayFabAdminOpenIdConnection const* const*;
    // result.connectionsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminListBuildsResult( PlayFabAdminListBuildsResult* result )
{
    // result.builds = PlayFabAdminGetServerBuildInfoResult const* const*;
    // result.buildsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminListVirtualCurrencyTypesResult( PlayFabAdminListVirtualCurrencyTypesResult* result )
{
    // result.virtualCurrencies = PlayFabAdminVirtualCurrencyData const* const*;
    // result.virtualCurrenciesCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminModifyMatchmakerGameModesRequest( PlayFab::AdminModels::ModifyMatchmakerGameModesRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildVersion\": \"5.0.1\", \"GameModes\": [ {  \"Gamemode\": \"0\",  \"MinPlayerCount\": 2,  \"MaxPlayerCount\": 25 }, {  \"Gamemode\": \"1\",  \"MinPlayerCount\": 4,  \"MaxPlayerCount\": 35,  \"StartOpen\": false } ]}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminModifyServerBuildRequest( PlayFab::AdminModels::ModifyServerBuildRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildId\": \"5.0.1\", \"Timestamp\": \"2014-03-24T00:00:00Z\", \"ActiveRegions\": [ \"USCentral\", \"EUWest\" ], \"MaxGamesPerHost\": 5, \"MinFreeGameSlots\": 2, \"ExecutablePath\": \"\\ShooterGame\\Binaries\\Win64\\ShooterGameServer.exe\", \"Comment\": \"Testing new IAP methods\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminModifyServerBuildResult( PlayFabAdminModifyServerBuildResult* result )
{
    // result.activeRegions = PlayFabAdminRegion const*;
    // result.activeRegionsCount = uint32_t;
    // result.buildId = const char*;
    // result.commandLineTemplate = const char*;
    // result.comment = const char*;
    // result.executablePath = const char*;
    // result.maxGamesPerHost = int32_t;
    // result.minFreeGameSlots = int32_t;
    // result.status = PlayFabAdminGameBuildStatus const*;
    // result.timestamp = time_t;
    // result.titleId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminRefundPurchaseRequest( PlayFab::AdminModels::RefundPurchaseRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"OrderId\": \"B456AE0\", \"Reason\": \"Customer Request\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminRefundPurchaseResponse( PlayFabAdminRefundPurchaseResponse* result )
{
    // result.purchaseStatus = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminRemovePlayerTagRequest( PlayFab::AdminModels::RemovePlayerTagRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"TagName\": \"MostKilled\"}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminRemoveServerBuildRequest( PlayFab::AdminModels::RemoveServerBuildRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildId\": \"5.0.1\"}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminRemoveVirtualCurrencyTypesRequest( PlayFab::AdminModels::RemoveVirtualCurrencyTypesRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"VirtualCurrencies\": [ {  \"CurrencyCode\": \"CC\" }, {  \"CurrencyCode\": \"GC\" } ]}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminResetCharacterStatisticsRequest( PlayFab::AdminModels::ResetCharacterStatisticsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"CharacterId\": \"{{CharacterId}}\"}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminResetPasswordRequest( PlayFab::AdminModels::ResetPasswordRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Token\": \"2B584FA1DF645E4\", \"Password\": \"Password12345F00B@r\"}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminResetUserStatisticsRequest( PlayFab::AdminModels::ResetUserStatisticsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminResolvePurchaseDisputeRequest( PlayFab::AdminModels::ResolvePurchaseDisputeRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"OrderId\": \"B456AE0\", \"Reason\": \"Customer Request\", \"Outcome\": \"Reinstate\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminResolvePurchaseDisputeResponse( PlayFabAdminResolvePurchaseDisputeResponse* result )
{
    // result.purchaseStatus = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminRevokeAllBansForUserRequest( PlayFab::AdminModels::RevokeAllBansForUserRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminRevokeAllBansForUserResult( PlayFabAdminRevokeAllBansForUserResult* result )
{
    // result.banData = PlayFabAdminBanInfo const* const*;
    // result.banDataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminRevokeBansRequest( PlayFab::AdminModels::RevokeBansRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BanIds\": [ \"E0B5FF89542D413C\", \"EF43FF89542G1546\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminRevokeBansResult( PlayFabAdminRevokeBansResult* result )
{
    // result.banData = PlayFabAdminBanInfo const* const*;
    // result.banDataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminRevokeInventoryItemRequest( PlayFab::AdminModels::RevokeInventoryItemRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"ItemInstanceId\": \"2048583045\"}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminRevokeInventoryItemsRequest( PlayFab::AdminModels::RevokeInventoryItemsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Items\": [ {  \"PlayFabId\": \"203945882\",  \"ItemInstanceId\": \"2048583045\" } ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminRevokeInventoryItemsResult( PlayFabAdminRevokeInventoryItemsResult* result )
{
    // result.errors = PlayFabAdminRevokeItemError const* const*;
    // result.errorsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminRunTaskRequest( PlayFab::AdminModels::RunTaskRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Identifier\": { \"Id\": \"E1772FD927D8539D\" }}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminRunTaskResult( PlayFabAdminRunTaskResult* result )
{
    // result.taskInstanceId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminSendAccountRecoveryEmailRequest( PlayFab::AdminModels::SendAccountRecoveryEmailRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Email\": \"assignedemail@here.com\", \"EmailTemplateId\": \"D53AB15D8F12E330\"}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminUpdateCatalogItemsRequest( PlayFab::AdminModels::UpdateCatalogItemsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"CatalogVersion\": \"{{PrimaryCatalogName}}\", \"Catalog\": [ {  \"ItemId\": \"shield_level_5\",  \"ItemClass\": \"shields\",  \"DisplayName\": \"Level 5 Shield\",  \"Description\": \"Strong defense against projectile attacks\",  \"VirtualCurrencyPrices\": {  \"RM\": 199,  \"GV\": 25  },  \"RealCurrencyPrices\": {  \"GBP\": 149,  \"EUR\": 169  },  \"CanBecomeCharacter\": false,  \"IsStackable\": false,  \"IsTradable\": false,  \"IsLimitedEdition\": false,  \"InitialLimitedEditionCount\": 0 }, {  \"ItemId\": \"energy_boost_1\",  \"ItemClass\": \"boosts\",  \"DisplayName\": \"Energy Drink Six-Pack\",  \"Description\": \"Get a quick burst of energy whenever you need it\",  \"VirtualCurrencyPrices\": {  \"RM\": 199,  \"GV\": 25  },  \"CanBecomeCharacter\": false,  \"IsStackable\": false,  \"IsTradable\": false,  \"IsLimitedEdition\": false,  \"InitialLimitedEditionCount\": 0 }, {  \"ItemId\": \"required_item_for_grant_a_1\",  \"ItemClass\": \"sets\",  \"DisplayName\": \"Grant Set Item 1\",  \"Description\": \"Item 1 from the set of items needed to get Granted Item A for free\",  \"VirtualCurrencyPrices\": {  \"RM\": 249,  \"GV\": 1500  },  \"CanBecomeCharacter\": false,  \"IsStackable\": false,  \"IsTradable\": false,  \"IsLimitedEdition\": false,  \"InitialLimitedEditionCount\": 0 }, {  \"ItemId\": \"required_item_for_grant_a_2\",  \"ItemClass\": \"sets\",  \"DisplayName\": \"Grant Set Item 2\",  \"Description\": \"Item 2 from the set of items needed to get Granted Item A for free\",  \"VirtualCurrencyPrices\": {  \"RM\": 249,  \"GV\": 1500  },  \"CanBecomeCharacter\": false,  \"IsStackable\": false,  \"IsTradable\": false,  \"IsLimitedEdition\": false,  \"InitialLimitedEditionCount\": 0 }, {  \"ItemId\": \"required_item_for_grant_a_3\",  \"ItemClass\": \"sets\",  \"DisplayName\": \"Grant Set Item 3\",  \"Description\": \"Item 3 from the set of items needed to get Granted Item A for free\",  \"VirtualCurrencyPrices\": {  \"RM\": 249,  \"GV\": 1500  },  \"CanBecomeCharacter\": false,  \"IsStackable\": false,  \"IsTradable\": false,  \"IsLimitedEdition\": false,  \"InitialLimitedEditionCount\": 0 }, {  \"ItemId\": \"required_item_for_grant_a_4\",  \"ItemClass\": \"sets\",  \"DisplayName\": \"Grant Set Item 4\",  \"Description\": \"Item 4 from the set of items needed to get Granted Item A for free\",  \"VirtualCurrencyPrices\": {  \"RM\": 249,  \"GV\": 1500  },  \"CanBecomeCharacter\": false,  \"IsStackable\": false,  \"IsTradable\": false,  \"IsLimitedEdition\": false,  \"InitialLimitedEditionCount\": 0 }, {  \"ItemId\": \"granted_item_a\",  \"ItemClass\": \"sets\",  \"DisplayName\": \"Granted Item A\",  \"Description\": \"Bonus item granted for free once the full set of 4 Grant Set items are collected\",  \"CanBecomeCharacter\": false,  \"IsStackable\": false,  \"IsTradable\": false,  \"IsLimitedEdition\": false,  \"InitialLimitedEditionCount\": 0 }, {  \"ItemId\": \"consumable_item_1\",  \"ItemClass\": \"Consumables\",  \"DisplayName\": \"Consumable Item 1\",  \"Description\": \"Item demonstrating usage-based consumables\",  \"VirtualCurrencyPrices\": {  \"GV\": 500  },  \"Consumable\": {  \"UsageCount\": 3  },  \"CanBecomeCharacter\": false,  \"IsStackable\": false,  \"IsTradable\": false,  \"IsLimitedEdition\": false,  \"InitialLimitedEditionCount\": 0 }, {  \"ItemId\": \"consumable_item_2\",  \"ItemClass\": \"Consumables\",  \"DisplayName\": \"Consumable Item 2\",  \"Description\": \"Item demonstrating time-based consumables\",  \"VirtualCurrencyPrices\": {  \"GV\": 750  },  \"Consumable\": {  \"UsagePeriod\": 3600,  \"UsagePeriodGroup\": \"usage_group_1\"  },  \"CanBecomeCharacter\": false,  \"IsStackable\": false,  \"IsTradable\": false,  \"IsLimitedEdition\": false,  \"InitialLimitedEditionCount\": 0 }, {  \"ItemId\": \"sub_bundle_item_1\",  \"ItemClass\": \"Bundles\",  \"DisplayName\": \"Bundled Item 1\",  \"Description\": \"Item which is added to the user inventory as part of a bundle\",  \"CanBecomeCharacter\": false,  \"IsStackable\": false,  \"IsTradable\": false,  \"IsLimitedEdition\": false,  \"InitialLimitedEditionCount\": 0 }, {  \"ItemId\": \"sub_bundle_item_2\",  \"ItemClass\": \"Bundles\",  \"DisplayName\": \"Bundled Item 2\",  \"Description\": \"Item which is added to the user inventory as part of a bundle\",  \"CanBecomeCharacter\": false,  \"IsStackable\": false,  \"IsTradable\": false,  \"IsLimitedEdition\": false,  \"InitialLimitedEditionCount\": 0 }, {  \"ItemId\": \"item_bundle_1\",  \"ItemClass\": \"Bundles\",  \"DisplayName\": \"Item bundle 1\",  \"Description\": \"Item which, when added to the user inventory, also adds other bundled items\",  \"VirtualCurrencyPrices\": {  \"RM\": 599  },  \"Bundle\": {  \"BundledItems\": [   \"sub_bundle_item_1\",   \"sub_bundle_item_2\"  ],  \"BundledResultTables\": [   \"random_result_1\"  ],  \"BundledVirtualCurrencies\": {   \"GV\": 1000  }  },  \"CanBecomeCharacter\": false,  \"IsStackable\": false,  \"IsTradable\": false,  \"IsLimitedEdition\": false,  \"InitialLimitedEditionCount\": 0 }, {  \"ItemId\": \"key_item_1\",  \"ItemClass\": \"Containers\",  \"DisplayName\": \"Key Item 1\",  \"Description\": \"Key used to unlock Container 1\",  \"VirtualCurrencyPrices\": {  \"RM\": 199  },  \"CanBecomeCharacter\": false,  \"IsStackable\": false,  \"IsTradable\": false,  \"IsLimitedEdition\": false,  \"InitialLimitedEditionCount\": 0 }, {  \"ItemId\": \"sub_container_item_1\",  \"ItemClass\": \"Containers\",  \"DisplayName\": \"Container Item 1\",  \"Description\": \"Item which is added to the user inventory as part of opening a container\",  \"CanBecomeCharacter\": false,  \"IsStackable\": false,  \"IsTradable\": false,  \"IsLimitedEdition\": false,  \"InitialLimitedEditionCount\": 0 }, {  \"ItemId\": \"sub_container_item_2\",  \"ItemClass\": \"Containers\",  \"DisplayName\": \"Container Item 2\",  \"Description\": \"Item which is added to the user inventory as part of opening a container\",  \"CanBecomeCharacter\": false,  \"IsStackable\": false,  \"IsTradable\": false,  \"IsLimitedEdition\": false,  \"InitialLimitedEditionCount\": 0 }, {  \"ItemId\": \"item_container_1\",  \"ItemClass\": \"Containers\",  \"DisplayName\": \"Item Container 1\",  \"Description\": \"Item which, when opened with Key Item 1, also adds the items it holds to the user inventory\",  \"VirtualCurrencyPrices\": {  \"RM\": 499  },  \"Consumable\": {  \"UsageCount\": 1  },  \"Container\": {  \"KeyItemId\": \"key_item_1\",  \"ItemContents\": [   \"sub_container_item_1\",   \"sub_container_item_2\"  ],  \"ResultTableContents\": [   \"random_result_1\"  ],  \"VirtualCurrencyContents\": {   \"GV\": 1000  }  },  \"CanBecomeCharacter\": false,  \"IsStackable\": false,  \"IsTradable\": false,  \"IsLimitedEdition\": false,  \"InitialLimitedEditionCount\": 0 }, {  \"ItemId\": \"item_container_2\",  \"ItemClass\": \"Containers\",  \"DisplayName\": \"Item Container 2\",  \"Description\": \"Item which, when opened (no key needed), adds the items it holds to the user inventory\",  \"VirtualCurrencyPrices\": {  \"RM\": 99  },  \"Consumable\": {  \"UsageCount\": 1  },  \"Container\": {  \"VirtualCurrencyContents\": {   \"GV\": 1000  }  },  \"CanBecomeCharacter\": false,  \"IsStackable\": false,  \"IsTradable\": false,  \"IsLimitedEdition\": false,  \"InitialLimitedEditionCount\": 0 }, {  \"ItemId\": \"starterpack_1\",  \"ItemClass\": \"starterpacks\",  \"DisplayName\": \"Super Starter Pack\",  \"Description\": \"Everything you need to get started fast track at the right price\",  \"CanBecomeCharacter\": false,  \"IsStackable\": false,  \"IsTradable\": false,  \"IsLimitedEdition\": false,  \"InitialLimitedEditionCount\": 0 } ]}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminSetPlayerSecretRequest( PlayFab::AdminModels::SetPlayerSecretRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayerSecret\": \"secretkeyforthisplayer\", \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminSetPublishedRevisionRequest( PlayFab::AdminModels::SetPublishedRevisionRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Version\": 1, \"Revision\": 3}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminSetPublisherDataRequest( PlayFab::AdminModels::SetPublisherDataRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Key\": \"Running Speed\", \"Value\": \"1.03\"}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminUpdateStoreItemsRequest( PlayFab::AdminModels::UpdateStoreItemsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StoreId\": \"BonusStore\", \"Store\": [ {  \"ItemId\": \"shield_level_5\",  \"VirtualCurrencyPrices\": {  \"RM\": 180,  \"GV\": 20  },  \"RealCurrencyPrices\": {  \"GBP\": 100  } }, {  \"ItemId\": \"energy_boost_1\",  \"VirtualCurrencyPrices\": {  \"RM\": 250,  \"GV\": 30  } }, {  \"ItemId\": \"starterpack_1\",  \"VirtualCurrencyPrices\": {  \"RM\": 399  } } ]}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminSetTitleDataRequest( PlayFab::AdminModels::SetTitleDataRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Key\": \"Running Speed\", \"Value\": \"1.03\"}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminSetTitleDataAndOverridesRequest( PlayFab::AdminModels::SetTitleDataAndOverridesRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"OverrideLabel\": \"Holiday title data\", \"KeyValues\": [ {  \"Key\": \"Running Speed\",  \"Value\": \"1.03\" }, {  \"Key\": \"Walking Speed\",  \"Value\": \"0.05\" } ]}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminSetupPushNotificationRequest( PlayFab::AdminModels::SetupPushNotificationRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Name\": \"My Game\", \"Platform\": \"APNS_SANDBOX\", \"Key\": \"MyKey123\", \"Credential\": \"MyCredentialsXYZ\", \"OverwriteOldARN\": false}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminSetupPushNotificationResult( PlayFabAdminSetupPushNotificationResult* result )
{
    // result.aRN = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminSubtractUserVirtualCurrencyRequest( PlayFab::AdminModels::SubtractUserVirtualCurrencyRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"VirtualCurrency\": \"GC\", \"Amount\": 100}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminUpdateBansRequest( PlayFab::AdminModels::UpdateBansRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Bans\": [ {  \"BanId\": \"E0B5FF89542D413C\",  \"Permanent\": true,  \"Active\": true }, {  \"BanId\": \"EF43FF89542G1546\",  \"Reason\": \"Royal pardon\",  \"Expires\": \"2016-07-04T00:00:00Z\" } ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminUpdateBansResult( PlayFabAdminUpdateBansResult* result )
{
    // result.banData = PlayFabAdminBanInfo const* const*;
    // result.banDataCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminUpdateCloudScriptRequest( PlayFab::AdminModels::UpdateCloudScriptRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"CustomTags\": \"String\", \"DeveloperPlayFabId\": \"String\", \"Files\": \"Object\", \"Publish\": \"Boolean\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminUpdateCloudScriptResult( PlayFabAdminUpdateCloudScriptResult* result )
{
    // result.revision = int32_t;
    // result.version = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminUpdateOpenIdConnectionRequest( PlayFab::AdminModels::UpdateOpenIdConnectionRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ConnectionId\": \"oidconnection1\", \"ClientSecret\": \"new_example_secret\"}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminUpdatePlayerSharedSecretRequest( PlayFab::AdminModels::UpdatePlayerSharedSecretRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SecretKey\": \"keysaresecret\", \"FriendlyName\": \"XBox Users\", \"Disabled\": false}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminUpdatePlayerStatisticDefinitionRequest( PlayFab::AdminModels::UpdatePlayerStatisticDefinitionRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"StatisticName\": \"headshots\", \"VersionChangeInterval\": \"Day\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminUpdatePlayerStatisticDefinitionResult( PlayFabAdminUpdatePlayerStatisticDefinitionResult* result )
{
    // result.statistic = PlayFabAdminPlayerStatisticDefinition const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminUpdatePolicyRequest( PlayFab::AdminModels::UpdatePolicyRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PolicyName\": \"ApiPolicy\", \"Statements\": [ {  \"Resource\": \"pfrn:api--*\",  \"Action\": \"*\",  \"Effect\": \"Allow\",  \"Principal\": \"*\",  \"Comment\": \"The default allow all policy\" }, {  \"Resource\": \"pfrn:api--/Client/ConfirmPurchase\",  \"Action\": \"*\",  \"Effect\": \"Allow\",  \"Principal\": \"*\",  \"Comment\": \"This statement allows only request to ConfirmPurchase\" } ], \"OverwritePolicy\": false, \"PolicyVersion\": 0}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminUpdatePolicyResponse( PlayFabAdminUpdatePolicyResponse* result )
{
    // result.policyName = const char*;
    // result.statements = PlayFabAdminPermissionStatement const* const*;
    // result.statementsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminUpdateRandomResultTablesRequest( PlayFab::AdminModels::UpdateRandomResultTablesRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Tables\": [ {  \"TableId\": \"DropTable 1\",  \"Nodes\": [  {   \"ResultItemType\": \"ItemId\",   \"ResultItem\": \"Gold Crown 1\",   \"Weight\": 20  },  {   \"ResultItemType\": \"ItemId\",   \"ResultItem\": \"Magic Sword 3\",   \"Weight\": 50  },  {   \"ResultItemType\": \"ItemId\",   \"ResultItem\": \"Clear Shield 3\",   \"Weight\": 70  }  ] } ]}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminUpdateSegmentRequest( PlayFab::AdminModels::UpdateSegmentRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SegmentModel\": \"Object\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminUpdateSegmentResponse( PlayFabAdminUpdateSegmentResponse* result )
{
    // result.errorMessage = const char*;
    // result.segmentId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminUpdateTaskRequest( PlayFab::AdminModels::UpdateTaskRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Identifier\": { \"Name\": \"PushEventNotificationVIP_Halloween\" }, \"Name\": \"PushEventNotificationVIP_Thanksgiving\", \"Description\": \"Send push notification to VIP about Thanksgiving event\", \"IsActive\": false, \"Type\": \"ActionsOnPlayerSegment\", \"Parameter\": { \"SegmentId\": \"E2B0F9C19B02D796\", \"ActionId\": \"DEC740F924D304C6\" }}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminUpdateUserDataRequest( PlayFab::AdminModels::UpdateUserDataRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }, \"Permission\": \"Public\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminUpdateUserDataResult( PlayFabAdminUpdateUserDataResult* result )
{
    // result.dataVersion = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenAdminTests::FillPlayFabAdminUpdateUserInternalDataRequest( PlayFab::AdminModels::UpdateUserInternalDataRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Data\": { \"Class\": \"Fighter\", \"Gender\": \"Female\", \"Icon\": \"Guard 3\", \"Theme\": \"Colorful\" }}" );
    request->FromJson(inputJson);
}

void AutoGenAdminTests::FillPlayFabAdminUpdateUserTitleDisplayNameRequest( PlayFab::AdminModels::UpdateUserTitleDisplayNameRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"DisplayName\": \"New Display Name\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAdminTests::ValidatePlayFabAdminUpdateUserTitleDisplayNameResult( PlayFabAdminUpdateUserTitleDisplayNameResult* result )
{
    // result.displayName = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

 

}
