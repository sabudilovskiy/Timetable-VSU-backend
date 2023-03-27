CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

CREATE SCHEMA IF NOT EXISTS vsu_timetable;

DROP TABLE IF EXISTS vsu_timetable.user CASCADE;

CREATE TYPE  UserType as enum (
 'user', 'admin', 'root', 'teacher'
);

CREATE TABLE IF NOT EXISTS towns.user (
	id uuid PRIMARY KEY DEFAULT uuid_generate_v4(),
	login TEXT UNIQUE NOT NULL,
	password TEXT NOT NULL,
	user_type UserType NOT NULL
);

CREATE TABLE IF NOT EXISTS vsu_timetable.token (
	id TEXT PRIMARY KEY DEFAULT uuid_generate_v4(),
	user_id uuid UNIQUE NOT NULL references vsu_timetable."user"(id),
	expire_time timestamp with time zone NOT NULL
);