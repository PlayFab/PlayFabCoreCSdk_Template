#include "TestAppPch.h"
#include "XAsyncDispatcher.h"

namespace PlayFab
{
namespace Test
{

XAsyncDispatcher::XAsyncDispatcher()
{

}

XAsyncDispatcher::XAsyncDispatcher(XTaskQueueHandle queue)
{
    HRESULT hr = XTaskQueueDuplicateHandle(queue, &m_queue);
    if (FAILED(hr))
    {
        throw std::exception("Failed to duplicate XTaskQueueHandle");
    }

    hr = XTaskQueueRegisterMonitor(m_queue, this, OnWorkSubmitted, &m_monitorToken);
    if (FAILED(hr))
    {
        throw std::exception("Failed to register TaskQueue monitor");
    }

    m_dispatchThread = std::thread([this]
    {
        for (;;)
        {
            if (m_shutdown)
            {
                constexpr uint32_t finalDispatchTimeout{ 2000 };
                // After m_shutdown is signaled, wait an addition 2 seconds and ensure nothing is processed.
                auto processed = XTaskQueueDispatch(m_queue, XTaskQueuePort::Work, finalDispatchTimeout);
                UNREFERENCED_PARAMETER(processed);
                assert(!processed);
                break;
            }
            else
            {
                constexpr uint32_t dispatchTimeout{ 10 };
                XTaskQueueDispatch(m_queue, XTaskQueuePort::Work, dispatchTimeout);
            }
        }
    });
}

XAsyncDispatcher::~XAsyncDispatcher()
{
    m_shutdown = true;
    m_dispatchThread.join();

    XTaskQueueUnregisterMonitor(m_queue, m_monitorToken);
    XTaskQueueCloseHandle(m_queue);
}

XTaskQueueHandle XAsyncDispatcher::Queue() const
{
    return m_queue;
}

void CALLBACK XAsyncDispatcher::OnWorkSubmitted(void* context, XTaskQueueHandle queue, XTaskQueuePort)
{
    auto pThis{ static_cast<XAsyncDispatcher*>(context) };
    assert(pThis);
    assert(queue == pThis->m_queue);

    // Nothing should be submitted to the queue after XblCleanup has completed
    assert(!pThis->m_shutdown);
}

}
}
