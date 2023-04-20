import pytest
import logging
from testsuite.databases import pgsql

K_LESSONS = [
	{
		"id" : "f009d547-1388-49d9-b080-0fd481ed8a1f",
		"begin" : "2023-09-01T05:30:00.000Z",
		"end" : "2023-09-01T07:05:00.000Z",
		"number" : 1,
		"type" : "lection",
		"week_type" : "all",
		"subgroup" : "all",
		"day" : "monday",
		"room_id" : "e4c5dfe7-b2f2-469f-86c8-cbf9490cb108",
		"room_name" : "Room 101",
		"subject_id" : "e4af30de-1362-4cd7-813a-3eac34712dc2",
		"subject_name" : "Mathematics",
		"group_id" : "a0eae7e1-760c-48b1-a4e0-efd2c24540d7",
		"group_course" : 1,
		"group_name" : "MM-21",
		"group_type" : "magistracy",
		"faculty_id" : "b0b2fa1d-794a-4e19-9fb8-9b51d1913d03",
		"faculty_name" : "Faculty of Mathematics and Mechanics",
		"department_id" : "2cbe678d-8fc6-4fc5-afe4-8f342d62f378",
		"department_name" : "Department of Applied Mathematics",
		"teacher_id" : "d5a5a507-55bf-4637-8483-67439643d86d",
		"teacher_fio" : "John Doe",
		"teacher_bio" : "Professor of Mathematics"
	}
]

@pytest.mark.pgsql('db_1', files=['initial_data_timetable1.sql'])
async def test_get_timetable_successful(service_client):
    response = await service_client.post('/get-timetable', json={})
    assert response.status_code == 200
    assert 'lessons' in response.json()
    assert response.json()['lessons'] == K_LESSONS

