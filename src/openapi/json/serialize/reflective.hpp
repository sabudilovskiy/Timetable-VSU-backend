#pragma once

#include <array>
#include <boost/pfr.hpp>
#include <boost/pfr/core.hpp>
#include <openapi/base/named_traits.hpp>
#include <openapi/base/properties/object.hpp>
#include <openapi/base/properties/optional.hpp>
#include <openapi/base/reflective/checks.hpp>
#include <openapi/base/reflective/preferences.hpp>
#include <openapi/base/traits/object.hpp>
#include <stdexcept>
#include <string_view>
#include <unordered_set>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/logging/log.hpp>
#include <userver/utils/overloaded.hpp>
#include <utils/constexpr_string.hpp>

namespace openapi::detail
{
template <typename T>
requires checks::is_reflective_v<T> inline void serialize_without_additional(
    const T& item, userver::formats::json::ValueBuilder& result)
{
    auto matcher_common = [&result]<typename F>(const F& field) {
        constexpr auto name = traits::GetName(F::traits);
        static_assert(!name.empty(), "Common field must have name");
        userver::formats::json::ValueBuilder field_json{field()};
        if (!field_json.IsNull())
        {
            result.EmplaceNocheck(name.AsStringView(),
                                  field_json.ExtractValue());
        }
    };
    // noop
    auto matcher_additional_properties = [](const AdditionalProperties&) {};
    auto matcher_all = userver::utils::Overloaded{
        matcher_common, matcher_additional_properties};
    boost::pfr::for_each_field(item, std::move(matcher_all));
}

template <typename T>
requires checks::is_reflective_v<T> inline void serialize_additional(
    const T& item, userver::formats::json::ValueBuilder& result)
{
    // noop
    auto matcher_common = []<typename F>(const F&) {};
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
    auto matcher_all = userver::utils::Overloaded{
        matcher_common, matcher_additional_properties};
    boost::pfr::for_each_field(item, std::move(matcher_all));
}

}  // namespace openapi::detail

namespace userver::formats::serialize
{
template <typename T>
requires openapi::checks::is_reflective_v<T> userver::formats::json::Value
Serialize(const T& item, To<userver::formats::json::Value>)
{
    using namespace openapi;
    userver::formats::json::ValueBuilder result{
        userver::formats::json::Type::kObject};
    detail::serialize_without_additional(item, result);
    checks::ReflectivePreferences<T> prefs{};
    if constexpr (prefs.additional_properties_status ==
                  checks::AdditionalPropertiesStatus::True)
    {
        detail::serialize_additional(item, result);
    }
    return result.ExtractValue();
}

}  // namespace userver::formats::serialize
