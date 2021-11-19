#pragma once

#include "TestCase.h"
#include <playfab/PlayFabGlobal.h>
#include <playfab/PlayFabEventManagerApi.h>

namespace PlayFabUnit
{

class EventManagerTests : public PlayFabApiTestCase
{
private:
    void TestWriteEvent(TestContext& testContext);
    void WriteEventsStressTest(TestContext& testContext);

protected:
    void AddTests() override;

public:
    PlayFabStateHandle stateHandle{ nullptr };
    PFEntityHandle entityHandle{ nullptr };

    void ClassSetUp() override;
    void ClassTearDown() override;
    void SetUp(TestContext& testContext) override;
    void TearDown(TestContext& testContext) override;

    void Tick(TestContext&) override {}
};

}
