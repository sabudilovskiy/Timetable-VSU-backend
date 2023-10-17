#include <gtest/gtest.h>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <exception>
#include <openapi/all.hpp>
#include <openapi/http/base/response_info.hpp>
#include <string_view>
#include <userver/formats/serialize/boost_uuid.hpp>
#include <userver/formats/serialize/common_containers.hpp>
#include <userver/utest/utest.hpp>
#include <utils/serialize/uuid/string.hpp>
#include <utils/tests_macros.hpp>

using namespace openapi::http;
using namespace openapi::preferences;
using namespace openapi::types;
using namespace std::literals;

namespace
{
struct SomeBodyResponse
{
    Uuid<Name<"some_string">> some_string;
    Array<Uuid<>, Name<"some_array">> some_array;
    auto operator<=>(const SomeBodyResponse&) const = default;
};

struct SomeResponse
{
    Body<SomeBodyResponse> some_body;
    Header<boost::uuids::uuid, Name<"some_header">> some_header;
    auto operator<=>(const SomeResponse&) const = default;
};

boost::uuids::uuid UUID(std::string_view sv)
{
    return boost::lexical_cast<boost::uuids::uuid>(sv);
}

}  // namespace

UTEST(Openapi_http_response_serialize, BasicUuid)
{
    using Response200 = Resp<SomeResponse, 200>;
    // clang-format off
    Response200 resp{
    SomeResponse{
        .some_body = {
            SomeBodyResponse
            {
                .some_string = {UUID("6483030f-dcf7-4779-8fbe-e78113bec72e")},
                .some_array = {}
            }
        },
        .some_header = {UUID("314e672f-687c-4001-8df9-3be5d268a0b6")}
    }
    };
    resp().some_body().some_array().emplace_back(Uuid<>{UUID("6ee2dc21-7229-42b9-8fb9-39a49f38d836")});
    resp().some_body().some_array().emplace_back(Uuid<>{UUID("f757748c-03a8-4834-ad2c-e2fe9c03f1e7")});
    ResponseInfo expected{
      .userver_code  = userver::server::http::HttpStatus::kOk,
      .body = R"({"some_string":"6483030f-dcf7-4779-8fbe-e78113bec72e","some_array":["6ee2dc21-7229-42b9-8fb9-39a49f38d836","f757748c-03a8-4834-ad2c-e2fe9c03f1e7"]})",
      .headers = {{"some_header", "314e672f-687c-4001-8df9-3be5d268a0b6"}},
      .response_body_type = ResponseBodyType::kJson
    };
    // clang-format on
    auto got = Serialize(resp, userver::formats::serialize::To<ResponseInfo>{});
    EXPECT_TRUE(expected == got);
}
