import pytest
K_ADD_USER = """
insert into vsu_timetable."user"(id, login, password) values ('{}', '{}', '{}')
"""


@pytest.fixture(name='vsu_timetable_db')
def mock_vsu_timetable_db(pgsql):
    class Context:
        def __init__(self, pgsql):
            pgsql = pgsql

        def add_user(self, user_id, login, password):
            assert isinstance(user_id, str)
            assert isinstance(login, str)
            assert isinstance(password, str)
            db = pgsql['db_1']
            cursor = db.cursor()
            formated_query = K_ADD_USER.format(user_id, login, password)
            cursor.execute(formated_query)
    return Context(pgsql)
