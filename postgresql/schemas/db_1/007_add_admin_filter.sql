BEGIN;

DROP TYPE IF EXISTS timetable_vsu.admin_filter;
CREATE TYPE timetable_vsu.admin_filter AS
(
    admin_ids uuid[],
    user_ids uuid[],
	logins text[]
);

COMMIT;
