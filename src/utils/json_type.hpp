#include <string_view>
#pragma once
#include <userver/formats/json_fwd.hpp>
#include "userver/formats/json/value.hpp"

namespace timetable_vsu_backend::utils {
    std::string_view GetType(const userver::formats::json::Value& value);
}   