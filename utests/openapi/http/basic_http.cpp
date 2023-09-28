#include <gtest/gtest.h>

#include <exception>
#include <openapi/base/property_base.hpp>
#include <openapi/doc/serialize/all.hpp>
#include <openapi/http/base/body.hpp>
#include <openapi/http/base/cookie.hpp>
#include <openapi/http/base/cookie_property.hpp>
#include <openapi/http/base/header.hpp>
#include <openapi/http/base/header_property.hpp>
#include <openapi/http/base/request_info.hpp>
#include <openapi/http/base/status_code.hpp>
#include <openapi/http/parse/request.hpp>
#include <openapi/json/parse/all.hpp>
#include <openapi/types/array_type.hpp>
#include <openapi/types/string_type.hpp>
#include <string_view>
#include <userver/utest/utest.hpp>

#include "utils/string/parse/string.hpp"
#include "utils/tests_macros.hpp"

using namespace timetable_vsu_backend::openapi::http;
using namespace timetable_vsu_backend::openapi::preferences;
using namespace timetable_vsu_backend::openapi::types;

UTEST(Openapi_Doc_Serialize, BasicStatusCode)
{
    EXPECT_EQ(Code<200>::value, userver::server::http::HttpStatus::kOk);
}

struct SomeBody
{
    String<Name<"some_string">> some_string;
    Array<int, Name<"some_array">> some_array;
    REFLECTIVE_BASE(SomeBody);
};

struct SomeRequest
{
    REFLECTIVE_BASE(SomeRequest);
    Header<std::string, Name<"some_header">> some_header;
    Cookie<std::string, Name<"some_cookie">> some_cookie;
    Body<SomeBody> some_body;
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
    using namespace std::literals;
    req.headers["some_header"sv] = "header_value";
    req.cookies["some_cookie"] = "cookie_value";
    auto info = MakeInfoFromRequest(req);
    auto parsed = Parse(info, userver::formats::parse::To<SomeRequest>{});
    auto arr_value = std::vector<int>{1, 2, 3};
    EXPECT_EQ(parsed.some_body().some_array(), arr_value);
    EXPECT_EQ(parsed.some_body().some_string(), "test_string");
    EXPECT_EQ(parsed.some_cookie(), "cookie_value");
    EXPECT_EQ(parsed.some_header(), "header_value");
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
    using namespace std::literals;
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
    using namespace std::literals;
    req.headers["some_header"sv] = "header_value";
    auto info = MakeInfoFromRequest(req);
    EXPECT_THROW_MSG(Parse(info, userver::formats::parse::To<SomeRequest>{}),
                     std::exception, "Missing cookie: some_cookie");
}
