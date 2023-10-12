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
concept IsReflective = requires
{
    requires std::is_class_v<T>;
    requires std::is_aggregate_v<T>;

    requires !IsProperty<T>;
};

template <typename T>
concept IsReflectiveProperty = IsProperty<T> && IsReflective<typename T::value_type>;

template <typename T>
concept IsNotReflectiveProperty = IsProperty<T> && !IsReflective<typename T::value_type>;

}  // namespace checks
}  // namespace openapi
