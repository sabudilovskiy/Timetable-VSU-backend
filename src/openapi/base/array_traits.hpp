#pragma once

#include "array_property.hpp"
#include "named_traits.hpp"
#include "preferences.hpp"
#include "utils/constexpr_optional.hpp"
#include "utils/constexpr_string.hpp"
namespace timetable_vsu_backend::openapi
{
namespace checks
{
template <typename T>
concept HasMin = requires
{
    {
        T::kMin
    }
    ->std::convertible_to<utils::ConstexprOptional<size_t>>;
};

template <typename T>
concept HasMax = requires
{
    {
        T::kMax
    }
    ->std::convertible_to<utils::ConstexprOptional<size_t>>;
};

template <typename T>
concept HasUniqueItems = requires
{
    {
        T::kUniqueItems
    }
    ->std::convertible_to<utils::ConstexprOptional<bool>>;
};

template <typename T>
concept HasNotMin = !HasMin<T>;

template <typename T>
concept HasNotMax = !HasMax<T>;

template <typename T>
concept HasNotUniqueItems = !HasUniqueItems<T>;
}  // namespace checks

namespace detail
{
template <checks::HasMin T>
constexpr auto _getMin()
{
    return T::kMin;
}

template <checks::HasNotMin T>
constexpr auto _getMin()
{
    return utils::ConstexprOptional<size_t>{utils::kNull};
}

template <checks::HasMax T>
constexpr auto _getMax()
{
    return T::kMax;
}

template <checks::HasNotMax T>
constexpr auto _getMax()
{
    return utils::ConstexprOptional<size_t>{utils::kNull};
}

template <checks::HasUniqueItems T>
constexpr auto _getUniqueItems()
{
    return T::kUniqueItems;
}

template <checks::HasNotUniqueItems T>
constexpr auto _getUniqueItems()
{
    return utils::ConstexprOptional<bool>{utils::kNull};
}
}  // namespace detail

namespace traits
{
template <typename T>
constexpr utils::ConstexprOptional<size_t> GetMin()
{
    return detail::_getMin<T>();
}
template <typename T>
constexpr utils::ConstexprOptional<size_t> GetMax()
{
    return detail::_getMax<T>();
}
template <typename T>
constexpr utils::ConstexprOptional<bool> GetUniqueItems()
{
    return detail::_getUniqueItems<T>();
}

template <typename Traits>
struct ArrayHelperTraits : NamedHelperTraits<Traits>
{
    static constexpr utils::ConstexprOptional<size_t> min =
        traits::GetMin<Traits>();
    static constexpr utils::ConstexprOptional<size_t> max =
        traits::GetMax<Traits>();
    static constexpr utils::ConstexprOptional<bool> unique_items =
        traits::GetUniqueItems<Traits>();
    constexpr ArrayHelperTraits()
    {
    }
};

}  // namespace traits
}  // namespace timetable_vsu_backend::openapi
