#pragma once

#include "TestCase.h"

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
    PFServiceConfigHandle serviceConfig{ nullptr };
};

}
}
