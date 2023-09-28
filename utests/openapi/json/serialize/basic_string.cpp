#include <gtest/gtest.h>

#include <exception>
#include <openapi/base/named_traits.hpp>
#include <openapi/base/preferences.hpp>
#include <openapi/base/string_traits.hpp>
#include <openapi/json/serialize/string_property.hpp>
#include <openapi/types/string_type.hpp>
#include <stdexcept>
#include <string_view>
#include <userver/formats/json/value_builder.hpp>
#include <userver/utest/utest.hpp>
#include <vector>

#include "utils/constexpr_optional.hpp"
#include "utils/constexpr_string.hpp"
#include "utils/tests_macros.hpp"
#include "views/hello/view.hpp"

using namespace timetable_vsu_backend::openapi::preferences;
using namespace timetable_vsu_backend::openapi::types;

UTEST(Openapi_Json_Serialize, BasicStringPattern)
{
    using Serializable = String<Pattern<"dsds">>;
    Serializable serializable{"dsds"};
    userver::formats::json::ValueBuilder json{serializable};
    auto json_text = ToString(json.ExtractValue());
    EXPECT_EQ(json_text, "\"dsds\"");
}

UTEST(Openapi_Json_Serialize, BasicStringError)
{
    using Serializable = String<Pattern<"some_text$">>;
    Serializable serializable{"some_text_not_end"};
    EXPECT_THROW_MSG(
        userver::formats::json::ValueBuilder{serializable}, std::runtime_error,
        "Field doesnt satisfy pattern: some_text$, value: some_text_not_end");
}
