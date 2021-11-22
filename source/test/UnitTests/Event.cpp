#include "pch.h"
#include "event.h"

namespace PlayFab
{
namespace UnitTests
{

Event::Event() noexcept
{
    m_handle = CreateEvent(nullptr, false, false, nullptr);
    assert(m_handle);
}

Event::~Event() noexcept
{
    CloseHandle(m_handle);
}

void Event::Set() noexcept
{
    auto result = SetEvent(m_handle);
    assert(result);
    UNREFERENCED_PARAMETER(result);
}

void Event::Wait() noexcept
{
    WaitForSingleObject(m_handle, INFINITE);
}

}
}