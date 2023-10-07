#pragma once
#include <userver/storages/postgres/io/enum_types.hpp>
#include <userver/storages/postgres/io/type_mapping.hpp>
#include <userver/utils/trivial_map.hpp>

#include "type.hpp"

namespace userver::storages::postgres::io
{
using ::models::LessonType;
template <>
struct CppToUserPg<LessonType> : EnumMappingBase<LessonType>
{
    static constexpr userver::storages::postgres::DBTypeName postgres_name =
        "timetable_vsu.type_lesson";
    static constexpr userver::utils::TrivialBiMap enumerators =
        [](auto selector) {
            return selector()
                .Case("labaratory", LessonType::kLabaratory)
                .Case("lection", LessonType::kLection)
                .Case("practice", LessonType::kPractice);
        };
};
}  // namespace userver::storages::postgres::io
