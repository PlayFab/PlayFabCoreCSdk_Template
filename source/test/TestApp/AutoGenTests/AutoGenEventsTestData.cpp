#include "TestAppPch.h"
#include "TestContext.h"
#include "TestApp.h"
#include "AutoGenEventsTests.h"
#include "XAsyncHelper.h"

namespace PlayFabUnit
{

using namespace PlayFab::Wrappers;

#pragma region AdminAddPlayerTag

void AutoGenEventsTests::FillAdminAddPlayerTagRequest(PFEventsAddPlayerTagRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"TagName\": \"MostKilled\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region AdminGetPlayerTags

void AutoGenEventsTests::FillAdminGetPlayerTagsRequest(PFEventsGetPlayerTagsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Namespace\": \"title.AAA\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenEventsTests::ValidateAdminGetPlayerTagsResponse(PFEventsGetPlayerTagsResult* result)
{
    // result.playFabId = const char*;
    // result.tags = const char* const*;
    // result.tagsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminRemovePlayerTag

void AutoGenEventsTests::FillAdminRemovePlayerTagRequest(PFEventsRemovePlayerTagRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"TagName\": \"MostKilled\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientGetPlayerTags

void AutoGenEventsTests::FillClientGetPlayerTagsRequest(PFEventsGetPlayerTagsRequestWrapper<>& request)
{
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Namespace\": \"title.AAA\"}"
    request.SetPlayFabId("8C2294C98CAFA174");
}

HRESULT AutoGenEventsTests::ValidateClientGetPlayerTagsResponse(PFEventsGetPlayerTagsResult* result)
{
    // result.playFabId = const char*;
    // result.tags = const char* const*;
    // result.tagsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientWriteCharacterEvent

void AutoGenEventsTests::FillClientWriteCharacterEventRequest(PFEventsWriteClientCharacterEventRequestWrapper<>& request)
{
    // Example Request: "{ \"CharacterId\": \"{{CharacterId}}\", \"EventName\": \"character_defeated_enemy\", \"Timestamp\": \"2016-03-07T00:00:00Z\", \"Body\": { \"Enemy\": \"guardian\", \"Damage\": 5, \"Coordinates\": {  \"X\": 123.4,  \"Y\": 543.2 } }}"
    request.SetCharacterId("1CE3A7A40511570C");
    request.SetEventName("TestCharacterEventName");
}

HRESULT AutoGenEventsTests::ValidateClientWriteCharacterEventResponse(PFEventsWriteEventResponse* result)
{
    // result.eventId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientWritePlayerEvent

void AutoGenEventsTests::FillClientWritePlayerEventRequest(PFEventsWriteClientPlayerEventRequestWrapper<>& request)
{
    // Example Request: "{ \"EventName\": \"player_defeated_enemy\", \"Timestamp\": \"2014-03-07T00:00:00Z\", \"Body\": { \"Enemy\": \"guardian\", \"Damage\": 5, \"Coordinates\": {  \"X\": 123.4,  \"Y\": 543.2 } }}"
    request.SetEventName("TestPlayerEventName");
}

HRESULT AutoGenEventsTests::ValidateClientWritePlayerEventResponse(PFEventsWriteEventResponse* result)
{
    // result.eventId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientWriteTitleEvent

void AutoGenEventsTests::FillClientWriteTitleEventRequest(PFEventsWriteTitleEventRequestWrapper<>& request)
{
    // Example Request: "{ \"EventName\": \"client_update_submitted\", \"Timestamp\": \"2016-03-07T00:00:00Z\", \"Body\": { \"Version\": \"1.4.50\" }}"
    request.SetEventName("TestTitleEventName");
}

HRESULT AutoGenEventsTests::ValidateClientWriteTitleEventResponse(PFEventsWriteEventResponse* result)
{
    // result.eventId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerAddPlayerTag

void AutoGenEventsTests::FillServerAddPlayerTagRequest(PFEventsAddPlayerTagRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"TagName\": \"MostKilled\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ServerGetPlayerTags

void AutoGenEventsTests::FillServerGetPlayerTagsRequest(PFEventsGetPlayerTagsRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Namespace\": \"title.AAA\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenEventsTests::ValidateServerGetPlayerTagsResponse(PFEventsGetPlayerTagsResult* result)
{
    // result.playFabId = const char*;
    // result.tags = const char* const*;
    // result.tagsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerRemovePlayerTag

void AutoGenEventsTests::FillServerRemovePlayerTagRequest(PFEventsRemovePlayerTagRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"TagName\": \"MostKilled\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ServerWriteCharacterEvent

void AutoGenEventsTests::FillServerWriteCharacterEventRequest(PFEventsWriteServerCharacterEventRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"CharacterId\": \"{{CharacterId}}\", \"EventName\": \"character_defeated_enemy\", \"Timestamp\": \"2016-03-07T00:00:00Z\", \"Body\": { \"Enemy\": \"guardian\", \"Damage\": 5, \"Coordinates\": {  \"X\": 123.4,  \"Y\": 543.2 } }}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenEventsTests::ValidateServerWriteCharacterEventResponse(PFEventsWriteEventResponse* result)
{
    // result.eventId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerWritePlayerEvent

void AutoGenEventsTests::FillServerWritePlayerEventRequest(PFEventsWriteServerPlayerEventRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"EventName\": \"player_defeated_enemy\", \"Timestamp\": \"2016-03-07T00:00:00Z\", \"Body\": { \"Enemy\": \"guardian\", \"Damage\": 5, \"Coordinates\": {  \"X\": 123.4,  \"Y\": 543.2 } }}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenEventsTests::ValidateServerWritePlayerEventResponse(PFEventsWriteEventResponse* result)
{
    // result.eventId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ServerWriteTitleEvent

void AutoGenEventsTests::FillServerWriteTitleEventRequest(PFEventsWriteTitleEventRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"EventName\": \"client_update_submitted\", \"Timestamp\": \"2016-03-07T00:00:00Z\", \"Body\": { \"Version\": \"1.4.50\" }}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenEventsTests::ValidateServerWriteTitleEventResponse(PFEventsWriteEventResponse* result)
{
    // result.eventId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region WriteEvents

void AutoGenEventsTests::FillWriteEventsRequest(PFEventsWriteEventsRequestWrapper<>& request)
{
    // Example Request: "{ \"Events\": [ {  \"Entity\": {  \"Id\": \"A8140AB9109712B\",  \"Type\": \"title\",  \"TypeString\": \"title\"  },  \"EventNamespace\": \"com.playfab.events.example\",  \"Name\": \"something_happened\",  \"Payload\": {  \"Foo\": \"Bar\",  \"Nums\": [   1,   2,   3  ]  } } ]}"
    ModelVector<PFEventsEventContentsWrapper<>> events{};
    PFEventsEventContentsWrapper<> event1{};
    PFEntityKeyWrapper<> entity1{};

    entity1.SetId("B64BE91E5DBD5597");
    entity1.SetType("title_player_account");
    event1.SetEntity(entity1);
    event1.SetName("TestEventName");
    event1.SetEventNamespace("custom.test.namespace");
    event1.SetPayloadJSON("{ \"testPayloadKey\": \"testPayloadValue\" }");
    events.push_back(event1);

    request.SetEvents(events);
}

HRESULT AutoGenEventsTests::ValidateWriteEventsResponse(PFEventsWriteEventsResponse* result)
{
    // result.assignedEventIds = const char* const*;
    // result.assignedEventIdsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region WriteTelemetryEvents

void AutoGenEventsTests::FillWriteTelemetryEventsRequest(PFEventsWriteEventsRequestWrapper<>& request)
{
    // Example Request: "{ \"Events\": [ {  \"Entity\": {  \"Id\": \"A8140AB9109712B\",  \"Type\": \"title\",  \"TypeString\": \"title\"  },  \"EventNamespace\": \"com.playfab.events.example\",  \"Name\": \"something_happened\",  \"Payload\": {  \"Foo\": \"Bar\",  \"Nums\": [   1,   2,   3  ]  } } ]}"
    ModelVector<PFEventsEventContentsWrapper<>> events{};
    PFEventsEventContentsWrapper<> event1{};
    PFEntityKeyWrapper<> entity1{};

    entity1.SetId("B64BE91E5DBD5597");
    entity1.SetType("title_player_account");
    event1.SetEntity(entity1);
    event1.SetName("TestEventName");
    event1.SetEventNamespace("custom.test.namespace");
    event1.SetPayloadJSON("{ \"testPayloadKey\": \"testPayloadValue\" }");
    events.push_back(event1);

    request.SetEvents(events);
}

HRESULT AutoGenEventsTests::ValidateWriteTelemetryEventsResponse(PFEventsWriteEventsResponse* result)
{
    // result.assignedEventIds = const char* const*;
    // result.assignedEventIdsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion


}
