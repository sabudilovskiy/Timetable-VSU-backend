#pragma once

#include <openapi/base/holder.hpp>
#include <openapi/base/named_traits.hpp>
#include <openapi/base/preferences.hpp>
#include <utils/constexpr_string.hpp>
namespace openapi
{
struct HolderNamed
{
    traits::HolderField<utils::FixedString> name;
};

template <utils::ConstexprString value>
consteval void Apply(HolderNamed& holder, preferences::Name<value>)
{
    holder.name = value;
}

namespace details
{
template <typename... Option>
auto resolve_named_traits()
{
    constexpr HolderNamed holder =
        traits::ResolveHolder<HolderNamed, Option...>();
    static_assert(holder.name.counter_changes <= 1,
                  "Don't use more 1 Name in template args");
    constexpr auto name = utils::MakeConstexprString<holder.name()>();
    return NamedTraits<name>{};
}
}  // namespace details

template <typename... Option>
using named_traits_from_options_t =
    decltype(details::resolve_named_traits<Option...>());
}  // namespace openapi
