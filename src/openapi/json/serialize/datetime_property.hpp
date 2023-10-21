#pragma once

#include <openapi/base/properties/datetime.hpp>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/utils/datetime.hpp>

namespace openapi
{
template <typename Traits>
userver::formats::json::Value Serialize(
    const DateTimeProperty<Traits>& item,
    userver::formats::serialize::To<userver::formats::json::Value>)
{
    using namespace openapi;

    auto& value = item();

    return userver::formats::json::ValueBuilder{
        userver::utils::datetime::Timestring(value)}
        .ExtractValue();
}

}  // namespace openapi
