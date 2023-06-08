BEGIN;

DROP TYPE IF EXISTS timetable_vsu.faculty_tuple;
CREATE TYPE timetable_vsu.faculty_tuple AS
(
	id uuid,
	name text
);

DROP TYPE IF EXISTS timetable_vsu.faculty_filter;
CREATE TYPE timetable_vsu.faculty_filter AS
(
    ids text[],
    names text[]
);

COMMIT;
