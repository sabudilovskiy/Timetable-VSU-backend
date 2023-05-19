import pytest
from timetable_get_data import K_IDS
from timetable_get_data import K_FIELDS
from timetable_get_data import K_LESSON
from timetable_get_data import K_FIELDS_LIKE
from timetable_get_data import K_IDS_LIKE


def _perform_filter(field, value):
    return {
        field: value
    }


def _perform_filter_like(field, value):
    newvalue = []
    for elem in value:
        newvalue.append(elem[:-1])
    return {
        field: newvalue
    }


@pytest.mark.pgsql('db_1', files=['initial_data_timetable1.sql'])
@pytest.mark.parametrize(
    'field, value, found',
    K_FIELDS,
    ids=K_IDS
)
async def test_timetable_get_one_lesson(service_client, field, value, found):

    response = await service_client.post('/timetable/get', json={
        "filter": _perform_filter(field, value)
    })
    assert response.status_code == 200
    assert 'lessons' in response.json()
    if found:
        assert len(response.json()['lessons']) == 1
        assert response.json()['lessons'] == [K_LESSON]
    else:
        assert len(response.json()['lessons']) == 0
        assert response.json()['lessons'] == []


@pytest.mark.pgsql('db_1', files=['initial_data_timetable1.sql'])
@pytest.mark.parametrize(
    'field, value, found',
    K_FIELDS_LIKE,
    ids=K_IDS_LIKE
)
async def test_timetable_get_one_lesson_like(service_client, field,
                                             value, found):

    response = await service_client.post('/timetable/get', json={
        "filter": _perform_filter_like(field, value)
    })
    assert response.status_code == 200
    assert 'lessons' in response.json()
    if found:
        assert len(response.json()['lessons']) == 1
        assert response.json()['lessons'] == [K_LESSON]
    else:
        assert len(response.json()['lessons']) == 0
        assert response.json()['lessons'] == []
