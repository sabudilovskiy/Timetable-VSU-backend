#pragma once

#include <iostream>
#include <userver/formats/json/value_builder.hpp>
#include <userver/formats/yaml/value_builder.hpp>
#include <userver/utils/strong_typedef.hpp>

#include "openapi/json/serialize/array_property.hpp"
#include "openapi/types/array_type.hpp"

namespace timetable_vsu_backend::openapi
{
// OpenApi описание типа
struct Doc
{
    userver::formats::yaml::ValueBuilder value_;
    auto& operator()()
    {
        return value_;
    }
    auto& operator()() const
    {
        return value_;
    }
};
}  // namespace timetable_vsu_backend::openapi
