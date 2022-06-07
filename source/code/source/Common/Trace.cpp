#include "stdafx.h"
#include "Trace.h"

HC_DEFINE_TRACE_AREA(PlayFab, HCTraceLevel::Verbose);

namespace PlayFab
{

TraceSettings& GetTraceSettings()
{
    // TraceSettings won't allocate memory and it's lifetime isn't tied to GlobalState
    static TraceSettings settings;
    return settings;
}

TraceFileOutput::TraceFileOutput(String traceFileDirectory)
{
    // For now log to a single output file with a fixed name. We will likely need to make this name, the max file size, etc. configurable eventually.

    static constexpr char s_filename[] = "PlayFabTrace.txt";
    static char s_fullFilePath[MAX_PATH];

    sprintf_s(s_fullFilePath, "%s%s", traceFileDirectory.data(), s_filename);

    m_file = std::ofstream{ s_fullFilePath, std::ios::binary | std::ofstream::trunc };
}

TraceFileOutput::~TraceFileOutput()
{
    m_file.flush();
    m_file.close();
}

void TraceFileOutput::TraceMessage(const char* message)
{
    if (m_file.is_open())
    {
        m_file << message;
    }
}

}
