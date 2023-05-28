BEGIN;

CREATE EXTENSION IF NOT EXISTS "uuid-ossp";
DROP SCHEMA IF EXISTS timetable_vsu CASCADE;

CREATE SCHEMA timetable_vsu;


DROP TABLE IF EXISTS timetable_vsu."user" CASCADE;
CREATE TABLE timetable_vsu."user" (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	login text,
	password text,
	CONSTRAINT user_pk PRIMARY KEY (id)
);

DROP TABLE IF EXISTS timetable_vsu.token CASCADE;
CREATE TABLE timetable_vsu.token (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	expire_time timestamptz,
	id_user uuid NOT NULL,
	CONSTRAINT token_pk PRIMARY KEY (id)
);
 

ALTER TABLE timetable_vsu.token DROP CONSTRAINT IF EXISTS user_fk CASCADE;
ALTER TABLE timetable_vsu.token ADD CONSTRAINT user_fk FOREIGN KEY (id_user) REFERENCES timetable_vsu."user" (id) MATCH FULL ON DELETE RESTRICT ON UPDATE CASCADE;


DROP TABLE IF EXISTS timetable_vsu.admin CASCADE;
CREATE TABLE timetable_vsu.admin (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	id_user uuid NOT NULL,
	CONSTRAINT admin_pk PRIMARY KEY (id)
);
ALTER TABLE timetable_vsu.admin DROP CONSTRAINT IF EXISTS user_fk CASCADE;
ALTER TABLE timetable_vsu.admin ADD CONSTRAINT user_fk FOREIGN KEY (id_user) REFERENCES timetable_vsu."user" (id) MATCH FULL ON DELETE RESTRICT ON UPDATE CASCADE;
ALTER TABLE timetable_vsu.admin DROP CONSTRAINT IF EXISTS admin_user_unique CASCADE;
ALTER TABLE timetable_vsu.admin ADD CONSTRAINT admin_user_unique UNIQUE(id_user);


DROP TABLE IF EXISTS timetable_vsu.faculty CASCADE;
CREATE TABLE timetable_vsu.faculty (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	name text,
	CONSTRAINT faculty_pk PRIMARY KEY (id)
);



DROP TABLE IF EXISTS timetable_vsu.department CASCADE;
CREATE TABLE timetable_vsu.department (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	name text,
	id_faculty uuid,
	CONSTRAINT department_pk PRIMARY KEY (id)
);



ALTER TABLE timetable_vsu.department DROP CONSTRAINT IF EXISTS faculty_fk CASCADE;
ALTER TABLE timetable_vsu.department ADD CONSTRAINT faculty_fk FOREIGN KEY (id_faculty)
REFERENCES timetable_vsu.faculty (id) MATCH FULL
ON DELETE CASCADE ON UPDATE CASCADE;



CREATE TABLE timetable_vsu.teacher (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	fio text,
	bio text,
	id_department uuid,
	CONSTRAINT teacher_pk PRIMARY KEY (id)
);



ALTER TABLE timetable_vsu.teacher DROP CONSTRAINT IF EXISTS department_fk CASCADE;
ALTER TABLE timetable_vsu.teacher ADD CONSTRAINT department_fk FOREIGN KEY (id_department)
REFERENCES timetable_vsu.department (id) MATCH FULL
ON DELETE CASCADE ON UPDATE CASCADE;



DROP TYPE IF EXISTS timetable_vsu.grouptype CASCADE;
CREATE TYPE timetable_vsu.grouptype AS
ENUM ('undergraduate','magistracy','postgraduate','specialty');



DROP TABLE IF EXISTS timetable_vsu."group" CASCADE;
CREATE TABLE timetable_vsu."group" (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	name text,
	type timetable_vsu.grouptype,
	id_faculty uuid NOT NULL,
	CONSTRAINT group_pk PRIMARY KEY (id)
);

ALTER TABLE timetable_vsu.group DROP CONSTRAINT IF EXISTS group_faculty_fk CASCADE;
ALTER TABLE timetable_vsu.group ADD CONSTRAINT group_faculty_fk FOREIGN KEY (id_faculty)
REFERENCES timetable_vsu."faculty" (id) MATCH FULL
ON DELETE CASCADE ON UPDATE CASCADE;



DROP TABLE IF EXISTS timetable_vsu.group_stage CASCADE;
CREATE TABLE timetable_vsu.group_stage (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	begin timestamptz,
	"end" timestamptz,
	course smallint,
	id_group uuid NOT NULL,
	CONSTRAINT group_stage_pk PRIMARY KEY (id)
);



ALTER TABLE timetable_vsu.group_stage DROP CONSTRAINT IF EXISTS group_fk CASCADE;
ALTER TABLE timetable_vsu.group_stage ADD CONSTRAINT group_fk FOREIGN KEY (id_group)
REFERENCES timetable_vsu."group" (id) MATCH FULL
ON DELETE CASCADE ON UPDATE CASCADE;



DROP TABLE IF EXISTS timetable_vsu.room CASCADE;
CREATE TABLE timetable_vsu.room (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	name text,
	CONSTRAINT room_pk PRIMARY KEY (id)
);



DROP TYPE IF EXISTS timetable_vsu.type_lesson CASCADE;
CREATE TYPE timetable_vsu.type_lesson AS
ENUM ('labaratory','lection','practice');



