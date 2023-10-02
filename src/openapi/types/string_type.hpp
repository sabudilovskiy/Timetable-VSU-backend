#pragma once
#include <openapi/base/preferences.hpp>
#include <openapi/base/string_property.hpp>
#include <openapi/base/string_traits.hpp>
#include <string_view>
#include <utils/compilers_macros.hpp>

namespace timetable_vsu_backend::openapi
{
namespace detail
{
template <utils::ConstexprString Name, utils::ConstexprString Pattern>
struct StringTraits : NamedTraits<Name>
{
    static constexpr auto kPattern = Pattern;
};

//вся эта структура нужна для того, чтобы работать с трейтами как с значением и
//применять поэтапно опции
//у меня нет иного выбора, кроме как стереть информацию о
//реальном размере строки, так как мне нельзя менять тип.
// 256 должно хватить
struct StringTraitsHolder
{
    std::array<char, 256> Pattern{};
    size_t Pattern_was_changed = 0;
    std::array<char, 256> Name{};
    size_t Name_was_changed = 0;
};

template <utils::ConstexprString value>
void consteval Apply(StringTraitsHolder& traits, preferences::Name<value> name)
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

template <utils::ConstexprString value>
void consteval Apply(StringTraitsHolder& traits,
                     preferences::Pattern<value> name)
{
    size_t Size = name.kValue.kSize;
    for (size_t index = 0; index < Size; index++)
    {
        traits.Pattern[index] = name.kValue[index];
    }
    for (size_t index = Size; index < 256; index++)
    {
        traits.Pattern[index] = '\0';
    }
    traits.Pattern_was_changed++;
}

template <typename T>
void consteval Apply(StringTraitsHolder&, const T&)
{
    STATIC_ASSERT_FALSE("You are used unknown option");
}

template <typename... Option>
void consteval ApplyAll(StringTraitsHolder& traits, Option... option)
{
    (Apply(traits, option), ...);
}

template <typename... Option>
struct StringMagicHelper
{
    consteval static auto resolve_holder()
    {
        StringTraitsHolder helper{};
        ApplyAll(helper, Option{}...);
        return helper;
    }
    consteval static auto resolve_traits()
    {
        constexpr StringTraitsHolder traits = resolve_holder();
        static_assert(traits.Name_was_changed <= 1,
                      "Don't use more 1 Name in template args");
        static_assert(traits.Pattern_was_changed <= 1,
                      "Don't use more 1 Pattern in template args");
        constexpr auto name = utils::MakeConstexprString<traits.Name>();
        constexpr auto pattern = utils::MakeConstexprString<traits.Pattern>();
        return StringTraits<name, pattern>{};
    }
};

template <typename... Option>
using string_traits_helper_t =
    decltype(StringMagicHelper<Option...>::resolve_traits());
}  // namespace detail

namespace types
{
template <typename... Option>
using String = StringProperty<detail::string_traits_helper_t<Option...>>;

}
}  // namespace timetable_vsu_backend::openapi
