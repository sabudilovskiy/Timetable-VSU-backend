#pragma once

#include <array>
#include <boost/pfr.hpp>
#include <boost/pfr/core.hpp>
#include <exception>
#include <openapi/base/named_traits.hpp>
#include <openapi/base/property_base.hpp>
#include <optional>
#include <stdexcept>
#include <string_view>
#include <unordered_map>
#include <userver/formats/json/value.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/utils/overloaded.hpp>
#include <utils/constexpr_string.hpp>

namespace userver::formats::parse
{
template <typename T>
requires openapi::IsProperty<T> T Parse(const json::Value& item, To<T>)
{
    return T{item.As<typename T::value_type>()};
}
}  // namespace userver::formats::parse
