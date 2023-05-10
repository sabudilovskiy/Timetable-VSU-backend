#pragma once
#include <userver/storages/postgres/query.hpp>

namespace timetable_vsu_backend::components::controllers::postgres::admin::sql {
const userver::storages::postgres::Query qCreateAdminAccount(R"(
WITH
created_user AS(
    INSERT INTO vsu_timetable."user"(login, password) values ($1.login, $1.password) ON CONFLICT DO NOTHING 
    RETURNING id
)
INSERT INTO vsu_timetable."admin"(id_user)
    SELECT id FROM created_user
RETURNING id
;
)"),
    qGetAdminAccountByAdminId(R"(
    SELECT 
        u.id AS user_id,
        a.id AS admin_id,
        u.login AS user_login,
        u.password AS user_password
    FROM  vsu_timetable."admin" AS a
    LEFT JOIN vsu_timetable."user" AS u ON u.id = a.id_user
    WHERE a.id = $1
    ;
)");
}
