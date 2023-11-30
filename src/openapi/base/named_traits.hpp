#pragma once
#include <concepts>
#include <openapi/base/property_base.hpp>
#include <type_traits>
#include <utils/constexpr_optional.hpp>
#include <utils/constexpr_string.hpp>

namespace openapi
{
struct NamedTraits
{
    utils::FixedString name;
};

namespace checks
{
template <typename T>
concept HasName = requires(T& t)
{
    t.name;
};

}  // namespace checks

namespace traits
{
// returns ConstexprString
template <typename T>
constexpr utils::FixedString GetName(const T& t)
{
    if constexpr (checks::HasName<T>)
    {
        return t.name;
    }
    else
        return utils::k_empty_fixed_string;
}

template <auto Traits>
struct NamedHelperTraits
{
    static constexpr auto name = traits::GetName(Traits);
};
}  // namespace traits
}  // namespace openapi
