#include <gtest/gtest.h>

#include <boost/pfr/core.hpp>
#include <exception>
#include <openapi/all.hpp>
#include <openapi/doc/path.hpp>
#include <string_view>
#include <userver/utest/utest.hpp>
#include <utils/constexpr_optional.hpp>
#include <utils/constexpr_string.hpp>
#include <utils/tests_macros.hpp>
#include <vector>

using namespace openapi;
using namespace openapi::types;
using namespace openapi::preferences;

UTEST(Openapi_Json_Parse, BasicArrayProperty)
{
    using Type = types::Array<int>;
    constexpr auto jsonString = R"(
        {
            "test" : [1,2,2]
        }
    )";
    auto json = userver::formats::json::FromString(jsonString);
    auto item = json["test"].As<Type>();
    Type expected_item{{1, 2, 2}};
    EXPECT_EQ(item, expected_item);
}

UTEST(Openapi_Json_Parse, BasicArrayPropertyMin)
{
    using Type = types::Array<int, preferences::Min<4>>;
    constexpr auto jsonString = R"(
        {
            "test" : [1,2,2]
        }
    )";
    auto json = userver::formats::json::FromString(jsonString);
    EXPECT_THROW_MSG(
        json["test"].As<Type>(), std::runtime_error,
        "Field has elements less than allowed, current: 3, min: 4");
}

UTEST(Openapi_Json_Parse, BasicArrayPropertyMax)
{
    using Type = Array<int, Max<2>, Min<1>, UniqueItems>;
    constexpr auto jsonString = R"(
        {
            "test" : [1,2,3]
        }
    )";
    auto json = userver::formats::json::FromString(jsonString);
    EXPECT_THROW_MSG(
        json["test"].As<Type>(), std::runtime_error,
        "Field has elements more than allowed, current: 3, max: 2");
}

UTEST(Openapi_Json_Parse, BasicArrayPropertyUnique)
{
    using Type = types::Array<int, preferences::UniqueItems>;
    constexpr auto jsonString = R"(
        {
            "test" : [1,2,2]
        }
    )";
    ::openapi::http::HeaderProperty<int, EmptyTraits{}> h{1};
    EXPECT_EQ(h(), 1);
    auto json = userver::formats::json::FromString(jsonString);
    EXPECT_THROW_MSG(json["test"].As<Type>(), std::runtime_error,
                     "Field has equals elements, element 2 and 3 are equal");
}
