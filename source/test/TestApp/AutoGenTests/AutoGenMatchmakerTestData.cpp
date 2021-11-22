#include "TestAppPch.h"
#include "TestContext.h"
#include "TestApp.h"
#include "AutoGenMatchmakerTests.h"
#include "XAsyncHelper.h"
#include <playfab/PlayFabClientAuthApi.h>
#include <playfab/PlayFabClientApi.h>
#include <playfab/PlayFabProfilesApi.h>
#include <playfab/PlayFabAdminApi.h>
#include <playfab/PlayFabAuthenticationAuthApi.h>
#include <playfab/PlayFabClientDataModels.h>

namespace PlayFabUnit
{

void AutoGenMatchmakerTests::FillPlayFabMatchmakerAuthUserRequest( PlayFab::MatchmakerModels::AuthUserRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"AuthorizationTicket\": \"9F856B4A071A9A5D-0-0-AD0-8D165320C16429B-72087E2356D29870.9D0410B3E78D8A5F\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMatchmakerTests::ValidatePlayFabMatchmakerAuthUserResponse( PlayFabMatchmakerAuthUserResponse* result )
{
    // result.authorized = bool;
    // result.playFabId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMatchmakerTests::FillPlayFabMatchmakerPlayerJoinedRequest( PlayFab::MatchmakerModels::PlayerJoinedRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"LobbyId\": \"serverID\", \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

void AutoGenMatchmakerTests::FillPlayFabMatchmakerPlayerLeftRequest( PlayFab::MatchmakerModels::PlayerLeftRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"LobbyId\": \"serverID\", \"PlayFabId\": \"{{PlayFabId}}\"}" );
    request->FromJson(inputJson);
}

void AutoGenMatchmakerTests::FillPlayFabMatchmakerStartGameRequest( PlayFab::MatchmakerModels::StartGameRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Build\": \"6.01\", \"Region\": \"USCentral\", \"GameMode\": \"capture_the_flag\", \"CustomCommandLineData\": \"custom_gameserver_commandline_parameter\", \"ExternalMatchmakerEventEndpoint\": \"https://yourmatchmaker.com/gamestatusevents/\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMatchmakerTests::ValidatePlayFabMatchmakerStartGameResponse( PlayFabMatchmakerStartGameResponse* result )
{
    // result.gameID = const char*;
    // result.serverIPV4Address = const char*;
    // result.serverIPV6Address = const char*;
    // result.serverPort = uint32_t;
    // result.serverPublicDNSName = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenMatchmakerTests::FillPlayFabMatchmakerUserInfoRequest( PlayFab::MatchmakerModels::UserInfoRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayFabId\": \"{{PlayFabId}}\", \"MinCatalogVersion\": 4}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenMatchmakerTests::ValidatePlayFabMatchmakerUserInfoResponse( PlayFabMatchmakerUserInfoResponse* result )
{
    // result.inventory = PlayFabItemInstance const* const*;
    // result.inventoryCount = uint32_t;
    // result.isDeveloper = bool;
    // result.playFabId = const char*;
    // result.steamId = const char*;
    // result.titleDisplayName = const char*;
    // result.username = const char*;
    // result.virtualCurrency = struct PlayFabInt32DictionaryEntry const*;
    // result.virtualCurrencyCount = uint32_t;
    // result.virtualCurrencyRechargeTimes = struct PlayFabVirtualCurrencyRechargeTimeDictionaryEntry const*;
    // result.virtualCurrencyRechargeTimesCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

 

}
