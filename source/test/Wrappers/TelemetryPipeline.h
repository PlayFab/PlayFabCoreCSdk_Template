#include <playfab/PFTelemetry.h>
#include <assert.h>
#include <algorithm>

namespace PlayFab
{
namespace Wrappers
{

class TelemetryPipeline
{
public:
    TelemetryPipeline(PFTitlePlayerHandle uploadingPlayer, XTaskQueueHandle queue) noexcept
    {
        HRESULT hr = PFTelemetryPipelineCreateHandle(uploadingPlayer, queue, nullptr, nullptr, &m_handle);
        assert(SUCCEEDED(hr));
        UNREFERENCED_PARAMETER(hr);
    }

    TelemetryPipeline(PFTitlePlayerHandle uploadingPlayer, XTaskQueueHandle queue, uint32_t maxWaitTimeInSeconds, uint32_t pollTimeInMs) noexcept
    {
        HRESULT hr = PFTelemetryPipelineCreateHandle(uploadingPlayer, queue, &maxWaitTimeInSeconds, &pollTimeInMs, &m_handle);
        assert(SUCCEEDED(hr));
        UNREFERENCED_PARAMETER(hr);
    }

    TelemetryPipeline(TelemetryPipeline const& other)
    {
        HRESULT hr = PFTelemetryPipelineDuplicateHandle(other.m_handle, &m_handle);
        assert(SUCCEEDED(hr));
        UNREFERENCED_PARAMETER(hr);
    }

    TelemetryPipeline(TelemetryPipeline&& other)
    {
        std::swap(m_handle, other.m_handle);
    }

    TelemetryPipeline& operator=(TelemetryPipeline other)
    {
        std::swap(m_handle, other.m_handle);
        return *this;
    }

    virtual ~TelemetryPipeline()
    {
        PFTelemetryPipelineCloseHandle(m_handle);
    }

    PFTelemetryPipelineHandle Handle() const noexcept
    {
        return m_handle;
    }

    HRESULT EmitEvent(const char* eventNamespace, const char* eventName, const char* eventPayloadJson) const noexcept
    {
        return PFTelemetryPipelineEmitEvent(m_handle, eventNamespace, eventName, eventPayloadJson);
    }

private:
    PFTelemetryPipelineHandle m_handle{ nullptr };
};

}
}
