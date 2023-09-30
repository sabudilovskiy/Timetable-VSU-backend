#pragma once

#include <cstddef>
#include <string>
#include <userver/server/http/http_request.hpp>

namespace timetable_vsu_backend::openapi::http
{
template <userver::server::http::HttpStatus Code>
struct ResponseInfo
{
    static constexpr auto userver_code = Code;
    std::string body;
    userver::server::http::HttpRequest::HeadersMap headers;
};
}  // namespace timetable_vsu_backend::openapi::http
