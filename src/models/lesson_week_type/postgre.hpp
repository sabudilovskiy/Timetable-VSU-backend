#pragma once
#include <userver/storages/postgres/io/enum_types.hpp>
#include <userver/storages/postgres/io/type_mapping.hpp>
#include <userver/utils/trivial_map.hpp>

#include "type.hpp"

namespace userver::storages::postgres::io
{
using timetable_vsu_backend::models::LessonWeekType;
template <>
struct CppToUserPg<LessonWeekType> : EnumMappingBase<LessonWeekType>
{
    static constexpr userver::storages::postgres::DBTypeName postgres_name =
        "timetable_vsu.type_of_week";
    static constexpr userver::utils::TrivialBiMap enumerators =
        [](auto selector) {
            return selector()
                .Case("all", LessonWeekType::kAll)
                .Case("even", LessonWeekType::kEven)
                .Case("odd", LessonWeekType::kOdd);
        };
};
}  // namespace userver::storages::postgres::io
