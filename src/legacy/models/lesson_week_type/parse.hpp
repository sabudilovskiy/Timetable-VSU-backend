#pragma once
#include <string_view>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json_fwd.hpp>

#include "type.hpp"

namespace legacy::models
{
LessonWeekType Parse(std::string_view str,
                     userver::formats::parse::To<LessonWeekType>);
LessonWeekType Parse(const userver::formats::json::Value& value,
                     userver::formats::parse::To<LessonWeekType>);
}  // namespace legacy::models
