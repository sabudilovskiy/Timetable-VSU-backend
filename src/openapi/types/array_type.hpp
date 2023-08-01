#pragma once
#include <string_view>

#include "openapi/base/array_traits.hpp"

namespace timetable_vsu_backend::openapi
{
namespace detail
{
template <utils::ConstexprString Name,
          utils::ConstexprOptional<size_t> Min = utils::kNull,
          utils::ConstexprOptional<size_t> Max = utils::kNull,
          utils::ConstexprOptional<bool> UniqueItems = utils::kNull>
struct ArrayTraits : NamedTraits<Name>
{
    static constexpr auto kMin = Min;
    static constexpr auto kMax = Max;
    static constexpr auto kUniqueItems = UniqueItems;
};

//вся эта структура нужна для того, чтобы работать с трейтами как с значением и
//применять поэтапно опции
//у меня нет иного выбора, кроме как стереть информацию о
//реальном размере строки, так как мне нельзя менять тип.
// 256 должно хватить
struct ArrayTraitsHolder
{
    std::array<char, 256> Name{};
    size_t Name_was_changed = 0;
    utils::ConstexprOptional<size_t> Min = utils::kNull;
    size_t Min_was_changed = 0;
    utils::ConstexprOptional<size_t> Max = utils::kNull;
    size_t Max_was_changed = 0;
    utils::ConstexprOptional<bool> UniqueItems = utils::kNull;
    size_t UniqueItems_was_changed = 0;
};

template <utils::ConstexprString value>
void consteval Apply(ArrayTraitsHolder& traits, preferences::Name<value> name)
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
void consteval Apply(ArrayTraitsHolder&, const T&)
{
    static_assert(
        ![] {}, "You are used unknown option");
}

template <size_t value>
void consteval Apply(ArrayTraitsHolder& traits, preferences::Min<value>)
{
    traits.Min = value;
    traits.Min_was_changed++;
}

template <size_t value>
void consteval Apply(ArrayTraitsHolder& traits, preferences::Max<value>)
{
    traits.Max = value;
    traits.Max_was_changed++;
}

template <bool value>
void consteval Apply(ArrayTraitsHolder& traits, preferences::UniqueItems<value>)
{
    traits.UniqueItems = value;
    traits.UniqueItems_was_changed++;
}

template <typename... Option>
void consteval ApplyAll(ArrayTraitsHolder& traits, Option... option)
{
    (Apply(traits, option), ...);
}

template <typename T, typename... Option>
struct ArrayMagicHelper
{
    consteval static auto resolve_holder()
    {
        ArrayTraitsHolder helper{};
        ApplyAll(helper, Option{}...);
        return helper;
    }
    consteval static auto resolve_traits()
    {
        constexpr ArrayTraitsHolder traits = resolve_holder();
        constexpr auto name = utils::MakeConstexprString<traits.Name>();
        static_assert(traits.Name_was_changed <= 1,
                      "Don't use more 1 Name in template args");
        static_assert(traits.Max_was_changed <= 1,
                      "Don't use more 1 Max in template args");
        static_assert(traits.Min_was_changed <= 1,
                      "Don't use more 1 Min in template args");
        static_assert(traits.UniqueItems_was_changed <= 1,
                      "Don't use more 1 UniqueItems in template args");
        return ArrayTraits<name, traits.Min, traits.Max, traits.UniqueItems>{};
    }
};

template <typename T, typename... Option>
using array_traits_helper_t =
    decltype(ArrayMagicHelper<T, Option...>::resolve_traits());
}  // namespace detail

namespace types
{
template <typename T, typename... Option>
using Array = ArrayProperty<T, detail::array_traits_helper_t<T, Option...>>;

}
}  // namespace timetable_vsu_backend::openapi
