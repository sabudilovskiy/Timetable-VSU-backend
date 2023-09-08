#pragma once

#include <array>
#include <stdexcept>
#include <string_view>
#include <unordered_set>
#include <userver/utils/overloaded.hpp>

#include "boost/pfr.hpp"
#include "boost/pfr/core.hpp"
#include "openapi/base/named_traits.hpp"
#include "openapi/base/object_property.hpp"
#include "openapi/base/object_traits.hpp"
#include "openapi/base/optional_property.hpp"
#include "openapi/base/reflective_preferences.hpp"
#include "userver/formats/json/value.hpp"
#include "userver/formats/json/value_builder.hpp"
#include "userver/formats/parse/to.hpp"
#include "userver/logging/log.hpp"
#include "utils/constexpr_string.hpp"

namespace timetable_vsu_backend::openapi::detail
{
template <checks::IsReflective T>
inline void serialize_without_additional(
    const T& item, userver::formats::json::ValueBuilder& result)
{
    auto matcher_common = [&result]<typename F>(const F& field) {
        constexpr auto name = traits::GetName<typename F::traits>();
        static_assert(!name.empty(), "Common field must have name");
        result[name] = field();
    };
    // noop
    auto matcher_additional_properties = [](const AdditionalProperties&) {};
    auto matcher_all = userver::utils::Overloaded(
        std::move(matcher_common), std::move(matcher_additional_properties));
    boost::pfr::for_each_field(item, std::move(matcher_all));
}

template <checks::IsReflective T>
inline void serialize_additional(const T& item,
                                 std::unordered_set<std::string> used,
                                 userver::formats::json::ValueBuilder& result)
{
    // noop
    auto matcher_common = [&result, &used]<typename F>(const F&) {};
    auto matcher_additional_properties =
        [&result](const AdditionalProperties& field) {
            for (auto it = field().begin(); it != field().end(); ++it)
            {
                auto name = it.GetName();
                if (!result.HasMember(name))
                {
                    result[name] = field()[name];
                }
            }
        };
    auto matcher_all = userver::utils::Overloaded(
        std::move(matcher_common), std::move(matcher_additional_properties));
    boost::pfr::for_each_field(item, std::move(matcher_all));
}

}  // namespace timetable_vsu_backend::openapi::detail

namespace timetable_vsu_backend::openapi
{
template <checks::IsReflective T>
userver::formats::json::Value Serialize(
    const T& item,
    userver::formats::serialize::To<userver::formats::json::Value>)
{
    userver::formats::json::ValueBuilder result{
        userver::formats::json::Type::kObject};
    auto used = detail::serialize_without_additional(item, result);

    return userver::formats::json::ValueBuilder(item()).ExtractValue();
}

}  // namespace timetable_vsu_backend::openapi
