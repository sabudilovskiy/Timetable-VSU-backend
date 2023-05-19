BEGIN;

DROP TYPE IF EXISTS timetable_vsu.admin_account;
CREATE TYPE timetable_vsu.admin_account AS
(
    user_id uuid,
	admin_id uuid
);

COMMIT;
