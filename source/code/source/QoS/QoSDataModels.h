#pragma once

#include <playfab/PFQoS.h>

namespace PlayFab
{
namespace QoS
{

struct Server
{
    String region;
    String address;
};

struct RegionResult : public Wrappers::ModelWrapper<PFQoSRegionResult, Allocator>
{
    using ModelWrapperType = RegionResult;
    using ModelType = typename PFQoSRegionResult;

    RegionResult(const String& _region);
    RegionResult(const RegionResult& src);
    RegionResult(RegionResult&& src) = default;
    RegionResult& operator=(const RegionResult& src);
    RegionResult& operator=(RegionResult&& src) = default;
    ~RegionResult() = default;

    void AddPingResult(Result<uint32_t> pingResult);

    static size_t RequiredBufferSize(const PFQoSRegionResult& model);
    static HRESULT Copy(const PFQoSRegionResult& input, PFQoSRegionResult& output, ModelBuffer& buffer);

private:
    String m_region;
    uint32_t m_totalLatencyMs;
};

struct Measurements : public Wrappers::ModelWrapper<PFQoSMeasurements, Allocator>, public OutputModel<PFQoSMeasurements>
{
    using ModelWrapperType = Measurements;
    using ModelType = typename PFQoSMeasurements;

    Measurements() = default;
    Measurements(const UnorderedMap<String, RegionResult>& regionResultsMap);
    Measurements(const Measurements& src);
    Measurements(Measurements&& src);
    ~Measurements() = default;

    void FromJson(const JsonValue& input) override;
    size_t RequiredBufferSize() const override;
    Result<PFQoSMeasurements const*> Copy(ModelBuffer& buffer) const override;

private:
    static Vector<RegionResult> SortRegionResults(const UnorderedMap<String, RegionResult>& regionResultsMap);

    ModelVector<RegionResult> m_regionResults;
};

} // namespace QoS
} // namespace PlayFab
