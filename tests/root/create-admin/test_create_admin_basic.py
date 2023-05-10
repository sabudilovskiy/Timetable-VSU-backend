import pytest

from testsuite.databases import pgsql


def _assert_ok_response(response, login, password):
    assert response.status_code == 200
    assert 'created_account' in response.json().keys()
    assert isinstance(response.json()['created_account'], dict)
    assert 'admin_id' in response.json()['created_account'].keys()
    assert 'user_id' in response.json()['created_account'].keys()
    assert response.json()['created_account']['login'] == login
    assert response.json()['created_account']['password'] == password


# костыль, так как
# если фильтровать тесты,
# то на самый первый тест
# не накатываются файлы для бд
async def test_root_create_nothing(service_client):
    pass


@pytest.mark.pgsql('db_1',
                   files=[
                       'initial_data_auth_root.sql',
                       'initial_data_auth_root_token.sql',
                   ])
@pytest.mark.parametrize(
    'type',
    [
        ('user'),
        ('teacher'),
        ('admin'),
    ],
)
async def test_root_create_admin_ok(service_client, type):
    login = 'some_' + type
    password = type + '_password'
    credentials = {'login': login, 'password': password}
    body = {
        'credentials': credentials
    }
    headers = {'token': 'dddddddd-dddd-dddd-dddd-dddddddddddd'}
    response = await service_client.post('/root/create-admin',
                                         json=body, headers=headers)
    _assert_ok_response(response, login, password)


@pytest.mark.pgsql('db_1',
                   files=[
                       'initial_data_auth_root.sql',
                       'initial_data_auth_root_token.sql',
                       'initial_data_auth_user.sql',
                       'initial_data_auth_admin.sql',
                       'initial_data_auth_teacher.sql',
                   ])
@pytest.mark.parametrize(
    'type',
    [
        ('user'),
        ('teacher'),
        ('admin'),
    ],
)
async def test_root_create_admin_fail_taken(service_client, type):
    credentials = {'login': 'some_' + type, 'password': type + '_password'}
    body = {
        'credentials': credentials
    }
    headers = {'token': 'dddddddd-dddd-dddd-dddd-dddddddddddd'}
    response = await service_client.post('/root/create-admin',
                                         json=body, headers=headers)
    assert response.status_code == 400
    assert 'description' in response.json()
    assert 'machine_id' in response.json()
    assert response.json()['machine_id'] == 'LOGIN_TAKEN'


@pytest.mark.pgsql('db_1',
                   files=[
                       'initial_data_auth_user.sql',
                       'initial_data_auth_user_token.sql',
                       'initial_data_auth_admin.sql',
                       'initial_data_auth_admin_token.sql',
                       'initial_data_auth_teacher.sql',
                       'initial_data_auth_teacher_token.sql',
                   ])
@pytest.mark.parametrize(
    'type, token',
    [
        ('user', '111111c7-9654-4814-b36b-7d39c1ddded2'),
        ('teacher', '222111c7-9654-4814-b36b-7d39c1ddded2'),
        ('admin', '333111c7-9654-4814-b36b-7d39c1ddded2'),
    ],
)
async def test_root_create_admin_forbidden(service_client, type, token):
    credentials = {'login': 'some_' + type, 'password': type + '_password'}
    body = {
        'credentials': credentials
    }
    headers = {'token': token}
    response = await service_client.post('/root/create-admin',
                                         json=body, headers=headers)
    assert response.status_code == 403
    assert 'description' in response.json()
    assert 'machine_id' in response.json()
    assert response.json()['machine_id'] == 'NOT_ENOUGH_PERMISSIONS'


@pytest.mark.pgsql('db_1',
                   files=[
                       'initial_data_auth_user.sql',
                       'initial_data_auth_admin.sql',
                       'initial_data_auth_teacher.sql',
                   ])
@pytest.mark.parametrize(
    'type, token',
    [
        ('user', '111111c7-9654-4814-b36b-7d39c1ddded2'),
        ('teacher', '222111c7-9654-4814-b36b-7d39c1ddded2'),
        ('admin', '333111c7-9654-4814-b36b-7d39c1ddded2'),
    ],
)
async def test_root_create_admin_bad_token(service_client, type, token):
    credentials = {'login': 'some_' + type, 'password': type + '_password'}
    body = {
        'credentials': credentials
    }
    headers = {'token': token}
    response = await service_client.post('/root/create-admin',
                                         json=body, headers=headers)
    assert response.status_code == 401
    assert 'description' in response.json()
    assert 'machine_id' in response.json()
    assert response.json()['machine_id'] == 'INVALID_TOKEN'
