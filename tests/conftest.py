import pathlib
import os
from datetime import datetime
import pytest

from testsuite.databases.pgsql import discover
from _pytest.assertion import truncate

truncate.DEFAULT_MAX_LINES = 9999
truncate.DEFAULT_MAX_CHARS = 9999

pytest_plugins = ['pytest_userver.plugins.postgresql']


@pytest.hookimpl
def pytest_runtest_setup(item):
    logging_plugin = item.config.pluginmanager.get_plugin("logging-plugin")
    timestamp = datetime.strftime(datetime.now(), '%Y-%m-%d_%H-%M-%S')
    path = 'results'
    if item.cls is not None:
        path = os.path.join(path, item.cls.__name__)
    logging_plugin.set_log_path(os.path.join(
        path, f'{item.name}_{timestamp}.log'))


@pytest.fixture(scope='session')
def service_source_dir():
    """Path to root directory service."""
    return pathlib.Path(__file__).parent.parent


@pytest.fixture(scope='session')
def initial_data_path(service_source_dir):
    """Path for find files with data"""
    return [
        service_source_dir / 'postgresql/data',
    ]


@pytest.fixture(scope='session')
def pgsql_local(service_source_dir, pgsql_local_create):
    """Create schemas databases for tests"""
    databases = discover.find_schemas(
        'timetable_vsu_backend',  # service name that goes to the DB connection
        [service_source_dir.joinpath('postgresql/schemas')],
    )
    return pgsql_local_create(list(databases.values()))
