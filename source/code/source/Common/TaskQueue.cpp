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
    _In_opt_ std::function<void()> queueTerminatedCallback
) const noexcept
{
    auto context = queueTerminatedCallback ? MakeUnique<std::function<void()>>(std::move(queueTerminatedCallback)) : nullptr;

    RETURN_IF_FAILED(XTaskQueueTerminate(m_handle, wait, context.get(),
        [](void* context)
    {
        if (context)
        {
            // Be sure to retake ownership of the callback here
            UniquePtr<std::function<void()>> callback{ reinterpret_cast<std::function<void()>*>(context) };
            (*callback)();
        }
    }));

    context.release();
    return S_OK;
}

HRESULT TaskQueue::RunWork(
    _In_ AsyncWork&& work,
    _In_ uint64_t delayInMs
) const noexcept
{
    return RunOnPort(XTaskQueuePort::Work, std::move(work), delayInMs);
}

HRESULT TaskQueue::RunCompletion(
    _In_ AsyncWork&& work,
    _In_ uint64_t delayInMs
) const noexcept
{
    return RunOnPort(XTaskQueuePort::Completion, std::move(work), delayInMs);
}

HRESULT TaskQueue::RunOnPort(
    _In_ XTaskQueuePort port,
    _In_ AsyncWork&& work,
    _In_ uint64_t delayInMs
) const noexcept
{
    RETURN_HR_INVALIDARG_IF_NULL(work);

    auto context{ MakeUnique<AsyncWork>(std::move(work)) };

    RETURN_IF_FAILED(XTaskQueueSubmitDelayedCallback(m_handle, port, static_cast<uint32_t>(delayInMs), context.get(),
        [](void* context, bool canceled)
    {
        UniquePtr<AsyncWork> work{ static_cast<AsyncWork*>(context) };
        if (!canceled)
        {
            (*work)();
        }
    }));

    context.release();
    return S_OK;
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
