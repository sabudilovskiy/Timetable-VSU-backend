#pragma once
#include <openapi/enum/pg_mapper.hpp>

#include "type.hpp"

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<::legacy::models::EducationType>
    : openapi::PgMapper<::legacy::models::EducationType,
                        "timetable_vsu.grouptype">
{
};
}  // namespace userver::storages::postgres::io
