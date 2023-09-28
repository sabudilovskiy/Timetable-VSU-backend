#include <gtest/gtest.h>

#include <exception>
#include <openapi/base/preferences.hpp>
#include <openapi/base/property_base.hpp>
#include <openapi/base/reflective_preferences.hpp>
#include <openapi/base/string_traits.hpp>
#include <openapi/json/parse/all.hpp>
#include <openapi/types/all.hpp>
#include <string_view>
#include <userver/formats/json.hpp>
#include <userver/utest/utest.hpp>
#include <vector>

#include "utils/constexpr_optional.hpp"
#include "utils/constexpr_string.hpp"
#include "views/hello/view.hpp"

using namespace timetable_vsu_backend::openapi;
using namespace timetable_vsu_backend::openapi::types;
using namespace timetable_vsu_backend::openapi::preferences;

struct First
{
    REFLECTIVE_BASE(First);
    String<Name<"field">> field;
    Array<std::int32_t, Name<"field2">> field2;
};

UTEST(Openapi_Json_Parse, BasicObject)
{
    using Type = Object<First>;
    constexpr auto jsonString = R"(
        {
            "field" : "test",
            "field2" : [1,3,5]
        }
    )";
    auto json = userver::formats::json::FromString(jsonString);
    auto got_object = json.As<Type>();
    auto expected_object = Type();
    expected_object().field() = "test";
    expected_object().field2() = {1, 3, 5};
    EXPECT_EQ(got_object().field(), expected_object().field());
    EXPECT_EQ(got_object().field2(), expected_object().field2());
}

struct Second
{
    REFLECTIVE_BASE(Second);
    String<Name<"field">> field;
    AdditionalProperties other;
};

UTEST(Openapi_Json_Parse, BasicObjectAdditional)
{
    constexpr auto jsonString = R"(
        {
            "field" : "test",
            "field2" : [1,3,5]
        }
    )";
    using Type = Object<Second>;
    auto json = userver::formats::json::FromString(jsonString);
    auto got_object = json.As<Type>();
    EXPECT_TRUE(got_object().other().IsObject());
    auto field2 = got_object().other()["field2"];
    EXPECT_TRUE(field2.IsArray());
    EXPECT_EQ(field2.GetSize(), 3);
    auto first_elem = field2[0].As<int>();
    EXPECT_EQ(first_elem, 1);
    auto second_elem = field2[1].As<int>();
    EXPECT_EQ(second_elem, 3);
    auto thirst_elem = field2[2].As<int>();
    EXPECT_EQ(thirst_elem, 5);
}
