#pragma once
#include <cstdint>
#include <openapi/all.hpp>
#include <openapi/base/preferences.hpp>
#include <userver/storages/postgres/io/io_fwd.hpp>

using namespace openapi::types;
using namespace openapi::http;
using namespace openapi::preferences;
namespace views::test::login
{
struct RequestBody
{
    String<Name<"login">> login;
    String<Name<"password">> password;
    auto operator<=>(const RequestBody&) const = default;
};

struct Request
{
    Body<RequestBody> body;
    auto operator<=>(const Request&) const = default;
};

struct ResponseBody
{
    String<Name<"result">> some_string;
    auto operator<=>(const ResponseBody&) const = default;
};

struct Response
{
    Body<ResponseBody> body;
    Header<std::string, Name<"some_header">> some_header;
    auto operator<=>(const Response&) const = default;
};

}  // namespace views::test::login
