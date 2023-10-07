#pragma once
#include <cstdint>
#include <openapi/all.hpp>
#include <openapi/base/preferences.hpp>

using namespace openapi::types;
using namespace openapi::http;
using namespace openapi::preferences;
namespace views::test::login
{
struct RequestBody
{
    String<Name<"asdasdasdas">> login;
    String<Name<"passdasdasdaword_first">> password;
    Array<std::int32_t, Min<1>, Max<2>, UniqueItems, Name<"some_array">>
        some_array;
    auto operator<=>(const RequestBody&) const = default;
};

struct Request
{
    Body<RequestBody> body;
    Header<std::optional<std::string>, Name<"some_token">> some_token;
    auto operator<=>(const Request&) const = default;
};

struct ResponseBody
{
    String<Name<"some_string">> some_string;
    auto operator<=>(const ResponseBody&) const = default;
};

struct Response
{
    Body<ResponseBody> body;
    Header<std::string, Name<"some_header">> some_header;
    auto operator<=>(const Response&) const = default;
};
}  // namespace views::test::login
