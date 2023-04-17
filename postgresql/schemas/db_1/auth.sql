CREATE EXTENSION IF NOT EXISTS "uuid-ossp";
DROP SCHEMA IF EXISTS vsu_timetable CASCADE;

CREATE SCHEMA vsu_timetable;


DROP TABLE IF EXISTS vsu_timetable."user" CASCADE;
CREATE TABLE vsu_timetable."user" (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	login text,
	password text,
	CONSTRAINT user_pk PRIMARY KEY (id)
);

DROP TABLE IF EXISTS vsu_timetable.token CASCADE;
CREATE TABLE vsu_timetable.token (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	expire_time timestamptz,
	id_user uuid NOT NULL,
	CONSTRAINT token_pk PRIMARY KEY (id)
);


ALTER TABLE vsu_timetable.token DROP CONSTRAINT IF EXISTS user_fk CASCADE;
ALTER TABLE vsu_timetable.token ADD CONSTRAINT user_fk FOREIGN KEY (id_user) REFERENCES vsu_timetable."user" (id) MATCH FULL ON DELETE RESTRICT ON UPDATE CASCADE;


DROP TABLE IF EXISTS vsu_timetable.admin CASCADE;
CREATE TABLE vsu_timetable.admin (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	id_user uuid NOT NULL,
	CONSTRAINT admin_pk PRIMARY KEY (id)
);
ALTER TABLE vsu_timetable.admin DROP CONSTRAINT IF EXISTS user_fk CASCADE;
ALTER TABLE vsu_timetable.admin ADD CONSTRAINT user_fk FOREIGN KEY (id_user) REFERENCES vsu_timetable."user" (id) MATCH FULL ON DELETE RESTRICT ON UPDATE CASCADE;
ALTER TABLE vsu_timetable.admin DROP CONSTRAINT IF EXISTS admin_user_unique CASCADE;
ALTER TABLE vsu_timetable.admin ADD CONSTRAINT admin_user_unique UNIQUE(id_user);


DROP TABLE IF EXISTS vsu_timetable.faculty CASCADE;
CREATE TABLE vsu_timetable.faculty (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	name text,
	CONSTRAINT faculty_pk PRIMARY KEY (id)
);



DROP TABLE IF EXISTS vsu_timetable.department CASCADE;
CREATE TABLE vsu_timetable.department (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	name text,
	id_faculty uuid,
	CONSTRAINT department_pk PRIMARY KEY (id)
);



ALTER TABLE vsu_timetable.department DROP CONSTRAINT IF EXISTS faculty_fk CASCADE;
ALTER TABLE vsu_timetable.department ADD CONSTRAINT faculty_fk FOREIGN KEY (id_faculty)
REFERENCES vsu_timetable.faculty (id) MATCH FULL
ON DELETE SET NULL ON UPDATE CASCADE;



CREATE TABLE vsu_timetable.teacher (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	fio text,
	bio text,
	id_department uuid,
	CONSTRAINT teacher_pk PRIMARY KEY (id)
);



ALTER TABLE vsu_timetable.teacher DROP CONSTRAINT IF EXISTS department_fk CASCADE;
ALTER TABLE vsu_timetable.teacher ADD CONSTRAINT department_fk FOREIGN KEY (id_department)
REFERENCES vsu_timetable.department (id) MATCH FULL
ON DELETE SET NULL ON UPDATE CASCADE;



DROP TYPE IF EXISTS vsu_timetable.grouptype CASCADE;
CREATE TYPE vsu_timetable.grouptype AS
ENUM ('undergraduate','magistracy','postgraduate','specialty');



DROP TABLE IF EXISTS vsu_timetable."group" CASCADE;
CREATE TABLE vsu_timetable."group" (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	name text,
	type vsu_timetable.grouptype,
	CONSTRAINT group_pk PRIMARY KEY (id)
);



DROP TABLE IF EXISTS vsu_timetable.group_stage CASCADE;
CREATE TABLE vsu_timetable.group_stage (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	begin timestamptz,
	"end" timestamptz,
	course smallint,
	id_group uuid,
	CONSTRAINT group_stage_pk PRIMARY KEY (id)
);



ALTER TABLE vsu_timetable.group_stage DROP CONSTRAINT IF EXISTS group_fk CASCADE;
ALTER TABLE vsu_timetable.group_stage ADD CONSTRAINT group_fk FOREIGN KEY (id_group)
REFERENCES vsu_timetable."group" (id) MATCH FULL
ON DELETE SET NULL ON UPDATE CASCADE;



DROP TABLE IF EXISTS vsu_timetable.room CASCADE;
CREATE TABLE vsu_timetable.room (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	name text,
	CONSTRAINT room_pk PRIMARY KEY (id)
);



DROP TYPE IF EXISTS vsu_timetable.type_lesson CASCADE;
CREATE TYPE vsu_timetable.type_lesson AS
ENUM ('labaratory','lection','practice');



DROP TYPE IF EXISTS vsu_timetable.type_of_week CASCADE;
CREATE TYPE vsu_timetable.type_of_week AS
ENUM ('all','even','odd');




