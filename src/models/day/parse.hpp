#pragma once
#include <string_view>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json_fwd.hpp>

#include "type.hpp"

namespace timetable_vsu_backend::models
{
Day Parse(std::string_view str, userver::formats::parse::To<Day>);
Day Parse(const userver::formats::json::Value& value,
          userver::formats::parse::To<Day>);
}  // namespace timetable_vsu_backend::models
