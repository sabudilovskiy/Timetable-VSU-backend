#pragma once

#include <openapi/base/property_base.hpp>

namespace timetable_vsu_backend::openapi::http
{
template <typename T, typename Traits>
struct CookieProperty : PropertyBase<T, Traits>
{
};
};  // namespace timetable_vsu_backend::openapi::http
