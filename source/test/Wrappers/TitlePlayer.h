// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include <playfab/PFTitlePlayer.h>
#include <string>
#include <assert.h>

namespace PlayFab
{
namespace Wrappers
{

template<template<typename AllocT> class Alloc = std::allocator>
class TitlePlayer
{
public:
    using String = typename std::basic_string<char, std::char_traits<char>, Alloc<char>>;

    static TitlePlayer Wrap(PFTitlePlayerHandle handle)
    {
        // Take ownership of handle
        return TitlePlayer{ handle };
    }

    TitlePlayer(TitlePlayer const& other)
    {
        HRESULT hr = PFTitlePlayerDuplicateHandle(other.m_handle, &m_handle);
        assert(SUCCEEDED(hr));
        UNREFERENCED_PARAMETER(hr);
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

private:
    TitlePlayer(PFTitlePlayerHandle handle) : m_handle{ handle }
    {
    }

    PFTitlePlayerHandle m_handle{ nullptr };
};

}
}
