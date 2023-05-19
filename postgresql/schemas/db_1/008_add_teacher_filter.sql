BEGIN;

DROP TYPE IF EXISTS timetable_vsu.teacher_filter;
CREATE TYPE timetable_vsu.teacher_filter AS
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
