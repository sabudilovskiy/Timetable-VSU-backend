#pragma once

#include <gtest/gtest.h>

#include <boost/pfr/core.hpp>
#include <boost/pfr/tuple_size.hpp>
#include <compare>
#include <cstddef>
#include <openapi/base/object_property.hpp>
#include <openapi/base/property_base.hpp>
#include <openapi/base/reflective_checks.hpp>
#include <tuple>
#include <type_traits>
#include <userver/formats/json/value.hpp>
#include <utility>
#include <utils/compilers_macros.hpp>

namespace openapi
{
/* Добавьте это поле в свою структуру, чтобы её схема была с
AddditionalProperties: true */

struct AdditionalProperties : PropertyBase<userver::formats::json::Value>
{
    std::partial_ordering operator<=>(const AdditionalProperties& rhs) const
    {
        return *this <=> rhs.value;
    }
    std::partial_ordering operator<=>(
        const userver::formats::json::Value& rhs) const
    {
        auto& lhs = *this;
        if (lhs.value == rhs)
            return std::partial_ordering::equivalent;
        return std::partial_ordering::unordered;
    }
    bool operator==(const AdditionalProperties& rhs) const = default;
};

namespace checks
{
enum struct AdditionalPropertiesStatus
{
    True,
    False
};
struct ReflectivePreferencesHelper
{
    size_t counter_additional_properties = 0;
};
namespace impl
{
template <typename T>
consteval void apply(ReflectivePreferencesHelper&)
{
}
template <>
consteval void apply<AdditionalProperties>(ReflectivePreferencesHelper& helper)
{
    helper.counter_additional_properties++;
}

template <typename... Field>
consteval void resolve_fields(ReflectivePreferencesHelper& helper,
                              std::type_identity<std::tuple<Field...>>)
{
    (apply<Field>(helper), ...);
}

template <typename T, size_t... I>
requires checks::is_reflective_v<T> consteval void resolve_tuple(
    ReflectivePreferencesHelper& helper, std::integer_sequence<size_t, I...>)
{
    using Tuple =
        std::tuple<std::remove_cvref_t<boost::pfr::tuple_element_t<I, T>>...>;
    resolve_fields(helper, std::type_identity<Tuple>{});
}

template <typename T>
requires checks::is_reflective_v<T> consteval ReflectivePreferencesHelper
resolve_helper()
{
    ReflectivePreferencesHelper helper{};
    constexpr size_t size = boost::pfr::tuple_size_v<T>;
    constexpr auto indexes = std::make_integer_sequence<size_t, size>{};
    resolve_tuple<T>(helper, indexes);
    return helper;
}

template <typename T>
requires checks::is_reflective_v<T>
    AdditionalPropertiesStatus consteval resolve_additional_properties_status()
{
    constexpr ReflectivePreferencesHelper helper = resolve_helper<T>();
    if constexpr (helper.counter_additional_properties == 0)
    {
        return AdditionalPropertiesStatus::False;
    }
    else if constexpr (helper.counter_additional_properties == 1)
    {
        return AdditionalPropertiesStatus::True;
    }
    else
    {
        STATIC_ASSERT_FALSE("You use more one AdditionalProperties");
    }
}
}  // namespace impl
template <typename T>
requires checks::is_reflective_v<T> struct ReflectivePreferences
{
    static constexpr AdditionalPropertiesStatus additional_properties_status =
        impl::resolve_additional_properties_status<T>();
};
}  // namespace checks

}  // namespace openapi
