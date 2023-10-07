#pragma once
#include <string_view>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json_fwd.hpp>

#include "type.hpp"

namespace models
{
LessonType Parse(std::string_view str, userver::formats::parse::To<LessonType>);
LessonType Parse(const userver::formats::json::Value& value,
                 userver::formats::parse::To<LessonType>);
}  // namespace models
