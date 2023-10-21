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
concept HasPattern = requires
{
    {
        T::kPattern
    };
};
}  // namespace checks

namespace traits
{
template <typename T>
constexpr auto GetPattern()
{
    if constexpr (checks::HasPattern<T>){
        return T::kPattern;
    }
    else return utils::kEmptyString;
}

template <typename Traits>
struct StringHelperTraits
{
    static constexpr utils::ConstexprString name = traits::GetName<Traits>();
    static constexpr utils::ConstexprString pattern =
        traits::GetPattern<Traits>();
    constexpr StringHelperTraits()
    {
    }
};

}  // namespace traits
}  // namespace openapi
