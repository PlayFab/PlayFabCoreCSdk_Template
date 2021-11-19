#include "pch.h"
#include "EnumTraits.h"
#include "JsonUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PlayFab
{

enum class PFEnum
{
    Value1,
    Value2
};

template<> struct EnumRange<PFEnum> { static constexpr PFEnum maxValue = PFEnum::Value2; };
template<> struct EnumRange<PFCountryCode> { static constexpr PFCountryCode maxValue = PFCountryCode::ZW; };

namespace UnitTests
{

constexpr char jsonString[] = R"(
{
    "EnumValue":"Value2",
    "ArrayValue":["0","1","2","3","4","5"],
    "SubObjectValue": 
    {
        "CountryCode":"IN"
    }
}
)";

TEST_CLASS(JsonParsingTests)
{
public:
    TEST_METHOD(BasicJsonParsing)
    {
        struct SubObjectModel : public InputModel, OutputModel<SubObjectModel>
        {
            using ModelType = SubObjectModel;

            PFCountryCode CountryCode;

            void FromJson(const JsonValue& input)
            {
                JsonUtils::ObjectGetMember(input, "CountryCode", CountryCode);
            }

            size_t RequiredBufferSize() const 
            {
                // unused
                return 0; 
            }

            Result<SubObjectModel const*> Copy(ModelBuffer&) const
            {
                // unused
                return E_NOTIMPL;
            }

            JsonValue ToJson() const
            {
                return ToJson(*this);
            }

            static JsonValue ToJson(const SubObjectModel& model)
            {
                JsonValue output{ rapidjson::kObjectType };
                JsonUtils::ObjectAddMember(output, "CountryCode", model.CountryCode);
                return output;
            }
        };

        struct ObjectModel : public InputModel, OutputModel<ObjectModel>
        {
            using ModelType = ObjectModel;

            PFEnum EnumValue;
            CStringVector ArrayValue;
            SubObjectModel SubObjectValue;

            void FromJson(const JsonValue& input)
            {
                JsonUtils::ObjectGetMember(input, "EnumValue", EnumValue);
                JsonUtils::ObjectGetMember(input, "ArrayValue", ArrayValue);
                JsonUtils::ObjectGetMember(input, "SubObjectValue", SubObjectValue);
            }


            size_t RequiredBufferSize() const
            {
                // unused
                return 0;
            }

            Result<ObjectModel const*> Copy(ModelBuffer&) const
            {
                // unused
                return E_NOTIMPL;
            }

            JsonValue ToJson() const
            {
                JsonValue output{ rapidjson::kObjectType };
                JsonUtils::ObjectAddMember(output, "EnumValue", EnumValue);
                JsonUtils::ObjectAddMemberArray(output, "ArrayValue", ArrayValue.data(), static_cast<uint32_t>(ArrayValue.size()));
                JsonUtils::ObjectAddMember<SubObjectModel>(output, "SubObjectValue", &SubObjectValue);
                return output;
            }
        };

        JsonDocument inputJson;
        inputJson.Parse(jsonString);

        ObjectModel model;
        model.FromJson(inputJson);

        JsonValue outputJson{ model.ToJson() };
        Assert::IsTrue(inputJson == outputJson);
    }
};

} // UnitTests
} // PlayFab