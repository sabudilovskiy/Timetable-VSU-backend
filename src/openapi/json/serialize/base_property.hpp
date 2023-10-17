#pragma once

#include <openapi/base/property_base.hpp>
#include <string_view>
#include <unordered_map>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/utils/overloaded.hpp>
#include <utils/constexpr_string.hpp>

namespace openapi
{
template <typename T, typename Traits>
userver::formats::json::Value Serialize(
    const PropertyBase<T, Traits>& value,
    userver::formats::serialize::To<userver::formats::json::Value> s)
{
    return Serialize(value(), s);
}
}  // namespace openapi
