#pragma once

#include <array>
#include <boost/pfr.hpp>
#include <boost/pfr/core.hpp>
#include <stdexcept>
#include <string_view>
#include <unordered_map>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/logging/log.hpp>
#include <userver/utils/overloaded.hpp>

#include "openapi/base/named_traits.hpp"
#include "openapi/base/object_property.hpp"
#include "openapi/base/object_traits.hpp"
#include "openapi/base/optional_property.hpp"
#include "utils/constexpr_string.hpp"

namespace timetable_vsu_backend::openapi
{
template <typename T, typename Traits>
userver::formats::json::Value Serialize(
    const timetable_vsu_backend::openapi::ObjectProperty<T, Traits>& item,
    userver::formats::serialize::To<userver::formats::json::Value>)
{
    return userver::formats::json::ValueBuilder(item()).ExtractValue();
}

}  // namespace timetable_vsu_backend::openapi
