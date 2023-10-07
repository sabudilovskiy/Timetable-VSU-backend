#pragma once

#include <openapi/base/property_base.hpp>

namespace openapi::http
{
template <typename T, typename Traits>
struct CookieProperty : PropertyBase<T, Traits>
{
};
};  // namespace openapi::http
