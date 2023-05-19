BEGIN;

DROP TYPE IF EXISTS vsu_timetable.lesson_filterv2;
CREATE TYPE vsu_timetable.lesson_filter_v2 AS
(
    lesson_ids text[],
	begin timestamptz,
	"end" timestamptz,
	days vsu_timetable.day[],
	department_ids text[],
	department_names text[],
	faculty_ids text[],
	faculty_names text[],
	group_ids text[],
	group_names text[],
    group_courses SMALLINT[],
    group_types vsu_timetable.grouptype[],
    room_ids text[],
	room_names text[],
	subgroup vsu_timetable.subgroup,
	subject_ids text[],
	subject_names text[],
	teacher_ids text[],
	teacher_fios text[],
	teacher_bios text[],
	week vsu_timetable.type_of_week,
	lesson_type vsu_timetable.type_lesson,
    numbers SMALLINT[]
);

COMMIT;
