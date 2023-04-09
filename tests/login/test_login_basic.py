import pytest

from testsuite.databases import pgsql


@pytest.mark.pgsql('db_1', files=['initial_data_auth.sql'])
async def test_login_successful(service_client):
    credentials = {'login': 'some_nickname', 'password': 'some_password'}
    response = await service_client.post('/login', json=credentials)

    assert response.status_code == 200
    assert 'token' in response.json()
    assert 'user_type' in response.json()
    assert response.json()['user_type'] == 'user'


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
