#pragma once
#include <openapi/enum/pg_mapper.hpp>

#include "type.hpp"

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<::legacy::models::Subgroup>
    : openapi::PgMapperFixed<::legacy::models::Subgroup, "timetable_vsu", "subgroup">
{
};

}  // namespace userver::storages::postgres::io
