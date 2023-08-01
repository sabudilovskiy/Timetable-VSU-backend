#include <gtest/gtest.h>

#include <exception>
#include <string_view>
#include <userver/utest/utest.hpp>
#include <vector>

#include "openapi/base/named_traits.hpp"
#include "openapi/base/preferences.hpp"
#include "openapi/base/string_traits.hpp"
#include "openapi/json/parse/string_property.hpp"
#include "openapi/types/string_type.hpp"
#include "utils/constexpr_optional.hpp"
#include "utils/constexpr_string.hpp"
#include "views/hello/view.hpp"

using namespace timetable_vsu_backend::openapi;

UTEST(Openapi_Json_Serialize, BasicStringPattern)
{
    using Type = types::String<preferences::Pattern<"dsds">>;
    constexpr auto jsonString = R"(
        {
            "test" : ""
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
        std::string expected = "Field doesnt satisfy pattern: dsds, value: ";
        EXPECT_EQ(exc_msg, expected);
    }
    EXPECT_TRUE(was_exception);
}

UTEST(Openapi_Json_Serialize, EndStringPattern)
{
    using Type = types::String<preferences::Pattern<"some_text$">>;
    constexpr auto jsonString = R"(
        {
            "test" : "some_text_not_end"
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
            "Field doesnt satisfy pattern: some_text$, value: "
            "some_text_not_end";
        EXPECT_EQ(exc_msg, expected);
    }
    EXPECT_TRUE(was_exception);
}
