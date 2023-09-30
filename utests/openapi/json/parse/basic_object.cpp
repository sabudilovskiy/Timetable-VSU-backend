#include <gtest/gtest.h>

#include <exception>
#include <openapi/all.hpp>
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
    // clang-format off
    Type expected_object = {
        First
        {
        .field = {"test"}, 
        .field2 = {{1, 3, 5}}
        }
    };
    // clang-format on
    EXPECT_EQ(got_object, expected_object);
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
    // clang-format off
    Second expected{
        .field = {"test"},
        .other = {userver::formats::json::FromString(R"({
            "field2" : [1,3,5]
        })")}
    };
    // clang-format on
    EXPECT_TRUE(got_object == expected);
}
