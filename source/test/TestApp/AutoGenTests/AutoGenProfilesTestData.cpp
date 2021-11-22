#include "TestAppPch.h"
#include "TestContext.h"
#include "TestApp.h"
#include "AutoGenProfilesTests.h"
#include "XAsyncHelper.h"

namespace PlayFabUnit
{

using namespace PlayFab::Wrappers;

#pragma region GetGlobalPolicy

void AutoGenProfilesTests::FillGetGlobalPolicyRequest(PFProfilesGetGlobalPolicyRequestWrapper<>& request)
{
    // Example Request: "{}"
    UNREFERENCED_PARAMETER(request); // TODO
}

HRESULT AutoGenProfilesTests::ValidatePFProfilesGetGlobalPolicyResponse(PFProfilesGetGlobalPolicyResponse* result)
{
    // result.permissions = PFProfilesEntityPermissionStatement const* const*;
    // result.permissionsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region GetProfile

void AutoGenProfilesTests::FillGetEntityProfileRequest(PFProfilesGetEntityProfileRequestWrapper<>& request)
{
    // Example Request: "{ \"Entity\": { \"Id\": \"1234567787392\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    PFEntityKeyWrapper<> entity{};
    entity.SetId("B64BE91E5DBD5597");
    entity.SetType(PFTitlePlayerEntityType);
    request.SetEntity(entity);
}

HRESULT AutoGenProfilesTests::ValidatePFProfilesGetEntityProfileResponse(PFProfilesGetEntityProfileResponse* result)
{
    // result.profile = PFProfilesEntityProfileBody const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region GetProfiles

void AutoGenProfilesTests::FillGetEntityProfilesRequest(PFProfilesGetEntityProfilesRequestWrapper<>& request)
{
    // Example Request: "{ \"Entities\": [ {  \"Id\": \"1234567787392\",  \"Type\": \"title_player_account\",  \"TypeString\": \"title_player_account\" }, {  \"Id\": \"42434567785265\",  \"Type\": \"title_player_account\",  \"TypeString\": \"title_player_account\" } ]}"
    PFEntityKeyWrapper<> entity1{};
    entity1.SetId("B64BE91E5DBD5597");
    entity1.SetType(PFTitlePlayerEntityType);

    PFEntityKeyWrapper<> entity2{};
    entity2.SetId("61E37494004A216C");
    entity2.SetType(PFTitlePlayerEntityType);

    ModelVector<PFEntityKeyWrapper<>> entities{};
    entities.push_back(entity1);
    entities.push_back(entity2);
    request.SetEntities(entities);
}

HRESULT AutoGenProfilesTests::ValidatePFProfilesGetEntityProfilesResponse(PFProfilesGetEntityProfilesResponse* result)
{
    // result.profiles = PFProfilesEntityProfileBody const* const*;
    // result.profilesCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region GetTitlePlayersFromMasterPlayerAccountIds

void AutoGenProfilesTests::FillGetTitlePlayersFromMasterPlayerAccountIdsRequest(PFProfilesGetTitlePlayersFromMasterPlayerAccountIdsRequestWrapper<>& request)
{
    // Example Request: "{ \"MasterPlayerAccountIds\": [ \"1233455677\" ], \"TitleId\": \"{{TitleId}}\"}"
    request.SetMasterPlayerAccountIds({ "8C2294C98CAFA174" });
}

HRESULT AutoGenProfilesTests::ValidatePFProfilesGetTitlePlayersFromMasterPlayerAccountIdsResponse(PFProfilesGetTitlePlayersFromMasterPlayerAccountIdsResponse* result)
{
    // result.titleId = const char*;
    // result.titlePlayerAccounts = struct PFEntityKeyDictionaryEntry const*;
    // result.titlePlayerAccountsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region SetGlobalPolicy

void AutoGenProfilesTests::FillSetGlobalPolicyRequest(PFProfilesSetGlobalPolicyRequestWrapper<>& request)
{
    // Example Request: "{ \"Permissions\": [ {  \"Resource\": \"pfrn:data--title_player_account!90901000/Profile/SomethingCool\",  \"Action\": \"*\",  \"Effect\": \"Allow\",  \"Principal\": {  \"ChildOf\": {   \"EntityType\": \"[SELF]\"  }  },  \"Comment\": \"An example policy\" } ]}"
    PFProfilesEntityPermissionStatementWrapper<> permission;
    permission.SetAction("Write");
    permission.SetEffect(PFEffectType::Deny);
    permission.SetCondition({ "{ \"CallingEntityType\": \"character\" }" });
    permission.SetComment("Testing Global Policy: Only title can edit user statistics");
    permission.SetPrincipal({ "{ \"*\" }" });
    permission.SetResource("pfrn:data--*!*/Profile/Statistics/*");

    ModelVector<PFProfilesEntityPermissionStatementWrapper<>> permissions;
    permissions.push_back(permission);
    request.SetPermissions(permissions);
}

#pragma endregion

#pragma region SetProfileLanguage

void AutoGenProfilesTests::FillSetProfileLanguageRequest(PFProfilesSetProfileLanguageRequestWrapper<>& request)
{
    // Example Request: "{ \"Language\": \"en\", \"ExpectedVersion\": 123, \"Entity\": { \"Id\": \"1234\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    PFEntityKeyWrapper<> entity{};
    entity.SetId("B64BE91E5DBD5597");
    entity.SetType(PFTitlePlayerEntityType);
    request.SetEntity(entity);

    request.SetLanguage("en");
}

HRESULT AutoGenProfilesTests::ValidatePFProfilesSetProfileLanguageResponse(PFProfilesSetProfileLanguageResponse* result)
{
    // result.operationResult = PFOperationTypes const*;
    // result.versionNumber = int32_t const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region SetProfilePolicy

void AutoGenProfilesTests::FillSetEntityProfilePolicyRequest(PFProfilesSetEntityProfilePolicyRequestWrapper<>& request)
{
    // Example Request: "{ \"Statements\": [ {  \"Resource\": \"pfrn:data--*!*/Profile/Files/avatar.png\",  \"Action\": \"Read\",  \"Effect\": \"Allow\",  \"Principal\": {  \"FriendOf\": \"true\"  },  \"Comment\": \"Allow my friends to read my avatar\" } ], \"Entity\": { \"Id\": \"90901000\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    PFEntityKeyWrapper<> entity{};
    entity.SetId("B64BE91E5DBD5597");
    entity.SetType(PFTitlePlayerEntityType);
    request.SetEntity(entity);

    PFJsonObject doc;
    doc.stringValue = "{ \"Friend\": \"true\" }";

    PFProfilesEntityPermissionStatementWrapper<> permission1;
    permission1.SetAction("Read");
    permission1.SetEffect(PFEffectType::Allow);
    permission1.SetComment("Testing Profile Policy 1");
    permission1.SetPrincipal(doc);
    permission1.SetResource("pfrn:data--title_player_account!B64BE91E5DBD5597/Profile/Objects/*");

    PFProfilesEntityPermissionStatementWrapper<> permission2;
    permission2.SetAction("Write");
    permission2.SetEffect(PFEffectType::Deny);
    permission2.SetComment("Testing Profile Policy 2");
    permission2.SetPrincipal(doc);
    permission2.SetResource("pfrn:data--title_player_account!B64BE91E5DBD5597/Profile/Files/*");

    ModelVector<PFProfilesEntityPermissionStatementWrapper<>> permissions;
    permissions.push_back(permission1);
    permissions.push_back(permission2);
    request.SetStatements(permissions);
}

HRESULT AutoGenProfilesTests::ValidatePFProfilesSetEntityProfilePolicyResponse(PFProfilesSetEntityProfilePolicyResponse* result)
{
    // result.permissions = PFProfilesEntityPermissionStatement const* const*;
    // result.permissionsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion
 

}
