// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "stdafx.h"
#include "TaskQueue.h"

namespace PlayFab {

TaskQueue::TaskQueue() noexcept : TaskQueue{ nullptr }
{
}

TaskQueue::TaskQueue(XTaskQueueHandle handle) noexcept
{
    if (handle)
    {
        auto hr = XTaskQueueDuplicateHandle(handle, &m_handle);
        UNREFERENCED_PARAMETER(hr);
    }
    else
    {
        auto haveProcessQueue = XTaskQueueGetCurrentProcessTaskQueue(&m_handle);
        UNREFERENCED_PARAMETER(haveProcessQueue);
    }
}

TaskQueue::TaskQueue(const TaskQueue& other) noexcept
{
    if (other.m_handle)
    {
        auto hr = XTaskQueueDuplicateHandle(other.m_handle, &m_handle);
        UNREFERENCED_PARAMETER(hr);
    }
}

TaskQueue::TaskQueue(TaskQueue&& other) noexcept
{
    m_handle = other.m_handle;
    other.m_handle = nullptr;
}

TaskQueue& TaskQueue::operator=(TaskQueue other) noexcept
{
    std::swap(other.m_handle, m_handle);
    return *this;
}

TaskQueue::~TaskQueue() noexcept
{
    if (m_handle)
    {
        XTaskQueueCloseHandle(m_handle);
    }
}

TaskQueue TaskQueue::DeriveWorkerQueue() const noexcept
{
    return DeriveWorkerQueue(m_handle);
}

XTaskQueueHandle TaskQueue::GetHandle() const noexcept
{
    return m_handle;
}

HRESULT TaskQueue::Terminate(
    _In_ bool wait,
    _In_opt_ XTaskQueueTerminatedCallback* callback,
    _In_opt_ void* callbackContext
) const noexcept
{
    return XTaskQueueTerminate(m_handle, wait, callbackContext, callback);
}

HRESULT TaskQueue::ScheduleWork(
    _In_ XTaskQueueCallback callback,
    _In_opt_ void* callbackContext,
    _In_ uint64_t delayInMs
) const noexcept
{
    return XTaskQueueSubmitDelayedCallback(m_handle, XTaskQueuePort::Work, static_cast<uint32_t>(delayInMs), callbackContext, callback);
}

HRESULT TaskQueue::ScheduleCompeletion(
    _In_ XTaskQueueCallback callback,
    _In_opt_ void* callbackContext,
    _In_ uint64_t delayInMs
) const noexcept
{
    return XTaskQueueSubmitDelayedCallback(m_handle, XTaskQueuePort::Completion, static_cast<uint32_t>(delayInMs), callbackContext, callback);
}

TaskQueue TaskQueue::DeriveWorkerQueue(XTaskQueueHandle handle) noexcept
{
    TaskQueue derivedQueue{ nullptr };
    TaskQueue queue{ handle };

    if (!queue.m_handle)
    {
        TaskQueue processQueue{ nullptr };
        bool haveProcessQueue = XTaskQueueGetCurrentProcessTaskQueue(&processQueue.m_handle);
        if (haveProcessQueue)
        {
            queue = processQueue;
        }
    }

    XTaskQueuePortHandle worker{ nullptr };
    auto hr = XTaskQueueGetPort(queue.m_handle, XTaskQueuePort::Work, &worker);
    if (SUCCEEDED(hr))
    {
        hr = XTaskQueueCreateComposite(worker, worker, &derivedQueue.m_handle);
        UNREFERENCED_PARAMETER(hr);
    }

    return derivedQueue;
}

} // PlayFab
