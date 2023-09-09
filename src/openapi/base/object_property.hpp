#pragma once

#include <optional>
#include <type_traits>
#include <vector>

#include "property_base.hpp"
#include "userver/formats/json/value.hpp"

namespace timetable_vsu_backend::openapi
{
namespace checks
{
template <typename T>
concept IsReflective = requires
{
    requires std::is_class_v<T>;
    requires std::is_base_of_v<Reflective, T>;
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
