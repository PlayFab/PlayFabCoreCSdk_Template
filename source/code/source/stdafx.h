#pragma once

#include <algorithm>
#include <chrono>
#include <condition_variable>
#include <cstring>
#include <functional>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <array>
#include <assert.h>
#include <atomic>

// libHttpClient headers
#include <httpClient/pal.h>
#include <httpClient/async.h>

// rapidjson headers
#define RAPIDJSON_NAMESPACE PlayFab::rapidjson
#define RAPIDJSON_NAMESPACE_BEGIN namespace PlayFab { namespace rapidjson {
#define RAPIDJSON_NAMESPACE_END } }
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <rapidjson/error/en.h>

#include <playfab/cpp/StdOptional.h>

// PlayFabSharedInternal
#include <ResultMacros.h>
#include <Memory.h>
#include <Types.h>
#include <Result.h>
#include <Error.h>
#include <PlatformUtils.h>
#include <Trace.h>
#include <RunContext.h>

#define UNREFERENCED_PARAMETER(P) (P)
