BEGIN;

DROP TYPE IF EXISTS timetable_vsu.group_stage_filter;
CREATE TYPE timetable_vsu.group_stage_filter AS
(
    group_stage_ids text[],
    group_stage_courses SMALLINT[],
    group_stage_begin timestamptz,
    group_stage_end timestamptz,
    group_ids text[],
    group_names text[],
    group_types timetable_vsu.grouptype[],
    faculty_ids text[],
    faculty_names text[]
);

COMMIT;
