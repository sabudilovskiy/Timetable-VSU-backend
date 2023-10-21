#pragma once

#include <array>
#include <cstddef>
#include <openapi/base/holder_named.hpp>
#include <openapi/base/named_traits.hpp>
#include <openapi/base/preferences.hpp>
#include <openapi/http/base/cookie_property.hpp>
#include <openapi/types/optional.hpp>
#include <type_traits>
#include <utils/compilers_macros.hpp>
#include <utils/constexpr_string.hpp>

namespace openapi::http
{
/*
Данное поле в запросе будет взято из cookie.

Ограничения:

Из-за особенностей парсинга не используйте Cookie<Optional<T>>, используйте
Cookie<std::optional<T>>
*/
template <typename T, typename... Options>
using Cookie = CookieProperty<T, named_traits_from_options_t<Options...>>;
}  // namespace openapi::http
