BEGIN;

DROP TYPE IF EXISTS timetable_vsu.lesson_filterv2;
CREATE TYPE timetable_vsu.lesson_filter_v2 AS
(
    lesson_ids text[],
	begin timestamptz,
	"end" timestamptz,
	days timetable_vsu.day[],
	department_ids text[],
	department_names text[],
	faculty_ids text[],
	faculty_names text[],
	group_ids text[],
	group_names text[],
    group_courses SMALLINT[],
    group_types timetable_vsu.grouptype[],
    room_ids text[],
	room_names text[],
	subgroup timetable_vsu.subgroup,
	subject_ids text[],
	subject_names text[],
	teacher_ids text[],
	teacher_fios text[],
	teacher_bios text[],
	week timetable_vsu.type_of_week,
	lesson_type timetable_vsu.type_lesson,
    numbers SMALLINT[]
);

COMMIT;
