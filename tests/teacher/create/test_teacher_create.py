import pytest


def _assert_teachers(vsu_timetable_db, teacher_id, bio, fio, department_id):
    teachers = vsu_timetable_db.get_teacher_by_id(teacher_id)
    assert len(teachers) == 1
    teacher = teachers[0]
    assert teacher.id == teacher_id
    assert teacher.bio == bio
    assert teacher.fio == fio
    assert teacher.department_id == department_id


@pytest.mark.pgsql('db_1', files=['initial_data_timetable1.sql',
                                  'initial_data_auth_admin.sql',
                                  'initial_data_auth_admin_token.sql'])
async def test_teacher_create_one_ok(service_client, vsu_timetable_db):

    response = await service_client.post('/teacher/create', json={
        "teacher_info": {
            "fio": "test_fio",
            "bio": "test_bio",
            "department_id": '1f93ceb4-d931-4b66-a0e5-7323d6b60f3b'
        }
    },
        headers={
            'token': '333111c7-9654-4814-b36b-7d39c1ddded2'
    })
    assert response.status_code == 200
    assert 'id_created_teacher' in response.json()
    id_created_teacher = response.json()['id_created_teacher']
    _assert_teachers(vsu_timetable_db, id_created_teacher, 'test_bio',
                     'test_fio', '1f93ceb4-d931-4b66-a0e5-7323d6b60f3b')


@pytest.mark.pgsql('db_1', files=['initial_data_auth_admin.sql',
                                  'initial_data_auth_admin_token.sql'])
async def test_teacher_create_one_bad_data(service_client):

    response = await service_client.post('/teacher/create', json={
        "teacher_info": {
            "fio": "test_fio",
            "bio": "test_bio",
            "department_id": '1f93ceb4-d931-4b66-a0e5-7323d6b60f3b'
        }
    },
        headers={
            'token': '333111c7-9654-4814-b36b-7d39c1ddded2'
    })
    assert response.status_code == 400
    assert response.json()['machine_id'] == 'INVALID_DATA'


@pytest.mark.pgsql('db_1', files=['initial_data_auth_admin.sql',
                                  'initial_data_auth_admin_token.sql'])
async def test_teacher_create_one_bad_token(service_client):
    response = await service_client.post('/teacher/create', json={
        "teacher_info": {
            "fio": "test_fio",
            "bio": "test_bio",
            "department_id": '1f93ceb4-d931-4b66-a0e5-7323d6b60f3b'
        }
    },
        headers={
            'token': '333333c7-9654-4814-b36b-7d39c1ddded2'
    })
    assert response.status_code == 401
    assert response.json()['machine_id'] == 'INVALID_TOKEN'


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
    'token',
    [
        ('111111c7-9654-4814-b36b-7d39c1ddded2'),
        ('222111c7-9654-4814-b36b-7d39c1ddded2'),
    ],
)
async def test_teacher_create_forbiden(service_client, token):

    response = await service_client.post('/teacher/create', json={
        "teacher_info": {
            "fio": "test_fio",
            "bio": "test_bio",
            "department_id": '1f93ceb4-d931-4b66-a0e5-7323d6b60f3b'
        }
    },
        headers={
            'token': token
    })
    assert response.status_code == 403
    assert response.json()['machine_id'] == 'NOT_ENOUGH_PERMISSIONS'
