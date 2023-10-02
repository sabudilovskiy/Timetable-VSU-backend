// #include <gtest/gtest.h>

// #include <exception>
// #include <initializer_list>
// #include <optional>
// #include <stdexcept>
// #include <string_view>
// #include <userver/utest/utest.hpp>
// #include <vector>

// #include <openapi/base/named_traits.hpp>
// #include <openapi/base/preferences.hpp>
// #include <openapi/json/serialize/optional_property.hpp>
// #include <openapi/json/serialize/array_property.hpp>
// #include <openapi/types/array_type.hpp>
// #include <openapi/types/optional_type.hpp>
// #include <userver/formats/json/value.hpp>
// #include <userver/formats/json/value_builder.hpp>
// #include <utils/constexpr_optional.hpp>
// #include <utils/constexpr_string.hpp>
// #include <utils/tests_macros.hpp>
// #include <userver/formats/serialize/common_containers.hpp>
// #include "views/hello/view.hpp"

// using namespace timetable_vsu_backend::openapi::types;
// using namespace timetable_vsu_backend::openapi::preferences;

// UTEST(Openapi_Json_Serialize, BasicOptional)
// {
//     using Serializable = Optional<int>;
//     Serializable value{1};
//     userver::formats::json::ValueBuilder test(value);
//     auto json_text = ToString(test.ExtractValue());
//     EXPECT_EQ(json_text, "1");
// }

// UTEST(Openapi_Json_Serialize, BasicOptionalNull)
// {
//     using Serializable = Optional<int>;
//     Serializable value{std::nullopt};
//     userver::formats::json::ValueBuilder test(value);
//     auto json_text = ToString(test.ExtractValue());
//     EXPECT_EQ(json_text, "null");
// }

// UTEST(Openapi_Json_Serialize, BasicOptionalMinError)
// {
//     using Serializable = Optional<Array<int, Min<5>>>;
//     Serializable value;
//     value().emplace(Array<int, Min<5>>{{1,2,3,4}});
//     EXPECT_THROW_MSG(
//         userver::formats::json::ValueBuilder{value}, std::runtime_error,
//         "Field has elements less than allowed, current: 4, min: 5");
// }

// UTEST(Openapi_Json_Serialize, BasicOptionalNullOnError)
// {
//     using Serializable = Optional<Array<int, Min<5>>, UseNullOnFail>;
//     Serializable value;
//     value().emplace(Array<int, Min<5>>{{1,2,3,4}});
//     userver::formats::json::ValueBuilder test(value);
//     auto json_text = ToString(test.ExtractValue());
//     EXPECT_EQ(json_text, "null");
// }
