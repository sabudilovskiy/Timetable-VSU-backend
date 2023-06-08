import pytest

K_GET_ALL_TEACHERS = """
SELECT id, fio, bio, id_department FROM timetable_vsu."teacher"
WHERE id = '{}'
"""

K_GET_ALL_TEACHER_LINKS = """
SELECT id, id_user, id_teacher FROM timetable_vsu."teacher_link"
WHERE id = '{}'
"""


@pytest.fixture(name='vsu_timetable_db')
def mock_vsu_timetable_db(pgsql):
    class Teacher:
        def __init__(self, teacher_id, fio, bio, department_id):
            self.id = teacher_id
            self.fio = fio
            self.bio = bio
            self.department_id = department_id

    class TeacherLink:
        def __init__(self, link_id, teacher_id, user_id):
            self.id = link_id
            self.teacher_id = teacher_id
            self.user_id = user_id

    class Context:
        def __init__(self, pgsql):
            self.pgsql = pgsql

        def get_teacher_by_id(self, teacher_id):
            db = self.pgsql['db_1']
            cursor = db.cursor()
            cursor.execute(K_GET_ALL_TEACHERS.format(teacher_id))
            elems = cursor.fetchall()
            result = []
            for elem in elems:
                teacher_id, fio, bio, department_id = elem
                result.append(Teacher(teacher_id, fio, bio, department_id))
            return result

        def get_link_by_id(self, out_link_id):
            db = self.pgsql['db_1']
            cursor = db.cursor()
            cursor.execute(K_GET_ALL_TEACHER_LINKS.format(out_link_id))
            elems = cursor.fetchall()
            result = []
            for elem in elems:
                link_id, link_id_user, link_id_teacher = elem
                result.append(TeacherLink(
                    link_id, link_id_teacher, link_id_user))
            return result

    return Context(pgsql)
