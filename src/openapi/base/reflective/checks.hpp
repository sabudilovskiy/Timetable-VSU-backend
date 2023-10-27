#pragma once
#include <boost/pfr.hpp>
#include <boost/pfr/core.hpp>
#include <boost/pfr/tuple_size.hpp>
#include <openapi/base/property_base.hpp>
#include <type_traits>
#include <utility>

namespace openapi
{
namespace checks
{
namespace details
{
template <typename T, std::size_t... I>
consteval bool is_fields_property_idxs(std::integer_sequence<std::size_t, I...>)
{
    return (IsProperty<boost::pfr::tuple_element_t<I, T>> && ...);
}

template <typename T>
requires std::is_aggregate_v<T> consteval bool is_fields_property_helper()
{
    auto seq = std::make_index_sequence<boost::pfr::tuple_size_v<T>>{};
    return is_fields_property_idxs<T>(seq);
}
}  // namespace details

template <typename T>
concept is_fields_property = details::is_fields_property_helper<T>();

template <typename T>
concept IsReflective = std::is_class_v<T>&& std::is_aggregate_v<T> &&
                       !IsProperty<T> && is_fields_property<T>;

template <typename T>
constexpr bool is_reflective_v = IsReflective<T>;

template <typename T>
concept IsReflectiveProperty =
    IsProperty<T>&& IsReflective<typename T::value_type>;

template <typename T>
constexpr bool is_reflective_property_v = IsReflectiveProperty<T>;

template <typename T>
concept IsNotReflectiveProperty =
    IsProperty<T> && !IsReflective<typename T::value_type>;

template <typename T>
constexpr bool is_not_reflective_property_v = IsNotReflectiveProperty<T>;

}  // namespace checks
}  // namespace openapi
