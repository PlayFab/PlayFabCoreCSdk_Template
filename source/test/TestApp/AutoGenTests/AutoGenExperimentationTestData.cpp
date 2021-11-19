#include "TestAppPch.h"
#include "TestContext.h"
#include "TestApp.h"
#include "AutoGenExperimentationTests.h"
#include "XAsyncHelper.h"
#include <playfab/PlayFabClientAuthApi.h>
#include <playfab/PlayFabClientApi.h>
#include <playfab/PlayFabProfilesApi.h>
#include <playfab/PlayFabAdminApi.h>
#include <playfab/PlayFabAuthenticationAuthApi.h>
#include <playfab/PlayFabClientDataModels.h>

namespace PlayFabUnit
{

void AutoGenExperimentationTests::FillPlayFabExperimentationCreateExclusionGroupRequest( PlayFab::ExperimentationModels::CreateExclusionGroupRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Name\": \"Commerce Exclusion Group\", \"Description\": \"Exclusion group for independent, commerce-related experiments\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenExperimentationTests::ValidatePlayFabExperimentationCreateExclusionGroupResult( PlayFabExperimentationCreateExclusionGroupResult* result )
{
    // result.exclusionGroupId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenExperimentationTests::FillPlayFabExperimentationCreateExperimentRequest( PlayFab::ExperimentationModels::CreateExperimentRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Name\": \"BackgroundColor Experiment\", \"Description\": \"Tests whether a green background color increases revenue\", \"StartDate\": \"2019-10-25T20:37:00Z\", \"EndDate\": \"2019-11-13T20:37:00Z\", \"Variants\": [ {  \"Name\": \"Control\",  \"Description\": \"Control variant\",  \"TrafficPercentage\": 10,  \"Variables\": [  {   \"Name\": \"BackgroundColor\",   \"Value\": \"White\"  }  ],  \"IsControl\": true }, {  \"Name\": \"Treatment\",  \"Description\": \"Treatment variant\",  \"TrafficPercentage\": 90,  \"Variables\": [  {   \"Name\": \"BackgroundColor\",   \"Value\": \"Green\"  }  ],  \"IsControl\": false } ], \"ExperimentType\": \"Active\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenExperimentationTests::ValidatePlayFabExperimentationCreateExperimentResult( PlayFabExperimentationCreateExperimentResult* result )
{
    // result.experimentId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenExperimentationTests::FillPlayFabExperimentationDeleteExclusionGroupRequest( PlayFab::ExperimentationModels::DeleteExclusionGroupRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ExclusionGroupId\": \"00000000-0000-0000-0000-000000000000\"}" );
    request->FromJson(inputJson);
}

void AutoGenExperimentationTests::FillPlayFabExperimentationDeleteExperimentRequest( PlayFab::ExperimentationModels::DeleteExperimentRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ExperimentId\": \"00000000-0000-0000-0000-000000000000\"}" );
    request->FromJson(inputJson);
}

void AutoGenExperimentationTests::FillPlayFabExperimentationGetExclusionGroupsRequest( PlayFab::ExperimentationModels::GetExclusionGroupsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenExperimentationTests::ValidatePlayFabExperimentationGetExclusionGroupsResult( PlayFabExperimentationGetExclusionGroupsResult* result )
{
    // result.exclusionGroups = PlayFabExperimentationExperimentExclusionGroup const* const*;
    // result.exclusionGroupsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenExperimentationTests::FillPlayFabExperimentationGetExclusionGroupTrafficRequest( PlayFab::ExperimentationModels::GetExclusionGroupTrafficRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenExperimentationTests::ValidatePlayFabExperimentationGetExclusionGroupTrafficResult( PlayFabExperimentationGetExclusionGroupTrafficResult* result )
{
    // result.trafficAllocations = PlayFabExperimentationExclusionGroupTrafficAllocation const* const*;
    // result.trafficAllocationsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenExperimentationTests::FillPlayFabExperimentationGetExperimentsRequest( PlayFab::ExperimentationModels::GetExperimentsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenExperimentationTests::ValidatePlayFabExperimentationGetExperimentsResult( PlayFabExperimentationGetExperimentsResult* result )
{
    // result.experiments = PlayFabExperimentationExperiment const* const*;
    // result.experimentsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenExperimentationTests::FillPlayFabExperimentationGetLatestScorecardRequest( PlayFab::ExperimentationModels::GetLatestScorecardRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ExperimentId\": \"00000000-0000-0000-0000-000000000000\"}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenExperimentationTests::ValidatePlayFabExperimentationGetLatestScorecardResult( PlayFabExperimentationGetLatestScorecardResult* result )
{
    // result.scorecard = PlayFabExperimentationScorecard const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenExperimentationTests::FillPlayFabExperimentationGetTreatmentAssignmentRequest( PlayFab::ExperimentationModels::GetTreatmentAssignmentRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenExperimentationTests::ValidatePlayFabExperimentationGetTreatmentAssignmentResult( PlayFabExperimentationGetTreatmentAssignmentResult* result )
{
    // result.treatmentAssignment = PlayFabTreatmentAssignment const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenExperimentationTests::FillPlayFabExperimentationStartExperimentRequest( PlayFab::ExperimentationModels::StartExperimentRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ExperimentId\": \"00000000-0000-0000-0000-000000000000\"}" );
    request->FromJson(inputJson);
}

void AutoGenExperimentationTests::FillPlayFabExperimentationStopExperimentRequest( PlayFab::ExperimentationModels::StopExperimentRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ExperimentId\": \"00000000-0000-0000-0000-000000000000\"}" );
    request->FromJson(inputJson);
}

void AutoGenExperimentationTests::FillPlayFabExperimentationUpdateExclusionGroupRequest( PlayFab::ExperimentationModels::UpdateExclusionGroupRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ExclusionGroupId\": \"00000000-0000-0000-0000-000000000000\", \"Name\": \"Commerce Exclusion Group\", \"Description\": \"Exclusion group for independent, commerce-related experiments\"}" );
    request->FromJson(inputJson);
}

void AutoGenExperimentationTests::FillPlayFabExperimentationUpdateExperimentRequest( PlayFab::ExperimentationModels::UpdateExperimentRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"Name\": \"BackgroundColor Experiment\", \"Id\": \"B9A90E90-A009-4254-80A4-46B5933E9D26\", \"Description\": \"Tests whether a green background color increases revenue\", \"StartDate\": \"2019-10-25T20:37:00Z\", \"EndDate\": \"2019-11-13T20:37:00Z\", \"SegmentId\": \"0\", \"Variants\": [ {  \"Name\": \"Control\",  \"Description\": \"Control variant\",  \"TrafficPercentage\": 10,  \"Variables\": [  {   \"Name\": \"BackgroundColor\",   \"Value\": \"White\"  }  ],  \"IsControl\": true }, {  \"Name\": \"Treatment\",  \"Description\": \"Treatment variant\",  \"TrafficPercentage\": 90,  \"Variables\": [  {   \"Name\": \"BackgroundColor\",   \"Value\": \"Green\"  }  ],  \"IsControl\": false } ], \"ExperimentType\": \"Active\"}" );
    request->FromJson(inputJson);
}

 

}
