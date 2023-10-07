#pragma once

#include <compare>
#include <cstddef>
#include <iostream>
#include <string>
#include <userver/server/http/http_request.hpp>
#include <utility>

namespace openapi::http
{
enum struct ResponseBodyType
{
    kText,
    kJson
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
        if (auto cmp = lhs.userver_code <=> rhs.userver_code;
            cmp != std::strong_ordering::equal)
        {
            return cmp;
        }
        if (auto cmp = lhs.body <=> rhs.body;
            cmp != std::strong_ordering::equal)
        {
            return cmp;
        }
        if (auto cmp = lhs.headers == rhs.headers; !cmp)
        {
            return std::partial_ordering::unordered;
        }
        if (auto cmp = lhs.response_body_type == rhs.response_body_type; !cmp){
            return std::partial_ordering::unordered;
        }
        return std::partial_ordering::equivalent;
    }
    bool operator==(const ResponseInfo& rhs) const = default;
};
}  // namespace openapi::http
