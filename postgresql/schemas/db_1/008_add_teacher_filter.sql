BEGIN;

DROP TYPE IF EXISTS vsu_timetable.teacher_filter;
CREATE TYPE vsu_timetable.teacher_filter AS
(
    teacher_ids text[],
    teacher_fios text[],
	teacher_bios text[],
    department_ids text[],
    department_names text[],
    faculty_ids text[],
    faculty_names text[]
);

COMMIT;
