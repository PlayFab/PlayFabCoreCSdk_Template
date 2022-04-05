// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include "XTaskQueue.h"

namespace PlayFab
{

// RAII wrapper around XTaskQueueHandle
class TaskQueue
{
public:
    TaskQueue() noexcept;
    TaskQueue(XTaskQueueHandle handle) noexcept;
    TaskQueue(const TaskQueue& other) noexcept;
    TaskQueue(TaskQueue&& other) noexcept;
    TaskQueue& operator=(TaskQueue other) noexcept;
    ~TaskQueue() noexcept;

    TaskQueue DeriveWorkerQueue() const noexcept;
    static TaskQueue DeriveWorkerQueue(XTaskQueueHandle handle) noexcept;

    XTaskQueueHandle GetHandle() const noexcept;

    HRESULT Terminate(
        _In_ bool wait,
        _In_opt_ XTaskQueueTerminatedCallback* callback,
        _In_opt_ void* callbackContext
    ) const noexcept;

    HRESULT ScheduleWork(
        _In_ XTaskQueueCallback callback,
        _In_opt_ void* callbackContext,
        _In_ uint64_t delayInMs
    ) const noexcept;

    HRESULT ScheduleCompeletion(
        _In_ XTaskQueueCallback callback,
        _In_opt_ void* callbackContext,
        _In_ uint64_t delayInMs
    ) const noexcept;

private:
    XTaskQueueHandle m_handle{ nullptr };
};

} // PlayFab
