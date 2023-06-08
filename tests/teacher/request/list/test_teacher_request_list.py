import pytest


@pytest.mark.pgsql('db_1',
                   files=[
                       'initial_data_teacher_request.sql',
                       'initial_data_auth_admin.sql',
                       'initial_data_auth_admin_token.sql'])
async def test_teacher_request_list_successful(service_client):
    response = await service_client.post('/teacher/requests/list', headers={
        'token': '333111c7-9654-4814-b36b-7d39c1ddded2'
    })
    assert response.status_code == 200
    assert len(response.json()['requests']) == 1
    assert response.json()['requests'][0] == {
        'request_id': '111111c7-0000-4814-b36b-7d39c1ddded2',
        'user_id': '111111c7-9999-4814-b36b-7d39c1ddded2',
        'description': 'some_description'
    }


async def test_teacher_request_list_bad_token(service_client):
    response = await service_client.post('/teacher/requests/list', headers={
        'token': '333111c7-9654-4814-b36b-7d39c1ddded2'
    })
    assert response.status_code == 401
    assert response.json()['machine_id'] == 'INVALID_TOKEN'


@pytest.mark.pgsql('db_1',
                   files=[
                       'initial_data_auth_user.sql',
                       'initial_data_auth_user_token.sql',
                       'initial_data_auth_teacher.sql',
                       'initial_data_auth_teacher_token.sql',
                   ])
@pytest.mark.parametrize(
    'token',
    [
        ('111111c7-9654-4814-b36b-7d39c1ddded2'),
        ('222111c7-9654-4814-b36b-7d39c1ddded2'),
    ],
)
async def test_teacher_request_list_forbiden(service_client, token):
    response = await service_client.post('/teacher/requests/list', headers={
        'token': token
    })
    assert response.status_code == 403
    assert response.json()['machine_id'] == 'NOT_ENOUGH_PERMISSIONS'
