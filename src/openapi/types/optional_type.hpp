#pragma once
#include <string_view>

#include "openapi/base/object_property.hpp"
#include "openapi/base/optional_property.hpp"
#include "openapi/base/optional_traits.hpp"
#include "openapi/base/preferences.hpp"
#include "utils/constexpr_optional.hpp"

namespace timetable_vsu_backend::openapi
{
namespace detail
{
template <utils::ConstexprString Name,
          utils::ConstexprOptional<bool> useNullOnFail>
struct OptionalTraits : NamedTraits<Name>
{
    static constexpr auto kUseNullOnFail = useNullOnFail;
};

//вся эта структура нужна для того, чтобы работать с трейтами как с значением и
//применять поэтапно опции
//у меня нет иного выбора, кроме как стереть информацию о
//реальном размере строки, так как мне нельзя менять тип.
// 256 должно хватить
struct OptionalTraitsHolder
{
    utils::ConstexprOptional<bool> UseNullOnFail{utils::kNull};
    size_t UseNullOnFail_was_changed = 0;
    std::array<char, 256> Name{};
    size_t Name_was_changed = 0;
};

template <utils::ConstexprString value>
void consteval Apply(OptionalTraitsHolder& traits,
                     preferences::Name<value> name)
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

void consteval Apply(OptionalTraitsHolder& traits, preferences::UseNullOnFail)
{
    traits.UseNullOnFail = true;
    traits.UseNullOnFail_was_changed++;
}

template <typename T>
void consteval Apply(OptionalTraitsHolder&, const T&)
{
    static_assert(
        ![] {}, "You are used unknown option");
}

template <typename... Option>
void consteval ApplyAll(OptionalTraitsHolder& traits, Option... option)
{
    (Apply(traits, option), ...);
}

template <typename T, typename... Option>
struct OptionalMagicHelper
{
    consteval static auto resolve_holder()
    {
        OptionalTraitsHolder helper{};
        ApplyAll(helper, Option{}...);
        return helper;
    }
    consteval static auto resolve_type()
    {
        constexpr OptionalTraitsHolder traits = resolve_holder();
        constexpr auto name = utils::MakeConstexprString<traits.Name>();
        static_assert(traits.Name_was_changed <= 1,
                      "Don't use more 1 Name in template args");
        static_assert(traits.UseNullOnFail_was_changed <= 1,
                      "Don't use more 1 UseNullOnFail in template args");
        using Traits = OptionalTraits<name, traits.UseNullOnFail>;
        return OptionalProperty<T, Traits>{};
    }
};

}  // namespace detail

namespace types
{
template <typename T, typename... Option>
using Optional =
    decltype(detail::OptionalMagicHelper<T, Option...>::resolve_type());

}
}  // namespace timetable_vsu_backend::openapi
