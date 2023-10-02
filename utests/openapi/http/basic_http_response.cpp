#include <gtest/gtest.h>

#include <exception>
#include <openapi/all.hpp>
#include <openapi/http/base/response_info.hpp>
#include <string_view>
#include <userver/formats/serialize/common_containers.hpp>
#include <userver/utest/utest.hpp>
#include <utils/tests_macros.hpp>

using namespace timetable_vsu_backend::openapi::http;
using namespace timetable_vsu_backend::openapi::preferences;
using namespace timetable_vsu_backend::openapi::types;
using namespace std::literals;

struct SomeBodyResponse
{
    REFLECTIVE_BASE(SomeBodyResponse);
    String<Name<"some_string">> some_string;
    Array<int, Name<"some_array">> some_array;
};

struct SomeResponse
{
    REFLECTIVE_BASE(SomeResponse);
    Body<SomeBodyResponse> some_body;
    Header<std::string, Name<"some_header">> some_header;
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
      .headers = {{"some_header", "some_header_value"}}
    };
    // clang-format on
    auto got =
        Serialize(resp, userver::formats::serialize::To<ResponseInfo>{});
    EXPECT_EQ(expected, got);
}
