import pytest
from teacher_data import K_IDS
from teacher_data import K_FIELDS
from teacher_data import K_TEACHER


def _perform_filter(field, value):
    return {
        field: value
    }


@pytest.mark.pgsql('db_1', files=['initial_data_timetable1.sql'])
@pytest.mark.parametrize(
    'field, value, found',
    K_FIELDS,
    ids=K_IDS
)
async def test_teacher_get_one_teachers(service_client, field, value, found):

    response = await service_client.post('/teacher/list', json={
        "filter": _perform_filter(field, value)
    })
    assert response.status_code == 200
    assert 'teachers' in response.json()
    if found:
        assert len(response.json()['teachers']) == 1
        assert response.json()['teachers'] == [K_TEACHER]
    else:
        assert len(response.json()['teachers']) == 0
        assert response.json()['teachers'] == []
