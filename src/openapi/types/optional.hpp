#pragma once
#include <openapi/base/holder.hpp>
#include <openapi/base/preferences.hpp>
#include <openapi/base/properties/optional.hpp>
#include <openapi/base/traits/optional.hpp>
#include <string_view>
#include <utils/constexpr_optional.hpp>
#include <utils/constexpr_string.hpp>

namespace openapi
{
namespace detail
{
template <utils::ConstexprString Name,
          utils::ConstexprOptional<bool> useNullOnFail>
struct OptionalTraits : NamedTraits<Name>
{
    static constexpr auto kUseNullOnFail = useNullOnFail;
};

struct OptionalHolder
{
    traits::HolderField<utils::FixedString> name;
    traits::HolderField<utils::ConstexprOptional<bool>> use_null_non_fail;
};

template <utils::ConstexprString value>
void consteval Apply(OptionalHolder& traits, preferences::Name<value>)
{
    traits.name = value;
}

void consteval Apply(OptionalHolder& traits, preferences::UseNullOnFail)
{
    traits.use_null_non_fail = true;
}

template <typename T, typename... Option>
struct OptionalHelper
{
    consteval static OptionalHolder resolve_holder()
    {
        return traits::ResolveHolder<OptionalHolder, Option...>();
    }
    consteval static auto resolve_type()
    {
        constexpr OptionalHolder traits = resolve_holder();
        static_assert(traits.name.counter_changes <= 1,
                      "Don't use more 1 Name in template args");
        static_assert(traits.use_null_non_fail.counter_changes <= 1,
                      "Don't use more 1 UseNullOnFail in template args");
        constexpr auto name = utils::MakeConstexprString<traits.name()>();
        using Traits = OptionalTraits<name, traits.use_null_non_fail()>;
        return OptionalProperty<T, Traits>{};
    }
};

}  // namespace detail

namespace types
{
template <typename T, typename... Option>
using Optional =
    decltype(::openapi::detail::OptionalHelper<T, Option...>::resolve_type());

}
}  // namespace openapi
