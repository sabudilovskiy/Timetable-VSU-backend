#pragma once

#include <array>
#include <boost/pfr.hpp>
#include <boost/pfr/core.hpp>
#include <exception>
#include <openapi/base/named_traits.hpp>
#include <openapi/base/properties/optional.hpp>
#include <openapi/base/traits/optional.hpp>
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
template <typename T, typename Traits>
::openapi::OptionalProperty<T, Traits> Parse(
    const json::Value& item, To<::openapi::OptionalProperty<T, Traits>>)
{
    using namespace openapi::traits;
    constexpr OptionalHelperTraits<Traits> traits;
    if (item.IsMissing())
    {
        return {std::nullopt};
    }
    try
    {
        auto result = item.As<T>();
        return {std::move(result)};
    }
    catch (std::exception& exc)
    {
        if constexpr (traits.null_on_failure.value_or(false))
        {
            return {std::nullopt};
        }
        throw;
    }
}
}  // namespace userver::formats::parse
