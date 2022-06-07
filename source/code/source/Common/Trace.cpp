#include "stdafx.h"
#include "Trace.h"
#include "JsonUtils.h"

HC_DEFINE_TRACE_AREA(PlayFab, HCTraceLevel::Verbose);

namespace PlayFab
{

TraceSettings& GetTraceSettings()
{
    // TraceSettings won't allocate memory and it's lifetime isn't tied to GlobalState
    static std::atomic<bool> s_settingsLoaded{ false };
    static TraceSettings s_settings;

    if (!s_settingsLoaded.exchange(true))
    {
        static constexpr char s_configFile[] = "PlayFabTraceSettings.json";

        std::ifstream file{ s_configFile, std::ios::binary | std::ios::ate };

        int64_t size = file.tellg();
        if (size > 0)
        {
            file.seekg(0);

            Vector<char> data(static_cast<size_t>(size + 1), 0);

            file.read(reinterpret_cast<char*>(data.data()), size);
            if (file.good())
            {
                JsonDocument fileJson{ &JsonUtils::allocator };
                fileJson.Parse(data.data());
                if (!fileJson.HasParseError())
                {
                    JsonUtils::ObjectGetMember(fileJson, "enableTraceToFile", s_settings.enableTraceToFile);
                    String traceFileDirectory;
                    JsonUtils::ObjectGetMember(fileJson, "traceFileDirectory", traceFileDirectory);
                    strcpy_s(s_settings.traceFileDirectory, traceFileDirectory.data());
                }
            }
        }
    }

    return s_settings;
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
