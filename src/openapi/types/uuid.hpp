#pragma once
#include <openapi/base/holder.hpp>
#include <openapi/base/holder_named.hpp>
#include <openapi/base/named_traits.hpp>
#include <openapi/base/preferences.hpp>
#include <openapi/base/properties/uuid.hpp>
#include <string_view>
#include <utils/compilers_macros.hpp>
#include <utils/constexpr_string.hpp>

namespace openapi
{
namespace types
{
template <typename... Option>
using Uuid = UuidProperty<::openapi::named_traits_from_options_t<Option...>>;

}
}  // namespace openapi
