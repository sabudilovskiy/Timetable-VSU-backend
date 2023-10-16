#pragma once
#include <userver/storages/postgres/query.hpp>

namespace legacy::components::controllers::postgres::admin::sql
{
const userver::storages::postgres::Query qCreateAdminAccount(R"(
WITH
created_user AS(
    INSERT INTO timetable_vsu."user"(login, password) values ($1.login, $1.password) ON CONFLICT DO NOTHING 
    RETURNING id
)
INSERT INTO timetable_vsu."admin"(id_user)
    SELECT id FROM created_user
RETURNING id
;
)"),
    qGetAdminAccountByAdminId(R"(
    SELECT 
        u.id AS user_id,
        a.id AS admin_id,
        u.login AS user_login
    FROM  timetable_vsu."admin" AS a
    LEFT JOIN timetable_vsu."user" AS u ON u.id = a.id_user
    WHERE a.id = $1
    ;
)"),
    qGetAdminsByFilter(R"(
    WITH admin_info as (SELECT
        a.id AS admin_id,
        a.id_user AS user_id,
        u.login AS login
    FROM timetable_vsu.admin AS a
        LEFT JOIN timetable_vsu.user AS u ON a.id_user = u.id
    )
    SELECT 
        user_id,
        admin_id,
        login
    FROM admin_info
    WHERE 
    ($1.admin_ids IS null OR admin_id::text ILIKE ANY($1.admin_ids)) and
	($1.user_ids IS null OR user_id::text ILIKE ANY($1.user_ids)) and
	($1.logins IS null OR login ILIKE ANY($1.logins))
    ;
    )");
}
