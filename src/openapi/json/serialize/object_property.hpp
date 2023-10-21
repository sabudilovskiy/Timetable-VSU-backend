#pragma once

#include <array>
#include <boost/pfr.hpp>
#include <boost/pfr/core.hpp>
#include <openapi/base/named_traits.hpp>
#include <openapi/base/properties/object.hpp>
#include <openapi/base/properties/optional.hpp>
#include <openapi/base/traits/object.hpp>
#include <stdexcept>
#include <string_view>
#include <unordered_map>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/logging/log.hpp>
#include <userver/utils/overloaded.hpp>
#include <utils/constexpr_string.hpp>

namespace openapi
{
template <typename T, typename Traits>
userver::formats::json::Value Serialize(
    const ::openapi::ObjectProperty<T, Traits>& item,
    userver::formats::serialize::To<userver::formats::json::Value>)
{
    return userver::formats::json::ValueBuilder(item()).ExtractValue();
}

}  // namespace openapi
