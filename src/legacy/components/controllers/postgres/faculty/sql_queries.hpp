#pragma once
#include <userver/storages/postgres/query.hpp>

namespace legacy::components::controllers::postgres::faculty::sql
{
const userver::storages::postgres::Query qGetFacultiesByFilter(R"(
    SELECT 
        id,
        name
    FROM timetable_vsu.faculty
    WHERE 
    ($1.ids IS null OR id::text ILIKE ANY($1.ids)) and
	($1.names IS null OR name ILIKE ANY($1.names))
    ;
    )");
}
