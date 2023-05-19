#pragma once
#include <string_view>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json_fwd.hpp>

#include "type.hpp"

namespace timetable_vsu_backend::models {
SubString Parse(const std::string& str, userver::formats::parse::To<SubString>);
SubString Parse(const userver::formats::json::Value& value,
                userver::formats::parse::To<SubString>);
}  // namespace timetable_vsu_backend::models
