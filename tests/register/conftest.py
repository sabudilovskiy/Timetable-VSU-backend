import pytest
K_GET_USER_BY_ID = """
SELECT * from timetable_vsu."user" WHERE id = '{}'
"""

K_GET_TOKEN_BY_ID_USER = """
SELECT * from timetable_vsu."token" WHERE id_user = '{}'::uuid
"""

K_GET_USER_BY_LOGIN = """
SELECT * from timetable_vsu."user" WHERE login = '{}'
"""

K_GET_ALL_TABLE = """
SELECT * from {}
"""


@pytest.fixture(name='vsu_timetable_db')
def mock_vsu_timetable_db(pgsql):
    class Context:
        def __init__(self, pgsql):
            pgsql = pgsql

        def get_all_from_table(self, table):
            assert isinstance(table, str)
            db = pgsql['db_1']
            cursor = db.cursor()
            formated_query = K_GET_ALL_TABLE.format(table)
            cursor.execute(formated_query)
            return cursor.fetchall()

        def get_user_by_id(self, user_id):
            assert isinstance(user_id, str)
            db = pgsql['db_1']
            cursor = db.cursor()
            formated_query = K_GET_USER_BY_ID.format(user_id)
            cursor.execute(formated_query)
            return cursor.fetchall()

        def get_user_by_login(self, user_login):
            assert isinstance(user_login, str)
            db = pgsql['db_1']
            cursor = db.cursor()
            formated_query = K_GET_USER_BY_LOGIN.format(user_login)
            cursor.execute(formated_query)
            return cursor.fetchall()

        def get_token_by_id_user(self, id_user):
            assert isinstance(id_user, str)
            db = pgsql['db_1']
            cursor = db.cursor()
            formated_query = K_GET_TOKEN_BY_ID_USER.format(id_user)
            cursor.execute(formated_query)
            return cursor.fetchall()

    return Context(pgsql)
