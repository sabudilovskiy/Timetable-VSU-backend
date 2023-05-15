K_ADMIN = {
    'login': 'some_admin',
    'user_id': '333111c7-9654-4814-b36b-7d39c1ddded2',
    'admin_id': '000111c7-9654-4814-b36b-7d39c1ddded2'
}

K_LOGIN_IDS = [
    'logins_true', 'logins_false', 'logins_many'
]

K_LOGIN_FIELDS = [
    ('logins', ['some_admin'], True),
    ('logins', ['some_user'], False),
    ('logins', ['some_user', 'some_admin'], True),
]

K_USER_IDS_IDS = [
    'user_ids_true', 'user_ids_false', 'user_ids_many'
]

K_USER_IDS_FIELDS = [
    ('user_ids', ['333111c7-9654-4814-b36b-7d39c1ddded2'], True),
    ('user_ids', ['ddd111c7-9654-4814-b36b-7d39c1ddded2'], False),
    ('user_ids', ['ddd111c7-9654-4814-b36b-7d39c1ddded2',
     '333111c7-9654-4814-b36b-7d39c1ddded2'], True),
]

K_ADMIN_IDS_IDS = [
    'admin_ids_true', 'admin_ids_false', 'admin_ids_many'
]

K_ADMIN_IDS_FIELDS = [
    ('admin_ids', ['000111c7-9654-4814-b36b-7d39c1ddded2'], True),
    ('admin_ids', ['ddd111c7-9654-4814-b36b-7d39c1ddded2'], False),
    ('admin_ids', ['ddd111c7-9654-4814-b36b-7d39c1ddded2',
     '000111c7-9654-4814-b36b-7d39c1ddded2'], True),
]

K_IDS = K_LOGIN_IDS + K_ADMIN_IDS_IDS + K_USER_IDS_IDS

K_FIELDS = K_LOGIN_FIELDS + K_ADMIN_IDS_FIELDS + K_USER_IDS_FIELDS
