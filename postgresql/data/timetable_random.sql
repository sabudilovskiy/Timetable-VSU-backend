-- Insert test data into the user table
INSERT INTO vsu_timetable.user (login, password)
VALUES ('user1', 'password1');

-- Insert test data into the token table
INSERT INTO vsu_timetable.token (expire_time, id_user)
VALUES ('2023-04-18 12:00:00', (SELECT id FROM vsu_timetable.user ORDER BY random() LIMIT 1));

-- Insert test data into the admin table
INSERT INTO vsu_timetable.admin (id_user)
VALUES ((SELECT id FROM vsu_timetable.user ORDER BY random() LIMIT 1));

-- Insert test data into the faculty table
INSERT INTO vsu_timetable.faculty (name)
VALUES ('Faculty of Mathematics and Mechanics');

-- Insert test data into the department table
INSERT INTO vsu_timetable.department (name, id_faculty)
VALUES ('Department of Applied Mathematics', (SELECT id FROM vsu_timetable.faculty ORDER BY random() LIMIT 1));

-- Insert test data into the teacher table
INSERT INTO vsu_timetable.teacher (fio, bio, id_department)
VALUES ('John Doe', 'Professor of Mathematics', (SELECT id FROM vsu_timetable.department ORDER BY random() LIMIT 1));

-- Insert test data into the group table
INSERT INTO vsu_timetable."group" (name, type)
VALUES ('MM-21', 'magistracy');

-- Insert test data into the group_stage table
INSERT INTO vsu_timetable.group_stage (begin, "end", course, id_group)
VALUES ('2023-09-01 00:00:00', '2024-06-30 00:00:00', 1, (SELECT id FROM vsu_timetable."group" ORDER BY random() LIMIT 1));

-- Insert test data into the room table
INSERT INTO vsu_timetable.room (name)
VALUES ('Room 101');

-- Insert test data into the subject table
INSERT INTO vsu_timetable.subject (name)
VALUES ('Mathematics');

-- Insert test data into the shedule table
INSERT INTO vsu_timetable.shedule (id_teacher, id_subject, id_group_stage)
VALUES ((SELECT id FROM vsu_timetable.teacher ORDER BY random() LIMIT 1), (SELECT id FROM vsu_timetable.subject ORDER BY random() LIMIT 1), (SELECT id FROM vsu_timetable.group_stage ORDER BY random() LIMIT 1));

-- Insert test data into the lesson table
INSERT INTO vsu_timetable.lesson (begin, "end", number_lesson, type_lesson, type_week, subgroup, day, id_room, id_shedule)
VALUES ('2023-09-01 08:30:00', '2023-09-01 10:05:00', 1, 'lection', 'all', 'all', 'monday', (SELECT id FROM vsu_timetable.room ORDER BY random() LIMIT 1), (SELECT id FROM vsu_timetable.shedule ORDER BY random() LIMIT 1));