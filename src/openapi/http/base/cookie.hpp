#pragma once

#include <array>
#include <cstddef>
#include <openapi/base/named_traits.hpp>
#include <openapi/base/preferences.hpp>
#include <openapi/http/base/cookie_property.hpp>
#include <openapi/types/optional_type.hpp>
#include <type_traits>
#include <utils/compilers_macros.hpp>
#include <utils/constexpr_string.hpp>

namespace openapi::http
{
struct CookieTraitsHolder
{
    std::array<char, 256> Name{};
    size_t Name_was_changed = 0;
};
template <utils::ConstexprString value>
void consteval Apply(CookieTraitsHolder& traits, preferences::Name<value> name)
{
    size_t Size = name.kValue.kSize;
    for (size_t index = 0; index < Size; index++)
    {
        traits.Name[index] = name.kValue[index];
    }
    for (size_t index = Size; index < 256; index++)
    {
        traits.Name[index] = '\0';
    }
    traits.Name_was_changed++;
}

template <typename T>
void consteval Apply(CookieTraitsHolder&, const T&)
{
    STATIC_ASSERT_FALSE("You are used unknown option");
}

template <typename... Option>
void consteval ApplyAll(CookieTraitsHolder& traits, Option... option)
{
    (Apply(traits, option), ...);
}

template <typename T, typename... Options>
struct CookieTraitsHelper
{
    static consteval CookieTraitsHolder resolve_holder()
    {
        CookieTraitsHolder traits{};
        ApplyAll(traits, Options{}...);
        return traits;
    }
    static consteval auto resolve_type()
    {
        constexpr CookieTraitsHolder traits = resolve_holder();
        static_assert(traits.Name_was_changed <= 1,
                      "Don't use more 1 Name in template args");
        constexpr auto name = utils::MakeConstexprString<traits.Name>();
        return CookieProperty<T, NamedTraits<name>>();
    }
};

// template <typename T, typename... Options> requires IsOptionalProperty<T>
// struct CookieTraitsHelper{
//    STATIC_ASSERT_FALSE("Не используйте Optional<...> из-за особенностей
//    парсинга. Используйте явный std::optional<T>");
// };

/*
Данное поле в запросе будет взято из cookie.

Ограничения:

Из-за особенностей парсинга не используйте Cookie<Optional<T>>, используйте
Cookie<std::optional<T>>
*/
template <typename T, typename... Options>
using Cookie = decltype(CookieTraitsHelper<T, Options...>::resolve_type());
}  // namespace openapi::http
