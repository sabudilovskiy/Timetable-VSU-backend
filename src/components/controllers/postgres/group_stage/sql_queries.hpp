#pragma once
#include <userver/storages/postgres/query.hpp>

namespace timetable_vsu_backend::components::controllers::postgres::
    group_stage::sql
{
const userver::storages::postgres::Query qGetGroupStages(R"(
    WITH group_stages_info AS(SELECT
            gs.id AS group_stage_id,
            gs.course AS group_stage_course,
            gs.begin AS group_stage_begin,
            gs."end" AS group_stage_end,
            g.id AS group_id, 
            g.name AS group_name,
            g.type AS group_type,
            f.id AS faculty_id,
            f.name AS faculty_name
        FROM timetable_vsu.group_stage AS gs
            LEFT JOIN timetable_vsu.group AS g ON gs.id_group = g.id
            LEFT JOIN timetable_vsu.faculty AS f ON g.id_faculty = f.id
    )
    SELECT 
        group_stage_id,
        group_stage_course,
        group_stage_begin,
        group_stage_end,
        group_id,
        group_name,
        group_type,
        faculty_id,
        faculty_name
    FROM group_stages_info
    WHERE
    ($1.group_stage_ids IS null OR group_stage_id::text ILIKE ANY($1.group_stage_ids)) and
    ($1.group_stage_courses IS null or group_stage_course = ANY($1.group_stage_courses)) and
    ($1.group_stage_begin IS null OR $1.group_stage_begin <= group_stage_end) and
    ($1.group_stage_end IS null OR $1.group_stage_end >= group_stage_begin) and
    ($1.group_ids IS null OR group_id::text ILIKE ANY($1.group_ids)) and
    ($1.group_names IS null OR group_name ILIKE ANY($1.group_names)) and
    ($1.group_types IS null OR group_type = ANY($1.group_types)) and
    ($1.faculty_ids IS null OR faculty_id::text ILIKE ANY($1.faculty_ids)) and
    ($1.faculty_names IS null OR faculty_name ILIKE ANY($1.faculty_names))
    ;
    )");
}
