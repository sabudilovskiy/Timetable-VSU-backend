#pragma once
#include "property_base.hpp"

namespace timetable_vsu_backend::openapi
{
template <typename T, typename Traits = EmptyTraits>
struct OptionalProperty : public PropertyBase<std::optional<T>, Traits>
{
};

template <typename T, typename Traits>
struct Property<std::optional<T>, Traits> : public OptionalProperty<T, Traits>
{
};

}  // namespace timetable_vsu_backend::openapi
