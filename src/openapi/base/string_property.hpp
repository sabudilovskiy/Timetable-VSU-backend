#pragma once

#include <string>

#include "property_base.hpp"

namespace timetable_vsu_backend::openapi
{
template <typename Traits = EmptyTraits>
struct StringProperty : public PropertyBase<std::string, Traits>
{
};

template <typename Traits>
struct Property<std::string, Traits> : public StringProperty<Traits>
{
};

}  // namespace timetable_vsu_backend::openapi
