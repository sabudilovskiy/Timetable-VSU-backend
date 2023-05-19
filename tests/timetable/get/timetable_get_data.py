K_LESSON = {
    "id": "3d04fc36-ab71-42db-9e38-efd792afa7ba",  # +
    "begin": "2023-04-01T05:30:00+0000",  # +
    "end": "2023-05-01T07:05:00+0000",  # +
    "number": 1,  # +
    "type": "lection",  # +
    "week_type": "all",  # +
    "subgroup": "all",  # +
    "day": "monday",  # +
    "room_id": "f245127f-a730-4d13-a15d-7648deb1d4d2",  # +
    "room_name": "101",  # +
    "subject_id": "053222c5-315a-4301-abfe-586d2409fcd3",
    "subject_name": "Mathematics",  # +
    "group_id": "4148147a-740b-48f9-aba1-47eb17432855",  # +
    "group_course": 1,  # +
    "group_name": "MM-21",  # +
    "group_type": "magistracy",  # +
    "faculty_id": "bbc6312c-f25e-4db3-b2a0-3f5dc6717a8d",  # +
    "faculty_name": "Faculty of Mathematics and Mechanics",  # +
    "department_id": "1f93ceb4-d931-4b66-a0e5-7323d6b60f3b",  # +
    "department_name": "Department of Applied Mathematics",  # +
    "teacher_id": "241416c7-9654-4814-b36b-7d39c1ddded2",  # +
    "teacher_fio": "John Doe",  # +
    "teacher_bio": "Professor of Mathematics"  # +
}

K_FIELDS_SUBJECT_IDS = [
    ('subject_ids', ['053222c5-315a-4301-abfe-586d2409fcd3'], True),
    ('subject_ids', ['22244447-9654-4814-b36b-7d39c1ddded2'], False),
    ('subject_ids', ['22244447-9654-4814-b36b-7d39c1ddded2',
     '053222c5-315a-4301-abfe-586d2409fcd3'], True),
]

K_IDS_SUBJECT_IDS = [
    'subject_ids_true',
    'subject_ids_false',
    'subject_ids_many'
]

K_FIELDS_TEACHER_BIOS = [
    ('teacher_bios', ['Professor of Mathematics'], True),
    ('teacher_bios', ['Uskova'], False),
    ('teacher_bios', ['Uskova', 'Professor of Mathematics'], True)
]

K_IDS_TEACHER_BIOS = [
    'teacher_bios_true',
    'teacher_bios_false',
    'teacher_bios_many'
]

K_FIELDS_GROUP_TYPES = [
    ('group_types', ['magistracy'], True),
    ('group_types', ['postgraduate'], False),
    ('group_types', ['postgraduate', 'magistracy'], True)
]

K_IDS_GROUP_TYPES = [
    'group_types_true',
    'group_types_false',
    'group_types_many'
]

K_FIELDS_GROUP_COURSES = [
    ('group_courses', [1], True),
    ('group_courses', [2], False),
    ('group_courses', [2, 1], True)
]

K_IDS_GROUP_COURSES = [
    'group_courses_true',
    'group_courses_false',
    'group_courses_many'
]

K_FIELDS_ROOM_IDS = [
    ('room_ids', ['f245127f-a730-4d13-a15d-7648deb1d4d2'], True),
    ('room_ids', ['22244447-9654-4814-b36b-7d39c1ddded2'], False),
    ('room_ids', ['22244447-9654-4814-b36b-7d39c1ddded2',
     'f245127f-a730-4d13-a15d-7648deb1d4d2'], True),
]

K_IDS_ROOM_IDS = [
    'room_ids_true',
    'room_ids_false',
    'room_ids_many'
]

K_FIELDS_LESSON_IDS = [
    ('lesson_ids', ['3d04fc36-ab71-42db-9e38-efd792afa7ba'], True),
    ('lesson_ids', ['22244447-9654-4814-b36b-7d39c1ddded2'], False),
    ('lesson_ids', ['22244447-9654-4814-b36b-7d39c1ddded2',
     '3d04fc36-ab71-42db-9e38-efd792afa7ba'], True),
]

