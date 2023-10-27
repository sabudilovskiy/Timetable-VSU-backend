SELECT 
    u.id AS user_id,
    a.id AS admin_id,
    u.login AS user_login
FROM  timetable_vsu."admin" AS a
LEFT JOIN timetable_vsu."user" AS u ON u.id = a.id_user
WHERE a.id = $1
;
