#include <gtest/gtest.h>

#include <exception>
#include <string_view>
#include <userver/utest/utest.hpp>
#include <vector>

#include "openapi/base/named_traits.hpp"
#include "openapi/base/preferences.hpp"
#include "openapi/base/property_base.hpp"
#include "openapi/base/string_traits.hpp"
#include "openapi/json/parse/array_property.hpp"
#include "openapi/json/parse/object_property.hpp"
#include "openapi/json/parse/string_property.hpp"
#include "openapi/types/array_type.hpp"
#include "openapi/types/object_type.hpp"
#include "openapi/types/string_type.hpp"
#include "utils/constexpr_optional.hpp"
#include "utils/constexpr_string.hpp"
#include "views/hello/view.hpp"

using namespace timetable_vsu_backend::openapi;
using namespace timetable_vsu_backend::openapi::types;
using namespace timetable_vsu_backend::openapi::preferences;

struct First
{
    String<Name<"field">> field;
    Array<int, Name<"field2">> field2;
    using Reflective = Yes;
};

UTEST(Openapi_Json_Serialize, BasicObject)
{
    static_assert(checks::IsReflective<First>);
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

struct SecondRootObject
{
    String<Name<"field">> field;
    Array<int, Name<"field2">> field2;
    using Reflective = Yes;
};

struct SecondSubObject
{
    Object<SecondRootObject, UseRoot<true>> a;
    String<Name<"field3">> field3;
    using Reflective = Yes;
};

UTEST(Openapi_Json_Serialize, BasicUseRootObject)
{
    using Type = Object<SecondSubObject>;
    constexpr auto jsonString = R"(
        {
            "field" : "test",
            "field2" : [1,3,5],
            "field3" : "test3"
        }
    )";
    auto json = userver::formats::json::FromString(jsonString);
    auto got_object = json.As<Type>();
    auto expected_object = Type();
    expected_object().a().field() = "test";
    expected_object().a().field2() = {1, 3, 5};
    expected_object().field3() = "test3";
    EXPECT_EQ(expected_object().a().field(), got_object().a().field());
    EXPECT_EQ(expected_object().a().field2(),
              got_object().a().field2());
    EXPECT_EQ(expected_object().field3(), got_object().field3());
}
