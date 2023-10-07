#pragma once

#include <cstddef>
#include <openapi/http/base/status_code.hpp>
namespace openapi::http
{
template <std::size_t CodeInt>
struct ResponseTraits
{
    static constexpr userver::server::http::HttpStatus code = code_v<CodeInt>;
};
}  // namespace openapi::http
