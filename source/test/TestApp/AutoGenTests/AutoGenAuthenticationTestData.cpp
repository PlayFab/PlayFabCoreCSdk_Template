#include "TestAppPch.h"
#include "TestContext.h"
#include "TestApp.h"
#include "AutoGenAuthenticationTests.h"
#include "XAsyncHelper.h"
#include <playfab/PlayFabClientAuthApi.h>
#include <playfab/PlayFabClientApi.h>
#include <playfab/PlayFabProfilesApi.h>
#include <playfab/PlayFabAdminApi.h>
#include <playfab/PlayFabAuthenticationAuthApi.h>
#include <playfab/PlayFabClientDataModels.h>

namespace PlayFabUnit
{

void AutoGenAuthenticationTests::FillPlayFabAuthenticationValidateEntityTokenRequest( PlayFab::AuthenticationModels::ValidateEntityTokenRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"EntityToken\": \"50c61b9065b27a124a400ee3b95d404313986969\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenAuthenticationTests::ValidatePlayFabAuthenticationValidateEntityTokenResponse( PlayFabAuthenticationValidateEntityTokenResponse* result )
{
    // result.entity = PlayFabEntityKey const*;
    // result.identifiedDeviceType = PlayFabAuthenticationIdentifiedDeviceType const*;
    // result.identityProvider = PlayFabLoginIdentityProvider const*;
    // result.lineage = PlayFabAuthenticationEntityLineage const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

 

}
