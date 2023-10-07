#pragma once
#include <userver/formats/json/value.hpp>

#include "type.hpp"

namespace models
{
userver::formats::json::Value Serialize(
    const LessonWeekType& value,
    userver::formats::serialize::To<userver::formats::json::Value>);
std::string Serialize(const LessonWeekType& value,
                      userver::formats::serialize::To<std::string>);
}  // namespace models
