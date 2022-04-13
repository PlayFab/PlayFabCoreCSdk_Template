// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include <playfab/PFCore.h>
#include <string>
#include <assert.h>

namespace PlayFab
{
namespace Wrappers
{

template<template<typename AllocT> class Alloc = std::allocator>
class ServiceConfig
{
public:
    using String = typename std::basic_string<char, std::char_traits<char>, Alloc<char>>;

    ServiceConfig(_In_z_ const char* connectionString, _In_z_ const char* titleId, _In_z_ const char* playerAccountPoolId)
    {
        HRESULT hr = PFServiceConfigCreateHandle(connectionString, titleId, playerAccountPoolId, &m_handle);
        assert(SUCCEEDED(hr));
        UNREFERENCED_PARAMETER(hr);
    }

    ServiceConfig(ServiceConfig const& other)
    {
        HRESULT hr = PFServiceConfigDuplicateHandle(other.m_handle, &m_handle);
        assert(SUCCEEDED(hr));
        UNREFERENCED_PARAMETER(hr);
    }

    ServiceConfig(ServiceConfig&& other)
    {
        std::swap(m_handle, other.m_handle);
    }

    ServiceConfig& operator=(ServiceConfig other)
    {
        std::swap(m_handle, other.m_handle);
        return *this;
    }

    virtual ~ServiceConfig()
    {
        PFServiceConfigCloseHandle(m_handle);
    }

    PFServiceConfigHandle Handle() const noexcept
    {
        return m_handle;
    }

    String ConnectionString() const noexcept
    {
        const char* connectionString{ nullptr };
        HRESULT hr = PFServiceConfigGetConnectionString(m_handle, &connectionString);
        assert(SUCCEEDED(hr));
        UNREFERENCED_PARAMETER(hr);

        return connectionString;
    }

    String TitleId() const noexcept
    {
        const char* titleId{ nullptr };
        HRESULT hr = PFServiceConfigGetTitleId(m_handle, &titleId);
        assert(SUCCEEDED(hr));
        UNREFERENCED_PARAMETER(hr);

        return titleId;
    }

    String PlayerAccountPoolId() const noexcept
    {
        const char* playerAccountPoolId{ nullptr };
        HRESULT hr = PFServiceConfigGetConnectionString(m_handle, &playerAccountPoolId);
        assert(SUCCEEDED(hr));
        UNREFERENCED_PARAMETER(hr);

        return playerAccountPoolId;
    }

private:
    PFServiceConfigHandle m_handle{ nullptr };
};

}
}
