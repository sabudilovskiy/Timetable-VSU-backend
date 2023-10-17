#pragma once
#include <boost/pfr.hpp>
#include <boost/pfr/core.hpp>
#include <boost/pfr/tuple_size.hpp>
#include <openapi/base/property_base.hpp>

namespace openapi
{
namespace checks
{
template <typename T, std::size_t... Indexes>
concept IsReflectiveHelper = requires
{
    requires(IsProperty<boost::pfr::tuple_element_t<Indexes, T>> && ...);
};

template <typename T>
concept IsReflective =
    std::is_class_v<T>&& std::is_aggregate_v<T> && !IsProperty<T>;

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
