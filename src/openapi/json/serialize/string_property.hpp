#pragma once

#include <openapi/base/named_traits.hpp>
#include <openapi/base/properties/string.hpp>
#include <openapi/base/traits/string.hpp>
#include <regex>
#include <stdexcept>
#include <string_view>
#include <unordered_map>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/logging/log.hpp>
#include <utils/constexpr_string.hpp>

namespace openapi
{
template <auto Traits>
userver::formats::json::Value Serialize(
    const StringProperty<Traits>& item,
    userver::formats::serialize::To<userver::formats::json::Value>)
{
    using namespace openapi;

    constexpr traits::StringHelperTraits<Traits> traits;

    auto& value = item();

    if constexpr (!traits.pattern.empty())
    {
        std::regex reg(traits.pattern.data());
        if (!std::regex_match(value, reg))
        {
            throw std::runtime_error(
                fmt::format("Field doesnt satisfy pattern: {}, value: {}",
                            traits.pattern, value));
        }
    }
    return userver::formats::json::ValueBuilder{value}.ExtractValue();
}

}  // namespace openapi