K_IDS_LESSON_IDS = [
    'lesson_ids_true',
    'lesson_ids_false',
    'lesson_ids_many'
]

K_FIELDS_NUMBERS = [
    ('numbers', [1], True),
    ('numbers', [2], False),
    ('numbers', [2, 1], True)
]

K_IDS_NUMBERS = [
    'numbers_true',
    'numbers_false',
    'numbers_many'
]

K_FIELDS_FACULTY_NAMES = [
    ('faculty_names', ['Faculty of Mathematics and Mechanics'], True),
    ('faculty_names', ['RGF'], False),
    ('faculty_names', ['RGF', 'Faculty of Mathematics and Mechanics'], True)
]

K_IDS_FACULTY_NAMES = [
    'faculty_names_true',
    'faculty_names_false',
    'faculty_names_many'
]

K_FIELDS_SUBJECT_NAMES = [
    ('subject_names', ['Mathematics'], True),
    ('subject_names', ['Russian'], False),
    ('subject_names', ['Russian', 'Mathematics'], True)
]

K_IDS_SUBJECT_NAMES = [
    'subject_names_true',
    'subject_names_false',
    'subject_names_many'
]

K_FIELDS_GROUP_NAMES = [
    ('group_names', ['MM-21'], True),
    ('group_names', ['62'], False),
    ('group_names', ['62', 'MM-21'], True)
]

K_IDS_GROUP_NAMES = [
    'group_names_true',
    'group_names_false',
    'group_names_many'
]

K_FIELDS_GROUP_IDS = [
    ('group_ids', ['4148147a-740b-48f9-aba1-47eb17432855'], True),
    ('group_ids', ['22244447-9654-4814-b36b-7d39c1ddded2'], False),
    ('group_ids', ['22244447-9654-4814-b36b-7d39c1ddded2',
     '4148147a-740b-48f9-aba1-47eb17432855'], True),
]

K_IDS_GROUP_IDS = [
    'group_ids_true',
    'group_ids_false',
    'group_ids_many'
]

K_FIELDS_TEACHER_FIOS = [
    ('teacher_fios', ['John Doe'], True),
    ('teacher_fios', ['Uskova'], False),
    ('teacher_fios', ['Uskova', 'John Doe'], True)
]

K_IDS_TEACHER_FIOS = [
    'teacher_fios_true',
    'teacher_fios_false',
    'teacher_fios_many'
]

K_FIELDS_TEACHER_IDS = [
    ('teacher_ids', ['241416c7-9654-4814-b36b-7d39c1ddded2'], True),
    ('teacher_ids', ['22244447-9654-4814-b36b-7d39c1ddded2'], False),
    ('teacher_ids', ['22244447-9654-4814-b36b-7d39c1ddded2',
     '241416c7-9654-4814-b36b-7d39c1ddded2'], True),
]

K_IDS_TEACHER_IDS = [
    'teacher_ids_true',
    'teacher_ids_false',
    'teacher_ids_many'
]

K_FIELDS_ROOM_NAMES = [
    ('room_names', ['101'], True),
    ('room_names', ['201'], False),
    ('room_names', ['201', '101'], True)
]

K_IDS_ROOM_NAMES = [
    'room_names_true',
    'room_names_false',
    'room_names_many'
]

K_FIELDS_FACULTY_IDS = [
    ('faculty_ids', ['bbc6312c-f25e-4db3-b2a0-3f5dc6717a8d'], True),
    ('faculty_ids', ['bbcccccc-f25e-4db3-b2a0-3f5dc6717a8d'], False),
    ('faculty_ids', ['bbcccccc-f25e-4db3-b2a0-3f5dc6717a8d',
     'bbc6312c-f25e-4db3-b2a0-3f5dc6717a8d'], True)
]

K_IDS_FACULTY_IDS = [
    'faculty_ids_true',
    'faculty_ids_false',
    'faculty_ids_many'
]

K_FIELDS_BEGIN = [
    ('begin', '2023-04-01T05:30:00+0000', True),
    ('begin', '2023-06-01T05:30:00+0000', False)
]

K_IDS_BEGIN = [
    'begin_true',
    'begin_false'
]

