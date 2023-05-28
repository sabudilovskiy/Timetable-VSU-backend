K_FACULTY = {
    'id' : 'bbc6312c-f25e-4db3-b2a0-3f5dc6717a8d',
    'name' : 'Faculty of Mathematics and Mechanics'
}

K_IDS_FIELDS = [
    ('ids', ['bbc6312c'], True),
    ('ids', ['bbbbb'], False),
    ('ids', ['bbbbb', 'bbc6312c'], True),
]

K_IDS_IDS = [
    'ids_true', 'ids_false', 'ids_many'
]

K_NAMES_FIELDS = [
    ('names', ['Math'], True),
    ('names', ['Russian'], False),
    ('names', ['Russian', 'Math'], True),
]

K_NAMES_IDS = [
    'names_true', 'names_false', 'names_many'
]

K_FIELDS = K_IDS_FIELDS + K_NAMES_FIELDS
K_IDS = K_IDS_IDS + K_NAMES_IDS