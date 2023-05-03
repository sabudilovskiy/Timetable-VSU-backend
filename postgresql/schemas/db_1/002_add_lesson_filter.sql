BEGIN;

DROP TYPE IF EXISTS vsu_timetable.lesson_filter;
CREATE TYPE vsu_timetable.lesson_filter AS
(
    lesson_ids uuid[],
	begin timestamptz,
	"end" timestamptz,
	days vsu_timetable.day[],
	department_ids uuid[],
	department_names text[],
	faculty_ids uuid[],
	faculty_names text[],
	group_ids uuid[],
	group_names text[],
    group_courses SMALLINT[],
    group_types vsu_timetable.grouptype[],
    room_ids uuid[],
	room_names text[],
	subgroup vsu_timetable.subgroup,
	subject_ids uuid[],
	subject_names text[],
	teacher_ids uuid[],
	teacher_fios text[],
	teacher_bios text[],
	week vsu_timetable.type_of_week,
	lesson_type vsu_timetable.type_lesson,
    numbers SMALLINT[]
);

COMMIT;
