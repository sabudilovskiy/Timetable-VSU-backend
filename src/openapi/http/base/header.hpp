#pragma once

#include <array>
#include <cstddef>
#include <openapi/base/holder_named.hpp>
#include <openapi/base/named_traits.hpp>
#include <openapi/base/preferences.hpp>
#include <openapi/http/base/header_property.hpp>
#include <openapi/types/optional.hpp>
#include <type_traits>
#include <utils/compilers_macros.hpp>
#include <utils/constexpr_string.hpp>

namespace openapi::http
{
/*
Данное поле в запросе будет взято из cookie.

Ограничения:

Из-за особенностей парсинга не используйте Header<Optional<T>>, используйте
Header<std::optional<T>>
*/
template <typename T, typename... Options>
using Header = HeaderProperty<T, named_traits_from_options_v<Options...>>;
}  // namespace openapi::http
