#include "pch.h"
#include "Memory.h"

namespace PlayFab
{

// Default memory functions
_Ret_maybenull_ _Post_writable_byte_size_(size) void* DefaultAlloc(size_t size) noexcept
{
    return operator new(size);
}

void DefaultFree(_In_ _Post_invalid_ void* pointer) noexcept
{
    operator delete(pointer);
}

PFMemoryHooks& GetMemoryHooks()
{
    // The memory hooks are a function level static so we have guarantees about initialization order. If we make them a
    // global static, the initialization of other globals that require allocation may cause a crash
    static PFMemoryHooks s_hooks{ DefaultAlloc, DefaultFree };
    return s_hooks;
}

HRESULT SetMemoryHooks(PFMemoryHooks& newHooks)
{
    auto& hooks = GetMemoryHooks();

    if (newHooks.alloc && newHooks.free)
    {
        hooks = newHooks;
    }
    else if (!newHooks.alloc && !newHooks.free)
    {
        hooks.alloc = DefaultAlloc;
        hooks.free = DefaultFree;
    }
    else
    {
        // Hooks must be set together
        return E_INVALIDARG;
    }

    return S_OK;
}

void* Alloc(size_t size)
{
    void* pointer = GetMemoryHooks().alloc(size);

    assert(pointer);
    return pointer;
}

void Free(void* pointer) noexcept
{
    if (pointer)
    {
        GetMemoryHooks().free(pointer);
    }
}

void* JsonAllocator::Malloc(size_t size)
{
    return PlayFab::Alloc(size);
}

void* JsonAllocator::Realloc(void* originalPtr, size_t originalSize, size_t newSize)
{
    void* newPtr = nullptr;
    if (newSize > 0)
    {
        newPtr = PlayFab::Alloc(newSize);
        memcpy(newPtr, originalPtr, (originalSize < newSize ? originalSize : newSize));
    }
    Free(originalPtr);
    return newPtr;
}

void JsonAllocator::Free(void* ptr)
{
    PlayFab::Free(ptr);
}

}
