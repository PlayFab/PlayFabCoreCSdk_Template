#pragma once

#include <httpClient/trace.h>
#include "RunContext.h"
#include "Platform/LocalStorage.h"

HC_DECLARE_TRACE_AREA(PlayFab);

namespace PlayFab
{

#define TRACE_ERROR(msg, ...)           HC_TRACE_ERROR(PlayFab, msg, ##__VA_ARGS__)
#define TRACE_ERROR_HR(failedHr, msg)   HC_TRACE_ERROR_HR(PlayFab, failedHr, msg)

#define TRACE_WARNING(msg, ...)         HC_TRACE_WARNING(PlayFab, msg, ##__VA_ARGS__)
#define TRACE_WARNING_HR(failedHr, msg) HC_TRACE_WARNING_HR(PlayFab, failedHr, msg)

#define TRACE_IMPORTANT(msg, ...)       HC_TRACE_IMPORTANT(PlayFab, msg, ##__VA_ARGS__)

#define TRACE_INFORMATION(msg, ...)     HC_TRACE_INFORMATION(PlayFab, msg, ##__VA_ARGS__)

#define TRACE_VERBOSE(msg, ...)         HC_TRACE_VERBOSE(PlayFab, msg, ##__VA_ARGS__)

struct TraceSettings
{
    bool enableTraceToFile{ false };
    char traceFileDirectory[MAX_PATH]{ 0 };
};

TraceSettings& GetTraceSettings();

struct TraceOutput
{
    virtual ~TraceOutput() = default;

    virtual void TraceMessage(const char* message) = 0;
    virtual void Stop() {};
};

class TraceState : public ITerminationListener
{
public:
    TraceState(const TraceState&) = delete;
    TraceState& operator=(TraceState) = delete;
    ~TraceState() noexcept;

    static HRESULT Create(RunContext&& runContext, LocalStorage localStorage) noexcept;
    static HRESULT Get(SharedPtr<TraceState>& state) noexcept;
    static HRESULT CleanupAsync(XAsyncBlock* async) noexcept;

private:
    TraceState(RunContext&& runContext, Vector<UniquePtr<TraceOutput>>&& outputs) noexcept;

    static HRESULT CALLBACK CleanupAsyncProvider(XAsyncOp op, XAsyncProviderData const* data) noexcept;

    static void CALLBACK TraceCallback(
        _In_z_ const char* areaName,
        _In_ HCTraceLevel level,
        _In_ uint64_t threadId,
        _In_ uint64_t timestamp,
        _In_z_ const char* message
    ) noexcept;

    // ITerminationListener
    void OnTerminated(SharedPtr<ITerminationListener>&& traceState, void* context) noexcept override;

    RunContext m_runContext;
    Vector<UniquePtr<TraceOutput>> const m_outputs;

    static constexpr char s_configFile[] = "PlayFabTraceSettings.json";
};



}
