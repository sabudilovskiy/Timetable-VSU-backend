CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

CREATE SCHEMA IF NOT EXISTS vsu_timetable;

DROP TABLE IF EXISTS vsu_timetable.user CASCADE;

CREATE TYPE  vsu_timetable.usertype as enum (
 'user', 'admin', 'root', 'teacher'
);

CREATE TABLE IF NOT EXISTS vsu_timetable.user (
	id uuid PRIMARY KEY DEFAULT uuid_generate_v4(),
	login TEXT UNIQUE NOT NULL,
	password TEXT NOT NULL,
	user_type vsu_timetable.usertype NOT NULL
);

CREATE TABLE IF NOT EXISTS vsu_timetable.token (
	id uuid PRIMARY KEY DEFAULT uuid_generate_v4(),
	user_id uuid NOT NULL references vsu_timetable."user"(id),
	expire_time timestamp with time zone NOT NULL
);

DROP SCHEMA IF EXISTS hello_schema CASCADE;

CREATE SCHEMA IF NOT EXISTS hello_schema;

CREATE TABLE IF NOT EXISTS hello_schema.users (
    name TEXT PRIMARY KEY,
    count INTEGER DEFAULT(1)
);