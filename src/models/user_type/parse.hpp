#pragma once
#include "type.hpp"
#include "userver/formats/json/value.hpp"
#include <string_view>
#include <userver/formats/json_fwd.hpp>

namespace timetable_vsu_backend::models{
    UserType Parse(std::string_view str,
                 userver::formats::parse::To<UserType>);
    UserType Parse(const userver::formats::json::Value& value, userver::formats::parse::To<UserType>);
}