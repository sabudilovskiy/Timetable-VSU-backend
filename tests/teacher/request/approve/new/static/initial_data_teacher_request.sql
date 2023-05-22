INSERT INTO timetable_vsu.user(login, password, id)
VALUES('some_request_user', 'request_user_password', '000000c7-9999-4814-b36b-7d39c1ddded2');

INSERT INTO timetable_vsu.teacher_requests(id, id_user, description)
VALUES('000000c7-1111-4814-b36b-7d39c1ddded2','000000c7-9999-4814-b36b-7d39c1ddded2', 'some_description');

INSERT INTO timetable_vsu.faculty (id, name)
VALUES ('bbc6312c-f25e-4db3-b2a0-3f5dc6717a8d', 'Faculty of Mathematics and Mechanics');

INSERT INTO timetable_vsu.department (id, name, id_faculty)
VALUES ('1f93ceb4-d931-4b66-a0e5-7323d6b60f3b', 'Department of Applied Mathematics', 'bbc6312c-f25e-4db3-b2a0-3f5dc6717a8d');
