import pytest
import logging
from testsuite.databases import pgsql
from get_timetable_data import K_IDS
from get_timetable_data import K_FIELDS
from get_timetable_data import K_LESSON


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
async def test_get_timetable_one_lesson(service_client, field, value, found):

    response = await service_client.post('/get-timetable', json={
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
