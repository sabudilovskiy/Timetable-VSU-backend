#pragma once

#include <openapi/base/property_base.hpp>

namespace openapi::http
{
template <typename T, auto Traits = EmptyTraits{}>
struct ResponseProperty : PropertyBase<T, Traits>
{
};

}  // namespace openapi::http
