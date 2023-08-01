#pragma once

#include <array>
#include <stdexcept>
#include <string_view>
#include <unordered_map>
#include <userver/utils/overloaded.hpp>

#include "boost/pfr.hpp"
#include "boost/pfr/core.hpp"
#include "openapi/base/extended_object_property.hpp"
#include "openapi/base/named_traits.hpp"
#include "openapi/base/object_property.hpp"
#include "openapi/base/object_traits.hpp"
#include "userver/formats/json/value.hpp"
#include "userver/formats/parse/to.hpp"
#include "userver/logging/log.hpp"
#include "utils/constexpr_string.hpp"

namespace userver::formats::parse
{
template <typename T, typename Traits>
timetable_vsu_backend::openapi::ObjectProperty<T, Traits> Parse(
    const json::Value& item,
    To<timetable_vsu_backend::openapi::ObjectProperty<T, Traits>>)
{
    using namespace timetable_vsu_backend::openapi;



    // constexpr traits::ObjectHelperTraits<Traits> traits;
    T result;
    auto matcher_common_type = [&item]<typename F>(F& field) {
        constexpr auto name = timetable_vsu_backend::openapi::traits::GetName<
            typename F::traits>();
        static_assert(!name.empty(), "Common field must have name");
        field = item[name.AsStringView()].template As<F>();
    };
    auto matcher_object = [&item]<typename F, typename FTraits>(
                              ObjectProperty<F, FTraits>& field) {
        using R = ObjectProperty<F, FTraits>;
        if constexpr (traits::GetUseRoot<FTraits>().value_or(false))
        {
            field = item.As<R>();
        }
        else
        {
            constexpr auto name =
                timetable_vsu_backend::openapi::traits::GetName<FTraits>();
            static_assert(!name.empty(),
                          "Object field without use_root must have name");
            field = item[name.AsStringView()].template As<R>();
        }
    };
    auto matcher_extended_object =
        [&item]<typename F, typename FTraits>(
            ExtendedObjectProperty<F, FTraits>& field) {
            using R = ExtendedObjectProperty<F, FTraits>;
            if constexpr (traits::GetUseRoot<FTraits>().value_or(false))
            {
                field = item.As<R>();
            }
            else
            {
                constexpr auto name =
                    timetable_vsu_backend::openapi::traits::GetName<FTraits>();
                static_assert(!name.empty(),
                              "Object field without use_root must have name");
                field = item[name.AsStringView()].template As<R>();
            }
        };
    auto matcher = utils::Overloaded{std::move(matcher_common_type),
                                     std::move(matcher_object),
                                     std::move(matcher_extended_object)};

    boost::pfr::for_each_field(result, matcher);

    return {std::move(result)};
}

}  // namespace userver::formats::parse
