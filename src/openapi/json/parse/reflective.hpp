#pragma once

#include <array>
#include <stdexcept>
#include <string_view>
#include <unordered_map>
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
inline userver::formats::json::Value collect_additional_properties(
    const userver::formats::json::Value& item,
    const std::unordered_set<std::string>& used_keys)
{
    userver::formats::json::ValueBuilder additional{
        userver::formats::json::Type::kObject};
    for (auto it = item.begin(); it != item.end(); it++)
    {
        auto it_name = it.GetName();
        //если ключ не был замечен, то копируем соответствующее поле
        if (!used_keys.contains(it_name))
        {
            additional[it_name] = item[it_name];
        }
    }
    return additional.ExtractValue();
}

//парсим все поля, запоминаем те, которые не были использованы
template <typename T>
inline std::unordered_set<std::string> parse_without_additional_properties(
    const userver::formats::json::Value& item, T& result)
{
    std::unordered_set<std::string> used_keys;
    //запоминаем ключи, которые были использованы
    auto matcher_common_type = [&item, &used_keys]<typename F>(F& field) {
        constexpr auto name = traits::GetName<typename F::traits>();
        static_assert(!name.empty(), "Common field must have name");
        field = item[name.AsStringView()].template As<F>();
        used_keys.emplace(name);
    };
    // no-op, пропускаем в начале, заполним потом
    auto matcher_additional_properies_noop = [](AdditionalProperties&) {};
    auto matcher_all = userver::utils::Overloaded{
        std::move(matcher_common_type),
        std::move(matcher_additional_properies_noop)};
    boost::pfr::for_each_field(result, matcher_all);
    return used_keys;
}
//парсим оставшиеся поля в additional properties
template <typename T>
void parse_additional_properties(
    T& result, userver::formats::json::Value&& result_additional)
{
    auto matcher_additional_properies =
        [&result_additional](AdditionalProperties& field) mutable {
            field() = std::move(result_additional);
        };
    auto matcher_all_noop = []<typename F>(F&) {};
    auto matcher_all = userver::utils::Overloaded{
        std::move(matcher_all_noop), std::move(matcher_additional_properies)};
    boost::pfr::for_each_field(result, matcher_all);
}
}  // namespace timetable_vsu_backend::openapi::detail

namespace userver::formats::parse
{
template <timetable_vsu_backend::openapi::checks::IsReflective T>
T Parse(const json::Value& item, To<T>)
{
    using namespace timetable_vsu_backend::openapi;
    T result;
    constexpr checks::ReflectivePreferences<T> preferences{};

    if constexpr (preferences.additional_properties_status ==
                  checks::AdditionalPropertiesStatus::True)
    {
        auto used_keys =
            detail::parse_without_additional_properties(item, result);
        auto result_additional =
            detail::collect_additional_properties(item, used_keys);
        detail::parse_additional_properties(result,
                                            std::move(result_additional));
    }
    else
    {
        auto matcher_common_type = [&item]<typename F>(F& field) {
            constexpr auto name = traits::GetName<typename F::traits>();
            static_assert(!name.empty(), "Common field must have name");
            field = item[name.AsStringView()].template As<F>();
        };
        boost::pfr::for_each_field(result, matcher_common_type);
    }
    return {std::move(result)};
}

}  // namespace userver::formats::parse
