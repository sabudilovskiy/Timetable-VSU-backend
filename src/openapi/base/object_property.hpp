#pragma once

#include <type_traits>

#include "property_base.hpp"

namespace timetable_vsu_backend::openapi
{
namespace checks
{
template <typename T>
concept IsReflective = requires
{
    requires std::is_class_v<T>;
    requires std::is_aggregate_v<T>;
};
}  // namespace checks

template <checks::IsReflective T, typename Traits = EmptyTraits>
struct ObjectProperty : public PropertyBase<T, Traits>
{
};

template <checks::IsReflective T, typename Traits>
struct Property<T, Traits> : public ObjectProperty<T, Traits>
{
};

}  // namespace timetable_vsu_backend::openapi
