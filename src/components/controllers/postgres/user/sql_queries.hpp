#pragma once

#include "userver/storages/postgres/query.hpp"

namespace timetable_vsu_backend::components::controllers::postgres::user::sql {
const userver::storages::postgres::Query qGetUser(R"(
    WITH all_user AS ( SELECT 
		u.id AS user_id,
		a.id AS admin_id,
		tl.id_teacher AS teacher_id
	from vsu_timetable.user AS u
        left join vsu_timetable.admin AS a on u.id = a.id_user
        left join vsu_timetable.teacher_link AS tl on u.id = tl.id_user
	where u.login = $1.login and u."password" = $1.password
    )
    SELECT 
        user_id, 
        CASE 
            WHEN admin_id IS NOT NULL THEN 'admin'::vsu_timetable.user_type
            WHEN teacher_id IS NOT NULL THEN 'teacher'::vsu_timetable.user_type
            ELSE 'user' 
        END AS type 
    FROM all_user;
    )"),
    qAddUser(R"(
    insert into vsu_timetable."user"(login, password) values ($1.login, $1.password) ON CONFLICT DO NOTHING 
    RETURNING id
    )"),
    qInternalAddUser(R"(
    insert into vsu_timetable."user"(id, login, password) values ($1, $2.login, $2.password)
    )"),
    qDropUserByLogin(R"(
        DELETE FROM vsu_timetable."user" WHERE login=$1;
    )"),
    qDropUserById(R"(
        DELETE FROM vsu_timetable."user" WHERE id=$1;
    )");
}
