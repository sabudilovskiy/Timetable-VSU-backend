#include <gtest/gtest.h>

#include <exception>
#include <string_view>
#include <userver/utest/utest.hpp>
#include <vector>

#include "openapi/base/named_traits.hpp"
#include "openapi/base/preferences.hpp"
#include "openapi/json/parse/array_property.hpp"
#include "openapi/types/array_type.hpp"
#include "utils/constexpr_optional.hpp"
#include "utils/constexpr_string.hpp"
#include "views/hello/view.hpp"

using namespace timetable_vsu_backend::openapi;

UTEST(Openapi_Json_Serialize, BasicArrayProperty)
{
    using Type = types::Array<int>;
    constexpr auto jsonString = R"(
        {
            "test" : [1,2,2]
        }
    )";
    auto json = userver::formats::json::FromString(jsonString);
    auto item = json["test"].As<Type>();
    std::vector<int> expected_item{1, 2, 2};
    EXPECT_EQ(item(), expected_item);
}

UTEST(Openapi_Json_Serialize, BasicArrayPropertyMin)
{
    using Type = types::Array<int, preferences::Min<4>>;
    constexpr auto jsonString = R"(
        {
            "test" : [1,2,2]
        }
    )";
    auto json = userver::formats::json::FromString(jsonString);
    bool was_exception = false;
    try
    {
        json["test"].As<Type>();
    }
    catch (std::exception& exc)
    {
        was_exception = true;
        std::string exc_msg = exc.what();
        std::string expected =
            "Field has elements less than allowed, current: 3, "
            "min: 4";
        EXPECT_EQ(exc_msg, expected);
    }
    EXPECT_TRUE(was_exception);
}

UTEST(Openapi_Json_Serialize, BasicArrayPropertyMax)
{
    using Type = types::Array<int, preferences::Min<1>, preferences::Max<2>>;
    constexpr auto jsonString = R"(
        {
            "test" : [1,2,2]
        }
    )";
    auto json = userver::formats::json::FromString(jsonString);
    bool was_exception = false;
    try
    {
        json["test"].As<Type>();
    }
    catch (std::exception& exc)
    {
        was_exception = true;
        std::string exc_msg = exc.what();
        std::string expected =
            "Field has elements more than allowed, current: 3, "
            "max: 2";
        EXPECT_EQ(exc_msg, expected);
    }
    EXPECT_TRUE(was_exception);
}

UTEST(Openapi_Json_Serialize, BasicArrayPropertyUnique)
{
    using Type = types::Array<int, preferences::UniqueItems<true>>;
    constexpr auto jsonString = R"(
        {
            "test" : [1,2,2]
        }
    )";
    auto json = userver::formats::json::FromString(jsonString);
    bool was_exception = false;
    try
    {
        json["test"].As<Type>();
    }
    catch (std::exception& exc)
    {
        was_exception = true;
        std::string exc_msg = exc.what();
        std::string expected =
            "Field has equals elements, element 2 and 3 are "
            "equal";
        EXPECT_EQ(exc_msg, expected);
    }
    EXPECT_TRUE(was_exception);
}
