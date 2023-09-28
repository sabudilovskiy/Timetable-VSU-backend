#pragma once

#include "body_property.hpp"

namespace timetable_vsu_backend::openapi::http
{
template <typename T, typename... Options>
using Body = BodyProperty<T, EmptyTraits>;
}
