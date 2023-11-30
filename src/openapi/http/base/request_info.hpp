#pragma once
#include <userver/server/http/http_request.hpp>

namespace openapi::http
{
struct RequestInfo
{
    const userver::server::http::HttpRequest::HeadersMap& headers;
    const userver::server::http::HttpRequest::CookiesMap& cookies;
    const std::string& body;
};

struct TestRequest
{
    userver::server::http::HttpRequest::HeadersMap headers;
    userver::server::http::HttpRequest::CookiesMap cookies;
    std::string body;
};

inline RequestInfo MakeInfoFromRequest(
    const userver::server::http::HttpRequest& request)
{
    return RequestInfo{.headers = request.RequestHeaders(),
                       .cookies = request.RequestCookies(),
                       .body = request.RequestBody()};
}

inline RequestInfo MakeInfoFromRequest(const TestRequest& request)
{
    return RequestInfo{.headers = request.headers,
                       .cookies = request.cookies,
                       .body = request.body};
}
}  // namespace openapi::http
