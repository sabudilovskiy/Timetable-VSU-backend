#include <gtest/gtest.h>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <exception>
#include <openapi/all.hpp>
#include <stdexcept>
#include <string_view>
#include <userver/formats/json/value_builder.hpp>
#include <userver/formats/serialize/boost_uuid.hpp>
#include <userver/utest/utest.hpp>
#include <utility>
#include <utils/constexpr_optional.hpp>
#include <utils/constexpr_string.hpp>
#include <utils/serialize/uuid/string.hpp>
#include <utils/tests_macros.hpp>
#include <vector>

using namespace openapi::preferences;
using namespace openapi::types;

UTEST(Openapi_Json_Serialize, BasicUuud)
{
    using Serializable = Uuid<>;
    Serializable serializable{boost::lexical_cast<boost::uuids::uuid>(
        "3dae9084-ec1a-4df4-92da-65f9f649e1f5")};
    userver::formats::json::ValueBuilder json{serializable};
    auto json_text = ToString(json.ExtractValue());
    EXPECT_EQ(json_text, "\"3dae9084-ec1a-4df4-92da-65f9f649e1f5\"");
}
