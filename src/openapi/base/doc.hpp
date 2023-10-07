#pragma once

#include <iostream>
#include <openapi/json/serialize/array_property.hpp>
#include <openapi/types/array_type.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/formats/yaml/value_builder.hpp>
#include <userver/utils/strong_typedef.hpp>

namespace openapi
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
}  // namespace openapi
