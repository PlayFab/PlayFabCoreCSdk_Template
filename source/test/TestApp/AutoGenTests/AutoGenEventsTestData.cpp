#include "TestAppPch.h"
#include "TestContext.h"
#include "TestApp.h"
#include "AutoGenEventsTests.h"
#include "XAsyncHelper.h"
#include <playfab/PlayFabClientAuthApi.h>
#include <playfab/PlayFabClientApi.h>
#include <playfab/PlayFabProfilesApi.h>
#include <playfab/PlayFabAdminApi.h>
#include <playfab/PlayFabAuthenticationAuthApi.h>
#include <playfab/PlayFabClientDataModels.h>

namespace PlayFabUnit
{

void AutoGenEventsTests::FillPlayFabEventsWriteEventsRequest( PlayFab::EventsModels::WriteEventsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Events\": [ {  \"Entity\": {  \"Id\": \"A8140AB9109712B\",  \"Type\": \"title\",  \"TypeString\": \"title\"  },  \"EventNamespace\": \"com.playfab.events.example\",  \"Name\": \"something_happened\",  \"Payload\": {  \"Foo\": \"Bar\",  \"Nums\": [   1,   2,   3  ]  } } ]}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenEventsTests::ValidatePlayFabEventsWriteEventsResponse( PlayFabEventsWriteEventsResponse* result )
{
    // result.assignedEventIds = const char* const*;
    // result.assignedEventIdsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

 

}
