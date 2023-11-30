#pragma once
#include <openapi/base/holder.hpp>
#include <openapi/base/holder_named.hpp>
#include <openapi/base/named_traits.hpp>
#include <openapi/base/preferences.hpp>
#include <openapi/base/properties/datetime.hpp>
#include <utils/constexpr_string.hpp>

namespace openapi::types
{
template <typename... Option>
using Datetime = DateTimeProperty<named_traits_from_options_v<Option...>>;

}  // namespace openapi::types
