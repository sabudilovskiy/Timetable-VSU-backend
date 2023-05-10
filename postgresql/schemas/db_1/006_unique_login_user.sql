BEGIN;

ALTER TABLE vsu_timetable.user DROP CONSTRAINT IF EXISTS user_login_unique CASCADE;
ALTER TABLE vsu_timetable.user ADD CONSTRAINT user_login_unique UNIQUE(login);

COMMIT;
