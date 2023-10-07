#pragma once
#include <userver/storages/postgres/io/enum_types.hpp>
#include <userver/storages/postgres/io/type_mapping.hpp>
#include <userver/utils/trivial_map.hpp>

#include "type.hpp"

namespace userver::storages::postgres::io
{
using ::models::Day;
template <>
struct CppToUserPg<Day> : EnumMappingBase<Day>
{
    static constexpr userver::storages::postgres::DBTypeName postgres_name =
        "timetable_vsu.day";
    static constexpr userver::utils::TrivialBiMap enumerators =
        [](auto selector) {
            return selector()
                .Case("monday", Day::kMonday)
                .Case("tuesday", Day::kTuesday)
                .Case("wednesday", Day::kWednesday)
                .Case("thursday", Day::kThursday)
                .Case("friday", Day::kFriday)
                .Case("saturday", Day::kSaturday);
        };
};
}  // namespace userver::storages::postgres::io
