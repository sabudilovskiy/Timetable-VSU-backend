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
#include <userver/formats/json/value_builder.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/utils/overloaded.hpp>
#include <utils/constexpr_string.hpp>

namespace openapi
{
template <typename T, auto Traits>
userver::formats::json::Value Serialize(
    const OptionalProperty<T, Traits>& value,
    userver::formats::serialize::To<userver::formats::json::Value>)
{
    using namespace userver::formats::json;
    constexpr traits::OptionalHelperTraits<Traits> traits;
    auto& item = value();
    if (!item)
    {
        return ValueBuilder{Type::kNull}.ExtractValue();
    }
    try
    {
        return ValueBuilder{item}.ExtractValue();
    }
    catch (std::exception& exc)
    {
        if constexpr (traits.null_on_failure.value_or(false))
        {
            return ValueBuilder{Type::kNull}.ExtractValue();
        }
        throw;
    }
}
}  // namespace openapi
