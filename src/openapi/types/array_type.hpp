#pragma once
#include <openapi/base/array_property.hpp>
#include <openapi/base/array_traits.hpp>
#include <openapi/base/preferences.hpp>
#include <string_view>
#include <utils/constexpr_optional.hpp>

namespace openapi
{
namespace detail
{
template <utils::ConstexprString Name,
          utils::ConstexprOptional<std::int64_t> Min = utils::kNull,
          utils::ConstexprOptional<std::int64_t> Max = utils::kNull,
          utils::ConstexprOptional<bool> UniqueItems = utils::kNull>
struct ArrayTraits : NamedTraits<Name>
{
    static constexpr auto kMin = Min;
    static constexpr auto kMax = Max;
    static constexpr auto kUniqueItems = UniqueItems;
};

/*вся эта структура нужна для того, чтобы работать с трейтами как с значением и
применять поэтапно опции

у меня нет иного выбора, кроме как стереть информацию о
реальном размере строки, так как мне нельзя менять тип.

256 должно хватить*/
struct ArrayTraitsHolder
{
    std::array<char, 256> Name{};
    size_t Name_was_changed = 0;
    utils::ConstexprOptional<std::int64_t> Min = utils::kNull;
    size_t Min_was_changed = 0;
    utils::ConstexprOptional<std::int64_t> Max = utils::kNull;
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

template <std::int64_t value>
void consteval Apply(ArrayTraitsHolder& traits, preferences::Min<value>)
{
    traits.Min = value;
    traits.Min_was_changed++;
}

template <std::int64_t value>
void consteval Apply(ArrayTraitsHolder& traits, preferences::Max<value>)
{
    traits.Max = value;
    traits.Max_was_changed++;
}

void consteval Apply(ArrayTraitsHolder& traits, preferences::UniqueItems)
{
    traits.UniqueItems = true;
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
    consteval static auto resolve_type()
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
        using Traits =
            ArrayTraits<name, traits.Min, traits.Max, traits.UniqueItems>;
        return ArrayProperty<T, Traits>{};
    }
};

}  // namespace detail

namespace types
{
/*
T -> тип, который вы хотите использовать.

Убедитесь, что в месте парса/сериализации будут доступны парсы/сериализаторы для
него

Option... -> свойства, которые вы хотите добавить.

Min<1> -> минимум элементов. Соответствует min: 1 в openapi

Max<2> -> максимум элементов. Соответствует max: 2 в openapi

Name<"FieldName"> -> имя поля в объекте

UniqueItems -> добавлять только уникальные итемы
*/
template <typename T, typename... Option>
using Array = decltype(detail::ArrayMagicHelper<T, Option...>::resolve_type());

}  // namespace types
}  // namespace openapi
