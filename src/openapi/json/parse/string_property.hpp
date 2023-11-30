#pragma once

#include <openapi/base/named_traits.hpp>
#include <openapi/base/properties/string.hpp>
#include <openapi/base/traits/string.hpp>
#include <regex>
#include <stdexcept>
#include <string_view>
#include <unordered_map>
#include <userver/formats/json/value.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/logging/log.hpp>
#include <utils/constexpr_string.hpp>

namespace userver::formats::parse
{
template <auto Traits>
::openapi::StringProperty<Traits> Parse(const json::Value& item,
                                        To<::openapi::StringProperty<Traits>>)
{
    using namespace openapi;

    constexpr traits::StringHelperTraits<Traits> traits;

    auto result = item.As<std::string>();

    if constexpr (!traits.pattern.empty())
    {
        std::regex reg(traits.pattern.data());
        if (!std::regex_match(result, reg))
        {
            throw std::runtime_error(
                fmt::format("Field doesnt satisfy pattern: {}, value: {}",
                            traits.pattern, result));
        }
    }
    return {std::move(result)};
}

}  // namespace userver::formats::parse
