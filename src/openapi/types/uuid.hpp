#pragma once
#include <openapi/base/holder.hpp>
#include <openapi/base/named_traits.hpp>
#include <openapi/base/preferences.hpp>
#include <openapi/base/properties/uuid.hpp>
#include <string_view>
#include <utils/compilers_macros.hpp>
#include <utils/constexpr_string.hpp>

namespace openapi
{
namespace detail
{
template <utils::ConstexprString Name>
struct UuidTraits : NamedTraits<Name>
{
};

struct UuidTraitsHolder
{
    traits::HolderField<utils::FixedString> name;
};

template <utils::ConstexprString value>
void consteval Apply(UuidTraitsHolder& traits, preferences::Name<value>)
{
    traits.name = value;
}

template <typename T>
void consteval Apply(UuidTraitsHolder&, const T&)
{
    STATIC_ASSERT_FALSE("You are used unknown option");
}

template <typename... Option>
void consteval ApplyAll(UuidTraitsHolder& traits, Option... option)
{
    (Apply(traits, option), ...);
}

template <typename... Option>
struct UuidHelper
{
    consteval static auto resolve_holder()
    {
        UuidTraitsHolder helper{};
        ApplyAll(helper, Option{}...);
        return helper;
    }
    consteval static auto resolve_traits()
    {
        constexpr UuidTraitsHolder traits = resolve_holder();
        static_assert(traits.name.counter_changes <= 1,
                      "Don't use more 1 Name in template args");
        constexpr auto name = utils::MakeConstexprString<traits.name.value_>();
        return UuidTraits<name>{};
    }
};

template <typename... Option>
using uuid_traits_helper_t = decltype(UuidHelper<Option...>::resolve_traits());
}  // namespace detail

namespace types
{
template <typename... Option>
using Uuid = UuidProperty<::openapi::detail::uuid_traits_helper_t<Option...>>;

}
}  // namespace openapi
