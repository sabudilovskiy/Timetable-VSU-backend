#pragma once

#include <openapi/base/named_traits.hpp>
#include <openapi/base/properties/datetime.hpp>
#include <openapi/base/traits/string.hpp>
#include <regex>
#include <stdexcept>
#include <string_view>
#include <unordered_map>
#include <userver/formats/json/value.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/logging/log.hpp>
#include <userver/utils/datetime.hpp>
#include <utils/constexpr_string.hpp>

namespace userver::formats::parse
{
template <auto Traits>
::openapi::DateTimeProperty<Traits> Parse(
    const json::Value& item, To<::openapi::DateTimeProperty<Traits>>)
{
    using namespace openapi;

    auto result = item.As<std::string>();
    return {userver::utils::datetime::GuessLocalTimezoneStringtime(result)};
}

}  // namespace userver::formats::parse
