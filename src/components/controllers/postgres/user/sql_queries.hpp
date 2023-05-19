#pragma once

#include <userver/storages/postgres/query.hpp>

namespace timetable_vsu_backend::components::controllers::postgres::user::sql
{
const userver::storages::postgres::Query qGetUserByCredentials(R"(
    WITH all_user AS ( SELECT 
		u.id AS user_id,
		a.id AS admin_id,
		tl.id_teacher AS teacher_id
	from timetable_vsu.user AS u
        left join timetable_vsu.admin AS a on u.id = a.id_user
        left join timetable_vsu.teacher_link AS tl on u.id = tl.id_user
	where u.login = $1.login and u."password" = $1.password
    )
    SELECT 
        user_id, 
        CASE 
            WHEN admin_id IS NOT NULL THEN 'admin'::timetable_vsu.user_type
            WHEN teacher_id IS NOT NULL THEN 'teacher'::timetable_vsu.user_type
            ELSE 'user' 
        END AS type 
    FROM all_user;
    )"),
    qGetUserByToken(R"(
    WITH all_user AS ( SELECT 
		u.id AS user_id,
		a.id AS admin_id,
        t.id AS token_id,
		tl.id_teacher AS teacher_id
	from timetable_vsu.token AS t
        left join timetable_vsu.user AS u on u.id = t.id_user
        left join timetable_vsu.admin AS a on u.id = a.id_user
        left join timetable_vsu.teacher_link AS tl on u.id = tl.id_user
	where t.id = $1
    )
    SELECT 
        user_id, 
        CASE 
            WHEN admin_id IS NOT NULL THEN 'admin'::timetable_vsu.user_type
            WHEN teacher_id IS NOT NULL THEN 'teacher'::timetable_vsu.user_type
            ELSE 'user' 
        END AS type 
    FROM all_user;
    )"),
    qAddUser(R"(
    insert into timetable_vsu."user"(login, password) values ($1.login, $1.password) ON CONFLICT DO NOTHING 
    RETURNING id
    )"),
    qInternalAddUser(R"(
    insert into timetable_vsu."user"(id, login, password) values ($1, $2.login, $2.password)
    )"),
    qDropUserByLogin(R"(
        DELETE FROM timetable_vsu."user" WHERE login=$1;
    )"),
    qDropUserById(R"(
        DELETE FROM timetable_vsu."user" WHERE id=$1;
    )"),
    qCreateTeacherRequest(R"(
        INSERT INTO timetable_vsu."teacher_requests"(id_user, description) values ($1, $2) ON CONFLICT DO NOTHING 
    )"),
    qCreateAdminRequest(R"(
        INSERT INTO timetable_vsu."admin_requests"(id_user, description) values ($1, $2) ON CONFLICT DO NOTHING 
    )");
}
