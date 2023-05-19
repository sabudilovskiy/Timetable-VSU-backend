BEGIN;

DROP TYPE IF EXISTS timetable_vsu.admin_filter_v2;
CREATE TYPE timetable_vsu.admin_filter_v2 AS
(
    admin_ids text[],
    user_ids text[],
	logins text[]
);

COMMIT;
