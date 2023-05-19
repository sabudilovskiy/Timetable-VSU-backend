BEGIN;

DROP TYPE IF EXISTS vsu_timetable.admin_filter_v2;
CREATE TYPE vsu_timetable.admin_filter_v2 AS
(
    admin_ids text[],
    user_ids text[],
	logins text[]
);

COMMIT;
