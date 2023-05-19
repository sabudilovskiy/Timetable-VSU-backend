#pragma once
#include <userver/formats/json/value.hpp>

#include "type.hpp"

namespace timetable_vsu_backend::models
{
userver::formats::json::Value Serialize(
    const UserType& value,
    userver::formats::serialize::To<userver::formats::json::Value>);
std::string Serialize(const UserType& value,
                      userver::formats::serialize::To<std::string>);
}  // namespace timetable_vsu_backend::models
