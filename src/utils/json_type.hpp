#pragma once

#include <string_view>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json_fwd.hpp>

namespace timetable_vsu_backend::utils
{
std::string_view GetType(const userver::formats::json::Value& value);
}
