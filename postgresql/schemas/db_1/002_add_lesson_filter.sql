BEGIN;

DROP TYPE IF EXISTS timetable_vsu.lesson_filter;
CREATE TYPE timetable_vsu.lesson_filter AS
(
    lesson_ids uuid[],
	begin timestamptz,
	"end" timestamptz,
	days timetable_vsu.day[],
	department_ids uuid[],
	department_names text[],
	faculty_ids uuid[],
	faculty_names text[],
	group_ids uuid[],
	group_names text[],
    group_courses SMALLINT[],
    group_types timetable_vsu.grouptype[],
    room_ids uuid[],
	room_names text[],
	subgroup timetable_vsu.subgroup,
	subject_ids uuid[],
	subject_names text[],
	teacher_ids uuid[],
	teacher_fios text[],
	teacher_bios text[],
	week timetable_vsu.type_of_week,
	lesson_type timetable_vsu.type_lesson,
    numbers SMALLINT[]
);

COMMIT;
