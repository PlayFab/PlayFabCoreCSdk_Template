#pragma once

#include "TestCase.h"
#include <playfab/PFGlobal.h>
#include <playfab/PFEntity.h>
#include <playfab/PFTitlePlayer.h>

namespace PlayFab
{
namespace Test
{

class ApiTests : public PlayFabApiTestCase
{
private:
    void TestAuth(TestContext& testContext);

protected:
    void AddTests() override;

public:
    void ClassSetUp() override;
    void ClassTearDown() override;

    void Tick(TestContext&) override {}

private:
    PFStateHandle stateHandle{ nullptr };
};

}
}
