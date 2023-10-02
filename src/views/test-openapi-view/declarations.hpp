#pragma once
#include <cstdint>
#include <openapi/all.hpp>
#include "openapi/base/preferences.hpp"
#include "openapi/base/reflective_base.hpp"

using namespace timetable_vsu_backend::openapi::types;
using namespace timetable_vsu_backend::openapi::http;
using namespace timetable_vsu_backend::openapi::preferences;
namespace timetable_vsu_backend::views::test::login
{

struct RequestBody{
    REFLECTIVE_BASE(RequestBody);
    String<Name<"login">> login;
    String<Name<"password">> password;
    Array<std::int32_t, Min<1>, Max<2>, UniqueItems, Name<"some_array">> some_array;
};

struct Request{
    REFLECTIVE_BASE(Request);
    Body<RequestBody> body;
    Header<std::optional<std::string>, Name<"some_token">> some_token;
};

struct ResponseBody{
    REFLECTIVE_BASE(ResponseBody);
    String<Name<"some_string">> some_string;
};

struct Response{
    REFLECTIVE_BASE(Response);
    Body<ResponseBody> body;
    Header<std::string, Name<"some_header">> some_header;
};
}  // namespace timetable_vsu_backend::views::login
