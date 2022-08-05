// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include <playfab/core/PFTitlePlayer.h>
#include "TypeWrappers.h"
#include "PlayFabException.h"
#include <string>

namespace PlayFab
{
namespace Wrappers
{

template<template<typename AllocT> class Alloc = std::allocator>
class TitlePlayer
{
public:
    using String = typename std::basic_string<char, std::char_traits<char>, Alloc<char>>;
    template<typename T>
    using Vector = typename std::vector<T, Alloc<T>>;

    // Creates a TitlePlayer by wrapping a PFTitlePlayerHandle (transfers ownership of the handle)
    static TitlePlayer Wrap(PFTitlePlayerHandle handle)
    {
        return TitlePlayer{ handle };
    }

    // Creates a TitlePlayer by duplicating a PFTitlePlayerHandle (caller still owns provided handle)
    static TitlePlayer Duplicate(PFTitlePlayerHandle handle)
    {
        PFTitlePlayerHandle duplicatedHandle;
        THROW_IF_FAILED(PFTitlePlayerDuplicateHandle(handle, &duplicatedHandle));
        return TitlePlayer{ duplicatedHandle };
    }

    TitlePlayer(TitlePlayer const& other)
    {
        THROW_IF_FAILED(PFTitlePlayerDuplicateHandle(other.m_handle, &m_handle));
    }

    TitlePlayer(TitlePlayer&& other)
    {
        std::swap(m_handle, other.m_handle);
    }

    TitlePlayer& operator=(TitlePlayer other)
    {
        std::swap(m_handle, other.m_handle);
        return *this;
    }

    virtual ~TitlePlayer()
    {
        PFTitlePlayerCloseHandle(m_handle);
    }

    PFTitlePlayerHandle Handle() const noexcept
    {
        return m_handle;
    }

    PFEntityKeyWrapper<Alloc> EntityKey() const
    {
        size_t size{};
        THROW_IF_FAILED(PFTitlePlayerGetEntityKeySize(m_handle, &size));

        PFEntityKey const* pEntityKey{};
        Vector<char> buffer(size);
        THROW_IF_FAILED(PFTitlePlayerGetEntityKey(m_handle, buffer.size(), buffer.data(), &pEntityKey, nullptr));

        return *pEntityKey;
    }

private:
    TitlePlayer(PFTitlePlayerHandle handle) : m_handle{ handle }
    {
    }

    PFTitlePlayerHandle m_handle{ nullptr };
};

}
}
