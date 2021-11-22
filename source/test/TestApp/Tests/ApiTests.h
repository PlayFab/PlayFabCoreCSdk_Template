#pragma once

#include "TestCase.h"
#include <playfab/PFGlobal.h>
#include <playfab/PFEntity.h>
#include <playfab/PFTitlePlayer.h>

namespace PlayFabUnit
{

class ApiTests : public PlayFabApiTestCase
{
private:
    // Choose a representative set of APIs to test. This includes at least one API for each GetResult pattern and
    // at least one API for each Auth method (SessionTicket, EntityToken, SecretKey, None)

    void TestApiStaticSizeResult(TestContext& testContext);
    void TestApiSerializableResult(TestContext& testContext);

    void TestApiSessionTicket(TestContext& testContext);
    void TestApiEntityToken(TestContext& testContext);
    void TestApiSecretKey(TestContext& testContext);
    void TestApiNoAuth(TestContext& testContext);

    // Tests for /Authentication/GetEntityToken APIs since they are not auto generated
    void TestGetEntityTokenWithAuthContext(TestContext& testContext);
    void TestGetEntityTokenWithSecretKey(TestContext& testContext);

    // Test for QoS API
    void TestGetQoSMeasurements(TestContext& testContext);

protected:
    void AddTests() override;

public:
    PFStateHandle stateHandle{ nullptr };
    PFTitlePlayerHandle titlePlayerHandle{ nullptr };
    PFEntityHandle entityHandle{ nullptr };

    void ClassSetUp() override;
    void ClassTearDown() override;
    void SetUp(TestContext& testContext) override;

    void Tick(TestContext&) override {}
};

}
