#pragma once
#include <fmt/core.h>

#include <boost/uuid/uuid_io.hpp>
#include <userver/formats/json.hpp>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/logging/log.hpp>

#include "type.hpp"

namespace legacy::models
{
inline userver::formats::json::Value Serialize(
    const AuthToken& token,
    userver::formats::serialize::To<userver::formats::json::Value>)
{
    userver::formats::json::ValueBuilder json;
    json["token"] = boost::uuids::to_string(token.id);
    return json.ExtractValue();
}
}  // namespace legacy::models
