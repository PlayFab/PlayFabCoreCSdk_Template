#include "TestAppPch.h"
#include "TestContext.h"
#include "TestApp.h"
#include "AutoGenEventsTests.h"
#include "XAsyncHelper.h"

namespace PlayFabUnit
{

using namespace PlayFab::Wrappers;

#pragma region AdminAddPlayerTag

void AutoGenEventsTests::FillAddPlayerTagRequest(PFEventsAddPlayerTagRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"TagName\": \"MostKilled\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region AdminGetPlayerTags

void AutoGenEventsTests::FillGetPlayerTagsRequest(PFEventsGetPlayerTagsRequestWrapper<>& request)
{
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"Namespace\": \"title.AAA\"}"
    request.SetPlayFabId("8C2294C98CAFA174");
}

HRESULT AutoGenEventsTests::ValidatePFEventsGetPlayerTagsResult(PFEventsGetPlayerTagsResult* result)
{
    // result.playFabId = const char*;
    // result.tags = const char* const*;
    // result.tagsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region AdminRemovePlayerTag

void AutoGenEventsTests::FillRemovePlayerTagRequest(PFEventsRemovePlayerTagRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"TagName\": \"MostKilled\"}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ClientGetPlayerTags


#pragma endregion

#pragma region ClientWriteCharacterEvent

void AutoGenEventsTests::FillWriteClientCharacterEventRequest(PFEventsWriteClientCharacterEventRequestWrapper<>& request)
{
    // Example Request: "{ \"CharacterId\": \"{{CharacterId}}\", \"EventName\": \"character_defeated_enemy\", \"Timestamp\": \"2016-03-07T00:00:00Z\", \"Body\": { \"Enemy\": \"guardian\", \"Damage\": 5, \"Coordinates\": {  \"X\": 123.4,  \"Y\": 543.2 } }}"
    request.SetCharacterId("1CE3A7A40511570C");
    request.SetEventName("TestCharacterEventName");
}

HRESULT AutoGenEventsTests::ValidatePFEventsWriteEventResponse(PFEventsWriteEventResponse* result)
{
    // result.eventId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ClientWritePlayerEvent

void AutoGenEventsTests::FillWriteClientPlayerEventRequest(PFEventsWriteClientPlayerEventRequestWrapper<>& request)
{
    // Example Request: "{ \"EventName\": \"player_defeated_enemy\", \"Timestamp\": \"2014-03-07T00:00:00Z\", \"Body\": { \"Enemy\": \"guardian\", \"Damage\": 5, \"Coordinates\": {  \"X\": 123.4,  \"Y\": 543.2 } }}"
    request.SetEventName("TestPlayerEventName");
}

#pragma endregion

#pragma region ClientWriteTitleEvent

void AutoGenEventsTests::FillWriteTitleEventRequest(PFEventsWriteTitleEventRequestWrapper<>& request)
{
    // Example Request: "{ \"EventName\": \"client_update_submitted\", \"Timestamp\": \"2016-03-07T00:00:00Z\", \"Body\": { \"Version\": \"1.4.50\" }}"
    request.SetEventName("TestTitleEventName");
}

#pragma endregion

#pragma region ServerAddPlayerTag


#pragma endregion

#pragma region ServerGetPlayerTags


#pragma endregion

#pragma region ServerRemovePlayerTag


#pragma endregion

#pragma region ServerWriteCharacterEvent

void AutoGenEventsTests::FillWriteServerCharacterEventRequest(PFEventsWriteServerCharacterEventRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"CharacterId\": \"{{CharacterId}}\", \"EventName\": \"character_defeated_enemy\", \"Timestamp\": \"2016-03-07T00:00:00Z\", \"Body\": { \"Enemy\": \"guardian\", \"Damage\": 5, \"Coordinates\": {  \"X\": 123.4,  \"Y\": 543.2 } }}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ServerWritePlayerEvent

void AutoGenEventsTests::FillWriteServerPlayerEventRequest(PFEventsWriteServerPlayerEventRequestWrapper<>& request)
{
    // TODO: debug Failing test
    // Example Request: "{ \"PlayFabId\": \"{{PlayFabId}}\", \"EventName\": \"player_defeated_enemy\", \"Timestamp\": \"2016-03-07T00:00:00Z\", \"Body\": { \"Enemy\": \"guardian\", \"Damage\": 5, \"Coordinates\": {  \"X\": 123.4,  \"Y\": 543.2 } }}"
    UNREFERENCED_PARAMETER(request); // TODO
}

#pragma endregion

#pragma region ServerWriteTitleEvent


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

HRESULT AutoGenEventsTests::ValidatePFEventsWriteEventsResponse(PFEventsWriteEventsResponse* result)
{
    // result.assignedEventIds = const char* const*;
    // result.assignedEventIdsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region WriteTelemetryEvents


#pragma endregion


}
