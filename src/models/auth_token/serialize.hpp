#pragma once
#include <fmt/core.h>
#include <userver/formats/json.hpp>
#include "userver/formats/json/value.hpp"
#include "type.hpp"
#include "userver/formats/json/value_builder.hpp"
#include "userver/logging/log.hpp"
#include <boost/uuid/uuid_io.hpp>

namespace timetable_vsu_backend::models{
    inline userver::formats::json::Value Serialize(const AuthToken& token, userver::formats::serialize::To<userver::formats::json::Value>){
        userver::formats::json::ValueBuilder json;
        json["token"] = boost::uuids::to_string(token.id);
        return json.ExtractValue();
    }
}