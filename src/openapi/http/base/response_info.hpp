#pragma once

#include <compare>
#include <cstddef>
#include <string>
#include <userver/server/http/http_request.hpp>

namespace timetable_vsu_backend::openapi::http
{
enum struct ResponseBodyType{
    kText, kJson 
};
struct ResponseInfo
{
    userver::server::http::HttpStatus userver_code;
    std::string body;
    userver::server::http::HttpRequest::HeadersMap headers;
    ResponseBodyType response_body_type;
    std::partial_ordering operator<=>(const ResponseInfo& rhs) const
    {
        auto& lhs = *this;
        if (auto cmp = (lhs.userver_code <=> rhs.userver_code);
            cmp != std::strong_ordering::equal)
        {
            return cmp;
        }
        if (auto cmp = (lhs.body <=> rhs.body);
            cmp != std::strong_ordering::equal)
        {
            return cmp;
        }
        auto cmp = lhs.headers == rhs.headers;
        if (cmp)
            return std::partial_ordering::equivalent;
        else
            return std::partial_ordering::unordered;
    }
    bool operator==(const ResponseInfo&) const = default;
};
}  // namespace timetable_vsu_backend::openapi::http
