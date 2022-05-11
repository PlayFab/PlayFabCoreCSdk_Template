#include "stdafx.h"
#include "JsonUtils.h"
#include "BaseModel.h"
#include <rapidjson/stream.h>

namespace PlayFab
{
namespace JsonUtils
{
JsonAllocator allocator{};

// Helper class for writing JsonValue directly into a PlayFab::String. Implements rapidjson write-only stream
// concept (see rapidjson/stream.h for details). Avoids additional copy needed when first writing to rapidjson::StringBuffer
class StringOutputStream
{
public:
    using Ch = String::traits_type::char_type;

    StringOutputStream(size_t initialCapacity = kDefaultCapacity)
    {
        m_string.reserve(initialCapacity);
    }

    void Put(Ch c)
    {
        m_string.push_back(c);
    }

    void Flush()
    {
        // no-op
    }

    const String& GetString() const
    {
        return m_string;
    }

    String&& ExtractString()
    {
        return std::move(m_string);
    }

    static const size_t kDefaultCapacity = 256; // use same default capacity as rapidjson::GenericStringBuffer

private:
    String m_string;
};

String WriteToString(const JsonValue& jsonValue)
{
    StringOutputStream stream;
    JsonWriter<StringOutputStream> writer{ stream, &allocator };
    jsonValue.Accept(writer);
    return stream.ExtractString();
}

JsonValue ToJson(const char* string)
{
    if (!string)
    {
        return JsonValue{ rapidjson::kNullType };
    }
    return JsonValue{ string, allocator };
}

JsonValue ToJson(const String& string)
{
    // By design, map empty string to null JsonValue
    if (string.empty())
    {
        return JsonValue{ rapidjson::kNullType };
    }
    return JsonValue{ string.data(), allocator };
}

JsonValue ToJson(const PFJsonObject& jsonObject)
{
    // By design, map empty jsonObject to null JsonValue
    if (!jsonObject.stringValue)
    {
        return JsonValue{ rapidjson::kNullType };
    }
    JsonDocument document{ &allocator };
    document.Parse(jsonObject.stringValue);
    return JsonValue{ document, allocator };
}

JsonValue ToJsonTime(time_t value)
{
    return JsonValue{ TimeTToIso8601String(value).data(), allocator };
}

JsonValue ToJson(const InputModel& value)
{
    return value.ToJson();
}

void FromJson(const JsonValue& input, String& output)
{
    output = input.GetString();
}

void FromJson(const JsonValue& input, bool& output)
{
    output = input.GetBool();
}

void FromJson(const JsonValue& input, int16_t& output)
{
    output = static_cast<int16_t>(input.GetInt());
}

void FromJson(const JsonValue& input, uint16_t& output)
{
    output = static_cast<uint16_t>(input.GetUint());
}

void FromJson(const JsonValue& input, int32_t& output)
{
    output = static_cast<int32_t>(input.GetInt());
}

void FromJson(const JsonValue& input, uint32_t& output)
{
    output = static_cast<uint32_t>(input.GetUint());
}

void FromJson(const JsonValue& input, int64_t& output)
{
    output = input.GetInt64();
}

void FromJson(const JsonValue& input, uint64_t& output)
{
    output = input.GetUint64();
}

void FromJson(const JsonValue& input, float& output)
{
    output = input.GetFloat();
}

void FromJson(const JsonValue& input, double& output)
{
    output = input.GetDouble();
}

void FromJsonTime(const JsonValue& input, time_t& output)
{
    output = Iso8601StringToTimeT(input.GetString());
}

void FromJson(const JsonValue& input, JsonObject& output)
{
    output.stringValue = JsonUtils::WriteToString(input);
}

void FromJson(const JsonValue& input, JsonValue& output)
{
    output.CopyFrom(input, allocator); // Deep copy
}

void ObjectAddMember(JsonValue& jsonObject, JsonValue::StringRefType name, JsonValue&& value)
{
    jsonObject.AddMember(name, value, allocator);
}

void ObjectAddMember(JsonValue& jsonObject, JsonValue::StringRefType name, const JsonValue& value)
{
    jsonObject.AddMember(name, JsonValue{}.CopyFrom(value, allocator), allocator);
}

void ObjectAddMember(JsonValue& jsonObject, JsonValue&& name, JsonValue&& value)
{
    jsonObject.AddMember(name, value, allocator);
}

void ObjectAddMember(JsonValue& jsonObject, JsonValue::StringRefType name, const String& value)
{
    jsonObject.AddMember(name, ToJson(value), allocator);
}

void ObjectAddMemberTime(JsonValue& jsonObject, JsonValue::StringRefType name, time_t value)
{
    ObjectAddMember(jsonObject, name, ToJsonTime(value));
}

void ObjectAddMemberTime(JsonValue& jsonObject, JsonValue::StringRefType name, const StdExtra::optional<time_t>& value)
{
    if (value.has_value())
    {
        ObjectAddMember(jsonObject, name, ToJsonTime(*value));
    }
    else
    {
        ObjectAddMember(jsonObject, name, JsonValue{ rapidjson::kNullType });
    }
}

void ObjectAddMemberTime(JsonValue& jsonObject, JsonValue::StringRefType name, const time_t* value)
{
    if (value != nullptr)
    {
        ObjectAddMember(jsonObject, name, ToJsonTime(*value));
    }
    else
    {
        ObjectAddMember(jsonObject, name, JsonValue{ rapidjson::kNullType });
    }
}

void ObjectAddMemberTime(JsonValue& jsonObject, JsonValue::StringRefType name, const time_t* array, uint32_t arrayCount)
{
    JsonValue member{ rapidjson::kArrayType };
    for (auto i = 0u; i < arrayCount; ++i)
    {
        member.PushBack(ToJsonTime(array[i]), allocator);
    }
    ObjectAddMember(jsonObject, name, std::move(member));
}

void ObjectAddMemberTime(JsonValue& jsonObject, JsonValue::StringRefType name, const PFDateTimeDictionaryEntry* associativeArray, uint32_t arrayCount)
{
    JsonValue member{ rapidjson::kObjectType };
    for (auto i = 0u; i < arrayCount; ++i)
    {
        auto& entry{ associativeArray[i] };
        ObjectAddMember(member, ToJson(entry.key), ToJsonTime(entry.value));
    }
    ObjectAddMember(jsonObject, name, std::move(member));
}

void ObjectGetMember(const JsonValue& jsonObject, const char* name, String& output)
{
    auto iter = jsonObject.FindMember(name);
    if (iter != jsonObject.MemberEnd() && iter->value.IsString())
    {
        FromJson(iter->value, output);
    }
}

void ObjectGetMember(const JsonValue& jsonObject, const char* name, JsonObject& output)
{
    output.stringValue.clear();
    auto iter = jsonObject.FindMember(name);
    if (iter != jsonObject.MemberEnd())
    {
        FromJson(iter->value, output);
    }
}

void ObjectGetMember(const JsonValue& jsonObject, const char* name, JsonValue& output)
{
    auto iter = jsonObject.FindMember(name);
    if (iter != jsonObject.MemberEnd())
    {
        FromJson(iter->value, output);
    }
    else
    {
        output.SetNull();
    }
}

void ObjectGetMember(const JsonValue& jsonObject, const char* name, CStringVector& output)
{
    output.clear();
    if (jsonObject.IsObject())
    {
        auto iter = jsonObject.FindMember(name);
        if (iter != jsonObject.MemberEnd() && iter->value.IsArray())
        {
            auto jsonArray{ iter->value.GetArray() };

            output.reserve(jsonArray.Size());

            for (auto& value : jsonArray)
            {
                String stringValue;
                FromJson(value, stringValue);
                output.push_back(std::move(stringValue));
            }
        }
    }
}

void ObjectGetMember(const JsonValue& jsonObject, const char* name, StringDictionaryEntryVector& output)
{
    output.clear();
    if (jsonObject.IsObject())
    {
        auto iter = jsonObject.FindMember(name);
        if (iter != jsonObject.MemberEnd() && iter->value.IsObject())
        {
            auto memberObject{ iter->value.GetObject() };

            output.reserve(memberObject.MemberCount());

            for (auto& pair : memberObject)
            {
                String stringValue{};
                FromJson(pair.value, stringValue);
                output.insert_or_assign(pair.name.GetString(), std::move(stringValue));
            }
        }
    }
}

void ObjectGetMemberTime(const JsonValue& jsonObject, const char* name, time_t& output)
{
    auto iter = jsonObject.FindMember(name);
    if (iter != jsonObject.MemberEnd())
    {
        FromJsonTime(iter->value, output);
    }
}

void ObjectGetMemberTime(const JsonValue& jsonObject, const char* name, StdExtra::optional<time_t>& output)
{
    output.reset();
    if (jsonObject.IsObject())
    {
        auto iter = jsonObject.FindMember(name);
        if (iter != jsonObject.MemberEnd())
        {
            output.emplace();
            FromJsonTime(iter->value, *output);
        }
    }
}

void ObjectGetMemberTime(const JsonValue& jsonObject, const char* name, Vector<time_t>& output)
{
    output.clear();
    if (jsonObject.IsObject())
    {
        auto iter = jsonObject.FindMember(name);
        if (iter != jsonObject.MemberEnd() && iter->value.IsArray())
        {
            auto jsonArray{ iter->value.GetArray() };
            output.reserve(jsonArray.Size());
            for (auto& value : jsonArray)
            {
                output.emplace_back();
                FromJsonTime(value, output.back());
            }
        }
    }
}

void ObjectGetMemberTime(const JsonValue& jsonObject, const char* name, DictionaryEntryVector<PFDateTimeDictionaryEntry>& output)
{
    output.clear();
    if (jsonObject.IsObject())
    {
        auto iter = jsonObject.FindMember(name);
        if (iter != jsonObject.MemberEnd() && iter->value.IsObject())
        {
            auto memberObject{ iter->value.GetObject() };

            output.reserve(memberObject.MemberCount());

            for (auto& pair : memberObject)
            {
                time_t value{};
                FromJsonTime(pair.value, value);
                output.insert_or_assign(pair.name.GetString(), value);
            }
        }
    }
}

} // namespace JsonUtils
} // namespace PlayFab
