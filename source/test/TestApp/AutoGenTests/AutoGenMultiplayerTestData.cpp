#include "TestAppPch.h"
#include "TestContext.h"
#include "TestApp.h"
#include "AutoGenMultiplayerTests.h"
#include "XAsyncHelper.h"
#include <playfab/PlayFabClientAuthApi.h>
#include <playfab/PlayFabClientApi.h>
#include <playfab/PlayFabProfilesApi.h>
#include <playfab/PlayFabAdminApi.h>
#include <playfab/PlayFabAuthenticationAuthApi.h>
#include <playfab/PlayFabClientDataModels.h>

namespace PlayFabUnit
{

void AutoGenMultiplayerTests::FillPlayFabMultiplayerCancelAllMatchmakingTicketsForPlayerRequest( PlayFab::MultiplayerModels::CancelAllMatchmakingTicketsForPlayerRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Entity\": { \"Id\": \"123123123\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }, \"QueueName\": \"custom123\"}" );
    request->FromJson(inputJson);
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerCancelAllServerBackfillTicketsForPlayerRequest( PlayFab::MultiplayerModels::CancelAllServerBackfillTicketsForPlayerRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Entity\": { \"Id\": \"123123123\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }, \"QueueName\": \"custom123\"}" );
    request->FromJson(inputJson);
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerCancelMatchmakingTicketRequest( PlayFab::MultiplayerModels::CancelMatchmakingTicketRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"TicketId\": \"1c4b0daa-150e-47ae-9923-d770c0f9b07c\", \"QueueName\": \"custom123\"}" );
    request->FromJson(inputJson);
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerCancelServerBackfillTicketRequest( PlayFab::MultiplayerModels::CancelServerBackfillTicketRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"TicketId\": \"1c4b0daa-150e-47ae-9923-d770c0f9b07c\", \"QueueName\": \"custom123\"}" );
    request->FromJson(inputJson);
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerCreateBuildAliasRequest( PlayFab::MultiplayerModels::CreateBuildAliasRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"AliasName\": \"AliasName\", \"BuildSelectionCriteria\": [ {  \"BuildWeightDistribution\": {  \"53781fa8-006d-4e9c-b733-57433d579285\": 1  } } ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerBuildAliasDetailsResponse( PlayFabMultiplayerBuildAliasDetailsResponse* result )
{
    // result.aliasId = const char*;
    // result.aliasName = const char*;
    // result.buildSelectionCriteria = PlayFabMultiplayerBuildSelectionCriterion const* const*;
    // result.buildSelectionCriteriaCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerCreateBuildWithCustomContainerRequest( PlayFab::MultiplayerModels::CreateBuildWithCustomContainerRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ContainerRunCommand\": \"/data/Assets -startserver\", \"GameAssetReferences\": [ {  \"FileName\": \"gameserver.zip\",  \"MountPath\": \"/data/Assets\" } ], \"ContainerImageReference\": { \"ImageName\": \"ContainerImageName\", \"Tag\": \"ContainerTag\" }, \"LinuxInstrumentationConfiguration\": { \"IsEnabled\": false }, \"ContainerFlavor\": \"CustomLinux\", \"BuildName\": \"GameBuildName\", \"Metadata\": { \"MetadataKey\": \"MetadataValue\" }, \"VmSize\": \"Standard_D2_v2\", \"MultiplayerServerCountPerVm\": 10, \"Ports\": [ {  \"Name\": \"PortName\",  \"Num\": 1243,  \"Protocol\": \"TCP\" } ], \"RegionConfigurations\": [ {  \"Region\": \"EastUs\",  \"MaxServers\": 10,  \"StandbyServers\": 5,  \"ScheduledStandbySettings\": {  \"IsEnabled\": true,  \"ScheduleList\": [   {   \"StartTime\": \"2020-08-21T17:00:00Z\",   \"EndTime\": \"2020-08-24T09:00:00Z\",   \"IsRecurringWeekly\": true,   \"IsDisabled\": false,   \"Description\": \"Weekend Schedule\",   \"TargetStandby\": 8   },   {   \"StartTime\": \"2020-08-24T09:00:00Z\",   \"EndTime\": \"2020-08-28T17:00:00Z\",   \"IsRecurringWeekly\": true,   \"IsDisabled\": false,   \"Description\": \"Weekday Schedule\",   \"TargetStandby\": 3   }  ]  } }, {  \"Region\": \"WestUs\",  \"MaxServers\": 50,  \"StandbyServers\": 8,  \"ScheduledStandbySettings\": {  \"IsEnabled\": true,  \"ScheduleList\": [   {   \"StartTime\": \"2020-08-21T09:00:00Z\",   \"EndTime\": \"2020-08-21T23:00:00Z\",   \"IsRecurringWeekly\": false,   \"IsDisabled\": false,   \"Description\": \"Game Launch\",   \"TargetStandby\": 30   }  ]  } }, {  \"Region\": \"NorthEurope\",  \"MaxServers\": 7,  \"StandbyServers\": 3 } ], \"GameCertificateReferences\": [ {  \"Name\": \"CertName\",  \"GsdkAlias\": \"CertGsdkAlias\" } ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerCreateBuildWithCustomContainerResponse( PlayFabMultiplayerCreateBuildWithCustomContainerResponse* result )
{
    // result.areAssetsReadonly = bool const*;
    // result.buildId = const char*;
    // result.buildName = const char*;
    // result.containerFlavor = PlayFabMultiplayerContainerFlavor const*;
    // result.containerRunCommand = const char*;
    // result.creationTime = time_t const*;
    // result.customGameContainerImage = PlayFabMultiplayerContainerImageReference const*;
    // result.gameAssetReferences = PlayFabMultiplayerAssetReference const* const*;
    // result.gameAssetReferencesCount = uint32_t;
    // result.gameCertificateReferences = PlayFabMultiplayerGameCertificateReference const* const*;
    // result.gameCertificateReferencesCount = uint32_t;
    // result.linuxInstrumentationConfiguration = PlayFabMultiplayerLinuxInstrumentationConfiguration const*;
    // result.metadata = struct PlayFabStringDictionaryEntry const*;
    // result.metadataCount = uint32_t;
    // result.multiplayerServerCountPerVm = int32_t;
    // result.osPlatform = const char*;
    // result.ports = PlayFabMultiplayerPort const* const*;
    // result.portsCount = uint32_t;
    // result.regionConfigurations = PlayFabMultiplayerBuildRegion const* const*;
    // result.regionConfigurationsCount = uint32_t;
    // result.serverType = const char*;
    // result.useStreamingForAssetDownloads = bool const*;
    // result.vmSize = PlayFabMultiplayerAzureVmSize const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerCreateBuildWithManagedContainerRequest( PlayFab::MultiplayerModels::CreateBuildWithManagedContainerRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"AreAssetsReadonly\": \"Boolean\", \"BuildName\": \"String\", \"ContainerFlavor\": \"String\", \"CustomTags\": \"String\", \"GameAssetReferences\": \"Object\", \"GameCertificateReferences\": \"Object\", \"GameWorkingDirectory\": \"String\", \"InstrumentationConfiguration\": \"Object\", \"Metadata\": \"String\", \"MultiplayerServerCountPerVm\": \"Number\", \"Ports\": \"Object\", \"RegionConfigurations\": \"Object\", \"StartMultiplayerServerCommand\": \"String\", \"UseStreamingForAssetDownloads\": \"Boolean\", \"VmSize\": \"String\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerCreateBuildWithManagedContainerResponse( PlayFabMultiplayerCreateBuildWithManagedContainerResponse* result )
{
    // result.areAssetsReadonly = bool const*;
    // result.buildId = const char*;
    // result.buildName = const char*;
    // result.containerFlavor = PlayFabMultiplayerContainerFlavor const*;
    // result.creationTime = time_t const*;
    // result.gameAssetReferences = PlayFabMultiplayerAssetReference const* const*;
    // result.gameAssetReferencesCount = uint32_t;
    // result.gameCertificateReferences = PlayFabMultiplayerGameCertificateReference const* const*;
    // result.gameCertificateReferencesCount = uint32_t;
    // result.gameWorkingDirectory = const char*;
    // result.instrumentationConfiguration = PlayFabMultiplayerInstrumentationConfiguration const*;
    // result.metadata = struct PlayFabStringDictionaryEntry const*;
    // result.metadataCount = uint32_t;
    // result.multiplayerServerCountPerVm = int32_t;
    // result.osPlatform = const char*;
    // result.ports = PlayFabMultiplayerPort const* const*;
    // result.portsCount = uint32_t;
    // result.regionConfigurations = PlayFabMultiplayerBuildRegion const* const*;
    // result.regionConfigurationsCount = uint32_t;
    // result.serverType = const char*;
    // result.startMultiplayerServerCommand = const char*;
    // result.useStreamingForAssetDownloads = bool const*;
    // result.vmSize = PlayFabMultiplayerAzureVmSize const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerCreateBuildWithProcessBasedServerRequest( PlayFab::MultiplayerModels::CreateBuildWithProcessBasedServerRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"OsPlatform\": \"Windows\", \"GameAssetReferences\": [ {  \"FileName\": \"game.zip\" } ], \"StartMultiplayerServerCommand\": \"gameserver.exe -startserver\", \"InstrumentationConfiguration\": { \"ProcessesToMonitor\": [  \"GameServerProcessName\" ] }, \"GameWorkingDirectory\": \"C:\\Assets\", \"IsOSPreview\": false, \"VmSize\": \"Standard_D2_v2\", \"MultiplayerServerCountPerVm\": 10, \"Ports\": [ {  \"Name\": \"PortName\",  \"Num\": 1243,  \"Protocol\": \"TCP\" } ], \"RegionConfigurations\": [ {  \"Region\": \"EastUs\",  \"MaxServers\": 10,  \"StandbyServers\": 5 }, {  \"Region\": \"WestUs\",  \"MaxServers\": 12,  \"StandbyServers\": 8 }, {  \"Region\": \"NorthEurope\",  \"MaxServers\": 7,  \"StandbyServers\": 3 } ], \"GameCertificateReferences\": [ {  \"Name\": \"CertName\",  \"GsdkAlias\": \"CertGsdkAlias\" } ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerCreateBuildWithProcessBasedServerResponse( PlayFabMultiplayerCreateBuildWithProcessBasedServerResponse* result )
{
    // result.areAssetsReadonly = bool const*;
    // result.buildId = const char*;
    // result.buildName = const char*;
    // result.containerFlavor = PlayFabMultiplayerContainerFlavor const*;
    // result.creationTime = time_t const*;
    // result.gameAssetReferences = PlayFabMultiplayerAssetReference const* const*;
    // result.gameAssetReferencesCount = uint32_t;
    // result.gameCertificateReferences = PlayFabMultiplayerGameCertificateReference const* const*;
    // result.gameCertificateReferencesCount = uint32_t;
    // result.gameWorkingDirectory = const char*;
    // result.instrumentationConfiguration = PlayFabMultiplayerInstrumentationConfiguration const*;
    // result.isOSPreview = bool const*;
    // result.metadata = struct PlayFabStringDictionaryEntry const*;
    // result.metadataCount = uint32_t;
    // result.multiplayerServerCountPerVm = int32_t;
    // result.osPlatform = const char*;
    // result.ports = PlayFabMultiplayerPort const* const*;
    // result.portsCount = uint32_t;
    // result.regionConfigurations = PlayFabMultiplayerBuildRegion const* const*;
    // result.regionConfigurationsCount = uint32_t;
    // result.serverType = const char*;
    // result.startMultiplayerServerCommand = const char*;
    // result.useStreamingForAssetDownloads = bool const*;
    // result.vmSize = PlayFabMultiplayerAzureVmSize const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerCreateMatchmakingTicketRequest( PlayFab::MultiplayerModels::CreateMatchmakingTicketRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Creator\": {}, \"MembersToMatchWith\": [], \"GiveUpAfterSeconds\": 100, \"QueueName\": \"custom123\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerCreateMatchmakingTicketResult( PlayFabMultiplayerCreateMatchmakingTicketResult* result )
{
    // result.ticketId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerCreateRemoteUserRequest( PlayFab::MultiplayerModels::CreateRemoteUserRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildId\": \"21781fa8-096d-4d9c-b699-75433d579285\", \"Region\": \"SouthCentralUs\", \"VmId\": \"VmID1\", \"Username\": \"AUsername\", \"ExpirationTime\": \"2014-04-07T09:04:28Z\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerCreateRemoteUserResponse( PlayFabMultiplayerCreateRemoteUserResponse* result )
{
    // result.expirationTime = time_t const*;
    // result.password = const char*;
    // result.username = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerCreateServerBackfillTicketRequest( PlayFab::MultiplayerModels::CreateServerBackfillTicketRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Members\": [], \"GiveUpAfterSeconds\": 100, \"ServerDetails\": { \"IPV4Address\": \"10.250.24.54\", \"Ports\": [  {  \"Name\": \"PortName\",  \"Num\": 1243,  \"Protocol\": \"TCP\"  } ], \"Region\": \"WestUS\", \"Fqdn\": \"vm.azure.cloudapp.net\" }, \"QueueName\": \"custom123\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerCreateServerBackfillTicketResult( PlayFabMultiplayerCreateServerBackfillTicketResult* result )
{
    // result.ticketId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerCreateServerMatchmakingTicketRequest( PlayFab::MultiplayerModels::CreateServerMatchmakingTicketRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Members\": [ null ], \"GiveUpAfterSeconds\": 100, \"QueueName\": \"custom123\"}" );
    request->FromJson(inputJson);
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerCreateTitleMultiplayerServersQuotaChangeRequest( PlayFab::MultiplayerModels::CreateTitleMultiplayerServersQuotaChangeRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ContactEmail\": \"john@mygamestudio.com\", \"StartDate\": \"2020-01-23T00:00:00Z\", \"ChangeDescription\": \"Season 3 Launch\", \"Notes\": \"Based on the last launch, we expect 1 trillion active users.\", \"Changes\": [ {  \"VmFamily\": \"Dv2\",  \"Region\": \"EastUs\",  \"NewCoreLimit\": 55000 }, {  \"VmFamily\": \"Dv2\",  \"Region\": \"NorthCentralUs\",  \"NewCoreLimit\": 65000 } ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerCreateTitleMultiplayerServersQuotaChangeResponse( PlayFabMultiplayerCreateTitleMultiplayerServersQuotaChangeResponse* result )
{
    // result.requestId = const char*;
    // result.wasApproved = bool;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerDeleteAssetRequest( PlayFab::MultiplayerModels::DeleteAssetRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"FileName\": \"gameserver.zip\"}" );
    request->FromJson(inputJson);
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerDeleteBuildRequest( PlayFab::MultiplayerModels::DeleteBuildRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildId\": \"21781fa8-096d-4d9c-b699-75433d579285\"}" );
    request->FromJson(inputJson);
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerDeleteBuildAliasRequest( PlayFab::MultiplayerModels::DeleteBuildAliasRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"AliasId\": \"21781fa8-096d-4d9c-b699-75433d579285\"}" );
    request->FromJson(inputJson);
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerDeleteBuildRegionRequest( PlayFab::MultiplayerModels::DeleteBuildRegionRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildId\": \"21781fa8-096d-4d9c-b699-75433d579285\", \"Region\": \"JapanEast\"}" );
    request->FromJson(inputJson);
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerDeleteCertificateRequest( PlayFab::MultiplayerModels::DeleteCertificateRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Name\": \"GameCertificate1\"}" );
    request->FromJson(inputJson);
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerDeleteContainerImageRequest( PlayFab::MultiplayerModels::DeleteContainerImageRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ImageName\": \"imageName1\"}" );
    request->FromJson(inputJson);
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerDeleteRemoteUserRequest( PlayFab::MultiplayerModels::DeleteRemoteUserRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildId\": \"21781fa8-096d-4d9c-b699-75433d579285\", \"Region\": \"SouthCentralUs\", \"VmId\": \"VmID1\", \"Username\": \"AUsername\"}" );
    request->FromJson(inputJson);
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerEnableMultiplayerServersForTitleRequest( PlayFab::MultiplayerModels::EnableMultiplayerServersForTitleRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerEnableMultiplayerServersForTitleResponse( PlayFabMultiplayerEnableMultiplayerServersForTitleResponse* result )
{
    // result.status = PlayFabMultiplayerTitleMultiplayerServerEnabledStatus const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerGetAssetUploadUrlRequest( PlayFab::MultiplayerModels::GetAssetUploadUrlRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"FileName\": \"gameserver.zip\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerGetAssetUploadUrlResponse( PlayFabMultiplayerGetAssetUploadUrlResponse* result )
{
    // result.assetUploadUrl = const char*;
    // result.fileName = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerGetBuildRequest( PlayFab::MultiplayerModels::GetBuildRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildId\": \"53781fa8-006d-4e9c-b733-57433d579285\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerGetBuildResponse( PlayFabMultiplayerGetBuildResponse* result )
{
    // result.areAssetsReadonly = bool const*;
    // result.buildId = const char*;
    // result.buildName = const char*;
    // result.buildStatus = const char*;
    // result.containerFlavor = PlayFabMultiplayerContainerFlavor const*;
    // result.containerRunCommand = const char*;
    // result.creationTime = time_t const*;
    // result.customGameContainerImage = PlayFabMultiplayerContainerImageReference const*;
    // result.gameAssetReferences = PlayFabMultiplayerAssetReference const* const*;
    // result.gameAssetReferencesCount = uint32_t;
    // result.gameCertificateReferences = PlayFabMultiplayerGameCertificateReference const* const*;
    // result.gameCertificateReferencesCount = uint32_t;
    // result.instrumentationConfiguration = PlayFabMultiplayerInstrumentationConfiguration const*;
    // result.metadata = struct PlayFabStringDictionaryEntry const*;
    // result.metadataCount = uint32_t;
    // result.multiplayerServerCountPerVm = int32_t;
    // result.osPlatform = const char*;
    // result.ports = PlayFabMultiplayerPort const* const*;
    // result.portsCount = uint32_t;
    // result.regionConfigurations = PlayFabMultiplayerBuildRegion const* const*;
    // result.regionConfigurationsCount = uint32_t;
    // result.serverType = const char*;
    // result.startMultiplayerServerCommand = const char*;
    // result.useStreamingForAssetDownloads = bool const*;
    // result.vmSize = PlayFabMultiplayerAzureVmSize const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerGetBuildAliasRequest( PlayFab::MultiplayerModels::GetBuildAliasRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"AliasId\": \"21781fa8-096d-4d9c-b699-75433d579285\"}" );
    request->FromJson(inputJson);
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerGetContainerRegistryCredentialsRequest( PlayFab::MultiplayerModels::GetContainerRegistryCredentialsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerGetContainerRegistryCredentialsResponse( PlayFabMultiplayerGetContainerRegistryCredentialsResponse* result )
{
    // result.dnsName = const char*;
    // result.password = const char*;
    // result.username = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerGetMatchRequest( PlayFab::MultiplayerModels::GetMatchRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"MatchId\": \"4e0c5fd7-80e9-4744-b0ce-061a7f067ff5\", \"QueueName\": \"custom123\", \"EscapeObject\": false, \"ReturnMemberAttributes\": false}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerGetMatchResult( PlayFabMultiplayerGetMatchResult* result )
{
    // result.matchId = const char*;
    // result.members = PlayFabMultiplayerMatchmakingPlayerWithTeamAssignment const* const*;
    // result.membersCount = uint32_t;
    // result.regionPreferences = const char* const*;
    // result.regionPreferencesCount = uint32_t;
    // result.serverDetails = PlayFabMultiplayerServerDetails const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerGetMatchmakingTicketRequest( PlayFab::MultiplayerModels::GetMatchmakingTicketRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"TicketId\": \"1c4b0daa-150e-47ae-9923-d770c0f9b07c\", \"QueueName\": \"custom123\", \"EscapeObject\": false}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerGetMatchmakingTicketResult( PlayFabMultiplayerGetMatchmakingTicketResult* result )
{
    // result.cancellationReasonString = const char*;
    // result.created = time_t;
    // result.creator = PlayFabEntityKey const*;
    // result.giveUpAfterSeconds = int32_t;
    // result.matchId = const char*;
    // result.members = PlayFabMultiplayerMatchmakingPlayer const* const*;
    // result.membersCount = uint32_t;
    // result.membersToMatchWith = PlayFabEntityKey const* const*;
    // result.membersToMatchWithCount = uint32_t;
    // result.queueName = const char*;
    // result.status = const char*;
    // result.ticketId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerGetMultiplayerServerDetailsRequest( PlayFab::MultiplayerModels::GetMultiplayerServerDetailsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildId\": \"21781fa8-096d-4d9c-b699-75433d579285\", \"SessionId\": \"02bdef0e-e01e-4b29-8efe-ff9f47a06d8c\", \"Region\": \"SouthCentralUs\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerGetMultiplayerServerDetailsResponse( PlayFabMultiplayerGetMultiplayerServerDetailsResponse* result )
{
    // result.buildId = const char*;
    // result.connectedPlayers = PlayFabMultiplayerConnectedPlayer const* const*;
    // result.connectedPlayersCount = uint32_t;
    // result.fQDN = const char*;
    // result.iPV4Address = const char*;
    // result.lastStateTransitionTime = time_t const*;
    // result.ports = PlayFabMultiplayerPort const* const*;
    // result.portsCount = uint32_t;
    // result.region = const char*;
    // result.serverId = const char*;
    // result.sessionId = const char*;
    // result.state = const char*;
    // result.vmId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerGetMultiplayerServerLogsRequest( PlayFab::MultiplayerModels::GetMultiplayerServerLogsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Region\": \"AustraliaEast\", \"ServerId\": \"SomeServerId\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerGetMultiplayerServerLogsResponse( PlayFabMultiplayerGetMultiplayerServerLogsResponse* result )
{
    // result.logDownloadUrl = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerGetMultiplayerSessionLogsBySessionIdRequest( PlayFab::MultiplayerModels::GetMultiplayerSessionLogsBySessionIdRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"SessionId\": \"92e29db9-4004-4349-9a1f-b70ac01bdc08\"}" );
    request->FromJson(inputJson);
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerGetQueueStatisticsRequest( PlayFab::MultiplayerModels::GetQueueStatisticsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"QueueName\": \"custom123\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerGetQueueStatisticsResult( PlayFabMultiplayerGetQueueStatisticsResult* result )
{
    // result.numberOfPlayersMatching = uint32_t const*;
    // result.timeToMatchStatisticsInSeconds = PlayFabMultiplayerStatistics const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerGetRemoteLoginEndpointRequest( PlayFab::MultiplayerModels::GetRemoteLoginEndpointRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildId\": \"21781fa8-096d-4d9c-b699-75433d579285\", \"Region\": \"SouthCentralUs\", \"VmId\": \"VmID1\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerGetRemoteLoginEndpointResponse( PlayFabMultiplayerGetRemoteLoginEndpointResponse* result )
{
    // result.iPV4Address = const char*;
    // result.port = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerGetServerBackfillTicketRequest( PlayFab::MultiplayerModels::GetServerBackfillTicketRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"TicketId\": \"1c4b0daa-150e-47ae-9923-d770c0f9b07c\", \"QueueName\": \"custom123\", \"EscapeObject\": false}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerGetServerBackfillTicketResult( PlayFabMultiplayerGetServerBackfillTicketResult* result )
{
    // result.cancellationReasonString = const char*;
    // result.created = time_t;
    // result.giveUpAfterSeconds = int32_t;
    // result.matchId = const char*;
    // result.members = PlayFabMultiplayerMatchmakingPlayerWithTeamAssignment const* const*;
    // result.membersCount = uint32_t;
    // result.queueName = const char*;
    // result.serverDetails = PlayFabMultiplayerServerDetails const*;
    // result.status = const char*;
    // result.ticketId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerGetTitleEnabledForMultiplayerServersStatusRequest( PlayFab::MultiplayerModels::GetTitleEnabledForMultiplayerServersStatusRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerGetTitleEnabledForMultiplayerServersStatusResponse( PlayFabMultiplayerGetTitleEnabledForMultiplayerServersStatusResponse* result )
{
    // result.status = PlayFabMultiplayerTitleMultiplayerServerEnabledStatus const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerGetTitleMultiplayerServersQuotaChangeRequest( PlayFab::MultiplayerModels::GetTitleMultiplayerServersQuotaChangeRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"RequestId\": \"1234\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerGetTitleMultiplayerServersQuotaChangeResponse( PlayFabMultiplayerGetTitleMultiplayerServersQuotaChangeResponse* result )
{
    // result.change = PlayFabMultiplayerQuotaChange const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerGetTitleMultiplayerServersQuotasRequest( PlayFab::MultiplayerModels::GetTitleMultiplayerServersQuotasRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerGetTitleMultiplayerServersQuotasResponse( PlayFabMultiplayerGetTitleMultiplayerServersQuotasResponse* result )
{
    // result.quotas = PlayFabMultiplayerTitleMultiplayerServersQuotas const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerJoinMatchmakingTicketRequest( PlayFab::MultiplayerModels::JoinMatchmakingTicketRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"TicketId\": \"1c4b0daa-150e-47ae-9923-d770c0f9b07c\", \"QueueName\": \"custom123\", \"Member\": {}}" );
    request->FromJson(inputJson);
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerListMultiplayerServersRequest( PlayFab::MultiplayerModels::ListMultiplayerServersRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildId\": \"21781fa8-096d-4d9c-b699-75433d579285\", \"Region\": \"SouthCentralUs\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerListMultiplayerServersResponse( PlayFabMultiplayerListMultiplayerServersResponse* result )
{
    // result.multiplayerServerSummaries = PlayFabMultiplayerMultiplayerServerSummary const* const*;
    // result.multiplayerServerSummariesCount = uint32_t;
    // result.pageSize = int32_t;
    // result.skipToken = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerListAssetSummariesRequest( PlayFab::MultiplayerModels::ListAssetSummariesRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PageSize\": 10}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerListAssetSummariesResponse( PlayFabMultiplayerListAssetSummariesResponse* result )
{
    // result.assetSummaries = PlayFabMultiplayerAssetSummary const* const*;
    // result.assetSummariesCount = uint32_t;
    // result.pageSize = int32_t;
    // result.skipToken = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerListBuildAliasesRequest( PlayFab::MultiplayerModels::ListBuildAliasesRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PageSize\": 10}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerListBuildAliasesResponse( PlayFabMultiplayerListBuildAliasesResponse* result )
{
    // result.buildAliases = PlayFabMultiplayerBuildAliasDetailsResponse const* const*;
    // result.buildAliasesCount = uint32_t;
    // result.pageSize = int32_t;
    // result.skipToken = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerListBuildSummariesRequest( PlayFab::MultiplayerModels::ListBuildSummariesRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PageSize\": 10}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerListBuildSummariesResponse( PlayFabMultiplayerListBuildSummariesResponse* result )
{
    // result.buildSummaries = PlayFabMultiplayerBuildSummary const* const*;
    // result.buildSummariesCount = uint32_t;
    // result.pageSize = int32_t;
    // result.skipToken = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerListCertificateSummariesRequest( PlayFab::MultiplayerModels::ListCertificateSummariesRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PageSize\": 10}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerListCertificateSummariesResponse( PlayFabMultiplayerListCertificateSummariesResponse* result )
{
    // result.certificateSummaries = PlayFabMultiplayerCertificateSummary const* const*;
    // result.certificateSummariesCount = uint32_t;
    // result.pageSize = int32_t;
    // result.skipToken = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerListContainerImagesRequest( PlayFab::MultiplayerModels::ListContainerImagesRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PageSize\": 10}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerListContainerImagesResponse( PlayFabMultiplayerListContainerImagesResponse* result )
{
    // result.images = const char* const*;
    // result.imagesCount = uint32_t;
    // result.pageSize = int32_t;
    // result.skipToken = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerListContainerImageTagsRequest( PlayFab::MultiplayerModels::ListContainerImageTagsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ImageName\": \"imageName1\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerListContainerImageTagsResponse( PlayFabMultiplayerListContainerImageTagsResponse* result )
{
    // result.tags = const char* const*;
    // result.tagsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerListMatchmakingTicketsForPlayerRequest( PlayFab::MultiplayerModels::ListMatchmakingTicketsForPlayerRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Entity\": { \"Id\": \"123123123\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }, \"QueueName\": \"custom123\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerListMatchmakingTicketsForPlayerResult( PlayFabMultiplayerListMatchmakingTicketsForPlayerResult* result )
{
    // result.ticketIds = const char* const*;
    // result.ticketIdsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerListPartyQosServersRequest( PlayFab::MultiplayerModels::ListPartyQosServersRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Version\": \"1.0.0\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerListPartyQosServersResponse( PlayFabMultiplayerListPartyQosServersResponse* result )
{
    // result.pageSize = int32_t;
    // result.qosServers = PlayFabMultiplayerQosServer const* const*;
    // result.qosServersCount = uint32_t;
    // result.skipToken = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerListQosServersForTitleRequest( PlayFab::MultiplayerModels::ListQosServersForTitleRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"IncludeAllRegions\": true}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerListQosServersForTitleResponse( PlayFabMultiplayerListQosServersForTitleResponse* result )
{
    // result.pageSize = int32_t;
    // result.qosServers = PlayFabMultiplayerQosServer const* const*;
    // result.qosServersCount = uint32_t;
    // result.skipToken = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerListServerBackfillTicketsForPlayerRequest( PlayFab::MultiplayerModels::ListServerBackfillTicketsForPlayerRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Entity\": { \"Id\": \"123123123\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }, \"QueueName\": \"custom123\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerListServerBackfillTicketsForPlayerResult( PlayFabMultiplayerListServerBackfillTicketsForPlayerResult* result )
{
    // result.ticketIds = const char* const*;
    // result.ticketIdsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerListTitleMultiplayerServersQuotaChangesRequest( PlayFab::MultiplayerModels::ListTitleMultiplayerServersQuotaChangesRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerListTitleMultiplayerServersQuotaChangesResponse( PlayFabMultiplayerListTitleMultiplayerServersQuotaChangesResponse* result )
{
    // result.changes = PlayFabMultiplayerQuotaChange const* const*;
    // result.changesCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerListVirtualMachineSummariesRequest( PlayFab::MultiplayerModels::ListVirtualMachineSummariesRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildId\": \"21781fa8-096d-4d9c-b699-75433d579285\", \"Region\": \"SouthCentralUs\", \"PageSize\": 10}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerListVirtualMachineSummariesResponse( PlayFabMultiplayerListVirtualMachineSummariesResponse* result )
{
    // result.pageSize = int32_t;
    // result.skipToken = const char*;
    // result.virtualMachines = PlayFabMultiplayerVirtualMachineSummary const* const*;
    // result.virtualMachinesCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerRequestMultiplayerServerRequest( PlayFab::MultiplayerModels::RequestMultiplayerServerRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildId\": \"21781fa8-096d-4d9c-b699-75433d579285\", \"SessionId\": \"02bdef0e-e01e-4b29-8efe-ff9f47a06d8c\", \"SessionCookie\": \"U2Vzc2lvbkNvb2tpZQ==\", \"InitialPlayers\": [ \"gamer1\", \"gamer2\" ], \"PreferredRegions\": [ \"SouthCentralUs\", \"WestUs\" ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerRequestMultiplayerServerResponse( PlayFabMultiplayerRequestMultiplayerServerResponse* result )
{
    // result.buildId = const char*;
    // result.connectedPlayers = PlayFabMultiplayerConnectedPlayer const* const*;
    // result.connectedPlayersCount = uint32_t;
    // result.fQDN = const char*;
    // result.iPV4Address = const char*;
    // result.lastStateTransitionTime = time_t const*;
    // result.ports = PlayFabMultiplayerPort const* const*;
    // result.portsCount = uint32_t;
    // result.region = const char*;
    // result.serverId = const char*;
    // result.sessionId = const char*;
    // result.state = const char*;
    // result.vmId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerRolloverContainerRegistryCredentialsRequest( PlayFab::MultiplayerModels::RolloverContainerRegistryCredentialsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMultiplayerTests::ValidatePlayFabMultiplayerRolloverContainerRegistryCredentialsResponse( PlayFabMultiplayerRolloverContainerRegistryCredentialsResponse* result )
{
    // result.dnsName = const char*;
    // result.password = const char*;
    // result.username = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerShutdownMultiplayerServerRequest( PlayFab::MultiplayerModels::ShutdownMultiplayerServerRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildId\": \"21781fa8-096d-4d9c-b699-75433d579285\", \"Region\": \"SouthCentralUs\", \"SessionId\": \"02bdef0e-e01e-4b29-8efe-ff9f47a06d8c\"}" );
    request->FromJson(inputJson);
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerUntagContainerImageRequest( PlayFab::MultiplayerModels::UntagContainerImageRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ImageName\": \"imageName1\", \"Tag\": \"tag1\"}" );
    request->FromJson(inputJson);
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerUpdateBuildAliasRequest( PlayFab::MultiplayerModels::UpdateBuildAliasRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"AliasName\": \"AliasName\", \"BuildSelectionCriteria\": [ {  \"BuildWeightDistribution\": {  \"53781fa8-006d-4e9c-b733-57433d579285\": 1  } } ], \"AliasId\": \"21781fa8-096d-4d9c-b699-75433d579285\"}" );
    request->FromJson(inputJson);
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerUpdateBuildNameRequest( PlayFab::MultiplayerModels::UpdateBuildNameRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildId\": \"21781fa8-096d-4d9c-b699-75433d579285\", \"BuildName\": \"GameBuildName\"}" );
    request->FromJson(inputJson);
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerUpdateBuildRegionRequest( PlayFab::MultiplayerModels::UpdateBuildRegionRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildId\": \"21781fa8-096d-4d9c-b699-75433d579285\", \"BuildRegion\": { \"Region\": \"NorthEurope\", \"MaxServers\": 7, \"StandbyServers\": 3 }}" );
    request->FromJson(inputJson);
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerUpdateBuildRegionsRequest( PlayFab::MultiplayerModels::UpdateBuildRegionsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"BuildId\": \"21781fa8-096d-4d9c-b699-75433d579285\", \"BuildRegions\": [ {  \"Region\": \"EastUs\",  \"MaxServers\": 10,  \"StandbyServers\": 5 }, {  \"Region\": \"WestUs\",  \"MaxServers\": 12,  \"StandbyServers\": 8 }, {  \"Region\": \"NorthEurope\",  \"MaxServers\": 7,  \"StandbyServers\": 3 } ]}" );
    request->FromJson(inputJson);
}

void AutoGenMultiplayerTests::FillPlayFabMultiplayerUploadCertificateRequest( PlayFab::MultiplayerModels::UploadCertificateRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"GameCertificate\": { \"Name\": \"GameCertificate1\", \"Base64EncodedValue\": \"UGxheUZhYlJvY2tzISEhTGV0J3NtYWtlYWxvdG9mZ2FtZXMh\", \"Password\": \"PasswordForPFXCertificate\" }}" );
    request->FromJson(inputJson);
}

 

}
