#pragma once

#include <playfab/core/PFTypes.h>
#include <playfab/core/cpp/TypeWrapperHelpers.h>
#include "EnumTraits.h"
#include "BaseModel.h"

namespace PlayFab
{
namespace JsonUtils
{

// Allocator to be used by rapidjson for all needed allocations
extern JsonAllocator allocator;

// Write JsonValue to String
String WriteToString(const JsonValue& jsonValue);

//------------------------------------------------------------------------------
// Helpers for serializing to JsonValue
//------------------------------------------------------------------------------

JsonValue ToJson(const char* string);

JsonValue ToJson(const String& string);

JsonValue ToJson(const PFJsonObject& jsonObject);

JsonValue ToJsonTime(time_t value);

// Specializations for InputModels
template <typename InternalModelWrapperT, typename std::enable_if_t<std::is_base_of_v<InputModel, InternalModelWrapperT>>* = 0>
JsonValue ToJson(const typename InternalModelWrapperT::ModelType& value);

JsonValue ToJson(const InputModel& value);

// Specialization for fundamental types
template <typename FundamentalT, typename std::enable_if_t<std::is_fundamental_v<FundamentalT>>* = 0>
JsonValue ToJson(FundamentalT value);

// Specialization for enum types
template <typename EnumT, typename std::enable_if_t<std::is_enum_v<EnumT>>* = 0>
JsonValue ToJson(EnumT value);

//------------------------------------------------------------------------------
// Helpers for deserializing from JsonValue
//------------------------------------------------------------------------------
void FromJson(const JsonValue& input, String& output);

void FromJson(const JsonValue& input, bool& output);

void FromJson(const JsonValue& input, int16_t& output);

void FromJson(const JsonValue& input, uint16_t& output);

void FromJson(const JsonValue& input, int32_t& output);

void FromJson(const JsonValue& input, uint32_t& output);

void FromJson(const JsonValue& input, int64_t& output);

void FromJson(const JsonValue& input, uint64_t& output);

void FromJson(const JsonValue& input, float& output);

void FromJson(const JsonValue& input, double& output);

// Special case needed for time_t since it is an Iso8601 formatted JsonString that gets converted to a time_t
void FromJsonTime(const JsonValue& input, time_t& output);

void FromJson(const JsonValue& input, JsonObject& output);

template<typename InternalModelWrapperT, typename std::enable_if_t<std::is_base_of_v<ServiceOutputModel, InternalModelWrapperT>>* = 0>
void FromJson(const JsonValue& input, InternalModelWrapperT& output);

template <typename EnumT, typename std::enable_if_t<std::is_enum_v<EnumT>>* = 0>
void FromJson(const JsonValue& jsonValue, EnumT& output);

// Deep copies input to output
void FromJson(const JsonValue& input, JsonValue& output);

//------------------------------------------------------------------------------
// Helpers for adding members JsonObjects. 'value' param will be converted to a JsonValue added as a member to 'jsonObject'.
// A global JsonAllocator will be used for any rapidjson allocations that are needed.
//------------------------------------------------------------------------------

void ObjectAddMember(JsonValue& jsonObject, JsonValue::StringRefType name, JsonValue&& value);

void ObjectAddMember(JsonValue& jsonObject, JsonValue::StringRefType name, const JsonValue& value);

void ObjectAddMember(JsonValue& jsonObject, JsonValue&& name, JsonValue&& value);

void ObjectAddMember(JsonValue& jsonObject, JsonValue::StringRefType name, const String& value);

template <typename T, typename std::enable_if_t<!std::is_pointer_v<T> || std::is_same_v<T, const char*>>* = 0>
void ObjectAddMember(JsonValue& jsonObject, JsonValue::StringRefType name, const T& value);

template <typename T>
void ObjectAddMember(JsonValue& jsonObject, JsonValue::StringRefType name, const StdExtra::optional<T>& value);

template <typename PtrT, typename std::enable_if_t<std::is_pointer_v<PtrT> && !std::is_same_v<PtrT, const char*>>* = 0>
void ObjectAddMember(JsonValue& jsonObject, JsonValue::StringRefType name, const PtrT value);

template <typename InternalModelWrapperT, typename std::enable_if_t<std::is_base_of_v<InputModel, InternalModelWrapperT>>* = 0>
void ObjectAddMember(JsonValue& jsonObject, JsonValue::StringRefType name, const typename InternalModelWrapperT::ModelType* value);

template <typename T>
void ObjectAddMemberArray(JsonValue& jsonObject, JsonValue::StringRefType name, const Vector<T>& array);

template <typename T>
void ObjectAddMemberArray(JsonValue& jsonObject, JsonValue::StringRefType name, const T* array, uint32_t arrayCount);

template <typename InternalModelWrapperT>
void ObjectAddMemberArray(JsonValue& jsonObject, JsonValue::StringRefType name, const typename InternalModelWrapperT::ModelType* const* array, uint32_t arrayCount);

template <typename ValueT>
void ObjectAddMemberDictionary(JsonValue& jsonObject, JsonValue::StringRefType name, const Map<String, ValueT>& map);

template <typename EntryT, typename std::enable_if_t<Detail::IsDictionaryEntry<EntryT>::value>* = 0>
void ObjectAddMemberDictionary(JsonValue& jsonObject, JsonValue::StringRefType name, const EntryT* associativeArray, uint32_t arrayCount);

template <typename InternalModelWrapperT, typename std::enable_if_t<std::is_base_of_v<InputModel, InternalModelWrapperT>>* = 0>
void ObjectAddMemberDictionary(JsonValue& jsonObject, JsonValue::StringRefType name, const typename InternalModelWrapperT::DictionaryEntryType* associativeArray, uint32_t arrayCount);

void ObjectAddMemberTime(JsonValue& jsonObject, JsonValue::StringRefType name, time_t value);

void ObjectAddMemberTime(JsonValue& jsonObject, JsonValue::StringRefType name, const StdExtra::optional<time_t>& value);

void ObjectAddMemberTime(JsonValue& jsonObject, JsonValue::StringRefType name, const time_t* value);

void ObjectAddMemberTime(JsonValue& jsonObject, JsonValue::StringRefType name, const time_t* array, uint32_t arrayCount);

void ObjectAddMemberTime(JsonValue& jsonObject, JsonValue::StringRefType name, const PFDateTimeDictionaryEntry* associativeArray, uint32_t arrayCount);

//------------------------------------------------------------------------------
// Helpers for getting fields from JsonObjects as Cpp types.
// Unless the output field is optional, rapidjson will assert if the JsonObject is missing the requested
// field or if the requested fields are not the expected Json type.
//
// Some of the methods also have output parameters where a pointer to the retreived value & (in the case of collections) the count is returned.
//------------------------------------------------------------------------------

template <typename T>
void ObjectGetMember(const JsonValue& jsonObject, const char* name, T& output);

template <typename T>
void ObjectGetMember(const JsonValue& jsonObject, const char* name, StdExtra::optional<T>& output);

// Because they are already nullable, JsonObjects, Strings, and collection types will not be wrapped in StdExtra::optional even if the properties are optional.
// The default templated ObjectGetMember assumes the property is required, these specializations will not.
void ObjectGetMember(const JsonValue& jsonObject, const char* name, JsonObject& output);

void ObjectGetMember(const JsonValue& jsonObject, const char* name, JsonValue& output);

void ObjectGetMember(const JsonValue& jsonObject, const char* name, String& output);

template <typename T>
void ObjectGetMember(const JsonValue& jsonObject, const char* name, Vector<T>& output);

template <typename InternalModelWrapperT, typename std::enable_if_t<std::is_base_of_v<ServiceOutputModel, InternalModelWrapperT>>* = 0>
void ObjectGetMember(const JsonValue& jsonObject, const char* name, ModelVector<InternalModelWrapperT>& output);

void ObjectGetMember(const JsonValue& jsonObject, const char* name, CStringVector& output);

template<class EntryT>
void ObjectGetMember(const JsonValue& jsonObject, const char* name, DictionaryEntryVector<EntryT>& output);

template<class InternalModelWrapperT, typename std::enable_if_t<std::is_base_of_v<ServiceOutputModel, InternalModelWrapperT>>* = 0>
void ObjectGetMember(const JsonValue& jsonObject, const char* name, ModelDictionaryEntryVector<InternalModelWrapperT>& output);

void ObjectGetMember(const JsonValue& jsonObject, const char* name, StringDictionaryEntryVector& output);

void ObjectGetMemberTime(const JsonValue& jsonObject, const char* name, time_t& output);

void ObjectGetMemberTime(const JsonValue& jsonObject, const char* name, StdExtra::optional<time_t>& output);

void ObjectGetMemberTime(const JsonValue& jsonObject, const char* name, Vector<time_t>& output);

void ObjectGetMemberTime(const JsonValue& jsonObject, const char* name, DictionaryEntryVector<PFDateTimeDictionaryEntry>& output);

//------------------------------------------------------------------------------
// Template implementations
//------------------------------------------------------------------------------

template <typename InternalModelWrapperT, typename std::enable_if_t<std::is_base_of_v<InputModel, InternalModelWrapperT>>*>
JsonValue ToJson(const typename InternalModelWrapperT::ModelType& value)
{
    return InternalModelWrapperT::ToJson(value);
}

template <typename FundamentalT, typename std::enable_if_t<std::is_fundamental_v<FundamentalT>>*>
JsonValue ToJson(FundamentalT value)
{
    return JsonValue{ value };
}

template <typename EnumT, typename std::enable_if_t<std::is_enum_v<EnumT>>*>
inline JsonValue ToJson(EnumT value)
{
    return JsonValue{ EnumName<EnumT>(value), allocator };
}

template<typename InternalModelWrapperT, typename std::enable_if_t<std::is_base_of_v<ServiceOutputModel, InternalModelWrapperT>>*>
void FromJson(const JsonValue& input, InternalModelWrapperT& output)
{
    output.FromJson(input);
}

template <typename EnumT, typename std::enable_if_t<std::is_enum_v<EnumT>>*>
void FromJson(const JsonValue& jsonValue, EnumT& output)
{
    output = EnumValue<EnumT>(jsonValue.GetString());
}

template <typename T, typename std::enable_if_t<!std::is_pointer_v<T> || std::is_same_v<T, const char*>>*>
void ObjectAddMember(JsonValue& jsonObject, JsonValue::StringRefType name, const T& value)
{
    ObjectAddMember(jsonObject, name, ToJson(value));
}

template <typename T>
void ObjectAddMember(JsonValue& jsonObject, JsonValue&& name, const T& value)
{
    ObjectAddMember(jsonObject, std::move(name), ToJson(value));
}

template <typename T>
void ObjectAddMember(JsonValue& jsonObject, JsonValue::StringRefType name, const StdExtra::optional<T>& value)
{
    if (value.has_value())
    {
        return ObjectAddMember(jsonObject, name, *value);
    }
    else
    {
        return ObjectAddMember(jsonObject, name, JsonValue{ rapidjson::kNullType });
    }
}

template <typename PtrT, typename std::enable_if_t<std::is_pointer_v<PtrT> && !std::is_same_v<PtrT, const char*>>*>
void ObjectAddMember(JsonValue& jsonObject, JsonValue::StringRefType name, const PtrT value)
{
    if (value)
    {
        return ObjectAddMember(jsonObject, name, *value);
    }
    else
    {
        return ObjectAddMember(jsonObject, name, JsonValue{ rapidjson::kNullType });
    }
}

template <typename InternalModelWrapperT, typename std::enable_if_t<std::is_base_of_v<InputModel, InternalModelWrapperT>>*>
void ObjectAddMember(JsonValue& jsonObject, JsonValue::StringRefType name, const typename InternalModelWrapperT::ModelType* value)
{
    if (value)
    {
        return ObjectAddMember(jsonObject, name, ToJson<InternalModelWrapperT>(*value));
    }
    else
    {
        return ObjectAddMember(jsonObject, name, JsonValue{ rapidjson::kNullType });
    }
}

template <typename T>
void ObjectAddMemberArray(JsonValue& jsonObject, JsonValue::StringRefType name, const Vector<T>& array)
{
    JsonValue member{ rapidjson::kArrayType };
    for (auto& item : array)
    {
        member.PushBack(ToJson(item), allocator);
    }
    ObjectAddMember(jsonObject, name, std::move(member));
}

template <typename T>
void ObjectAddMemberArray(JsonValue& jsonObject, JsonValue::StringRefType name, const T* array, uint32_t arrayCount)
{
    JsonValue member{ rapidjson::kArrayType };
    for (auto i = 0u; i < arrayCount; ++i)
    {
        member.PushBack(ToJson(array[i]), allocator);
    }
    ObjectAddMember(jsonObject, name, std::move(member));
}

template <typename InternalModelWrapperT>
void ObjectAddMemberArray(JsonValue& jsonObject, JsonValue::StringRefType name, const typename InternalModelWrapperT::ModelType* const* array, uint32_t arrayCount)
{
    JsonValue member{ rapidjson::kArrayType };
    for (auto i = 0u; i < arrayCount; ++i)
    {
        member.PushBack(ToJson<InternalModelWrapperT>(*array[i]), allocator);
    }
    ObjectAddMember(jsonObject, name, std::move(member));
}

template <typename ValueT>
void ObjectAddMemberDictionary(JsonValue& jsonObject, JsonValue::StringRefType name, const Map<String, ValueT>& map)
{
    JsonValue member{ rapidjson::kObjectType };
    for (auto& pair : map)
    {
        ObjectAddMember(member, ToJson(pair.first), ToJson(pair.second));
    }
    ObjectAddMember(jsonObject, name, std::move(member));
}

template <typename EntryT, typename std::enable_if_t<Detail::IsDictionaryEntry<EntryT>::value>*>
void ObjectAddMemberDictionary(JsonValue& jsonObject, JsonValue::StringRefType name, const EntryT* associativeArray, uint32_t arrayCount)
{
    JsonValue member{ rapidjson::kObjectType };
    for (auto i = 0u; i < arrayCount; ++i)
    {
        auto& entry{ associativeArray[i] };
        ObjectAddMember(member, ToJson(entry.key), ToJson(entry.value));
    }
    ObjectAddMember(jsonObject, name, std::move(member));
}

template <typename InternalModelWrapperT, typename std::enable_if_t<std::is_base_of_v<InputModel, InternalModelWrapperT>>*>
void ObjectAddMemberDictionary(JsonValue& jsonObject, JsonValue::StringRefType name, const typename InternalModelWrapperT::DictionaryEntryType* associativeArray, uint32_t arrayCount)
{
    JsonValue member{ rapidjson::kObjectType };
    for (auto i = 0u; i < arrayCount; ++i)
    {
        auto& entry{ associativeArray[i] };
        ObjectAddMember(member, ToJson(entry.key), ToJson<InternalModelWrapperT>(*entry.value));
    }
    ObjectAddMember(jsonObject, name, std::move(member));
}

template <typename T>
void ObjectGetMember(const JsonValue& jsonObject, const char* name, T& output)
{
    FromJson(jsonObject[name], output);
}

template <typename T>
void ObjectGetMember(const JsonValue& jsonObject, const char* name, StdExtra::optional<T>& output)
{
    output.reset();
    if (jsonObject.IsObject())
    {
        auto iter = jsonObject.FindMember(name);
        if (iter != jsonObject.MemberEnd() && !iter->value.IsNull())
        {
            output.emplace();
            FromJson(iter->value, *output);
        }
    }
}

template <typename T>
void ObjectGetMember(const JsonValue& jsonObject, const char* name, Vector<T>& output)
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
                FromJson(value, output.back());
            }
        }
    }
}

template <typename InternalModelWrapperT, typename std::enable_if_t<std::is_base_of_v<ServiceOutputModel, InternalModelWrapperT>>*>
void ObjectGetMember(const JsonValue& jsonObject, const char* name, ModelVector<InternalModelWrapperT>& output)
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
                InternalModelWrapperT model{};
                model.FromJson(value);
                output.push_back(std::move(model));
            }
        }
    }
}

template<class EntryT>
void ObjectGetMember(const JsonValue& jsonObject, const char* name, DictionaryEntryVector<EntryT>& output)
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
                decltype(EntryT::value) value{};
                FromJson(pair.value, value);
                output.insert_or_assign(pair.name.GetString(), value);
            }
        }
    }
}

template<class InternalModelWrapperT, typename std::enable_if_t<std::is_base_of_v<ServiceOutputModel, InternalModelWrapperT>>*>
void ObjectGetMember(const JsonValue& jsonObject, const char* name, ModelDictionaryEntryVector<InternalModelWrapperT>& output)
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
                InternalModelWrapperT model{};
                model.FromJson(pair.value);
                output.insert_or_assign(pair.name.GetString(), std::move(model));
            }
        }
    }
}

} // namespace JsonUtils
} // namespace PlayFab
