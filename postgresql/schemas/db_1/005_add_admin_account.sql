BEGIN;

DROP TYPE IF EXISTS vsu_timetable.admin_account;
CREATE TYPE vsu_timetable.admin_account AS
(
    user_id uuid,
	admin_id uuid
);

COMMIT;
