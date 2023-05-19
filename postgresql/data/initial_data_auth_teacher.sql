INSERT INTO timetable_vsu.faculty
(id, "name")
VALUES('999111c7-9654-4814-bbbb-7d39c1ddded2', '');

INSERT INTO timetable_vsu.department
(id, "name", id_faculty)
VALUES('555111c7-9654-4814-cccc-7d39c1ddded2', '', '999111c7-9654-4814-bbbb-7d39c1ddded2');

INSERT INTO timetable_vsu.teacher
(id, fio, bio, id_department)
VALUES('222111c7-9654-4814-dddd-7d39c1ddded2', '', '', '555111c7-9654-4814-cccc-7d39c1ddded2');

INSERT INTO timetable_vsu.user(login, password, id)
VALUES('some_teacher', 'teacher_password', '222111c7-9654-4814-b36b-7d39c1ddded2');

INSERT INTO timetable_vsu.teacher_link
(id, id_user, id_teacher)
VALUES('666111c7-9654-4814-b36b-7d39c1ddded2', '222111c7-9654-4814-b36b-7d39c1ddded2', '222111c7-9654-4814-dddd-7d39c1ddded2');
