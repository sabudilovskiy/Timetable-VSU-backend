#pragma once

#include <openapi/base/enum/string.hpp>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/utils/datetime.hpp>

namespace openapi
{
template <typename T>
userver::formats::json::Value Serialize(
    const T& item,
    userver::formats::serialize::To<
        userver::formats::json::Value>) requires HasIntrospector<T>
{
    std::string str = openapi::to_string_view(item);
    return userver::formats::json::ValueBuilder{str}.ExtractValue();
}

}  // namespace openapi