K_FIELDS_END = [
    ('end', '2023-06-01T05:30:00+0000', True),
    ('end', '2023-03-01T05:30:00+0000', False)
]

K_IDS_END = [
    'end_true',
    'end_false'
]

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
    ('department_ids', ['11111111-d931-4b66-a0e5-7323d6b60f1b'], False),
    ('department_ids', ['11111111-d931-4b66-a0e5-7323d6b60f1b',
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

K_FIELDS = K_FIELDS_DAYS \
    + K_FIELDS_DEPARTMENT_IDS \
    + K_FIELDS_DEPARTMENT_NAMES \
    + K_FIELDS_SUBGROUP \
    + K_FIELDS_WEEK_TYPE \
    + K_FIELDS_LESSON_TYPE \
    + K_FIELDS_BEGIN \
    + K_FIELDS_END \
    + K_FIELDS_FACULTY_IDS \
    + K_FIELDS_ROOM_NAMES \
    + K_FIELDS_TEACHER_IDS \
    + K_FIELDS_TEACHER_FIOS \
    + K_FIELDS_GROUP_IDS \
    + K_FIELDS_GROUP_NAMES \
    + K_FIELDS_SUBJECT_NAMES \
    + K_FIELDS_FACULTY_NAMES \
    + K_FIELDS_NUMBERS \
    + K_FIELDS_LESSON_IDS \
    + K_FIELDS_ROOM_IDS \
    + K_FIELDS_GROUP_COURSES \
    + K_FIELDS_GROUP_TYPES \
    + K_FIELDS_SUBJECT_IDS

K_IDS = K_IDS_DAYS \
    + K_IDS_DEPARTMENT_IDS \
    + K_IDS_DEPARTMENT_NAMES \
    + K_IDS_SUBGROUP \
    + K_IDS_WEEK_TYPE \
    + K_IDS_LESSON_TYPE \
    + K_IDS_BEGIN \
    + K_IDS_END \
    + K_IDS_FACULTY_IDS \
    + K_IDS_ROOM_NAMES \
    + K_IDS_TEACHER_IDS \
    + K_IDS_TEACHER_FIOS \
    + K_IDS_GROUP_IDS \
    + K_IDS_GROUP_NAMES \
    + K_IDS_SUBJECT_NAMES \
    + K_IDS_FACULTY_NAMES \
    + K_IDS_NUMBERS \
    + K_IDS_LESSON_IDS \
    + K_IDS_ROOM_IDS \
    + K_IDS_GROUP_COURSES \
    + K_IDS_GROUP_TYPES \
    + K_IDS_SUBJECT_IDS

K_FIELDS_LIKE = K_FIELDS_LESSON_IDS \
    + K_FIELDS_ROOM_IDS \
    + K_FIELDS_ROOM_NAMES \
    + K_FIELDS_SUBJECT_IDS \
    + K_FIELDS_SUBJECT_NAMES \
    + K_FIELDS_GROUP_IDS \
    + K_FIELDS_GROUP_NAMES \
    + K_FIELDS_FACULTY_IDS \
    + K_FIELDS_FACULTY_NAMES \
    + K_FIELDS_DEPARTMENT_IDS \
    + K_FIELDS_DEPARTMENT_NAMES \
    + K_FIELDS_TEACHER_IDS \
    + K_FIELDS_TEACHER_FIOS \
    + K_FIELDS_TEACHER_BIOS

K_IDS_LIKE = K_IDS_LESSON_IDS \
    + K_IDS_ROOM_IDS \
    + K_IDS_ROOM_NAMES \
    + K_IDS_SUBJECT_IDS \
    + K_IDS_SUBJECT_NAMES \
    + K_IDS_GROUP_IDS \
    + K_IDS_GROUP_NAMES \
    + K_IDS_FACULTY_IDS \
    + K_IDS_FACULTY_NAMES \
    + K_IDS_DEPARTMENT_IDS \
    + K_IDS_DEPARTMENT_NAMES \
    + K_IDS_TEACHER_IDS \
    + K_IDS_TEACHER_FIOS \
    + K_IDS_TEACHER_BIOS
