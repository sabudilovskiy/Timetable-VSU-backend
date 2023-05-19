#pragma once
#include <string_view>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json_fwd.hpp>

#include "type.hpp"

namespace timetable_vsu_backend::models
{
LessonWeekType Parse(std::string_view str,
                     userver::formats::parse::To<LessonWeekType>);
LessonWeekType Parse(const userver::formats::json::Value& value,
                     userver::formats::parse::To<LessonWeekType>);
}  // namespace timetable_vsu_backend::models