DROP TYPE IF EXISTS vsu_timetable.subgroup CASCADE;
CREATE TYPE vsu_timetable.subgroup AS
ENUM ('all','first','second');

DROP TYPE IF EXISTS vsu_timetable.day CASCADE;
CREATE TYPE vsu_timetable.day AS
ENUM ('monday','tuesday','wednesday','thursday', 'friday', 'saturday');



DROP TABLE IF EXISTS vsu_timetable.lesson CASCADE;
CREATE TABLE vsu_timetable.lesson (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	begin timestamptz,
	"end" timestamptz,
	number_lesson smallint,
	type_lesson vsu_timetable.type_lesson,
	type_week vsu_timetable.type_of_week,
	subgroup vsu_timetable.subgroup,
	day vsu_timetable.day,
	id_room uuid,
	id_shedule uuid,
	CONSTRAINT lesson_pk PRIMARY KEY (id)
);




DROP TABLE IF EXISTS vsu_timetable.subject CASCADE;
CREATE TABLE vsu_timetable.subject (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	name text,
	CONSTRAINT subject_pk PRIMARY KEY (id)
);




ALTER TABLE vsu_timetable.lesson DROP CONSTRAINT IF EXISTS room_fk CASCADE;
ALTER TABLE vsu_timetable.lesson ADD CONSTRAINT room_fk FOREIGN KEY (id_room)
REFERENCES vsu_timetable.room (id) MATCH FULL
ON DELETE SET NULL ON UPDATE CASCADE;



DROP TABLE IF EXISTS vsu_timetable.shedule CASCADE;
CREATE TABLE vsu_timetable.shedule (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	id_teacher uuid,
	id_subject uuid,
	id_group_stage uuid,
	CONSTRAINT shedule_pk PRIMARY KEY (id)
);




ALTER TABLE vsu_timetable.shedule DROP CONSTRAINT IF EXISTS teacher_fk CASCADE;
ALTER TABLE vsu_timetable.shedule ADD CONSTRAINT teacher_fk FOREIGN KEY (id_teacher)
REFERENCES vsu_timetable.teacher (id) MATCH FULL
ON DELETE SET NULL ON UPDATE CASCADE;



ALTER TABLE vsu_timetable.shedule DROP CONSTRAINT IF EXISTS subject_fk CASCADE;
ALTER TABLE vsu_timetable.shedule ADD CONSTRAINT subject_fk FOREIGN KEY (id_subject)
REFERENCES vsu_timetable.subject (id) MATCH FULL
ON DELETE SET NULL ON UPDATE CASCADE;



ALTER TABLE vsu_timetable.shedule DROP CONSTRAINT IF EXISTS group_stage_fk CASCADE;
ALTER TABLE vsu_timetable.shedule ADD CONSTRAINT group_stage_fk FOREIGN KEY (id_group_stage)
REFERENCES vsu_timetable.group_stage (id) MATCH FULL
ON DELETE SET NULL ON UPDATE CASCADE;



ALTER TABLE vsu_timetable.lesson DROP CONSTRAINT IF EXISTS shedule_fk CASCADE;
ALTER TABLE vsu_timetable.lesson ADD CONSTRAINT shedule_fk FOREIGN KEY (id_shedule)
REFERENCES vsu_timetable.shedule (id) MATCH FULL
ON DELETE SET NULL ON UPDATE CASCADE;



DROP TABLE IF EXISTS vsu_timetable.teacher_link CASCADE;
CREATE TABLE vsu_timetable.teacher_link (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	id_user uuid,
	id_teacher uuid NOT NULL,
	CONSTRAINT teacher_link_pk PRIMARY KEY (id)
);




ALTER TABLE vsu_timetable.teacher_link DROP CONSTRAINT IF EXISTS user_fk CASCADE;
ALTER TABLE vsu_timetable.teacher_link ADD CONSTRAINT user_fk FOREIGN KEY (id_user)
REFERENCES vsu_timetable."user" (id) MATCH FULL
ON DELETE SET NULL ON UPDATE CASCADE;


ALTER TABLE vsu_timetable.teacher_link DROP CONSTRAINT IF EXISTS teacher_fk CASCADE;
ALTER TABLE vsu_timetable.teacher_link ADD CONSTRAINT teacher_fk FOREIGN KEY (id_teacher)
REFERENCES vsu_timetable.teacher (id) MATCH FULL
ON DELETE SET NULL ON UPDATE CASCADE;


ALTER TABLE vsu_timetable.teacher_link DROP CONSTRAINT IF EXISTS teacher_link_user_unique CASCADE;
ALTER TABLE vsu_timetable.teacher_link ADD CONSTRAINT teacher_link_user_unique UNIQUE (id_user);


ALTER TABLE vsu_timetable.teacher_link DROP CONSTRAINT IF EXISTS teacher_unique CASCADE;
ALTER TABLE vsu_timetable.teacher_link ADD CONSTRAINT teacher_unique UNIQUE (id_teacher);



