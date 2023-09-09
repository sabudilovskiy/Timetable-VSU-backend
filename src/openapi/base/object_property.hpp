#pragma once

#include <optional>
#include <type_traits>
#include <userver/formats/json/value.hpp>
#include <vector>

#include "property_base.hpp"

namespace timetable_vsu_backend::openapi
{
namespace checks
{
template <typename T>
concept IsReflective = requires
{
    requires std::is_class_v<T>;
    typename T::Reflective;
    requires std::is_same_v<typename T::Reflective, Yes>;
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
