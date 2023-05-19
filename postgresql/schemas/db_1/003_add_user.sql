BEGIN;

DROP TYPE IF EXISTS timetable_vsu.user_type CASCADE;
CREATE TYPE timetable_vsu.user_type AS
ENUM ('user','admin','teacher');

DROP TYPE IF EXISTS timetable_vsu.userV1;
CREATE TYPE timetable_vsu.userV1 AS
(
    id uuid,
	type timetable_vsu.user_type
);

DROP TYPE IF EXISTS timetable_vsu.user_credentials;
CREATE TYPE timetable_vsu.user_credentials AS
(
    login text,
	password text
);

COMMIT;
