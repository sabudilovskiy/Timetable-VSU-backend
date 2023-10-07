#include <userver/storages/postgres/query.hpp>
namespace components::controllers::postgres::token::sql
{
const userver::storages::postgres::Query qGetUserByTokenId(R"(
   WITH found_token AS (select id_user
                 from timetable_vsu.token WHERE id = $1 AND expire_time > $2)
   SELECT id, login, password, user_type from timetable_vsu."user" LEFT OUTER JOIN found_token ON id_user = "user".id
    )"),
    qAddToken(R"(
      insert into timetable_vsu."token" (id_user, expire_time) values ($1, $2) RETURNING id
    )");
}
