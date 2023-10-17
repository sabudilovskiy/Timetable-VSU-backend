#pragma once

#include <cstddef>
#include <openapi/base/object_property.hpp>
#include <openapi/http/base/response_property.hpp>
#include <openapi/http/base/response_traits.hpp>

namespace openapi::http
{
template <typename T, std::size_t Code>
requires checks::is_reflective_v<T> using Resp =
    ResponseProperty<T, ResponseTraits<Code>>;
}
