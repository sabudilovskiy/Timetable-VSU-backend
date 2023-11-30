#pragma once
#include <cstddef>
#include <openapi/base/holder.hpp>
#include <openapi/base/named_traits.hpp>
#include <openapi/base/preferences.hpp>
#include <openapi/base/properties/array.hpp>
#include <openapi/base/traits/array.hpp>
#include <string_view>
#include <utils/constexpr_optional.hpp>
#include <utils/constexpr_string.hpp>

namespace openapi
{
namespace detail
{
struct ArrayTraits
{
    utils::FixedString name;
    utils::ConstexprOptional<std::int64_t> min;
    utils::ConstexprOptional<std::int64_t> max;
    utils::ConstexprOptional<bool> unique_items;
};

struct ArrayHolder
{
    traits::HolderField<utils::FixedString> name;
    traits::HolderField<utils::ConstexprOptional<std::int64_t>> min;
    traits::HolderField<utils::ConstexprOptional<std::int64_t>> max;
    traits::HolderField<bool> unique_items;
};

template <utils::ConstexprString value>
void consteval Apply(ArrayHolder& traits, preferences::Name<value>)
{
    traits.name = value;
}

template <std::int64_t value>
void consteval Apply(ArrayHolder& traits, preferences::Min<value>)
{
    traits.min = value;
}

template <std::int64_t value>
void consteval Apply(ArrayHolder& traits, preferences::Max<value>)
{
    traits.max = value;
}

void consteval Apply(ArrayHolder& traits, preferences::UniqueItems)
{
    traits.unique_items = true;
}

template <typename T, typename... Option>
struct ArrayMagicHelper
{
    consteval static ArrayHolder resolve_holder()
    {
        return traits::ResolveHolder<ArrayHolder, Option...>();
    }
    consteval static auto resolve_type()
    {
        constexpr ArrayHolder traits = resolve_holder();
        static_assert(traits.name.counter_changes <= 1,
                      "Don't use more 1 Name in template args");
        static_assert(traits.max.counter_changes <= 1,
                      "Don't use more 1 Max in template args");
        static_assert(traits.min.counter_changes <= 1,
                      "Don't use more 1 Min in template args");
        static_assert(traits.unique_items.counter_changes <= 1,
                      "Don't use more 1 UniqueItems in template args");
        return ArrayProperty<T, ArrayTraits{
                                    .name = traits.name(),
                                    .min = traits.min(),
                                    .max = traits.max(),
                                    .unique_items = traits.unique_items()}>{};
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
using Array =
    decltype(::openapi::detail::ArrayMagicHelper<T, Option...>::resolve_type());

}  // namespace types
}  // namespace openapi
