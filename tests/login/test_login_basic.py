import pytest

from testsuite.databases import pgsql

@pytest.mark.pgsql('db_1', files=['initial_data.sql'])
async def test_login_endpoint(service_client):
    response = await service_client.post(
        '/v1/login',
        json={'login': 'test_user', 'password': 'password123'}
    )
    assert response.status == 200
    assert response.json() == {'success': True, 'message': 'Login successful'}

@pytest.mark.pgsql('db_1', files=['initial_data.sql'])
async def test_login_endpoint_success(service_client):
    response = await service_client.post(
        '/v1/login',
        json={'login': 'test_user', 'password': 'password123'}
    )
    assert response.status == 200
    assert 'id' in response.json()
    assert isinstance(response.json()['id'], str)

@pytest.mark.pgsql('db_1', files=['initial_data.sql'])
async def test_login_endpoint_success(service_client):
    response = await service_client.post(
        '/v1/login',
        json={'login': 'test_user', 'password': 'password123'}
    )
    assert response.status == 200
    assert 'id' in response.json()
    assert isinstance(response.json()['id'], str)

@pytest.mark.pgsql('db_1', files=['initial_data.sql'])
async def test_login_endpoint_wrong_password(service_client):
    response = await service_client.post(
        '/v1/login',
        json={'login': 'test_user', 'password': 'wrong_password'}
    )
    assert response.status == 401

async def test_login_endpoint_missing_username(service_client):
    response = await service_client.post(
        '/v1/login',
        json={'password': 'password123'}
    )
    assert response.status == 400

@pytest.mark.pgsql('db_1', files=['initial_data.sql'])
async def test_login_endpoint_missing_password(service_client):
    response = await service_client.post(
        '/v1/login',
        json={'login': 'test_user'}
    )
    assert response.status == 400

