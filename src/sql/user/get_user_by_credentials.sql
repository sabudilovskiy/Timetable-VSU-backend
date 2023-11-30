WITH all_user AS 
( 
    SELECT 
        u.id AS user_id,
        a.id AS admin_id,
        tl.id_teacher AS teacher_id
    from 
        timetable_vsu.user AS u
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
