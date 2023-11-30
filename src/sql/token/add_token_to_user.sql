insert into timetable_vsu."token" (id_user, expire_time) values ($1, $2) RETURNING id
