#pragma once
#include <type_traits>

#include "property_base.hpp"

namespace timetable_vsu_backend::openapi
{
template <typename T>
concept IsReflective = requires
{
    requires std::is_class_v<T>;
    typename T::Enable;
    requires std::is_same_v<typename T::Enable, Yes>;
};

template <IsReflective T, typename Traits = EmptyTraits>
struct ReflectiveProperty : public PropertyBase<T, Traits>
{
};

template <IsReflective T, typename Traits>
struct Property<T, Traits> : public ReflectiveProperty<T, Traits>
{
};

template <IsReflective T, typename Traits = EmptyTraits>
struct OptionalReflectiveProperty
    : public PropertyBase<std::optional<T>, Traits>
{
};

template <IsReflective T, typename Traits>
struct Property<std::optional<T>, Traits>
    : public OptionalReflectiveProperty<T, Traits>
{
};

}  // namespace timetable_vsu_backend::openapi
