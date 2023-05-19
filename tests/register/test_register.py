import pytest

from testsuite.databases import pgsql


def _perform_request(login, password, type, description):
    return {
        'user_credentials': {
            'login': login,
            'password': password
        },
        'desired_type': type,
        'description': description
    }


def _assert_database(vsu_timetable_db, login, password,
                     description, table_requests, token):
    users = vsu_timetable_db.get_user_by_login(login)
    assert len(users) == 1
    (user_id, user_login, user_password) = users[0]
    assert user_login == login
    assert user_password == password
    if table_requests is not None:
        requests = vsu_timetable_db.get_all_from_table(table_requests)
        assert len(requests) == 1
        (request_id, request_id_user, request_description) = requests[0]
        assert user_id == request_id_user
        assert description == request_description
    tokens = vsu_timetable_db.get_token_by_id_user(user_id)
    assert len(tokens) == 1
    (token_id, expire_time, token_id_user) = tokens[0]
    assert token_id == token


def _assert_ok_response(response, type, user_id=None, token=None):
    assert response.status_code == 200
    assert 'token' in response.json()
    if token is not None:
        assert response.json()['token'] == token
    assert isinstance(response.json()['user'], dict)
    assert 'id' in response.json()['user']
    if user_id is not None:
        assert response.json()['user']['id'] == user_id
    assert response.json()['user']['type'] == type


@pytest.mark.parametrize(
    'type, table_requests',
    [('user', None),
     ('teacher', 'timetable_vsu.teacher_requests'),
     ('admin', 'timetable_vsu.admin_requests')],
)
async def test_register_successful(service_client,
                                   vsu_timetable_db, type, table_requests):
    request = _perform_request(
        'some_user', 'some_password', type, 'description')
    response = await service_client.post('/register',
                                         json=request)
    _assert_ok_response(response, 'user')
    _assert_database(vsu_timetable_db, 'some_user', 'some_password',
                     'description', table_requests, response.json()['token'])
