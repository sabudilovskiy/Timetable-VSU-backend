WITH all_user AS 
(
    SELECT 
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
