#pragma once
#include <openapi/enum/pg_mapper.hpp>
#include <userver/storages/postgres/io/enum_types.hpp>
#include <userver/storages/postgres/io/type_mapping.hpp>
#include <userver/utils/trivial_map.hpp>

#include "type.hpp"

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<legacy::models::UserType>
    : openapi::PgMapperFixed<legacy::models::UserType, "timetable_vsu", "user_type">
{
};
}  // namespace userver::storages::postgres::io
