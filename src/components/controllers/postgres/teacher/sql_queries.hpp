#pragma once
#include <userver/storages/postgres/query.hpp>

namespace components::controllers::postgres::teacher::sql
{
const userver::storages::postgres::Query qGetTeachersByFilter(R"(
    WITH teacher_info as (SELECT
        t.id AS teacher_id,
        t.fio AS teacher_fio,
        t.bio AS teacher_bio,
        d.id AS department_id,
        d.name AS department_name,
        f.id AS faculty_id,
        f.name AS faculty_name
    FROM timetable_vsu.teacher AS t
        LEFT JOIN timetable_vsu.department AS d ON t.id_department = d.id
        LEFT JOIN timetable_vsu.faculty AS f ON d.id_faculty = f.id
    )
    SELECT 
        teacher_id,
        teacher_fio,
        teacher_bio,
        department_id,
        department_name,
        faculty_id,
        faculty_name
    FROM teacher_info
    WHERE 
    ($1.teacher_ids IS null OR teacher_id::text ILIKE ANY($1.teacher_ids)) and
	($1.teacher_fios IS null OR teacher_fio ILIKE ANY($1.teacher_fios)) and
    ($1.teacher_bios IS null OR teacher_bio ILIKE ANY($1.teacher_bios)) and
	($1.department_ids IS null OR department_id::text ILIKE ANY($1.department_ids)) and
    ($1.department_names IS null OR department_name ILIKE ANY($1.department_names)) and
    ($1.faculty_ids IS null OR faculty_id::text ILIKE ANY($1.faculty_ids)) and
    ($1.faculty_names IS null OR faculty_name ILIKE ANY($1.faculty_names))
    ;
    )"),
    qCreateTeacher(R"(
        INSERT INTO timetable_vsu.teacher(fio, bio, id_department) VALUES($1.fio, $1.bio, $1.id_department)
        RETURNING id
        ;
    )"),
    qGetUserIdFromRequest(R"(
        SELECT id_user FROM timetable_vsu.teacher_requests WHERE id = $1
    )"),
    qCreateLink(R"(
        INSERT INTO timetable_vsu.teacher_link(id_user, id_teacher) VALUES($1, $2)
        ON CONFLICT DO NOTHING
        RETURNING id
    )"),
    qGetAllRequests(R"(
        SELECT id, id_user, description FROM timetable_vsu.teacher_requests
    )"),
    qDropRequestById(R"(
        DELETE FROM timetable_vsu.teacher_requests
        WHERE id = $1
        RETURNING id
    )");
}
