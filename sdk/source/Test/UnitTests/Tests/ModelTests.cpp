#include "pch.h"
#include "Shared/SharedDataModels.h"
#include "JsonUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PlayFab
{

namespace UnitTests
{

constexpr char profileResultJson[] = R"(
{
   "PlayerProfile":{
      "PublisherId":"624BD2B0B8811A52",
      "TitleId":"E18D7",
      "PlayerId":"6842934CB46C0834"
   }
}
)";

TEST_CLASS(ModelTests)
{
public:
    TEST_METHOD(MoveModel)
    {
        constexpr char jsonArray[] = "{\"array\" : [\"1\", \"2\", \"3\", \"4\", \"5\"] }";

        JsonDocument inputJson;
        inputJson.Parse(jsonArray);

        CStringVector pointerArray;
        JsonUtils::ObjectGetMember(inputJson, "array", pointerArray);

        auto movedArray{ std::move(pointerArray) };
        JsonValue outputJson{ rapidjson::kObjectType };
        JsonUtils::ObjectAddMemberArray(outputJson, "array", pointerArray.data(), static_cast<uint32_t>(pointerArray.size()));

        Assert::IsTrue(inputJson == outputJson);
    }

    TEST_METHOD(TimeDictionarySpecialization)
    {
        const std::array<time_t, 3> times{ time(0), time(0), time(0) };

        JsonDocument inputJson{ rapidjson::kObjectType };
        JsonValue timesJson{ rapidjson::kObjectType };
        auto& a{ inputJson.GetAllocator() };
        for (size_t i = 0; i < times.size(); ++i)
        {
            std::stringstream ss;
            ss << "DateTime" << i << "_" << times[i];
            timesJson.AddMember(JsonValue{ ss.str().data(), a }, JsonValue{ PlayFab::TimeTToIso8601String(times[i]).data(), a }, a);
        }
        inputJson.AddMember("times", timesJson.Move(), a);

        DictionaryEntryVector<PFDateTimeDictionaryEntry> dictionary;
        JsonUtils::ObjectGetMemberTime(inputJson, "times", dictionary);

        Assert::IsTrue(times.size() == inputJson["times"].MemberCount());
        Assert::IsTrue(times.size() == dictionary.size());
        for (size_t i = 0; i < times.size(); ++i)
        {
            Assert::IsTrue(times[i] == dictionary.data()[i].value);
        }

        JsonValue outputJson{ rapidjson::kObjectType };
        JsonUtils::ObjectAddMemberTime(outputJson, "times", dictionary.data(), static_cast<uint32_t>(dictionary.size()));
        Assert::IsTrue(inputJson == outputJson);
    }
};

} // UnitTests
} // PlayFab