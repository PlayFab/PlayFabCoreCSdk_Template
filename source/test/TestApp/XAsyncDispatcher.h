#pragma once

namespace PlayFabUnit
{

class XAsyncDispatcher
{
public:
    XAsyncDispatcher();
    XAsyncDispatcher(XTaskQueueHandle queue);
    XAsyncDispatcher(const XAsyncDispatcher&) = delete;
    XAsyncDispatcher& operator=(XAsyncDispatcher) = delete;
    ~XAsyncDispatcher();

    XTaskQueueHandle Queue() const;
private:
    static void CALLBACK OnWorkSubmitted(void* context, XTaskQueueHandle queue, XTaskQueuePort);

    XTaskQueueHandle m_queue{ nullptr };
    std::thread m_dispatchThread;
    std::atomic<bool> m_shutdown{ false };
    XTaskQueueRegistrationToken m_monitorToken{};
};

}
