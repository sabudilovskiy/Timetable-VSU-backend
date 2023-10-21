#pragma once

#include <openapi/base/named_traits.hpp>
#include <utils/constexpr_optional.hpp>
#include <utils/constexpr_string.hpp>
namespace openapi
{
namespace checks
{
template <typename T>
concept HasUseNullOnFail = requires
{
    {
        T::kUseNullOnFail
    };
};

}  // namespace checks

namespace traits
{
template <typename T>
constexpr utils::ConstexprOptional<bool> GetUseNullOnFail()
{
    if constexpr (checks::HasUseNullOnFail<T>){
        return T::kUseNullOnFail;
    }
    else return utils::kNull;
}

template <typename Traits>
struct OptionalHelperTraits : NamedHelperTraits<Traits>
{
    static constexpr utils::ConstexprOptional<bool> null_on_failure =
        traits::GetUseNullOnFail<Traits>();
    constexpr OptionalHelperTraits()
    {
    }
};

}  // namespace traits
}  // namespace openapi
