#include "stdafx.h"
#include "GlobalState.h"
#include "TraceState.h"

using namespace PlayFab;

PF_API PFTraceEnableTraceToFile(
    _In_z_ const char* traceFileDirectory
) noexcept
{
    SharedPtr<GlobalState> state;
    GlobalState::Get(state);
    RETURN_HR_IF(E_PF_ALREADY_INITIALIZED, state);

    auto& settings = GetTraceSettings();
    settings.enableTraceToFile = true;
    strcpy_s(settings.traceFileDirectory, traceFileDirectory);

    return S_OK;
}
