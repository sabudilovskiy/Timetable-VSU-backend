#include <gtest/gtest.h>

#include <openapi/all.hpp>
#include <stdexcept>
#include <string_view>
#include <userver/formats/parse/boost_uuid.hpp>
#include <userver/utest/utest.hpp>
#include <userver/utils/datetime.hpp>
#include <utils/constexpr_optional.hpp>
#include <utils/constexpr_string.hpp>
#include <utils/tests_macros.hpp>
#include <vector>

using namespace openapi;

UTEST(Openapi_Json_Parse, BasicDatetime)
{
    // 2011-08-12T20:17:46.384Z

    using Type = types::Datetime<>;
    constexpr auto jsonString = R"(
        {
            "test" : "2011-08-12T20:17:46.384Z"
        }
    )";
    auto expected = Type{userver::utils::datetime::GuessLocalTimezoneStringtime(
        "2011-08-12T20:17:46.384Z")};
    auto json = userver::formats::json::FromString(jsonString);
    auto got = json["test"].As<Type>();
    EXPECT_EQ(expected, got);
}
