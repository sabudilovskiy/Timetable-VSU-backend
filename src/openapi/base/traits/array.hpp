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
concept HasMin = requires
{
    {
        T::kMin
    };
};

template <typename T>
concept HasMax = requires
{
    {
        T::kMax
    };
};

template <typename T>
concept HasUniqueItems = requires
{
    {
        T::kUniqueItems
    };
};

}  // namespace checks


namespace traits
{
template <typename T>
constexpr utils::ConstexprOptional<std::int64_t> GetMin()
{
    if constexpr (checks::HasMin<T>){
        return T::kMin;
    }
    else return utils::kNull;
}
template <typename T>
constexpr utils::ConstexprOptional<std::int64_t> GetMax()
{
    if constexpr (checks::HasMax<T>){
      return T::kMax;
    }
    else return utils::kNull;
}
template <typename T>
constexpr utils::ConstexprOptional<bool> GetUniqueItems()
{
    if constexpr (checks::HasUniqueItems<T>){
        return T::kUniqueItems;
    }
    else return utils::kNull;
}

template <typename Traits>
struct ArrayHelperTraits : NamedHelperTraits<Traits>
{
    static constexpr utils::ConstexprOptional<std::int64_t> min =
        traits::GetMin<Traits>();
    static constexpr utils::ConstexprOptional<std::int64_t> max =
        traits::GetMax<Traits>();
    static constexpr utils::ConstexprOptional<bool> unique_items =
        traits::GetUniqueItems<Traits>();
    constexpr ArrayHelperTraits()
    {
    }
};

}  // namespace traits
}  // namespace openapi
