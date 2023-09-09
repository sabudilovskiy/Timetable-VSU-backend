#include <gtest/gtest.h>

#include <exception>
#include <string_view>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/formats/serialize/common_containers.hpp>
#include <userver/formats/serialize/to.hpp>
#include <userver/utest/utest.hpp>
#include <vector>

#include "openapi/base/named_traits.hpp"
#include "openapi/base/object_property.hpp"
#include "openapi/base/optional_traits.hpp"
#include "openapi/base/preferences.hpp"
#include "openapi/base/property_base.hpp"
#include "openapi/base/reflective_preferences.hpp"
#include "openapi/base/string_traits.hpp"
#include "openapi/json/serialize/array_property.hpp"
#include "openapi/json/serialize/object_property.hpp"
#include "openapi/json/serialize/optional_property.hpp"
#include "openapi/json/serialize/reflective.hpp"
#include "openapi/json/serialize/string_property.hpp"
#include "openapi/types/array_type.hpp"
#include "openapi/types/object_type.hpp"
#include "openapi/types/optional_type.hpp"
#include "openapi/types/string_type.hpp"
#include "utils/constexpr_optional.hpp"
#include "utils/constexpr_string.hpp"
#include "views/hello/view.hpp"

using namespace timetable_vsu_backend::openapi;
using namespace timetable_vsu_backend::openapi::types;
using namespace timetable_vsu_backend::openapi::preferences;

struct First : Reflective
{
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

struct Second : Reflective
{
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
