#pragma once
#include <openapi/enum/pg_mapper.hpp>

#include "type.hpp"

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<::legacy::models::LessonWeekType>
    : openapi::PgMapper<::legacy::models::LessonWeekType,
                        "timetable_vsu.type_of_week">
{
};
}  // namespace userver::storages::postgres::io
