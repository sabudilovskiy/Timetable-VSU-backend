#include <gtest/gtest.h>

#include <exception>
#include <openapi/all.hpp>
#include <openapi/http/base/response_info.hpp>
#include <string_view>
#include <userver/formats/serialize/common_containers.hpp>
#include <userver/utest/utest.hpp>
#include <utils/tests_macros.hpp>

using namespace openapi::http;
using namespace openapi::preferences;
using namespace openapi::types;
using namespace std::literals;

struct SomeBodyResponse
{
    String<Name<"some_string">> some_string;
    Array<int, Name<"some_array">> some_array;
    auto operator<=>(const SomeBodyResponse&) const = default;
};

struct SomeResponse
{
    Body<SomeBodyResponse> some_body;
    Header<std::string, Name<"some_header">> some_header;
    auto operator<=>(const SomeResponse&) const = default;
};

UTEST(Openapi_http_response_serialize, Basic)
{
    using Response200 = Resp<SomeResponse, 200>;
    // clang-format off
    Response200 resp{
    SomeResponse{
        .some_body = {
            SomeBodyResponse
            {
                .some_string = {"some_value_string"},
                .some_array = {{1,2,3}}
            }
        },
        .some_header = {"some_header_value"}
    }
    };
    ResponseInfo expected{
      .userver_code  = userver::server::http::HttpStatus::kOk,
      .body = R"({"some_string":"some_value_string","some_array":[1,2,3]})",
      .headers = {{"some_header", "some_header_value"}},
      .response_body_type = ResponseBodyType::kJson
    };
    // clang-format on
    auto got = Serialize(resp, userver::formats::serialize::To<ResponseInfo>{});
    EXPECT_TRUE(expected == got);
}
