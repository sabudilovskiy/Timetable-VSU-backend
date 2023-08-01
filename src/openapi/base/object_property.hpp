#pragma once

#include <optional>
#include <vector>

#include "property_base.hpp"

namespace timetable_vsu_backend::openapi
{
template <checks::IsReflective T, typename Traits = EmptyTraits>
struct ObjectProperty : public PropertyBase<T, Traits>
{
};

template <checks::IsReflective T, typename Traits>
struct Property<T, Traits> : public ObjectProperty<T, Traits>
{
};

}  // namespace timetable_vsu_backend::openapi
