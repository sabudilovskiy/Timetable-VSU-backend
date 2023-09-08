#pragma once

#include <optional>
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
    typename T::Reflective;
    requires std::same_as<typename T::Reflective, Yes>;
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
