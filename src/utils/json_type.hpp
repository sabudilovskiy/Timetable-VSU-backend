#pragma once

#include <string_view>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json_fwd.hpp>

namespace utils
{
std::string_view GetType(const userver::formats::json::Value& value);
}
