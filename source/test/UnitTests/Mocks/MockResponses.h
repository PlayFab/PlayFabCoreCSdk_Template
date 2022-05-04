#pragma once

namespace PlayFab
{
namespace UnitTests
{

constexpr char* kMockAuthResponseBody =
R"({
  "code": 200,
  "status": "OK",
  "data": {
    "MasterPlayerAccount": {
      "EntityToken": "MasterPlayerMockEntityToken",
      "Entity": {
        "Id": "MasterPlayerId",
        "Type": "master_player_account",
        "TypeString": "master_player_account",
        "IsTitle": false,
        "IsNamespace": false,
        "IsService": false,
        "IsMasterPlayer": true,
        "IsTitlePlayer": false
      }
    },
    "TitlePlayerAccount": {
      "EntityToken": "TitlePlayerMockEntityToken",
      "Entity": {
        "Id": "TitlePlayerId",
        "Type": "title_player_account",
        "TypeString": "title_player_account",
        "IsTitle": false,
        "IsNamespace": false,
        "IsService": false,
        "IsMasterPlayer": false,
        "IsTitlePlayer": true
      }
    }
  }
})";

}
}