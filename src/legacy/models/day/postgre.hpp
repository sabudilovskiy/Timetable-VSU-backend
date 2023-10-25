#pragma once
#include <openapi/enum/pg_mapper.hpp>

#include "type.hpp"

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<::legacy::models::Day>
    : openapi::PgMapper<::legacy::models::Day, "timetable_vsu.day">
{
};
}  // namespace userver::storages::postgres::io
