#pragma once

#include <array>
#include <exception>
#include <optional>
#include <stdexcept>
#include <string_view>
#include <unordered_map>
#include <userver/utils/overloaded.hpp>

#include "boost/pfr.hpp"
#include "boost/pfr/core.hpp"
#include "openapi/base/named_traits.hpp"
#include "openapi/base/optional_property.hpp"
#include "openapi/base/optional_traits.hpp"
#include "userver/formats/json/value.hpp"
#include "userver/formats/parse/to.hpp"
#include "utils/constexpr_string.hpp"

namespace userver::formats::parse
{
template <typename T, typename Traits>
timetable_vsu_backend::openapi::OptionalProperty<T, Traits> Parse(
    const json::Value& item,
    To<timetable_vsu_backend::openapi::OptionalProperty<T, Traits>>)
{
    using namespace timetable_vsu_backend::openapi::traits;
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
