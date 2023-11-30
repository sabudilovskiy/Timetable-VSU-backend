#pragma once
#include <string_view>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json_fwd.hpp>

#include "type.hpp"

namespace legacy::models
{
TimeString Parse(const std::string& str,
                 userver::formats::parse::To<TimeString>);
TimeString Parse(const userver::formats::json::Value& value,
                 userver::formats::parse::To<TimeString>);
}  // namespace legacy::models
