#pragma once
#include <openapi/base/holder.hpp>
#include <openapi/base/holder_named.hpp>
#include <openapi/base/named_traits.hpp>
#include <openapi/base/preferences.hpp>
#include <openapi/base/properties/object.hpp>
#include <string_view>
#include <utils/constexpr_optional.hpp>
#include <utils/constexpr_string.hpp>

namespace openapi
{
namespace types
{
template <typename T, typename... Option>
using Object = ObjectProperty<T, named_traits_from_options_t<Option...>>;

}
}  // namespace openapi
