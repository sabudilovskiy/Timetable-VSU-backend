#include <gtest/gtest.h>

#include <exception>
#include <openapi/all.hpp>
#include <string_view>
#include <userver/formats/parse/common_containers.hpp>
#include <userver/utest/utest.hpp>
#include <utils/tests_macros.hpp>

using namespace openapi::http;
using namespace openapi::preferences;
using namespace openapi::types;
using namespace std::literals;

UTEST(Openapi_Doc, BasicStatusCode)
{
    EXPECT_EQ(Code<200>::value, userver::server::http::HttpStatus::kOk);
}

struct SomeBody
{
    String<Name<"some_string">> some_string;
    Array<int, Name<"some_array">> some_array;
    auto operator<=>(const SomeBody&) const = default;
};

struct SomeRequest
{
    Header<std::string, Name<"some_header">> some_header;
    Cookie<std::string, Name<"some_cookie">> some_cookie;
    Body<SomeBody> some_body;
    auto operator<=>(const SomeRequest&) const = default;
};

UTEST(Openapi_http_request_parse, Basic)
{
    TestRequest req;
    req.body = R"(
{
    "some_string" : "test_string",
    "some_array" : [1,2,3]
}
    )";

    req.headers["some_header"sv] = "header_value";
    req.cookies["some_cookie"] = "cookie_value";
    auto info = MakeInfoFromRequest(req);
    auto parsed = Parse(info, userver::formats::parse::To<SomeRequest>{});
    // clang-format off
    SomeRequest expected{
        .some_header = {"header_value"},
        .some_cookie = {"cookie_value"},
        .some_body = {SomeBody{
            .some_string = {"test_string"},
            .some_array = {{1,2,3}}
        }}
    };
    // clang-format on
    EXPECT_EQ(parsed, expected);
}

UTEST(Openapi_http_request_parse, MissingHeader)
{
    TestRequest req;
    req.body = R"(
{
    "some_string" : "test_string",
    "some_array" : [1,2,3]
}
    )";
    req.cookies["some_cookie"] = "cookie_value";
    auto info = MakeInfoFromRequest(req);
    EXPECT_THROW_MSG(Parse(info, userver::formats::parse::To<SomeRequest>{}),
                     std::exception, "Missing header: some_header");
}

UTEST(Openapi_http_request_parse, MissingCookie)
{
    TestRequest req;
    req.body = R"(
{
    "some_string" : "test_string",
    "some_array" : [1,2,3]
}
    )";

    req.headers["some_header"sv] = "header_value";
    auto info = MakeInfoFromRequest(req);
    EXPECT_THROW_MSG(Parse(info, userver::formats::parse::To<SomeRequest>{}),
                     std::exception, "Missing cookie: some_cookie");
}
