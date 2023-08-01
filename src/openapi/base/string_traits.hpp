#pragma once
#include <algorithm>
#include <iterator>
#include <type_traits>

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
concept HasPattern = requires
{
    {
        decltype(T::kPattern)::kSize
    }
    ->std::convertible_to<std::size_t>;
    requires std::is_same_v<
        utils::ConstexprString<decltype(T::kPattern)::kSize>,
        std::remove_cv_t<decltype(T::kPattern)>>;
    {
        T::kPattern
    }
    ->std::convertible_to<utils::ConstexprString<decltype(T::kPattern)::kSize>>;
};
}  // namespace checks

namespace detail
{
template <typename T>
requires checks::HasPattern<T> constexpr auto _getPattern()
{
    return T::kPattern;
}

template <typename T>
requires(!checks::HasPattern<T>) constexpr auto _getPattern()
{
    using Type = utils::ConstexprString<1>;
    return Type{""};
}
}  // namespace detail

namespace traits
{
template <typename T>
constexpr auto GetPattern()
{
    return detail::_getPattern<T>();
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
}  // namespace timetable_vsu_backend::openapi
