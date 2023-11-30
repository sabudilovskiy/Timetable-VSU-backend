insert into timetable_vsu."user"
           (   login,    password) 
    values ($1.login, $1.password) 
ON CONFLICT DO NOTHING 
RETURNING id
