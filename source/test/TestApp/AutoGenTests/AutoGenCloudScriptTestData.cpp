#include "TestAppPch.h"
#include "TestContext.h"
#include "TestApp.h"
#include "AutoGenCloudScriptTests.h"
#include "XAsyncHelper.h"
#include <playfab/PlayFabClientAuthApi.h>
#include <playfab/PlayFabClientApi.h>
#include <playfab/PlayFabProfilesApi.h>
#include <playfab/PlayFabAdminApi.h>
#include <playfab/PlayFabAuthenticationAuthApi.h>
#include <playfab/PlayFabClientDataModels.h>

namespace PlayFabUnit
{

void AutoGenCloudScriptTests::FillPlayFabCloudScriptExecuteEntityCloudScriptRequest( PlayFab::CloudScriptModels::ExecuteEntityCloudScriptRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"FunctionName\": \"levelCompleted\", \"FunctionParameter\": { \"level\": 3, \"points\": 400 }, \"RevisionSelection\": \"Live\", \"GeneratePlayStreamEvent\": true, \"Entity\": { \"Id\": \"aaa\", \"Type\": \"master_player_account\", \"TypeString\": \"master_player_account\" }}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenCloudScriptTests::ValidatePlayFabCloudScriptExecuteCloudScriptResult( PlayFabCloudScriptExecuteCloudScriptResult* result )
{
    // result.aPIRequestsIssued = int32_t;
    // result.error = PlayFabCloudScriptScriptExecutionError const*;
    // result.executionTimeSeconds = double;
    // result.functionName = const char*;
    // result.functionResult = PlayFabJsonObject;
    // result.functionResultTooLarge = bool const*;
    // result.httpRequestsIssued = int32_t;
    // result.logs = PlayFabCloudScriptLogStatement const* const*;
    // result.logsCount = uint32_t;
    // result.logsTooLarge = bool const*;
    // result.memoryConsumedBytes = uint32_t;
    // result.processorTimeSeconds = double;
    // result.revision = int32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenCloudScriptTests::FillPlayFabCloudScriptExecuteFunctionRequest( PlayFab::CloudScriptModels::ExecuteFunctionRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"FunctionName\": \"LevelCompleted\", \"FunctionParameter\": { \"level\": 3, \"points\": 400 }, \"GeneratePlayStreamEvent\": true, \"Entity\": { \"Id\": \"aaa\", \"Type\": \"master_player_account\", \"TypeString\": \"master_player_account\" }}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenCloudScriptTests::ValidatePlayFabCloudScriptExecuteFunctionResult( PlayFabCloudScriptExecuteFunctionResult* result )
{
    // result.error = PlayFabCloudScriptFunctionExecutionError const*;
    // result.executionTimeMilliseconds = int32_t;
    // result.functionName = const char*;
    // result.functionResult = PlayFabJsonObject;
    // result.functionResultTooLarge = bool const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenCloudScriptTests::FillPlayFabCloudScriptListFunctionsRequest( PlayFab::CloudScriptModels::ListFunctionsRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{}" );
    request->FromJson(inputJson);
}

HRESULT AutoGenCloudScriptTests::ValidatePlayFabCloudScriptListFunctionsResult( PlayFabCloudScriptListFunctionsResult* result )
{
    // result.functions = PlayFabCloudScriptFunctionModel const* const*;
    // result.functionsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

HRESULT AutoGenCloudScriptTests::ValidatePlayFabCloudScriptListHttpFunctionsResult( PlayFabCloudScriptListHttpFunctionsResult* result )
{
    // result.functions = PlayFabCloudScriptHttpFunctionModel const* const*;
    // result.functionsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

HRESULT AutoGenCloudScriptTests::ValidatePlayFabCloudScriptListQueuedFunctionsResult( PlayFabCloudScriptListQueuedFunctionsResult* result )
{
    // result.functions = PlayFabCloudScriptQueuedFunctionModel const* const*;
    // result.functionsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenCloudScriptTests::FillPlayFabCloudScriptPostFunctionResultForEntityTriggeredActionRequest( PlayFab::CloudScriptModels::PostFunctionResultForEntityTriggeredActionRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"FunctionResult\": { \"ExecutionTimeMilliseconds\": 367, \"FunctionName\": \"LevelCompleted\", \"FunctionResult\": {  \"newScore\": 25,  \"isWinner\": false } }}" );
    request->FromJson(inputJson);
}

void AutoGenCloudScriptTests::FillPlayFabCloudScriptPostFunctionResultForFunctionExecutionRequest( PlayFab::CloudScriptModels::PostFunctionResultForFunctionExecutionRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"FunctionResult\": { \"ExecutionTimeMilliseconds\": 367, \"FunctionName\": \"LevelCompleted\", \"FunctionResult\": {  \"newScore\": 25,  \"isWinner\": false } }}" );
    request->FromJson(inputJson);
}

void AutoGenCloudScriptTests::FillPlayFabCloudScriptPostFunctionResultForPlayerTriggeredActionRequest( PlayFab::CloudScriptModels::PostFunctionResultForPlayerTriggeredActionRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"PlayStreamEventEnvelope\": { \"EntityId\": \"1234ABCD\", \"EntityType\": \"title_player_account\", \"EventName\": \"player_logged_in\", \"EventNamespace\": \"com.playfab\", \"EventData\": \"someeventdata\", \"EventSettings\": \"someeventsettings\", \"EventToBeDropped\": false }, \"PlayerProfile\": { \"TitleId\": \"FFFF\", \"PlayerId\": \"1234ABCD\", \"Created\": \"2019-02-11T20:23:05Z\", \"LastLogin\": \"2020-02-11T20:23:05Z\", \"DisplayName\": \"Gudge\" }, \"FunctionResult\": { \"ExecutionTimeMilliseconds\": 367, \"FunctionName\": \"LevelCompleted\", \"FunctionResult\": {  \"newScore\": 25,  \"isWinner\": false } }}" );
    request->FromJson(inputJson);
}

void AutoGenCloudScriptTests::FillPlayFabCloudScriptPostFunctionResultForScheduledTaskRequest( PlayFab::CloudScriptModels::PostFunctionResultForScheduledTaskRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"ScheduledTaskId\": { \"Name\": \"MyTask\", \"Id\": \"d739e188-22f6-4d13-a4d5-df2e93d4d2f7\" }, \"FunctionResult\": { \"ExecutionTimeMilliseconds\": 367, \"FunctionName\": \"LevelCompleted\", \"FunctionResult\": {  \"newScore\": 25,  \"isWinner\": false } }}" );
    request->FromJson(inputJson);
}

void AutoGenCloudScriptTests::FillPlayFabCloudScriptRegisterHttpFunctionRequest( PlayFab::CloudScriptModels::RegisterHttpFunctionRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"FunctionName\": \"functionName\", \"FunctionUrl\": \"http://function.url\"}" );
    request->FromJson(inputJson);
}

void AutoGenCloudScriptTests::FillPlayFabCloudScriptRegisterQueuedFunctionRequest( PlayFab::CloudScriptModels::RegisterQueuedFunctionRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"FunctionName\": \"functionName\", \"QueueName\": \"fn-queue\", \"ConnectionString\": \"SampleConnectionString\"}" );
    request->FromJson(inputJson);
}

void AutoGenCloudScriptTests::FillPlayFabCloudScriptUnregisterFunctionRequest( PlayFab::CloudScriptModels::UnregisterFunctionRequest* request )
{
    // TODO: debug  test
    PlayFab::JsonDocument inputJson;
    inputJson.Parse( "{ \"FunctionName\": \"functionName\"}" );
    request->FromJson(inputJson);
}

 

}
