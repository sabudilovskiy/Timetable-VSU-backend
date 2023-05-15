import pytest
from admin_list_data import K_IDS
from admin_list_data import K_FIELDS
from admin_list_data import K_ADMIN


def _perform_filter(field, value):
    return {
        field: value
    }

# костыль, так как
# если фильтровать тесты,
# то на самый первый тест
# не накатываются файлы для бд


async def test_admin_list_nothing(service_client):
    pass


@pytest.mark.pgsql('db_1', files=[
    'initial_data_auth_admin.sql',
    'initial_data_auth_root.sql',
    'initial_data_auth_root_token.sql'])
@pytest.mark.parametrize(
    'field, value, found',
    K_FIELDS,
    ids=K_IDS
)
async def test_admin_list_one_account_ok(service_client, field, value, found):

    response = await service_client.get('/admin/list', json={
        "filter": _perform_filter(field, value)
    }, headers={
        'token': 'dddddddd-dddd-dddd-dddd-dddddddddddd'
    })
    assert response.status_code == 200
    assert 'admins' in response.json()
    if found:
        assert len(response.json()['admins']) == 1
        assert response.json()['admins'] == [K_ADMIN]
    else:
        assert len(response.json()['admins']) == 0
        assert response.json()['admins'] == []


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
async def test_admin_list_forbidden(service_client, type, token):
    credentials = {'login': 'some_' + type, 'password': type + '_password'}
    headers = {'token': token}
    response = await service_client.get('/admin/list',
                                        json={}, headers=headers)
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
async def test_admin_liste_bad_token(service_client, type, token):
    headers = {'token': token}
    response = await service_client.get('/admin/list',
                                        json={}, headers=headers)
    assert response.status_code == 401
    assert 'description' in response.json()
    assert 'machine_id' in response.json()
    assert response.json()['machine_id'] == 'INVALID_TOKEN'
