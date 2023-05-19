BEGIN;

ALTER TABLE timetable_vsu.user DROP CONSTRAINT IF EXISTS user_login_unique CASCADE;
ALTER TABLE timetable_vsu.user ADD CONSTRAINT user_login_unique UNIQUE(login);

COMMIT;
