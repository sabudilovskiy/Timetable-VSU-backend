#include <gtest/gtest.h>

#include <exception>
#include <openapi/all.hpp>
#include <stdexcept>
#include <string_view>
#include <userver/formats/json/value_builder.hpp>
#include <userver/formats/serialize/boost_uuid.hpp>
#include <userver/utest/utest.hpp>
#include <userver/utils/datetime.hpp>
#include <utility>
#include <utils/constexpr_optional.hpp>
#include <utils/constexpr_string.hpp>
#include <utils/serialize/uuid/string.hpp>
#include <utils/tests_macros.hpp>
#include <vector>

using namespace openapi::preferences;
using namespace openapi::types;

UTEST(Openapi_Json_Serialize, BasicDatetime)
{
    using Serializable = Datetime<>;
    Serializable serializable{
        userver::utils::datetime::GuessLocalTimezoneStringtime(
            "2011-08-12T20:17:46.384Z")};
    userver::formats::json::ValueBuilder json{serializable};
    auto json_text = ToString(json.ExtractValue());
    EXPECT_EQ(json_text, "\"2011-08-12T20:17:46.384+0000\"");
}
