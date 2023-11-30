#pragma once
#include <openapi/enum/pg_mapper.hpp>

#include "type.hpp"

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<::legacy::models::LessonType>
    : openapi::PgMapperFixed<::legacy::models::LessonType, "timetable_vsu",
                             "type_lesson">
{
};
}  // namespace userver::storages::postgres::io
