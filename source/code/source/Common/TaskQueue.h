// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include "XTaskQueue.h"

namespace PlayFab
{

using AsyncWork = std::function<void()>;

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

    // Terminates a task queue by canceling all pending items and preventing new items from being queued.
    HRESULT Terminate(
        _In_ bool wait,
        _In_opt_ std::function<void()> queueTerminatedCallback = nullptr
    ) const noexcept;

    // Submits a callback to the queue for the work port.  The callback will be added to the queue after 
    // delayMs milliseconds.
    HRESULT RunWork(
        _In_ AsyncWork&& work,
        _In_ uint64_t delayInMs = 0
    ) const noexcept;

    // Submits a callback to the queue for the completion port.  The callback will be added to the queue after 
    // delayMs milliseconds.
    HRESULT RunCompletion(
        _In_ AsyncWork&& work,
        _In_ uint64_t delayInMs = 0
    ) const noexcept;

private:
    HRESULT RunOnPort(
        _In_ XTaskQueuePort port,
        _In_ AsyncWork&& work,
        _In_ uint64_t delayInMs = 0
    ) const noexcept;

    XTaskQueueHandle m_handle{ nullptr };
};

} // PlayFab
