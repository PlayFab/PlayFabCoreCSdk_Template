#include "pch.h"
#include "TestContext.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PlayFab
{
namespace UnitTests
{

TestContext::~TestContext()
{
    std::unique_lock<std::mutex> lock{ m_mutex };
    Assert::IsTrue(m_result.has_value());
}

void TestContext::Assert(bool condition)
{
    std::unique_lock<std::mutex> lock{ m_mutex };
    if (!condition && !m_result.has_value())
    {
        m_result.emplace(E_FAIL);
    }
}

void TestContext::AssertSucceeded(HRESULT hr)
{
    std::unique_lock<std::mutex> lock{ m_mutex };
    if (FAILED(hr) && !m_result.has_value())
    {
        m_result.emplace(hr);
    }
}

void TestContext::Complete()
{
    {
        std::unique_lock<std::mutex> lock{ m_mutex };
        if (!m_result.has_value())
        {
            m_result.emplace(S_OK);
        }
    }
    m_complete.Set();
}

void TestContext::AwaitResult()
{
    m_complete.Wait();

    std::unique_lock<std::mutex> lock{ m_mutex };
    Assert::IsTrue(m_result.has_value());
    Assert::IsTrue(SUCCEEDED(*m_result));
}

}
}
