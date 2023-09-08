#pragma once

#include <boost/pfr/core.hpp>
#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>

#include "boost/pfr/tuple_size.hpp"
#include "openapi/base/object_property.hpp"
#include "openapi/base/property_base.hpp"

namespace timetable_vsu_backend::openapi
{
/* Добавьте это поле в свою структуру, чтобы её схема была с

AddditionalProperties: true */
struct AdditionalProperties
{
    userver::formats::json::Value value_;
    userver::formats::json::Value& operator()() &
    {
        return value_;
    }
    const userver::formats::json::Value& operator()() const&
    {
        return value_;
    }
    userver::formats::json::Value operator()() &&
    {
        return std::move(value_);
    }
};

namespace checks
{
enum struct AdditionalPropertiesStatus
{
    True,
    False,
    Error
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

template <IsReflective T, size_t... I>
consteval void resolve_tuple(ReflectivePreferencesHelper& helper,
                             std::integer_sequence<size_t, I...>)
{
    using Tuple =
        std::tuple<std::remove_cvref_t<boost::pfr::tuple_element_t<I, T>>...>;
    resolve_fields(helper, std::type_identity<Tuple>{});
}

template <IsReflective T>
consteval ReflectivePreferencesHelper resolve_helper()
{
    ReflectivePreferencesHelper helper{};
    constexpr size_t size = boost::pfr::tuple_size_v<T>;
    constexpr auto indexes = std::make_integer_sequence<size_t, size>{};
    resolve_tuple<T>(helper, indexes);
    return helper;
}

template <IsReflective T>
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
        return AdditionalPropertiesStatus::Error;
    }
}
}  // namespace impl
template <IsReflective T>
struct ReflectivePreferences
{
    static constexpr AdditionalPropertiesStatus additional_properties_status =
        impl::resolve_additional_properties_status<T>();
};
}  // namespace checks

struct Test
{
    using Reflective = timetable_vsu_backend::openapi::Yes;
    AdditionalProperties other;
    AdditionalProperties other_2;
};

static_assert(checks::IsReflective<Test>);
static_assert(
    checks::ReflectivePreferences<Test>::additional_properties_status ==
    checks::AdditionalPropertiesStatus::Error);

}  // namespace timetable_vsu_backend::openapi
