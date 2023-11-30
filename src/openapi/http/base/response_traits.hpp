#pragma once

#include <cstddef>
#include <openapi/http/base/status_code.hpp>
namespace openapi::http
{
struct ResponseTraits
{
    userver::server::http::HttpStatus code;
};

template <std::size_t CodeInt>
constexpr ResponseTraits response_traits_v =
    ResponseTraits{.code = code_v<CodeInt>};
}  // namespace openapi::http
