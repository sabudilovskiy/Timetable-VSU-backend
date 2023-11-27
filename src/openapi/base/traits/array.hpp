#pragma once

#include <openapi/base/named_traits.hpp>
#include <openapi/base/properties/array.hpp>
#include <utils/constexpr_optional.hpp>
#include <utils/constexpr_string.hpp>
namespace openapi
{
namespace checks
{
template <typename T>
concept HasMin = requires(const T& t)
{
    t.min;
};

template <typename T>
concept HasMax = requires(const T& t)
{
    t.max;
};

template <typename T>
concept HasUniqueItems = requires(const T& t)
{
    t.unique_items;
};

}  // namespace checks

namespace traits
{
template <typename T>
constexpr utils::ConstexprOptional<std::int64_t> GetMin(const T& t)
{
    if constexpr (checks::HasMin<T>)
    {
        return t.min;
    }
    else
        return utils::kNull;
}
template <typename T>
constexpr utils::ConstexprOptional<std::int64_t> GetMax(const T& t)
{
    if constexpr (checks::HasMax<T>)
    {
        return t.max;
    }
    else
        return utils::kNull;
}
template <typename T>
constexpr utils::ConstexprOptional<bool> GetUniqueItems(const T& t)
{
    if constexpr (checks::HasUniqueItems<T>)
    {
        return t.unique_items;
    }
    else
        return utils::kNull;
}

template <auto traits>
struct ArrayHelperTraits : NamedHelperTraits<traits>
{
    static constexpr utils::ConstexprOptional<std::int64_t> min =
        traits::GetMin(traits);
    static constexpr utils::ConstexprOptional<std::int64_t> max =
        traits::GetMax(traits);
    static constexpr utils::ConstexprOptional<bool> unique_items =
        traits::GetUniqueItems(traits);
    constexpr ArrayHelperTraits()
    {
    }
};

}  // namespace traits
}  // namespace openapi