DROP TYPE IF EXISTS timetable_vsu.type_of_week CASCADE;
CREATE TYPE timetable_vsu.type_of_week AS
ENUM ('all','even','odd');




DROP TYPE IF EXISTS timetable_vsu.subgroup CASCADE;
CREATE TYPE timetable_vsu.subgroup AS
ENUM ('all','first','second');

DROP TYPE IF EXISTS timetable_vsu.day CASCADE;
CREATE TYPE timetable_vsu.day AS
ENUM ('monday','tuesday','wednesday','thursday', 'friday', 'saturday');



DROP TABLE IF EXISTS timetable_vsu.lesson CASCADE;
CREATE TABLE timetable_vsu.lesson (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	begin timestamptz,
	"end" timestamptz,
	number_lesson smallint,
	type_lesson timetable_vsu.type_lesson,
	type_week timetable_vsu.type_of_week,
	subgroup timetable_vsu.subgroup,
	day timetable_vsu.day,
	id_room uuid NOT NULL,
	id_shedule uuid NOT NULL,
	CONSTRAINT lesson_pk PRIMARY KEY (id)
);




DROP TABLE IF EXISTS timetable_vsu.subject CASCADE;
CREATE TABLE timetable_vsu.subject (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	name text,
	CONSTRAINT subject_pk PRIMARY KEY (id)
);




ALTER TABLE timetable_vsu.lesson DROP CONSTRAINT IF EXISTS room_fk CASCADE;
ALTER TABLE timetable_vsu.lesson ADD CONSTRAINT room_fk FOREIGN KEY (id_room)
REFERENCES timetable_vsu.room (id) MATCH FULL
ON DELETE CASCADE ON UPDATE CASCADE;



DROP TABLE IF EXISTS timetable_vsu.shedule CASCADE;
CREATE TABLE timetable_vsu.shedule (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	id_teacher uuid NOT NULL,
	id_subject uuid NOT NULL,
	id_group_stage uuid NOT NULL,
	CONSTRAINT shedule_pk PRIMARY KEY (id)
);




ALTER TABLE timetable_vsu.shedule DROP CONSTRAINT IF EXISTS teacher_fk CASCADE;
ALTER TABLE timetable_vsu.shedule ADD CONSTRAINT teacher_fk FOREIGN KEY (id_teacher)
REFERENCES timetable_vsu.teacher (id) MATCH FULL
ON DELETE CASCADE ON UPDATE CASCADE;



ALTER TABLE timetable_vsu.shedule DROP CONSTRAINT IF EXISTS subject_fk CASCADE;
ALTER TABLE timetable_vsu.shedule ADD CONSTRAINT subject_fk FOREIGN KEY (id_subject)
REFERENCES timetable_vsu.subject (id) MATCH FULL
ON DELETE CASCADE ON UPDATE CASCADE;



ALTER TABLE timetable_vsu.shedule DROP CONSTRAINT IF EXISTS group_stage_fk CASCADE;
ALTER TABLE timetable_vsu.shedule ADD CONSTRAINT group_stage_fk FOREIGN KEY (id_group_stage)
REFERENCES timetable_vsu.group_stage (id) MATCH FULL
ON DELETE CASCADE ON UPDATE CASCADE;



ALTER TABLE timetable_vsu.lesson DROP CONSTRAINT IF EXISTS shedule_fk CASCADE;
ALTER TABLE timetable_vsu.lesson ADD CONSTRAINT shedule_fk FOREIGN KEY (id_shedule)
REFERENCES timetable_vsu.shedule (id) MATCH FULL
ON DELETE CASCADE ON UPDATE CASCADE;



DROP TABLE IF EXISTS timetable_vsu.teacher_link CASCADE;
CREATE TABLE timetable_vsu.teacher_link (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	id_user uuid,
	id_teacher uuid NOT NULL,
	CONSTRAINT teacher_link_pk PRIMARY KEY (id)
);




ALTER TABLE timetable_vsu.teacher_link DROP CONSTRAINT IF EXISTS user_fk CASCADE;
ALTER TABLE timetable_vsu.teacher_link ADD CONSTRAINT user_fk FOREIGN KEY (id_user)
REFERENCES timetable_vsu."user" (id) MATCH FULL
ON DELETE CASCADE ON UPDATE CASCADE;


ALTER TABLE timetable_vsu.teacher_link DROP CONSTRAINT IF EXISTS teacher_fk CASCADE;
ALTER TABLE timetable_vsu.teacher_link ADD CONSTRAINT teacher_fk FOREIGN KEY (id_teacher)
REFERENCES timetable_vsu.teacher (id) MATCH FULL
ON DELETE CASCADE ON UPDATE CASCADE;


ALTER TABLE timetable_vsu.teacher_link DROP CONSTRAINT IF EXISTS teacher_link_user_unique CASCADE;
ALTER TABLE timetable_vsu.teacher_link ADD CONSTRAINT teacher_link_user_unique UNIQUE (id_user);


ALTER TABLE timetable_vsu.teacher_link DROP CONSTRAINT IF EXISTS teacher_unique CASCADE;
ALTER TABLE timetable_vsu.teacher_link ADD CONSTRAINT teacher_unique UNIQUE (id_teacher);

COMMIT;
