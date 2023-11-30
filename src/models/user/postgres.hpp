#pragma once

#include <userver/storages/postgres/io/composite_types.hpp>

#include "type.hpp"
namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<models::User>
{
    static constexpr DBTypeName postgres_name = "timetable_vsu.user";
};

}  // namespace userver::storages::postgres::io
