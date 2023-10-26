#pragma once
#include <openapi/enum/pg_mapper.hpp>
#include <userver/storages/postgres/io/pg_types.hpp>

#include "type.hpp"

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<::models::LessonFilter>
{
    static constexpr DBTypeName postgres_name =
        "timetable_vsu.lesson_filter_v2";
};

}  // namespace userver::storages::postgres::io
