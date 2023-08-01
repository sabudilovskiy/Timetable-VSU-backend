#pragma once

#include "extended_object_property.hpp"
#include "named_traits.hpp"
#include "object_property.hpp"
#include "preferences.hpp"
#include "utils/constexpr_optional.hpp"
#include "utils/constexpr_string.hpp"
namespace timetable_vsu_backend::openapi
{
namespace checks
{
template <typename T>
concept HasAdditionalProperties = requires
{
    {
        T::kAdditionalProperties
    }
    ->std::convertible_to<utils::ConstexprOptional<bool>>;
};

template <typename T>
concept HasUseRoot = requires
{
    {
        T::kUseRoot
    }
    ->std::convertible_to<utils::ConstexprOptional<bool>>;
};

}  // namespace checks

namespace detail
{
template <typename T>
requires checks::HasAdditionalProperties<T> constexpr utils::ConstexprOptional<
    bool>
_getAdditionalProperties()
{
    return T::kAdditionalProperties;
}

template <typename T>
requires(!checks::HasAdditionalProperties<
         T>) constexpr utils::ConstexprOptional<bool> _getAdditionalProperties()
{
    return utils::kNull;
}

template <typename T>
requires checks::HasUseRoot<T> constexpr utils::ConstexprOptional<bool>
_getUseRoot()
{
    return T::kUseRoot;
}

template <typename T>
requires(!checks::HasUseRoot<T>) constexpr utils::ConstexprOptional<
    bool> _getUseRoot()
{
    return utils::kNull;
}

}  // namespace detail

namespace traits
{
template <typename T>
constexpr utils::ConstexprOptional<bool> GetAdditionalProperties()
{
    return detail::_getAdditionalProperties<T>();
}
template <typename T>
constexpr utils::ConstexprOptional<bool> GetUseRoot()
{
    return detail::_getUseRoot<T>();
}

template <typename Traits>
struct ObjectHelperTraits : NamedHelperTraits<Traits>
{
    static constexpr utils::ConstexprOptional<bool> use_root =
        traits::GetUseRoot<Traits>();
    static constexpr utils::ConstexprOptional<bool> additional_properties =
        traits::GetAdditionalProperties<Traits>();
    constexpr ObjectHelperTraits()
    {
    }
};

}  // namespace traits
}  // namespace timetable_vsu_backend::openapi
