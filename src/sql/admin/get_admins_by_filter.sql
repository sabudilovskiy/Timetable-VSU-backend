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
