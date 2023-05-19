BEGIN;

DROP TABLE IF EXISTS timetable_vsu."teacher_requests" CASCADE;
CREATE TABLE timetable_vsu."teacher_requests" (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	id_user uuid,
	description text
);

ALTER TABLE timetable_vsu.teacher_requests DROP CONSTRAINT IF EXISTS teacher_requests_user_fk CASCADE;
ALTER TABLE timetable_vsu.teacher_requests ADD CONSTRAINT teacher_requests_user_fk FOREIGN KEY (id_user)
REFERENCES timetable_vsu."user" (id) MATCH FULL
ON DELETE SET NULL ON UPDATE CASCADE;

ALTER TABLE timetable_vsu.teacher_requests DROP CONSTRAINT IF EXISTS teacher_requests_user_uniq CASCADE;
ALTER TABLE timetable_vsu.teacher_requests ADD CONSTRAINT teacher_requests_user_uniq UNIQUE (id_user);

DROP TABLE IF EXISTS timetable_vsu."admin_requests" CASCADE;
CREATE TABLE timetable_vsu."admin_requests" (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	id_user uuid,
	description text
);

ALTER TABLE timetable_vsu.admin_requests DROP CONSTRAINT IF EXISTS admin_requests_user_fk CASCADE;
ALTER TABLE timetable_vsu.admin_requests ADD CONSTRAINT admin_requests_user_fk FOREIGN KEY (id_user)
REFERENCES timetable_vsu."user" (id) MATCH FULL
ON DELETE SET NULL ON UPDATE CASCADE;

ALTER TABLE timetable_vsu.admin_requests DROP CONSTRAINT IF EXISTS admin_requests_user_uniq CASCADE;
ALTER TABLE timetable_vsu.admin_requests ADD CONSTRAINT admin_requests_user_uniq UNIQUE (id_user);

COMMIT;
