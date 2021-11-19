#include "TestAppPch.h"
#include "TestContext.h"
#include "TestApp.h"
#include "AutoGenGroupsTests.h"
#include "XAsyncHelper.h"

namespace PlayFabUnit
{

using namespace PlayFab::Wrappers;

#pragma region AcceptGroupApplication

void AutoGenGroupsTests::FillAcceptGroupApplicationPrerequisiteGetGroupRequest(PFGroupsGetGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroupName("Permanent Group");
}

HRESULT AutoGenGroupsTests::StoreAcceptGroupApplicationPrerequisitePFGroupsGetGroupResponse(std::shared_ptr<GetGroupResponseHolder> result)
{
    testData.m_GetGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillAcceptGroupApplicationPrerequisiteApplyToGroupRequest(PFGroupsApplyToGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
}

HRESULT AutoGenGroupsTests::StoreAcceptGroupApplicationPrerequisitePFGroupsApplyToGroupResponse(std::shared_ptr<ApplyToGroupResponseHolder> result)
{
    testData.m_ApplyToGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillAcceptGroupApplicationRequest(PFGroupsAcceptGroupApplicationRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"Entity\": { \"Id\": \"90901000\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    request.SetEntity(*testData.m_ApplyToGroupResponse->result->entity->key);
}

void AutoGenGroupsTests::FillAcceptGroupApplicationCleanupRemoveMembersRequest(PFGroupsRemoveMembersRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"RoleId\": \"ABC1234DEF\", \"Members\": [ {  \"Id\": \"90901000\",  \"Type\": \"title_player_account\",  \"TypeString\": \"title_player_account\" } ]}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    ModelVector<PFEntityKeyWrapper<>> members;
    members.push_back(*testData.m_ApplyToGroupResponse->result->entity->key);
    request.SetMembers(std::move(members));
}

#pragma endregion

#pragma region AcceptGroupInvitation

void AutoGenGroupsTests::FillAcceptGroupInvitationPrerequisiteGetGroupRequest(PFGroupsGetGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroupName("Permanent Group");
}

HRESULT AutoGenGroupsTests::StoreAcceptGroupInvitationPrerequisitePFGroupsGetGroupResponse(std::shared_ptr<GetGroupResponseHolder> result)
{
    testData.m_GetGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillAcceptGroupInvitationPrerequisiteInviteToGroupRequest(PFGroupsInviteToGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"RoleId\": \"awesomepeople\", \"Entity\": { \"Id\": \"90901000\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    request.SetEntity(PFEntityKey{ "33D5E873FB4D8629", "title_player_account" });
}

HRESULT AutoGenGroupsTests::StoreAcceptGroupInvitationPrerequisitePFGroupsInviteToGroupResponse(std::shared_ptr<InviteToGroupResponseHolder> result)
{
    testData.m_InviteToGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillAcceptGroupInvitationRequest(PFGroupsAcceptGroupInvitationRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
}

void AutoGenGroupsTests::FillAcceptGroupInvitationCleanupRemoveMembersRequest(PFGroupsRemoveMembersRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"RoleId\": \"ABC1234DEF\", \"Members\": [ {  \"Id\": \"90901000\",  \"Type\": \"title_player_account\",  \"TypeString\": \"title_player_account\" } ]}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    ModelVector<PFEntityKeyWrapper<>> members;
    members.push_back(*testData.m_InviteToGroupResponse->result->invitedEntity->key);
    request.SetMembers(std::move(members));
}

#pragma endregion

#pragma region AddMembers

void AutoGenGroupsTests::FillAddMembersPrerequisiteGetGroupRequest(PFGroupsGetGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroupName("Permanent Group");
}

HRESULT AutoGenGroupsTests::StoreAddMembersPrerequisitePFGroupsGetGroupResponse(std::shared_ptr<GetGroupResponseHolder> result)
{
    testData.m_GetGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillAddMembersRequest(PFGroupsAddMembersRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"Members\": [ {  \"Id\": \"90901000\",  \"Type\": \"title_player_account\",  \"TypeString\": \"title_player_account\" } ]}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    ModelVector<PFEntityKeyWrapper<>> members;
    members.push_back(PFEntityKey{ "FED18FB0293BA445", "title_player_account" });
    request.SetMembers(std::move(members));
}

void AutoGenGroupsTests::FillAddMembersCleanupRemoveMembersRequest(PFGroupsRemoveMembersRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"RoleId\": \"ABC1234DEF\", \"Members\": [ {  \"Id\": \"90901000\",  \"Type\": \"title_player_account\",  \"TypeString\": \"title_player_account\" } ]}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    ModelVector<PFEntityKeyWrapper<>> members;
    members.push_back(PFEntityKey{ "FED18FB0293BA445", "title_player_account" });
    request.SetMembers(std::move(members));
}

#pragma endregion

#pragma region ApplyToGroup

void AutoGenGroupsTests::FillApplyToGroupPrerequisiteGetGroupRequest(PFGroupsGetGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroupName("Permanent Group");
}

HRESULT AutoGenGroupsTests::StoreApplyToGroupPrerequisitePFGroupsGetGroupResponse(std::shared_ptr<GetGroupResponseHolder> result)
{
    testData.m_GetGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillApplyToGroupRequest(PFGroupsApplyToGroupRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
}

HRESULT AutoGenGroupsTests::ValidatePFGroupsApplyToGroupResponse(PFGroupsApplyToGroupResponse* result)
{
    // result.entity = PFGroupsEntityWithLineage const*;
    // result.expires = time_t;
    // result.group = PFEntityKey const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenGroupsTests::FillApplyToGroupCleanupRemoveGroupApplicationRequest(PFGroupsRemoveGroupApplicationRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"Entity\": { \"Id\": \"90901000\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    request.SetEntity(PFEntityKey{ "33D5E873FB4D8629", "title_player_account" });
}

#pragma endregion

#pragma region BlockEntity

void AutoGenGroupsTests::FillBlockEntityPrerequisiteGetGroupRequest(PFGroupsGetGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroupName("Permanent Group");
}

HRESULT AutoGenGroupsTests::StoreBlockEntityPrerequisitePFGroupsGetGroupResponse(std::shared_ptr<GetGroupResponseHolder> result)
{
    testData.m_GetGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillBlockEntityRequest(PFGroupsBlockEntityRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"Entity\": { \"Id\": \"90901000\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    request.SetEntity(PFEntityKey{ "93402701D5183557", "title_player_account" });
}

void AutoGenGroupsTests::FillBlockEntityCleanupUnblockEntityRequest(PFGroupsUnblockEntityRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"Entity\": { \"Id\": \"90901000\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    request.SetEntity(PFEntityKey{ "93402701D5183557", "title_player_account" });
}

#pragma endregion

#pragma region ChangeMemberRole

void AutoGenGroupsTests::FillChangeMemberRolePrerequisiteGetGroupRequest(PFGroupsGetGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroupName("Permanent Group");
}

HRESULT AutoGenGroupsTests::StoreChangeMemberRolePrerequisitePFGroupsGetGroupResponse(std::shared_ptr<GetGroupResponseHolder> result)
{
    testData.m_GetGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillChangeMemberRoleRequest(PFGroupsChangeMemberRoleRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"OriginRoleId\": \"awesomepeople\", \"DestinationRoleId\": \"members\", \"Members\": [ {  \"Id\": \"90901000\",  \"Type\": \"title_player_account\",  \"TypeString\": \"title_player_account\" } ]}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    request.SetOriginRoleId("members");
    request.SetDestinationRoleId("testrole");
    ModelVector<PFEntityKeyWrapper<>> members;
    members.push_back(PFEntityKey{ "6037570B9CA839BF", "title_player_account" });
    request.SetMembers(std::move(members));
}

void AutoGenGroupsTests::FillChangeMemberRoleCleanupChangeMemberRoleRequest(PFGroupsChangeMemberRoleRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"OriginRoleId\": \"awesomepeople\", \"DestinationRoleId\": \"members\", \"Members\": [ {  \"Id\": \"90901000\",  \"Type\": \"title_player_account\",  \"TypeString\": \"title_player_account\" } ]}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    request.SetOriginRoleId("testrole");
    request.SetDestinationRoleId("members");
    ModelVector<PFEntityKeyWrapper<>> members;
    members.push_back(PFEntityKey{ "6037570B9CA839BF", "title_player_account" });
    request.SetMembers(std::move(members));
}

#pragma endregion

#pragma region CreateGroup

void AutoGenGroupsTests::FillCreateGroupRequest(PFGroupsCreateGroupRequestWrapper<>& request)
{
    // Example Request: "{ \"GroupName\": \"Example Group\"}"
    request.SetGroupName("Example Group");
}

HRESULT AutoGenGroupsTests::ValidatePFGroupsCreateGroupResponse(PFGroupsCreateGroupResponse* result)
{
    // result.adminRoleId = const char*;
    // result.created = time_t;
    // result.group = PFEntityKey const*;
    // result.groupName = const char*;
    // result.memberRoleId = const char*;
    // result.profileVersion = int32_t;
    // result.roles = struct PFStringDictionaryEntry const*;
    // result.rolesCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenGroupsTests::FillCreateGroupCleanupGetGroupRequest(PFGroupsGetGroupRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroupName("Example Group");
}

HRESULT AutoGenGroupsTests::StoreCreateGroupCleanupPFGroupsGetGroupResponse(std::shared_ptr<GetGroupResponseHolder> result)
{
    testData.m_GetGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillCreateGroupCleanupDeleteGroupRequest(PFGroupsDeleteGroupRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
}

#pragma endregion

#pragma region CreateRole

void AutoGenGroupsTests::FillCreateRolePrerequisiteGetGroupRequest(PFGroupsGetGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroupName("Permanent Group");
}

HRESULT AutoGenGroupsTests::StoreCreateRolePrerequisitePFGroupsGetGroupResponse(std::shared_ptr<GetGroupResponseHolder> result)
{
    testData.m_GetGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillCreateGroupRoleRequest(PFGroupsCreateGroupRoleRequestWrapper<>& request)
{
    // Example Request: "{ \"RoleId\": \"example\", \"RoleName\": \"Example Role\", \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetRoleId("example");
    request.SetRoleName("Example Role");
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
}

HRESULT AutoGenGroupsTests::ValidatePFGroupsCreateGroupRoleResponse(PFGroupsCreateGroupRoleResponse* result)
{
    // result.profileVersion = int32_t;
    // result.roleId = const char*;
    // result.roleName = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenGroupsTests::FillCreateRoleCleanupDeleteRoleRequest(PFGroupsDeleteRoleRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"RoleId\": \"ABC1234DEF\"}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    request.SetRoleId("example");
}

#pragma endregion

#pragma region DeleteGroup

void AutoGenGroupsTests::FillDeleteGroupPrerequisiteCreateGroupRequest(PFGroupsCreateGroupRequestWrapper<>& request)
{
    // Example request: "{ \"GroupName\": \"Example Group\"}"
    request.SetGroupName("Example Group2");
}

HRESULT AutoGenGroupsTests::StoreDeleteGroupPrerequisitePFGroupsCreateGroupResponse(std::shared_ptr<CreateGroupResponseHolder> result)
{
    testData.m_CreateGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillDeleteGroupRequest(PFGroupsDeleteGroupRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroup(*testData.m_CreateGroupResponse->result->group);
}

#pragma endregion

#pragma region DeleteRole

void AutoGenGroupsTests::FillDeleteRolePrerequisiteGetGroupRequest(PFGroupsGetGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroupName("Permanent Group");
}

HRESULT AutoGenGroupsTests::StoreDeleteRolePrerequisitePFGroupsGetGroupResponse(std::shared_ptr<GetGroupResponseHolder> result)
{
    testData.m_GetGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillDeleteRolePrerequisiteCreateGroupRoleRequest(PFGroupsCreateGroupRoleRequestWrapper<>& request)
{
    // Example request: "{ \"RoleId\": \"example\", \"RoleName\": \"Example Role\", \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    request.SetRoleId("example");
    request.SetRoleName("Example Role");
}

HRESULT AutoGenGroupsTests::StoreDeleteRolePrerequisitePFGroupsCreateGroupRoleResponse(std::shared_ptr<CreateGroupRoleResponseHolder> result)
{
    testData.m_CreateGroupRoleResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillDeleteRoleRequest(PFGroupsDeleteRoleRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"RoleId\": \"ABC1234DEF\"}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    request.SetRoleId("example");
}

#pragma endregion

#pragma region GetGroup

void AutoGenGroupsTests::FillGetGroupRequest(PFGroupsGetGroupRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroupName("Permanent Group");
}

HRESULT AutoGenGroupsTests::ValidatePFGroupsGetGroupResponse(PFGroupsGetGroupResponse* result)
{
    // result.adminRoleId = const char*;
    // result.created = time_t;
    // result.group = PFEntityKey const*;
    // result.groupName = const char*;
    // result.memberRoleId = const char*;
    // result.profileVersion = int32_t;
    // result.roles = struct PFStringDictionaryEntry const*;
    // result.rolesCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region InviteToGroup

void AutoGenGroupsTests::FillInviteToGroupPrerequisiteGetGroupRequest(PFGroupsGetGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroupName("Permanent Group");
}

HRESULT AutoGenGroupsTests::StoreInviteToGroupPrerequisitePFGroupsGetGroupResponse(std::shared_ptr<GetGroupResponseHolder> result)
{
    testData.m_GetGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillInviteToGroupRequest(PFGroupsInviteToGroupRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"RoleId\": \"awesomepeople\", \"Entity\": { \"Id\": \"90901000\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    request.SetEntity(PFEntityKey{ "33D5E873FB4D8629", "title_player_account" });
}

HRESULT AutoGenGroupsTests::ValidatePFGroupsInviteToGroupResponse(PFGroupsInviteToGroupResponse* result)
{
    // result.expires = time_t;
    // result.group = PFEntityKey const*;
    // result.invitedByEntity = PFGroupsEntityWithLineage const*;
    // result.invitedEntity = PFGroupsEntityWithLineage const*;
    // result.roleId = const char*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenGroupsTests::FillInviteToGroupCleanupRemoveGroupInvitationRequest(PFGroupsRemoveGroupInvitationRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"Entity\": { \"Id\": \"90901000\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    request.SetEntity(PFEntityKey{ "33D5E873FB4D8629", "title_player_account" });
}

#pragma endregion

#pragma region IsMember

void AutoGenGroupsTests::FillIsMemberPrerequisiteGetGroupRequest(PFGroupsGetGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroupName("Permanent Group");
}

HRESULT AutoGenGroupsTests::StoreIsMemberPrerequisitePFGroupsGetGroupResponse(std::shared_ptr<GetGroupResponseHolder> result)
{
    testData.m_GetGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillIsMemberRequest(PFGroupsIsMemberRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"RoleId\": \"ABC1234DEF\", \"Entity\": { \"Id\": \"90901000\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    request.SetEntity(PFEntityKey{ "B64BE91E5DBD5597", "title_player_account" });
}

HRESULT AutoGenGroupsTests::ValidatePFGroupsIsMemberResponse(PFGroupsIsMemberResponse* result)
{
    // result.isMember = bool;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ListGroupApplications

void AutoGenGroupsTests::FillListGroupApplicationsPrerequisiteGetGroupRequest(PFGroupsGetGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroupName("Permanent Group");
}

HRESULT AutoGenGroupsTests::StoreListGroupApplicationsPrerequisitePFGroupsGetGroupResponse(std::shared_ptr<GetGroupResponseHolder> result)
{
    testData.m_GetGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillListGroupApplicationsRequest(PFGroupsListGroupApplicationsRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
}

HRESULT AutoGenGroupsTests::ValidatePFGroupsListGroupApplicationsResponse(PFGroupsListGroupApplicationsResponse* result)
{
    // result.applications = PFGroupsGroupApplication const* const*;
    // result.applicationsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ListGroupBlocks

void AutoGenGroupsTests::FillListGroupBlocksPrerequisiteGetGroupRequest(PFGroupsGetGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroupName("Permanent Group");
}

HRESULT AutoGenGroupsTests::StoreListGroupBlocksPrerequisitePFGroupsGetGroupResponse(std::shared_ptr<GetGroupResponseHolder> result)
{
    testData.m_GetGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillListGroupBlocksRequest(PFGroupsListGroupBlocksRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
}

HRESULT AutoGenGroupsTests::ValidatePFGroupsListGroupBlocksResponse(PFGroupsListGroupBlocksResponse* result)
{
    // result.blockedEntities = PFGroupsGroupBlock const* const*;
    // result.blockedEntitiesCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ListGroupInvitations

void AutoGenGroupsTests::FillListGroupInvitationsPrerequisiteGetGroupRequest(PFGroupsGetGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroupName("Permanent Group");
}

HRESULT AutoGenGroupsTests::StoreListGroupInvitationsPrerequisitePFGroupsGetGroupResponse(std::shared_ptr<GetGroupResponseHolder> result)
{
    testData.m_GetGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillListGroupInvitationsRequest(PFGroupsListGroupInvitationsRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
}

HRESULT AutoGenGroupsTests::ValidatePFGroupsListGroupInvitationsResponse(PFGroupsListGroupInvitationsResponse* result)
{
    // result.invitations = PFGroupsGroupInvitation const* const*;
    // result.invitationsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ListGroupMembers

void AutoGenGroupsTests::FillListGroupMembersPrerequisiteGetGroupRequest(PFGroupsGetGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroupName("Permanent Group");
}

HRESULT AutoGenGroupsTests::StoreListGroupMembersPrerequisitePFGroupsGetGroupResponse(std::shared_ptr<GetGroupResponseHolder> result)
{
    testData.m_GetGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillListGroupMembersRequest(PFGroupsListGroupMembersRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
}

HRESULT AutoGenGroupsTests::ValidatePFGroupsListGroupMembersResponse(PFGroupsListGroupMembersResponse* result)
{
    // result.members = PFGroupsEntityMemberRole const* const*;
    // result.membersCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ListMembership

void AutoGenGroupsTests::FillListMembershipPrerequisiteGetGroupRequest(PFGroupsGetGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroupName("Permanent Group");
}

HRESULT AutoGenGroupsTests::StoreListMembershipPrerequisitePFGroupsGetGroupResponse(std::shared_ptr<GetGroupResponseHolder> result)
{
    testData.m_GetGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillListMembershipRequest(PFGroupsListMembershipRequestWrapper<>&)
{
    // Example Request: "{}"
}

HRESULT AutoGenGroupsTests::ValidatePFGroupsListMembershipResponse(PFGroupsListMembershipResponse* result)
{
    // result.groups = PFGroupsGroupWithRoles const* const*;
    // result.groupsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion

#pragma region ListMembershipOpportunities

void AutoGenGroupsTests::FillListMembershipOpportunitiesPrerequisiteGetGroupRequest(PFGroupsGetGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroupName("Permanent Group");
}

HRESULT AutoGenGroupsTests::StoreListMembershipOpportunitiesPrerequisitePFGroupsGetGroupResponse(std::shared_ptr<GetGroupResponseHolder> result)
{
    testData.m_GetGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillListMembershipOpportunitiesPrerequisiteApplyToGroupRequest(PFGroupsApplyToGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
}

HRESULT AutoGenGroupsTests::StoreListMembershipOpportunitiesPrerequisitePFGroupsApplyToGroupResponse(std::shared_ptr<ApplyToGroupResponseHolder> result)
{
    testData.m_ApplyToGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillListMembershipOpportunitiesRequest(PFGroupsListMembershipOpportunitiesRequestWrapper<>&)
{
    // Example Request: "{}"
}

HRESULT AutoGenGroupsTests::ValidatePFGroupsListMembershipOpportunitiesResponse(PFGroupsListMembershipOpportunitiesResponse* result)
{
    // result.applications = PFGroupsGroupApplication const* const*;
    // result.applicationsCount = uint32_t;
    // result.invitations = PFGroupsGroupInvitation const* const*;
    // result.invitationsCount = uint32_t;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenGroupsTests::FillListMembershipOpportunitiesCleanupRemoveGroupApplicationRequest(PFGroupsRemoveGroupApplicationRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"Entity\": { \"Id\": \"90901000\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    request.SetEntity(*testData.m_ApplyToGroupResponse->result->entity->key);
}

#pragma endregion

#pragma region RemoveGroupApplication

void AutoGenGroupsTests::FillRemoveGroupApplicationPrerequisiteGetGroupRequest(PFGroupsGetGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroupName("Permanent Group");
}

HRESULT AutoGenGroupsTests::StoreRemoveGroupApplicationPrerequisitePFGroupsGetGroupResponse(std::shared_ptr<GetGroupResponseHolder> result)
{
    testData.m_GetGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillRemoveGroupApplicationPrerequisiteApplyToGroupRequest(PFGroupsApplyToGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
}

HRESULT AutoGenGroupsTests::StoreRemoveGroupApplicationPrerequisitePFGroupsApplyToGroupResponse(std::shared_ptr<ApplyToGroupResponseHolder> result)
{
    testData.m_ApplyToGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillRemoveGroupApplicationRequest(PFGroupsRemoveGroupApplicationRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"Entity\": { \"Id\": \"90901000\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    request.SetEntity(*testData.m_ApplyToGroupResponse->result->entity->key);
}

#pragma endregion

#pragma region RemoveGroupInvitation

void AutoGenGroupsTests::FillRemoveGroupInvitationPrerequisiteGetGroupRequest(PFGroupsGetGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroupName("Permanent Group");
}

HRESULT AutoGenGroupsTests::StoreRemoveGroupInvitationPrerequisitePFGroupsGetGroupResponse(std::shared_ptr<GetGroupResponseHolder> result)
{
    testData.m_GetGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillRemoveGroupInvitationPrerequisiteInviteToGroupRequest(PFGroupsInviteToGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"RoleId\": \"awesomepeople\", \"Entity\": { \"Id\": \"90901000\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    request.SetEntity(PFEntityKey{ "33D5E873FB4D8629", "title_player_account" });
}

HRESULT AutoGenGroupsTests::StoreRemoveGroupInvitationPrerequisitePFGroupsInviteToGroupResponse(std::shared_ptr<InviteToGroupResponseHolder> result)
{
    testData.m_InviteToGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillRemoveGroupInvitationRequest(PFGroupsRemoveGroupInvitationRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"Entity\": { \"Id\": \"90901000\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    request.SetEntity(*testData.m_InviteToGroupResponse->result->invitedEntity->key);
}

#pragma endregion

#pragma region RemoveMembers

void AutoGenGroupsTests::FillRemoveMembersPrerequisiteGetGroupRequest(PFGroupsGetGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroupName("Permanent Group");
}

HRESULT AutoGenGroupsTests::StoreRemoveMembersPrerequisitePFGroupsGetGroupResponse(std::shared_ptr<GetGroupResponseHolder> result)
{
    testData.m_GetGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillRemoveMembersPrerequisiteAddMembersRequest(PFGroupsAddMembersRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"Members\": [ {  \"Id\": \"90901000\",  \"Type\": \"title_player_account\",  \"TypeString\": \"title_player_account\" } ]}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    ModelVector<PFEntityKeyWrapper<>> members;
    members.push_back(PFEntityKey{ "FED18FB0293BA445", "title_player_account" });
    request.SetMembers(std::move(members));
}

void AutoGenGroupsTests::FillRemoveMembersRequest(PFGroupsRemoveMembersRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"RoleId\": \"ABC1234DEF\", \"Members\": [ {  \"Id\": \"90901000\",  \"Type\": \"title_player_account\",  \"TypeString\": \"title_player_account\" } ]}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    ModelVector<PFEntityKeyWrapper<>> members;
    members.push_back(PFEntityKey{ "FED18FB0293BA445", "title_player_account" });
    request.SetMembers(std::move(members));
}

#pragma endregion

#pragma region UnblockEntity

void AutoGenGroupsTests::FillUnblockEntityPrerequisiteGetGroupRequest(PFGroupsGetGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroupName("Permanent Group");
}

HRESULT AutoGenGroupsTests::StoreUnblockEntityPrerequisitePFGroupsGetGroupResponse(std::shared_ptr<GetGroupResponseHolder> result)
{
    testData.m_GetGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillUnblockEntityPrerequisiteBlockEntityRequest(PFGroupsBlockEntityRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"Entity\": { \"Id\": \"90901000\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    request.SetEntity(PFEntityKey{ "93402701D5183557", "title_player_account" });
}

void AutoGenGroupsTests::FillUnblockEntityRequest(PFGroupsUnblockEntityRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"Entity\": { \"Id\": \"90901000\", \"Type\": \"title_player_account\", \"TypeString\": \"title_player_account\" }}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    request.SetEntity(PFEntityKey{ "93402701D5183557", "title_player_account" });
}

#pragma endregion

#pragma region UpdateGroup

void AutoGenGroupsTests::FillUpdateGroupPrerequisiteCreateGroupRequest(PFGroupsCreateGroupRequestWrapper<>& request)
{
    // Example request: "{ \"GroupName\": \"Example Group\"}"
    request.SetGroupName("Example Group");
}

HRESULT AutoGenGroupsTests::StoreUpdateGroupPrerequisitePFGroupsCreateGroupResponse(std::shared_ptr<CreateGroupResponseHolder> result)
{
    testData.m_CreateGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillUpdateGroupRequest(PFGroupsUpdateGroupRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"GroupName\": \"My New Group Name\", \"ExpectedProfileVersion\": 17}"
    request.SetGroup(*testData.m_CreateGroupResponse->result->group);
    request.SetGroupName("My New Group Name");
}

HRESULT AutoGenGroupsTests::ValidatePFGroupsUpdateGroupResponse(PFGroupsUpdateGroupResponse* result)
{
    // result.operationReason = const char*;
    // result.profileVersion = int32_t;
    // result.setResult = PFOperationTypes const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

void AutoGenGroupsTests::FillUpdateGroupCleanupDeleteGroupRequest(PFGroupsDeleteGroupRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroup(*testData.m_CreateGroupResponse->result->group);
}

#pragma endregion

#pragma region UpdateRole

void AutoGenGroupsTests::FillUpdateRolePrerequisiteGetGroupRequest(PFGroupsGetGroupRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }}"
    request.SetGroupName("Permanent Group");
}

HRESULT AutoGenGroupsTests::StoreUpdateRolePrerequisitePFGroupsGetGroupResponse(std::shared_ptr<GetGroupResponseHolder> result)
{
    testData.m_GetGroupResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillUpdateRolePrerequisiteUpdateGroupRoleRequest(PFGroupsUpdateGroupRoleRequestWrapper<>& request)
{
    // Example request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"RoleId\": \"ABC1234DEF\", \"RoleName\": \"My New Role Name\", \"ExpectedProfileVersion\": 17}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    request.SetRoleId("testrole");
    request.SetRoleName("Prereq Role");
}

HRESULT AutoGenGroupsTests::StoreUpdateRolePrerequisitePFGroupsUpdateGroupRoleResponse(std::shared_ptr<UpdateGroupRoleResponseHolder> result)
{
    testData.m_UpdateGroupRoleResponse = result;
    return S_OK;
}

void AutoGenGroupsTests::FillUpdateGroupRoleRequest(PFGroupsUpdateGroupRoleRequestWrapper<>& request)
{
    // Example Request: "{ \"Group\": { \"Id\": \"ABC1234ABC\" }, \"RoleId\": \"ABC1234DEF\", \"RoleName\": \"My New Role Name\", \"ExpectedProfileVersion\": 17}"
    request.SetGroup(*testData.m_GetGroupResponse->result->group);
    request.SetRoleId("testrole");
    request.SetRoleName("Test Role");
}

HRESULT AutoGenGroupsTests::ValidatePFGroupsUpdateGroupRoleResponse(PFGroupsUpdateGroupRoleResponse* result)
{
    // result.operationReason = const char*;
    // result.profileVersion = int32_t;
    // result.setResult = PFOperationTypes const*;

    UNREFERENCED_PARAMETER(result);
    return S_OK;
}

#pragma endregion
 

}
