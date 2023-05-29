-- Insert test data into the faculty table
INSERT INTO timetable_vsu.faculty (id, name)
VALUES ('af8f26b8-afc7-483d-b6cc-ffaec29d4bc7', 'ПММ');

-- Insert test data into the department table
INSERT INTO timetable_vsu.department (id, name, id_faculty)
VALUES ('3ec37598-6c49-4a02-8134-d9dbffafa8c4', 'МОЭВМ', 'af8f26b8-afc7-483d-b6cc-ffaec29d4bc7');

-- Insert test data into the teacher table
INSERT INTO timetable_vsu.teacher (id, fio, bio, id_department)
VALUES ('dc5bad6f-fcf6-4869-b0e5-5c36aed85cc1', 'УСКОВА О.Ф.', 'ЛУЧШИЙ ПРЕПОД МИРА', '3ec37598-6c49-4a02-8134-d9dbffafa8c4');

-- Insert test data into the group table
INSERT INTO timetable_vsu.group (id, name, type, id_faculty)
VALUES ('c8a34f05-f081-4d78-b971-30d562fd9f1c', '62', 'undergraduate', 'af8f26b8-afc7-483d-b6cc-ffaec29d4bc7');

-- Insert test data into the group_stage table
INSERT INTO timetable_vsu.group_stage (id, begin, "end", course, id_group)
VALUES ('4f9c8f36-c007-4d1a-9255-4a4ce8d45a96', '2023-09-01 00:00:00', '2024-06-30 00:00:00', 1, 'c8a34f05-f081-4d78-b971-30d562fd9f1c');

-- Insert test data into the room table
INSERT INTO timetable_vsu.room (id, name)
VALUES ('b5a90d34-307f-4ab1-9caf-8b6749189de8', '101');

-- Insert test data into the subject table
INSERT INTO timetable_vsu.subject (id, name)
VALUES ('6990a617-405e-492a-990f-621ab0411623', 'Mathematics');

-- Insert test data into the shedule table
INSERT INTO timetable_vsu.shedule (id, id_teacher, id_subject, id_group_stage)
VALUES ('75021a69-9ceb-4eec-8151-34f93c0af429', 'dc5bad6f-fcf6-4869-b0e5-5c36aed85cc1', '6990a617-405e-492a-990f-621ab0411623', '4f9c8f36-c007-4d1a-9255-4a4ce8d45a96');

-- Insert test data into the lesson table
INSERT INTO timetable_vsu.lesson (id, begin, "end", number_lesson, type_lesson, type_week, subgroup, day, id_room, id_shedule)
VALUES ('6e3092e3-ac10-47a8-b52b-a15682ecc40c', '2021-09-01 08:30:00', '2021-10-01 10:05:00', 1, 'practice', 'even', 'first', 'monday', 
'b5a90d34-307f-4ab1-9caf-8b6749189de8', 
'75021a69-9ceb-4eec-8151-34f93c0af429');
