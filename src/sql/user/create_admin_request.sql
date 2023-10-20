INSERT INTO timetable_vsu."admin_requests"(id_user, description) values ($1, $2) ON CONFLICT DO NOTHING
