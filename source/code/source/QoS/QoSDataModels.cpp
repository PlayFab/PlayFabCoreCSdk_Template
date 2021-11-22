#include "stdafx.h"
#include "QoSDataModels.h"

namespace PlayFab
{
namespace QoS
{

RegionResult::RegionResult(const String& _region) :
    ModelWrapper<PFQoSRegionResult, Allocator>{},
    m_region{ _region },
    m_totalLatencyMs{ 0 }
{
    m_model.region = m_region.data();
}

RegionResult::RegionResult(const RegionResult& src) :
    ModelWrapper<PFQoSRegionResult, Allocator>{ src },
    m_region{ src.m_region },
    m_totalLatencyMs{ src.m_totalLatencyMs }
{
    m_model.region = m_region.data();
}

RegionResult& RegionResult::operator=(const RegionResult& src)
{
    m_region = src.m_region;
    m_totalLatencyMs = src.m_totalLatencyMs;
    m_model.region = m_region.data();
    m_model.averageLatencyMs = src.m_model.averageLatencyMs;
    m_model.successfulPingCount = src.m_model.successfulPingCount;
    m_model.failedPingCount = src.m_model.failedPingCount;
    return *this;
}

void RegionResult::AddPingResult(Result<uint32_t> pingResult)
{
    if (Succeeded(pingResult))
    {
        ++m_model.successfulPingCount;
        m_totalLatencyMs += pingResult.Payload();
        m_model.averageLatencyMs = m_totalLatencyMs / m_model.successfulPingCount;
    }
    else
    {
        ++m_model.failedPingCount;
    }
}

size_t RegionResult::RequiredBufferSize(const PFQoSRegionResult& model)
{
    size_t requiredSize{ alignof(ModelType) + sizeof(ModelType) };
    if (model.region)
    {
        requiredSize += (std::strlen(model.region) + 1);
    }
    return requiredSize;
}

HRESULT RegionResult::Copy(const PFQoSRegionResult& input, PFQoSRegionResult& output, ModelBuffer& buffer)
{
    output = input;
    auto propCopyResult = buffer.CopyTo(input.region);
    RETURN_IF_FAILED(propCopyResult.hr);
    output.region = propCopyResult.ExtractPayload();
    return S_OK;
}

Measurements::Measurements(const UnorderedMap<String, RegionResult>& regionResultsMap) :
    ModelWrapper<PFQoSMeasurements, Allocator>{}
{
    auto sortedRegionResults = SortRegionResults(regionResultsMap);
    for (auto&& regionResult : sortedRegionResults)
    {
        m_regionResults.push_back(std::move(regionResult));
    }

    m_model.regionResults = m_regionResults.empty() ? nullptr : m_regionResults.data();
    m_model.regionResultsCount = static_cast<uint32_t>(m_regionResults.size());
}

Measurements::Measurements(const Measurements& src) :
    ModelWrapper<PFQoSMeasurements, Allocator>{ src },
    m_regionResults{ src.m_regionResults }
{
    m_model.regionResults = m_regionResults.empty() ? nullptr : m_regionResults.data();
}

Measurements::Measurements(Measurements&& src) :
    ModelWrapper<PFQoSMeasurements, Allocator>{ src },
    m_regionResults{ std::move(src.m_regionResults) }
{
    m_model.regionResults = m_regionResults.empty() ? nullptr : m_regionResults.data();
}

void Measurements::FromJson(const JsonValue&)
{
    // Should never be called
    assert(false);
}

size_t Measurements::RequiredBufferSize() const
{
    size_t requiredSize{ alignof(ModelType) + sizeof(ModelType) };
    requiredSize += (alignof(PFQoSRegionResult*) + sizeof(PFQoSRegionResult*) * m_model.regionResultsCount);
    for (size_t i = 0; i < m_regionResults.size(); ++i)
    {
        requiredSize += RegionResult::RequiredBufferSize(*m_model.regionResults[i]);
    }
    return requiredSize;
}

Result<PFQoSMeasurements const*> Measurements::Copy(ModelBuffer& buffer) const
{
    // Alloc
    auto allocResult = buffer.Alloc<PFQoSMeasurements>(1);
    RETURN_IF_FAILED(allocResult.hr);
    // Copy
    auto outputPtr = allocResult.ExtractPayload();
    *outputPtr = m_model;
    {
        auto propCopyResult = buffer.CopyToArray<RegionResult>(m_model.regionResults, m_model.regionResultsCount);
        RETURN_IF_FAILED(propCopyResult.hr);
        outputPtr->regionResults = propCopyResult.ExtractPayload();
    }
    return outputPtr;
}

Vector<RegionResult> Measurements::SortRegionResults(const UnorderedMap<String, RegionResult>& regionResultsMap)
{
    Vector<RegionResult> regionResults;
    regionResults.reserve(regionResultsMap.size());

    std::transform(regionResultsMap.begin(), regionResultsMap.end(), std::back_inserter(regionResults), [](const auto& mapEntry)
    {
        return mapEntry.second;
    });

    std::sort(regionResults.begin(), regionResults.end(), [](const RegionResult& r, const RegionResult& l)
    {
        return r.Model().averageLatencyMs < l.Model().averageLatencyMs && r.Model().successfulPingCount > 0;
    });

    return regionResults;
}

} // namespace QoS
} // namespace PlayFab
