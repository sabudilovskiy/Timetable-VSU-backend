#pragma once

#include <openapi/base/holder_named.hpp>
#include <openapi/base/property_base.hpp>
namespace openapi::types
{
template <typename T, typename... Options>
using Field = Property<T, named_traits_from_options_v<Options...>>;
}
