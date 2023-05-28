#pragma once
#include <userver/storages/postgres/query.hpp>

namespace timetable_vsu_backend::components::controllers::postgres::group_stage::sql
{
const userver::storages::postgres::Query qGetFacultiesByFilter(R"(
    SELECT 
        id,
        name
    FROM timetable_vsu.group_stage
    WHERE 
    ($1.ids IS null OR id::text ILIKE ANY($1.ids)) and
	($1.names IS null OR name ILIKE ANY($1.names))
    ;
    )");
}
