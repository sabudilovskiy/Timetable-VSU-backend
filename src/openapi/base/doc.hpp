#pragma once

#include <iostream>
#include <userver/formats/yaml/value_builder.hpp>

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
