K_LESSON = {
    "id": "3d04fc36-ab71-42db-9e38-efd792afa7ba",
    "begin": "2023-09-01T05:30:00+0000",
    "end": "2023-09-01T07:05:00+0000",
    "number": 1,
    "type": "lection", #+
    "week_type": "all", #+
    "subgroup": "all", #+
    "day": "monday", #+
    "room_id": "f245127f-a730-4d13-a15d-7648deb1d4d2",
    "room_name": "101",
    "subject_id": "053222c5-315a-4301-abfe-586d2409fcd3",
    "subject_name": "Mathematics",
    "group_id": "4148147a-740b-48f9-aba1-47eb17432855",
    "group_course": 1,
    "group_name": "MM-21",
    "group_type": "magistracy",
    "faculty_id": "bbc6312c-f25e-4db3-b2a0-3f5dc6717a8d",
    "faculty_name": "Faculty of Mathematics and Mechanics",
    "department_id": "1f93ceb4-d931-4b66-a0e5-7323d6b60f3b", #+
    "department_name": "Department of Applied Mathematics", #+
    "teacher_id": "241416c7-9654-4814-b36b-7d39c1ddded2",
    "teacher_fio": "John Doe",
    "teacher_bio": "Professor of Mathematics"
}

K_FIELDS_LESSON_TYPE = [
    ('lesson_type', 'lection', True),
    ('lesson_type', 'practice', False),
]

K_IDS_LESSON_TYPE = [
    'lesson_type_true',
    'lesson_type_false'
]

K_FIELDS_WEEK_TYPE = [
    ('week_type', 'all', True),
    ('week_type', 'odd', False),
]

K_IDS_WEEK_TYPE = [
    'week_type_true',
    'week_type_false'
]

K_FIELDS_SUBGROUP = [
     ('subgroup', 'all', True),
     ('subgroup', 'second', False),
]

K_IDS_SUBGROUP = [
    'subgroup_true',
    'subgroup_false'
]

K_FIELDS_DAYS = [
    ('days', ['monday'], True),
    ('days', ['tuesday'], False),
    ('days', ['monday', 'tuesday'], True)
]

K_IDS_DAYS = [
    'days_true',
    'days_false',
    'days_many_true',
]

K_FIELDS_DEPARTMENT_IDS = [
    ('department_ids', ['1f93ceb4-d931-4b66-a0e5-7323d6b60f3b'], True),
    ('department_ids', ['1f93ceb4-d931-4b66-a0e5-7323d6b60f1b'], False),
    ('department_ids', ['1f93ceb4-d931-4b66-a0e5-7323d6b60f1b',
                        '1f93ceb4-d931-4b66-a0e5-7323d6b60f3b'], True),
]

K_IDS_DEPARTMENT_IDS = [
    'dep_ids_true',
    'dep_ids_false',
    'dep_ids_many_true',
]

K_FIELDS_DEPARTMENT_NAMES = [
    ('department_names', ['Department of Applied Mathematics'], True),
    ('department_names', ['Another Department'], False),
    ('department_names', ['Another Department',
                          'Department of Applied Mathematics'], True),
]

K_IDS_DEPARTMENT_NAMES = [
    'dep_names_true',
    'dep_names_false',
    'dep_names_many_true',
]

K_FIELDS = K_FIELDS_DAYS + K_FIELDS_DEPARTMENT_IDS + K_FIELDS_DEPARTMENT_NAMES + K_FIELDS_SUBGROUP + K_FIELDS_WEEK_TYPE + K_FIELDS_LESSON_TYPE

K_IDS = K_IDS_DAYS + K_IDS_DEPARTMENT_IDS + K_IDS_DEPARTMENT_NAMES + K_IDS_SUBGROUP + K_IDS_WEEK_TYPE + K_IDS_LESSON_TYPE
