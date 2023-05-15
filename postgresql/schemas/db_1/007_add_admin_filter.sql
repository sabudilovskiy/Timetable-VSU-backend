BEGIN;

DROP TYPE IF EXISTS vsu_timetable.admin_filter;
CREATE TYPE vsu_timetable.admin_filter AS
(
    admin_ids uuid[],
    user_ids uuid[],
	logins text[]
);

COMMIT;
