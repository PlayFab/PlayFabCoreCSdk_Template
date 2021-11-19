#include "TestAppPch.h"
#include "TestContext.h"
#include "TestApp.h"
#include "AutoGenLocalizationTests.h"
#include "XAsyncHelper.h"
#include <playfab/PlayFabClientAuthApi.h>
#include <playfab/PlayFabClientApi.h>
#include <playfab/PlayFabProfilesApi.h>
#include <playfab/PlayFabAdminApi.h>
#include <playfab/PlayFabAuthenticationAuthApi.h>
#include <playfab/PlayFabClientDataModels.h>

namespace PlayFabUnit
{

void AutoGenLocalizationTests::FillPlayFabLocalizationGetLanguageListRequest( PlayFab::LocalizationModels::GetLanguageListRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenLocalizationTests::ValidatePlayFabLocalizationGetLanguageListResponse( PlayFabLocalizationGetLanguageListResponse* result )
{
    // result.languageList = const char* const*;
    // result.languageListCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

 

}
