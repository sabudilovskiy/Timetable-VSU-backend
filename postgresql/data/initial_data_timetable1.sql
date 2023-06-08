-- Insert test data into the faculty table
INSERT INTO timetable_vsu.faculty (id, name)
VALUES ('bbc6312c-f25e-4db3-b2a0-3f5dc6717a8d', 'Faculty of Mathematics and Mechanics');

-- Insert test data into the department table
INSERT INTO timetable_vsu.department (id, name, id_faculty)
VALUES ('1f93ceb4-d931-4b66-a0e5-7323d6b60f3b', 'Department of Applied Mathematics', 'bbc6312c-f25e-4db3-b2a0-3f5dc6717a8d');

-- Insert test data into the teacher table
INSERT INTO timetable_vsu.teacher (id, fio, bio, id_department)
VALUES ('241416c7-9654-4814-b36b-7d39c1ddded2', 'John Doe', 'Professor of Mathematics', '1f93ceb4-d931-4b66-a0e5-7323d6b60f3b');

-- Insert test data into the group table
INSERT INTO timetable_vsu.group (id, name, type, id_faculty)
VALUES ('c1fb3eac-de6d-44ef-bf35-18bebe832e1d', 'MM-21', 'magistracy', 'bbc6312c-f25e-4db3-b2a0-3f5dc6717a8d');

-- Insert test data into the group_stage table
INSERT INTO timetable_vsu.group_stage (id, begin, "end", course, id_group)
VALUES ('4148147a-740b-48f9-aba1-47eb17432855', '2023-09-01 00:00:00', '2024-06-30 00:00:00', 1, 'c1fb3eac-de6d-44ef-bf35-18bebe832e1d');

-- Insert test data into the room table
INSERT INTO timetable_vsu.room (id, name)
VALUES ('f245127f-a730-4d13-a15d-7648deb1d4d2', '101');

-- Insert test data into the subject table
INSERT INTO timetable_vsu.subject (id, name)
VALUES ('053222c5-315a-4301-abfe-586d2409fcd3', 'Mathematics');

-- Insert test data into the shedule table
INSERT INTO timetable_vsu.shedule (id, id_teacher, id_subject, id_group_stage)
VALUES ('ab5f0559-d2ee-4030-919e-5962f1ff2235', '241416c7-9654-4814-b36b-7d39c1ddded2', '053222c5-315a-4301-abfe-586d2409fcd3', '4148147a-740b-48f9-aba1-47eb17432855');

-- Insert test data into the lesson table
INSERT INTO timetable_vsu.lesson (id, begin, "end", number_lesson, type_lesson, type_week, subgroup, day, id_room, id_shedule)
VALUES ('3d04fc36-ab71-42db-9e38-efd792afa7ba', '2023-04-01 08:30:00', '2023-05-01 10:05:00', 1, 'lection', 'all', 'all', 'monday', 
'f245127f-a730-4d13-a15d-7648deb1d4d2', 
'ab5f0559-d2ee-4030-919e-5962f1ff2235');
