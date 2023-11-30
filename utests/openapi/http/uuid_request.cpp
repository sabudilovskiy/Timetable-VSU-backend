#include <gtest/gtest.h>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <exception>
#include <openapi/all.hpp>
#include <string_view>
#include <userver/formats/parse/boost_uuid.hpp>
#include <userver/formats/parse/common_containers.hpp>
#include <userver/utest/utest.hpp>
#include <utils/parse/uuid/string.hpp>
#include <utils/tests_macros.hpp>

using namespace openapi::http;
using namespace openapi::preferences;
using namespace openapi::types;
using namespace std::literals;

namespace
{
struct SomeBody
{
    Uuid<Name<"some_uuid">> some_uuid;
    Array<Uuid<>, Name<"some_array">> some_array;
    auto operator<=>(const SomeBody&) const = default;
};

struct SomeRequest
{
    Header<boost::uuids::uuid, Name<"some_header">> some_header;
    Cookie<boost::uuids::uuid, Name<"some_cookie">> some_cookie;
    Body<SomeBody> some_body;
    auto operator<=>(const SomeRequest&) const = default;
};

boost::uuids::uuid UUID(std::string_view sv)
{
    return boost::lexical_cast<boost::uuids::uuid>(sv);
}

}  // namespace

UTEST(Openapi_http_request_parse, BasicUuid)
{
    TestRequest req;
    req.body = R"(
{
    "some_uuid" : "2550a976-434f-4e9c-a5da-06fe0ddbfe5d",
    "some_array" : ["6ee2dc21-7229-42b9-8fb9-39a49f38d836", "f757748c-03a8-4834-ad2c-e2fe9c03f1e7"]
}
    )";

    req.headers["some_header"sv] = "6483030f-dcf7-4779-8fbe-e78113bec72e";
    req.cookies["some_cookie"] = "314e672f-687c-4001-8df9-3be5d268a0b6";
    auto info = MakeInfoFromRequest(req);
    auto parsed = Parse(info, userver::formats::parse::To<SomeRequest>{});
    // clang-format off
    SomeRequest expected{
        .some_header = {UUID("6483030f-dcf7-4779-8fbe-e78113bec72e")},
        .some_cookie = {UUID("314e672f-687c-4001-8df9-3be5d268a0b6")},
        .some_body = {SomeBody{
            .some_uuid = {UUID("2550a976-434f-4e9c-a5da-06fe0ddbfe5d")},
            .some_array = {}
        }}
    };
    expected.some_body().some_array().emplace_back(Uuid<>{UUID("6ee2dc21-7229-42b9-8fb9-39a49f38d836")});
    expected.some_body().some_array().emplace_back(Uuid<>{UUID("f757748c-03a8-4834-ad2c-e2fe9c03f1e7")});
    // clang-format on
    EXPECT_EQ(parsed, expected);
}
