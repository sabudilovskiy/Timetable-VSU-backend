#pragma once
#include <userver/formats/json/value.hpp>

#include "type.hpp"

namespace legacy::models
{
userver::formats::json::Value Serialize(
    const Subgroup& value,
    userver::formats::serialize::To<userver::formats::json::Value>);
std::string Serialize(const Subgroup& value,
                      userver::formats::serialize::To<std::string>);
}  // namespace legacy::models
