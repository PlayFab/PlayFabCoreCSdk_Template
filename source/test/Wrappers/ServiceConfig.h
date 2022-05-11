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
        size_t size{ 0 };
        HRESULT hr = PFServiceConfigGetConnectionStringSize(m_handle, &size);
        assert(SUCCEEDED(hr));

        std::vector<char> connectionString(size, '\0');
        hr = PFServiceConfigGetConnectionString(m_handle, size, &connectionString[0], nullptr);
        assert(SUCCEEDED(hr));
        UNREFERENCED_PARAMETER(hr);

        return String{ connectionString.data() };
    }

    String TitleId() const noexcept
    {
        size_t size{ 0 };
        HRESULT hr = PFServiceConfigGetTitleIdSize(m_handle, &size);
        assert(SUCCEEDED(hr));

        std::vector<char> titleId(size, '\0');
        hr = PFServiceConfigGetTitleId(m_handle, titleIdSize, &titleId[0], nullptr);
        assert(SUCCEEDED(hr));
        UNREFERENCED_PARAMETER(hr);

        return String{ titleId.data() };
    }

    String PlayerAccountPoolId() const noexcept
    {
        size_t size{ 0 };
        HRESULT hr = PFServiceConfigGetPlayerAccountPoolIdSize(m_handle, &size);
        assert(SUCCEEDED(hr));

        std::vector<char> playerAccountPoolId(size, '\0');
        hr = PFServiceConfigGetConnectionString(m_handle, size, &playerAccountPoolId[0], nullptr);
        assert(SUCCEEDED(hr));
        UNREFERENCED_PARAMETER(hr);

        return String{ playerAccountPoolId.data() };
    }

private:
    PFServiceConfigHandle m_handle{ nullptr };
};

}
}
