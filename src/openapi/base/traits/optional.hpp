#pragma once

#include <openapi/base/named_traits.hpp>
#include <utils/constexpr_optional.hpp>
#include <utils/constexpr_string.hpp>
namespace openapi
{
namespace checks
{
template <typename T>
concept HasUseNullOnFail = requires(const T& t)
{
    t.use_null_on_fail;
};

}  // namespace checks

namespace traits
{
template <typename T>
constexpr utils::ConstexprOptional<bool> GetUseNullOnFail(const T& t)
{
    if constexpr (checks::HasUseNullOnFail<T>)
    {
        return t.use_null_on_fail;
    }
    else
        return utils::kNull;
}

template <auto traits>
struct OptionalHelperTraits : NamedHelperTraits<traits>
{
    static constexpr utils::ConstexprOptional<bool> null_on_failure =
        traits::GetUseNullOnFail(traits);
    constexpr OptionalHelperTraits()
    {
    }
};

}  // namespace traits
}  // namespace openapi
