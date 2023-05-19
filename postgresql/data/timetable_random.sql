-- Insert test data into the user table
INSERT INTO timetable_vsu.user (login, password)
VALUES ('user1', 'password1');

-- Insert test data into the token table
INSERT INTO timetable_vsu.token (expire_time, id_user)
VALUES ('2023-04-18 12:00:00', (SELECT id FROM timetable_vsu.user ORDER BY random() LIMIT 1));

-- Insert test data into the admin table
INSERT INTO timetable_vsu.admin (id_user)
VALUES ((SELECT id FROM timetable_vsu.user ORDER BY random() LIMIT 1));

-- Insert test data into the faculty table
INSERT INTO timetable_vsu.faculty (name)
VALUES ('Faculty of Mathematics and Mechanics');

-- Insert test data into the department table
INSERT INTO timetable_vsu.department (name, id_faculty)
VALUES ('Department of Applied Mathematics', (SELECT id FROM timetable_vsu.faculty ORDER BY random() LIMIT 1));

-- Insert test data into the teacher table
INSERT INTO timetable_vsu.teacher (fio, bio, id_department)
VALUES ('John Doe', 'Professor of Mathematics', (SELECT id FROM timetable_vsu.department ORDER BY random() LIMIT 1));

-- Insert test data into the group table
INSERT INTO timetable_vsu."group" (name, type)
VALUES ('MM-21', 'magistracy');

-- Insert test data into the group_stage table
INSERT INTO timetable_vsu.group_stage (begin, "end", course, id_group)
VALUES ('2023-09-01 00:00:00', '2024-06-30 00:00:00', 1, (SELECT id FROM timetable_vsu."group" ORDER BY random() LIMIT 1));

-- Insert test data into the room table
INSERT INTO timetable_vsu.room (name)
VALUES ('Room 101');

-- Insert test data into the subject table
INSERT INTO timetable_vsu.subject (name)
VALUES ('Mathematics');

-- Insert test data into the shedule table
INSERT INTO timetable_vsu.shedule (id_teacher, id_subject, id_group_stage)
VALUES ((SELECT id FROM timetable_vsu.teacher ORDER BY random() LIMIT 1), (SELECT id FROM timetable_vsu.subject ORDER BY random() LIMIT 1), (SELECT id FROM timetable_vsu.group_stage ORDER BY random() LIMIT 1));

-- Insert test data into the lesson table
INSERT INTO timetable_vsu.lesson (begin, "end", number_lesson, type_lesson, type_week, subgroup, day, id_room, id_shedule)
VALUES ('2023-09-01 08:30:00', '2023-09-01 10:05:00', 1, 'lection', 'all', 'all', 'monday', (SELECT id FROM timetable_vsu.room ORDER BY random() LIMIT 1), (SELECT id FROM timetable_vsu.shedule ORDER BY random() LIMIT 1));
