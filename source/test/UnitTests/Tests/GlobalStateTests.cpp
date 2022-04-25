#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PlayFab
{
namespace UnitTests
{

class MemoryManager
{
public:
    MemoryManager() noexcept
    {
        s_allocCalls = 0;
        s_freeCalls = 0;

        VERIFY_SUCCEEDED(PFMemSetFunctions(&MemAllocHook, &MemFreeHook));
    }

    ~MemoryManager() noexcept
    {
        VERIFY_SUCCEEDED(PFMemSetFunctions(nullptr, nullptr));
        Assert::IsTrue(s_allocCalls == s_freeCalls);
    }

private:
    static _Ret_maybenull_ _Post_writable_byte_size_(dwSize) void* STDAPIVCALLTYPE MemAllocHook(
        _In_ size_t dwSize
    )
    {
        s_allocCalls++;
        return new char[dwSize];
    }

    static void STDAPIVCALLTYPE MemFreeHook(
        _In_ void* pAddress
    )
    {
        s_freeCalls++;
        delete[] pAddress;
    }

    static std::atomic<size_t> s_allocCalls;
    static std::atomic<size_t> s_freeCalls;
};

std::atomic<size_t> MemoryManager::s_allocCalls{ 0 };
std::atomic<size_t> MemoryManager::s_freeCalls{ 0 };

TEST_CLASS(GlobalStateTests)
{
public:
    TEST_METHOD(CustomMemHooks)
    {
        MemoryManager manager;
        VERIFY_SUCCEEDED(PFInitialize(nullptr));

        XAsyncBlock async{};
        VERIFY_SUCCEEDED(PFUninitializeAsync(&async));
        VERIFY_SUCCEEDED(XAsyncGetStatus(&async, true));
    }

    TEST_METHOD(SetHooksAfterInit)
    {
        VERIFY_SUCCEEDED(PFInitialize(nullptr));

        Assert::AreEqual(E_PF_ALREADY_INITIALIZED, PFMemSetFunctions(nullptr, nullptr));

        XAsyncBlock async{};
        VERIFY_SUCCEEDED(PFUninitializeAsync(&async));
        VERIFY_SUCCEEDED(XAsyncGetStatus(&async, true));
    }
};

} // UnitTests
} // PlayFab