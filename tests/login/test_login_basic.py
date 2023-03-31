import pytest

from testsuite.databases import pgsql


@pytest.mark.pgsql('db_1', files=['initial_data_auth.sql'])
async def test_login_endpoint(service_client):
    response = await service_client.post(
        '/login',
        json={'login': 'test_user', 'password': 'password123'}
    )
    assert response.status == 200
    assert 'token' in response.json()
    assert isinstance(response.json()['token'], str)


@pytest.mark.pgsql('db_1', files=['initial_data_auth.sql'])
async def test_login_endpoint_success(service_client):
    response = await service_client.post(
        '/login',
        json={'login': 'test_user', 'password': 'password123'}
    )
    assert response.status == 200
    assert 'token' in response.json()
    assert isinstance(response.json()['token'], str)


@pytest.mark.pgsql('db_1', files=['initial_data_auth.sql'])
async def test_login_endpoint_success(service_client):
    response = await service_client.post(
        '/login',
        json={'login': 'test_user', 'password': 'password123'}
    )
    assert response.status == 200
    assert 'token' in response.json()
    assert isinstance(response.json()['token'], str)


@pytest.mark.pgsql('db_1', files=['initial_data_auth.sql'])
async def test_login_endpoint_wrong_password(service_client):
    response = await service_client.post(
        '/login',
        json={'login': 'test_user', 'password': 'wrong_password'}
    )
    assert response.status == 401


async def test_login_endpoint_missing_username(service_client):
    response = await service_client.post(
        '/login',
        json={'password': 'password123'}
    )
    assert response.status == 400


@pytest.mark.pgsql('db_1', files=['initial_data_auth.sql'])
async def test_login_endpoint_missing_password(service_client):
    response = await service_client.post(
        '/login',
        json={'login': 'test_user'}
    )
    assert response.status == 400
