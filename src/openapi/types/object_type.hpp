#pragma once
#include <openapi/base/named_traits.hpp>
#include <openapi/base/object_property.hpp>
#include <openapi/base/preferences.hpp>
#include <string_view>
#include <utils/constexpr_optional.hpp>

namespace timetable_vsu_backend::openapi
{
namespace detail
{
template <utils::ConstexprString Name, utils::ConstexprOptional<bool> UseRoot,
          utils::ConstexprOptional<bool> AdditionalProperties>
struct ObjectTraits : NamedTraits<Name>
{
};

/*
вся эта структура нужна для того, чтобы работать с трейтами как с значением и
применять поэтапно опции

у меня нет иного выбора, кроме как стереть информацию о реальном размере строки,
так как мне нельзя менять тип.

256 должно хватить*/
struct ObjectTraitsHolder
{
    utils::ConstexprOptional<bool> AdditionalProperties{utils::kNull};
    size_t AdditionalProperties_was_changed = 0;
    utils::ConstexprOptional<bool> UseRoot{utils::kNull};
    size_t UseRoot_was_changed = 0;
    std::array<char, 256> Name{};
    size_t Name_was_changed = 0;
};

template <utils::ConstexprString value>
void consteval Apply(ObjectTraitsHolder& traits, preferences::Name<value> name)
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
void consteval Apply(ObjectTraitsHolder&, const T&)
{
    static_assert(
        ![] {}, "You are used unknown option");
}

template <typename... Option>
void consteval ApplyAll(ObjectTraitsHolder& traits, Option... option)
{
    (Apply(traits, option), ...);
}

template <typename T, typename... Option>
struct ObjectMagicHelper
{
    consteval static auto resolve_holder()
    {
        ObjectTraitsHolder helper{};
        ApplyAll(helper, Option{}...);
        return helper;
    }
    consteval static auto resolve_type()
    {
        constexpr ObjectTraitsHolder traits = resolve_holder();
        constexpr auto name = utils::MakeConstexprString<traits.Name>();
        static_assert(traits.Name_was_changed <= 1,
                      "Don't use more 1 Name in template args");
        // static_assert(!(traits.UseRoot.value_or(false) &&
        // traits.AdditionalProperties.value_or(false)), "Dont use UseRoot with
        // AdditionalProperties");
        using Traits =
            ObjectTraits<name, traits.UseRoot.value_or(false),
                         traits.AdditionalProperties.value_or(false)>;
        return ObjectProperty<T, Traits>{};
    }
};

}  // namespace detail

namespace types
{
template <typename T, typename... Option>
using Object =
    decltype(detail::ObjectMagicHelper<T, Option...>::resolve_type());

}
}  // namespace timetable_vsu_backend::openapi
