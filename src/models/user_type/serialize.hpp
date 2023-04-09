#pragma once
#include "type.hpp"
#include "userver/formats/json/value.hpp"

namespace timetable_vsu_backend::models {
userver::formats::json::Value Serialize(
    const UserType& value,
    userver::formats::serialize::To<userver::formats::json::Value>);
std::string Serialize(const UserType& value,
                      userver::formats::serialize::To<std::string>);
}  // namespace timetable_vsu_backend::models