#pragma once
#include <openapi/base/holder.hpp>
#include <openapi/base/preferences.hpp>
#include <openapi/base/properties/string.hpp>
#include <openapi/base/traits/string.hpp>
#include <string_view>
#include <utils/compilers_macros.hpp>
#include <utils/constexpr_string.hpp>

namespace openapi
{
namespace detail
{
struct StringTraits
{
    utils::FixedString name;
    utils::FixedString pattern;
};

struct StringHolder
{
    traits::HolderField<utils::FixedString> name;
    traits::HolderField<utils::FixedString> pattern;
};

template <utils::ConstexprString value>
void consteval Apply(StringHolder& traits, preferences::Name<value>)
{
    traits.name = value;
}

template <utils::ConstexprString value>
void consteval Apply(StringHolder& traits, preferences::Pattern<value>)
{
    traits.pattern = value;
}

template <typename... Option>
struct StringMagicHelper
{
    consteval static auto resolve_holder()
    {
        return traits::ResolveHolder<StringHolder, Option...>();
    }
    consteval static auto resolve_traits()
    {
        constexpr StringHolder traits = resolve_holder();
        static_assert(traits.name.counter_changes <= 1,
                      "Don't use more 1 Name in template args");
        static_assert(traits.pattern.counter_changes <= 1,
                      "Don't use more 1 Pattern in template args");
        return StringTraits{.name = traits.name(), .pattern = traits.pattern()};
    }
};

template <typename... Option>
constexpr StringTraits string_traits_helper_v =
    StringMagicHelper<Option...>::resolve_traits();
}  // namespace detail

namespace types
{
template <typename... Option>
using String = StringProperty<detail::string_traits_helper_v<Option...>>;
}
}  // namespace openapi
