#include <gtest/gtest.h>

#include <exception>
#include <openapi/all.hpp>
#include <string_view>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/formats/serialize/common_containers.hpp>
#include <userver/formats/serialize/to.hpp>
#include <userver/utest/utest.hpp>
#include <utils/constexpr_optional.hpp>
#include <utils/constexpr_string.hpp>
#include <vector>

#include "views/hello/view.hpp"
using namespace openapi;
using namespace openapi::types;
using namespace openapi::preferences;

struct First
{
    auto operator<=>(const First&) const = default;
    String<Name<"field">> field;
    Array<int, Name<"field2">> field2;
};

UTEST(Openapi_Json_Serialize, BasicObject)
{
    using Serializable = Object<First>;
    Serializable serializable{
        First{.field = {"test_string"}, .field2 = {{1, 2, 3}}}};
    userver::formats::json::ValueBuilder json(serializable);
    auto text_json = ToString(json.ExtractValue());
    EXPECT_EQ(text_json, R"({"field":"test_string","field2":[1,2,3]})");
}

struct Second
{
    auto operator<=>(const Second&) const = default;
    String<Name<"field">> field;
    AdditionalProperties other_fields;
};

UTEST(Openapi_Json_Serialize, BasicObjectAdditional)
{
    using Serializable = Object<Second>;
    Serializable serializable{Second{
        .field = {"test_string"},
        .other_fields = {
            userver::formats::json::FromString(R"({"field2":[1,2,3]})")}}};
    userver::formats::json::ValueBuilder json(serializable);
    auto text_json = ToString(json.ExtractValue());
    EXPECT_EQ(text_json, R"({"field":"test_string","field2":[1,2,3]})");
}
