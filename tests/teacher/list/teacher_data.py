K_TEACHER = {
    "id": "241416c7-9654-4814-b36b-7d39c1ddded2",
    "fio": "John Doe",
    "bio": "Professor of Mathematics",
    "department_id": "1f93ceb4-d931-4b66-a0e5-7323d6b60f3b",
    "department_name": "Department of Applied Mathematics",
    "faculty_id": "bbc6312c-f25e-4db3-b2a0-3f5dc6717a8d",
    "faculty_name": "Faculty of Mathematics and Mechanics"
}

K_FIELDS_TEACHER_IDS = [
    ('teacher_ids', ['241416c7'], True),
    ('teacher_ids', ['9999'], False),
    ('teacher_ids', ['241416c7', '9999'], True),
]

K_IDS_TEACHER_IDS = [
    'teacher_ids_true',
    'teacher_ids_false',
    'teacher_ids_many'
]

K_FIELDS_TEACHER_FIOS = [
    ('teacher_fios', ['John'], True),
    ('teacher_fios', ['Frank'], False),
    ('teacher_fios', ['Frank', 'John'], True),
]

K_IDS_TEACHER_FIOS = [
    'teacher_fios_true',
    'teacher_fios_false',
    'teacher_fios_many'
]

K_FIELDS_TEACHER_BIOS = [
    ('teacher_bios', ['Professor'], True),
    ('teacher_bios', ['Teacher'], False),
    ('teacher_bios', ['Teacher', 'Professor'], True),
]

K_IDS_TEACHER_BIOS = [
    'teacher_bios_true',
    'teacher_bios_false',
    'teacher_bios_many'
]

K_FIELDS_DEPARTMENT_IDS = [
    ('department_ids', ['1f93'], True),
    ('department_ids', ['1111'], False),
    ('department_ids', ['1111', '1f93'], True)
]

K_IDS_DEPARTMENT_IDS = [
    'department_ids_true',
    'department_ids_false',
    'department_ids_many'
]

K_FIELDS_DEPARTMENT_NAMES = [
    ('department_names', ['Mathematics'], True),
    ('department_names', ['Roman'], False),
    ('department_names', ['Roman', 'Mathematics'], True)
]

K_IDS_DEPARTMENT_NAMES = [
    'department_names_true',
    'department_names_false',
    'department_names_many'
]

K_FIELDS_FACULTY_IDS = [
    ('faculty_ids', ['bbc6312'], True),
    ('faculty_ids', ['6666'], False),
    ('faculty_ids', ['6666', 'bbc6312'], True)
]

K_IDS_FACULTY_IDS = [
    'faculty_ids_true',
    'faculty_ids_false',
    'faculty_ids_many'
]

K_FIELDS_FACULTY_NAMES = [
    ('faculty_names', ['Mathematics'], True),
    ('faculty_names', ['Roman'], False),
    ('faculty_names', ['Roman', 'Mathematics'], True)
]

K_IDS_FACULTY_NAMES = [
    'faculty_names_true',
    'faculty_names_false',
    'faculty_names_many'
]

K_FIELDS = K_FIELDS_TEACHER_IDS \
    + K_FIELDS_TEACHER_FIOS\
    + K_FIELDS_TEACHER_BIOS\
    + K_FIELDS_DEPARTMENT_IDS\
    + K_FIELDS_DEPARTMENT_NAMES\
    + K_FIELDS_FACULTY_IDS\
    + K_FIELDS_FACULTY_NAMES

K_IDS = K_IDS_TEACHER_IDS \
    + K_IDS_TEACHER_FIOS\
    + K_IDS_TEACHER_BIOS\
    + K_IDS_DEPARTMENT_IDS\
    + K_IDS_DEPARTMENT_NAMES\
    + K_IDS_FACULTY_IDS\
    + K_IDS_FACULTY_NAMES
