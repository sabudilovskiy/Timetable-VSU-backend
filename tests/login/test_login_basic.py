import pytest

from testsuite.databases import pgsql


@pytest.mark.pgsql('db_1', files=['initial_data_auth.sql'])
@pytest.mark.parametrize(
    'type, user_id',
    [('user', '111111c7-9654-4814-b36b-7d39c1ddded2'),
     ('teacher', '222111c7-9654-4814-b36b-7d39c1ddded2'),
     ('admin', '333111c7-9654-4814-b36b-7d39c1ddded2')],
)
async def test_login_successful(service_client, type, user_id):
    credentials = {'login': 'some_' + type, 'password': type + '_password'}
    response = await service_client.post('/login', json=credentials)

    assert response.status_code == 200
    assert 'token' in response.json()
    assert isinstance(response.json()['user'], dict)
    assert response.json()['user']['id'] == user_id
    assert response.json()['user']['type'] == type


@pytest.mark.pgsql('db_1', files=['initial_data_auth.sql'])
async def test_login_root_successful(service_client):
    credentials = {'login': 'root', 'password': 'secret-password'}
    response = await service_client.post('/login', json=credentials)
    assert response.status_code == 200
    assert 'token' in response.json()
    assert isinstance(response.json()['user'], dict)
    assert response.json()['user']['id']
    assert response.json()['user']['type'] == 'root'


@pytest.mark.pgsql('db_1', files=['initial_data_auth.sql'])
async def test_login_missing_credentials(service_client):
    response = await service_client.post('/login', json={})
    assert response.status_code == 400


@pytest.mark.pgsql('db_1', files=['initial_data_auth.sql'])
async def test_login_invalid_credentials(service_client):
    credentials = {'login': 'invalid_nickname', 'password': 'invalid_password'}
    response = await service_client.post('/login', json=credentials)

    assert response.status_code == 401
    assert 'description' in response.json()
    assert 'machine_id' in response.json()


@pytest.mark.pgsql('db_1', files=['initial_data_auth.sql'])
async def test_login_missing_login(service_client):
    credentials = {'password': 'some_password'}
    response = await service_client.post('/login', json=credentials)

    assert response.status_code == 400


@pytest.mark.pgsql('db_1', files=['initial_data_auth.sql'])
async def test_login_missing_password(service_client):
    credentials = {'login': 'some_nickname'}
    response = await service_client.post('/login', json=credentials)

    assert response.status_code == 400
