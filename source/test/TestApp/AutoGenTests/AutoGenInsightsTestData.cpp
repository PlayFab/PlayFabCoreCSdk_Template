#include "TestAppPch.h"
#include "TestContext.h"
#include "TestApp.h"
#include "AutoGenInsightsTests.h"
#include "XAsyncHelper.h"
#include <playfab/PlayFabClientAuthApi.h>
#include <playfab/PlayFabClientApi.h>
#include <playfab/PlayFabProfilesApi.h>
#include <playfab/PlayFabAdminApi.h>
#include <playfab/PlayFabAuthenticationAuthApi.h>
#include <playfab/PlayFabClientDataModels.h>

namespace PlayFabUnit
{

void AutoGenInsightsTests::FillPlayFabInsightsInsightsEmptyRequest( PlayFab::InsightsModels::InsightsEmptyRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenInsightsTests::ValidatePlayFabInsightsInsightsGetDetailsResponse( PlayFabInsightsInsightsGetDetailsResponse* result )
{
    // result.dataUsageMb = uint32_t;
    // result.errorMessage = const char*;
    // result.limits = PlayFabInsightsInsightsGetLimitsResponse const*;
    // result.pendingOperations = PlayFabInsightsInsightsGetOperationStatusResponse const* const*;
    // result.pendingOperationsCount = uint32_t;
    // result.performanceLevel = int32_t;
    // result.retentionDays = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

HRESULT AutoGenInsightsTests::ValidatePlayFabInsightsInsightsGetLimitsResponse( PlayFabInsightsInsightsGetLimitsResponse* result )
{
    // result.defaultPerformanceLevel = int32_t;
    // result.defaultStorageRetentionDays = int32_t;
    // result.storageMaxRetentionDays = int32_t;
    // result.storageMinRetentionDays = int32_t;
    // result.subMeters = PlayFabInsightsInsightsPerformanceLevel const* const*;
    // result.subMetersCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenInsightsTests::FillPlayFabInsightsInsightsGetOperationStatusRequest( PlayFab::InsightsModels::InsightsGetOperationStatusRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"OperationId\": \"3ee468c4-ad09-4bb1-bccf-209ef5abfb96\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenInsightsTests::ValidatePlayFabInsightsInsightsGetOperationStatusResponse( PlayFabInsightsInsightsGetOperationStatusResponse* result )
{
    // result.message = const char*;
    // result.operationCompletedTime = time_t;
    // result.operationId = const char*;
    // result.operationLastUpdated = time_t;
    // result.operationStartedTime = time_t;
    // result.operationType = const char*;
    // result.operationValue = int32_t;
    // result.status = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenInsightsTests::FillPlayFabInsightsInsightsGetPendingOperationsRequest( PlayFab::InsightsModels::InsightsGetPendingOperationsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"OperationType\": \"SetPerformance\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenInsightsTests::ValidatePlayFabInsightsInsightsGetPendingOperationsResponse( PlayFabInsightsInsightsGetPendingOperationsResponse* result )
{
    // result.pendingOperations = PlayFabInsightsInsightsGetOperationStatusResponse const* const*;
    // result.pendingOperationsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenInsightsTests::FillPlayFabInsightsInsightsSetPerformanceRequest( PlayFab::InsightsModels::InsightsSetPerformanceRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PerformanceLevel\": 3}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenInsightsTests::ValidatePlayFabInsightsInsightsOperationResponse( PlayFabInsightsInsightsOperationResponse* result )
{
    // result.message = const char*;
    // result.operationId = const char*;
    // result.operationType = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenInsightsTests::FillPlayFabInsightsInsightsSetStorageRetentionRequest( PlayFab::InsightsModels::InsightsSetStorageRetentionRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"RetentionDays\": 30}" );
    request->FromJson(inputJson);
}

 

}
