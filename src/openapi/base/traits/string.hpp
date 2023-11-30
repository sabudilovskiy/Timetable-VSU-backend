#pragma once
#include <algorithm>
#include <iterator>
#include <openapi/base/named_traits.hpp>
#include <type_traits>
#include <utils/constexpr_optional.hpp>
#include <utils/constexpr_string.hpp>
namespace openapi
{
namespace checks
{
template <typename T>
concept HasPattern = requires(const T& t)
{
    t.pattern;
};
}  // namespace checks

namespace traits
{
template <typename T>
constexpr utils::FixedString GetPattern(const T& t)
{
    if constexpr (checks::HasPattern<T>)
    {
        return t.pattern;
    }
    else
        return utils::k_empty_fixed_string;
}

template <auto traits>
struct StringHelperTraits
{
    static constexpr utils::FixedString name = traits::GetName(traits);
    static constexpr utils::FixedString pattern = traits::GetPattern(traits);
    constexpr StringHelperTraits()
    {
    }
};

}  // namespace traits
}  // namespace openapi
