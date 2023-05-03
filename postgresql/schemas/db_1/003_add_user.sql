BEGIN;

DROP TYPE IF EXISTS vsu_timetable.user_type CASCADE;
CREATE TYPE vsu_timetable.user_type AS
ENUM ('user','admin','teacher');

DROP TYPE IF EXISTS vsu_timetable.userV1;
CREATE TYPE vsu_timetable.userV1 AS
(
    id uuid,
	type vsu_timetable.user_type
);

DROP TYPE IF EXISTS vsu_timetable.user_credentials;
CREATE TYPE vsu_timetable.user_credentials AS
(
    login text,
	password text
);

COMMIT;
