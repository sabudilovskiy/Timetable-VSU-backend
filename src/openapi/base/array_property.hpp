#pragma once

#include <optional>
#include <vector>

#include "property_base.hpp"

namespace timetable_vsu_backend::openapi
{
template <typename T, typename Traits = EmptyTraits>
struct ArrayProperty : public PropertyBase<std::vector<T>, Traits>
{
};

template <typename T, typename Traits>
struct Property<std::vector<T>, Traits> : public ArrayProperty<T, Traits>
{
};

}  // namespace timetable_vsu_backend::openapi
