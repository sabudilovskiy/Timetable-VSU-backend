#pragma once
#include <concepts>
#include <openapi/base/property_base.hpp>
#include <type_traits>
#include <utils/constexpr_optional.hpp>
#include <utils/constexpr_string.hpp>

namespace openapi
{
template <utils::ConstexprString Name>
struct NamedTraits
{
    static constexpr auto kName = Name;
};

namespace checks
{
template <typename T>
concept HasName = requires
{
    {T::kName};
};

}  // namespace checks

namespace traits
{
// returns ConstexprString
template <typename T>
constexpr auto GetName()
{
    if constexpr (checks::HasName<T>)
    {
        return T::kName;
    }
    else
        return utils::kEmptyString;
}

template <typename Traits>
struct NamedHelperTraits
{
    static constexpr auto name = traits::GetName<Traits>();
};
}  // namespace traits
}  // namespace openapi
