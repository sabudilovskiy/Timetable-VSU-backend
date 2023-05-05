INSERT INTO vsu_timetable.user(login, password, id)
VALUES('some_user', 'user_password', '111111c7-9654-4814-b36b-7d39c1ddded2');

INSERT INTO vsu_timetable.faculty
(id, "name")
VALUES('999111c7-9654-4814-bbbb-7d39c1ddded2', '');

INSERT INTO vsu_timetable.department
(id, "name", id_faculty)
VALUES('555111c7-9654-4814-cccc-7d39c1ddded2', '', '999111c7-9654-4814-bbbb-7d39c1ddded2');

INSERT INTO vsu_timetable.teacher
(id, fio, bio, id_department)
VALUES('222111c7-9654-4814-dddd-7d39c1ddded2', '', '', '555111c7-9654-4814-cccc-7d39c1ddded2');

INSERT INTO vsu_timetable.user(login, password, id)
VALUES('some_teacher', 'teacher_password', '222111c7-9654-4814-b36b-7d39c1ddded2');

INSERT INTO vsu_timetable.teacher_link
(id, id_user, id_teacher)
VALUES('666111c7-9654-4814-b36b-7d39c1ddded2', '222111c7-9654-4814-b36b-7d39c1ddded2', '222111c7-9654-4814-dddd-7d39c1ddded2');


INSERT INTO vsu_timetable.user(login, password, id)
VALUES('some_admin', 'admin_password', '333111c7-9654-4814-b36b-7d39c1ddded2');

INSERT INTO vsu_timetable."admin"
(id, id_user)
VALUES('000111c7-9654-4814-b36b-7d39c1ddded2', '333111c7-9654-4814-b36b-7d39c1ddded2');
