#pragma once

#include <openapi/enum/string.hpp>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json/value_builder.hpp>

namespace userver::formats::serialize
{
template <typename T>
requires ::openapi::HasIntrospector<T> json::Value Serialize(
    const T& item, To<userver::formats::json::Value>)
{
    auto string = std::string(::openapi::to_string_view(item));
    return userver::formats::json::ValueBuilder{string}.ExtractValue();
}

}  // namespace userver::formats::serialize
