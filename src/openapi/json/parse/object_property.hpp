#pragma once

#include <array>
#include <boost/pfr.hpp>
#include <boost/pfr/core.hpp>
#include <openapi/base/named_traits.hpp>
#include <openapi/base/object_property.hpp>
#include <openapi/base/object_traits.hpp>
#include <openapi/base/optional_property.hpp>
#include <stdexcept>
#include <string_view>
#include <unordered_map>
#include <userver/formats/json/value.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/logging/log.hpp>
#include <userver/utils/overloaded.hpp>
#include <utils/constexpr_string.hpp>

namespace userver::formats::parse
{
template <typename T, typename Traits>
::openapi::ObjectProperty<T, Traits> Parse(
    const json::Value& item,
    To<::openapi::ObjectProperty<T, Traits>>)
{
    T result;
    return {item.As<T>()};
}

}  // namespace userver::formats::parse
