BEGIN;

DROP TYPE IF EXISTS timetable_vsu.teacher_info;
CREATE TYPE timetable_vsu.teacher_info AS
(
	fio text,
	bio text,
	id_department uuid
);

COMMIT;
