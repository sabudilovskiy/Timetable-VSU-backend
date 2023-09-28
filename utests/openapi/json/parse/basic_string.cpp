// #include <gtest/gtest.h>

// #include <exception>
// #include <stdexcept>
// #include <string_view>
// #include <userver/utest/utest.hpp>
// #include <vector>

// #include <openapi/base/named_traits.hpp>
// #include <openapi/base/preferences.hpp>
// #include <openapi/base/string_traits.hpp>
// #include <openapi/json/parse/string_property.hpp>
// #include <openapi/types/string_type.hpp>
// #include "utils/constexpr_optional.hpp"
// #include "utils/constexpr_string.hpp"
// #include "utils/tests_macros.hpp"
// #include "views/hello/view.hpp"

// using namespace timetable_vsu_backend::openapi;

// UTEST(Openapi_Json_Parse, BasicStringPattern)
// {
//     using Type = types::String<preferences::Pattern<"dsds">>;
//     constexpr auto jsonString = R"(
//         {
//             "test" : ""
//         }
//     )";
//     auto json = userver::formats::json::FromString(jsonString);
//     EXPECT_THROW_MSG(json["test"].As<Type>(), std::runtime_error,
//                      "Field doesnt satisfy pattern: dsds, value: ");
// }

// UTEST(Openapi_Json_Parse, EndStringPattern)
// {
//     using Type = types::String<preferences::Pattern<"some_text$">>;
//     constexpr auto jsonString = R"(
//         {
//             "test" : "some_text_not_end"
//         }
//     )";
//     auto json = userver::formats::json::FromString(jsonString);
//     EXPECT_THROW_MSG(
//         json["test"].As<Type>(), std::runtime_error,
//         "Field doesnt satisfy pattern: some_text$, value:
//         some_text_not_end");
// }
