#pragma once

#include "TestCase.h"
#include <playfab/PFGlobal.h>
#include <playfab/PFEntity.h>

namespace PlayFabUnit
{

class EntityTests : public PlayFabApiTestCase
{
private:
    void TestClientLogin(TestContext& testContext);
    void TestManualTokenRefresh(TestContext& testContext);
#if HC_PLATFORM == HC_PLATFORM_GDK
    void TestLoginWithXUser(TestContext& testContext);
#endif

protected:
    void AddTests() override;

public:
    PFStateHandle stateHandle{ nullptr };

    void ClassSetUp() override;
    void ClassTearDown() override;
    void SetUp(TestContext& testContext) override;

    void Tick(TestContext&) override {}
};

}
