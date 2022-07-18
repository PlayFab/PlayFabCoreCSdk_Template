// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include <playfab/core/PFCore.h>
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
    template<typename T>
    using Vector = typename std::vector<T, Allocator<T>>;

    ServiceConfig(_In_z_ const char* connectionString, _In_z_ const char* titleId, _In_z_ const char* playerAccountPoolId)
    {
        THROW_IF_FAILED(PFServiceConfigCreateHandle(connectionString, titleId, playerAccountPoolId, &m_handle));
    }

    ServiceConfig(ServiceConfig const& other)
    {
        THROW_IF_FAILED(PFServiceConfigDuplicateHandle(other.m_handle, &m_handle));
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

    String ConnectionString() const
    {
        size_t size{ 0 };
        THROW_IF_FAILED(PFServiceConfigGetConnectionStringSize(m_handle, &size));

        Vector<char> connectionString(size, '\0');
        THROW_IF_FAILED(PFServiceConfigGetConnectionString(m_handle, size, &connectionString[0], nullptr));

        return String{ connectionString.data() };
    }

    String TitleId() const
    {
        size_t size{ 0 };
        THROW_IF_FAILED(PFServiceConfigGetTitleIdSize(m_handle, &size));

        Vector<char> titleId(size, '\0');
        THROW_IF_FAILED(PFServiceConfigGetTitleId(m_handle, titleId.size(), &titleId[0], nullptr));

        return String{ titleId.data() };
    }

    String PlayerAccountPoolId() const
    {
        size_t size{ 0 };
        THROW_IF_FAILED(PFServiceConfigGetPlayerAccountPoolIdSize(m_handle, &size));

        Vector<char> playerAccountPoolId(size, '\0');
        THROW_IF_FAILED(PFServiceConfigGetConnectionString(m_handle, size, &playerAccountPoolId[0], nullptr));

        return String{ playerAccountPoolId.data() };
    }

private:
    ServiceConfig(PFServiceConfigHandle handle) : m_handle{ handle }
    {
    }

    PFServiceConfigHandle m_handle{ nullptr };
};

}
}
