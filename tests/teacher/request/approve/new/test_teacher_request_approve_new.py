import pytest


def _assert_link_db(vsu_timetable_db, link_id, user_id):
    links = vsu_timetable_db.get_link_by_id(link_id)
    assert len(links) == 1
    link = links[0]
    assert link.id == link_id
    assert link.user_id == user_id


async def _send_request(service_client,
                        token, request_id,
                        teacher_bio,
                        teacher_fio,
                        department_id):
    response = await service_client.post('/teacher/requests/approve/new',
                                         headers={
                                             'token': token
                                         }, json={
                                             'request_id': request_id,
                                             'teacher_info': {
                                                 'bio': teacher_bio,
                                                 'fio': teacher_fio,
                                                 'department_id': department_id
                                             }
                                         })
    return response


@pytest.mark.pgsql('db_1',
                   files=[
                       'initial_data_teacher_request.sql',
                       'initial_data_auth_admin.sql',
                       'initial_data_auth_admin_token.sql'])
async def test_teacher_request_approve_new_ok(service_client,
                                              vsu_timetable_db):
    token = '333111c7-9654-4814-b36b-7d39c1ddded2'
    request_id = '000000c7-1111-4814-b36b-7d39c1ddded2'
    teacher_bio = 'test_bio'
    teacher_fio = 'test_fio'
    department_id = '1f93ceb4-d931-4b66-a0e5-7323d6b60f3b'
    user_id = '000000c7-9999-4814-b36b-7d39c1ddded2'
    response = await _send_request(service_client,
                                   token,
                                   request_id,
                                   teacher_bio,
                                   teacher_fio,
                                   department_id)
    assert response.status_code == 200
    link_id = response.json()['link_id']
    assert link_id
    _assert_link_db(vsu_timetable_db, link_id, user_id)


@pytest.mark.pgsql('db_1',
                   files=[
                       'initial_data_teacher_request.sql'])
async def test_teacher_request_approve_new_bad_token(service_client):
    token = '333111c7-9654-4814-b36b-7d39c1ddded2'
    request_id = '000000c7-1111-4814-b36b-7d39c1ddded2'
    teacher_bio = 'test_bio'
    teacher_fio = 'test_fio'
    department_id = '1f93ceb4-d931-4b66-a0e5-7323d6b60f3b'
    response = await _send_request(service_client, token,
                                   request_id, teacher_bio,
                                   teacher_fio, department_id)
    assert response.status_code == 401
    assert response.json()['machine_id'] == 'INVALID_TOKEN'


@pytest.mark.pgsql('db_1',
                   files=[
                       'initial_data_teacher_request.sql',
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
async def test_teacher_request_approve_new_forbiden(service_client, token):
    request_id = '000000c7-1111-4814-b36b-7d39c1ddded2'
    teacher_bio = 'test_bio'
    teacher_fio = 'test_fio'
    department_id = '1f93ceb4-d931-4b66-a0e5-7323d6b60f3b'
    response = await _send_request(service_client, token,
                                   request_id, teacher_bio,
                                   teacher_fio, department_id)
    assert response.status_code == 403
    assert response.json()['machine_id'] == 'NOT_ENOUGH_PERMISSIONS'
