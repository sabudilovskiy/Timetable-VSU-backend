import pytest
from data_faculty import K_IDS
from data_faculty import K_FIELDS
from data_faculty import K_FACULTY


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
async def test_faculty_list(service_client, field, value, found):
    response = await service_client.post('/faculty/list', json={
        "filter": _perform_filter(field, value)
    })
    assert response.status_code == 200
    assert 'faculties' in response.json()
    if found:
        assert len(response.json()['faculties']) == 1
        assert response.json()['faculties'] == [K_FACULTY]
    else:
        assert len(response.json()['faculties']) == 0
        assert response.json()['faculties'] == []