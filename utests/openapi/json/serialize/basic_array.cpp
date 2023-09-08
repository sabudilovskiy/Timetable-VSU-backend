#include <gtest/gtest.h>

#include <exception>
#include <stdexcept>
#include <string_view>
#include <userver/utest/utest.hpp>
#include <variant>
#include <vector>

#include "openapi/base/named_traits.hpp"
#include "openapi/base/preferences.hpp"
#include "openapi/json/serialize/array_property.hpp"
#include "openapi/types/array_type.hpp"
#include "userver/formats/json/value.hpp"
#include "userver/formats/json/value_builder.hpp"
#include "utils/constexpr_optional.hpp"
#include "utils/constexpr_string.hpp"
#include "utils/tests_macros.hpp"
#include "views/hello/view.hpp"

using namespace timetable_vsu_backend::openapi::types;
using namespace timetable_vsu_backend::openapi::preferences;

UTEST(Openapi_Json_Serialize, BasicArray)
{
    using Serializable = Array<int>;
    Serializable value{{1, 2, 3, 4}};
    userver::formats::json::ValueBuilder test(value);
    auto json_text = ToString(test.ExtractValue());
    EXPECT_EQ(json_text, "[1,2,3,4]");
}

UTEST(Openapi_Json_Serialize, BasicArrayMinError)
{
    using Serializable = Array<int, Min<5>>;
    Serializable value{{1, 2, 3, 4}};
    EXPECT_THROW_MSG(
        userver::formats::json::ValueBuilder{value}, std::runtime_error,
        "Field has elements less than allowed, current: 4, min: 5");
}

UTEST(Openapi_Json_Serialize, BasicArrayMaxError)
{
    using Serializable = Array<int, Max<3>>;
    Serializable value{{1, 2, 3, 4}};
    EXPECT_THROW_MSG(
        userver::formats::json::ValueBuilder{value}, std::runtime_error,
        "Field has elements more than allowed, current: 4, max: 3");
}

UTEST(Openapi_Json_Serialize, BasicArrayUniqueError)
{
    using Serializable = Array<int, UniqueItems>;
    Serializable value{{1, 2, 3, 3}};
    EXPECT_THROW_MSG(userver::formats::json::ValueBuilder{value},
                     std::runtime_error,
                     "Field has equals elements, element 3 and 4 are equal");
}
