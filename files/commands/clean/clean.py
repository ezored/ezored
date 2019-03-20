"""Cleanup the workspace"""

import os

from ezored.mod import file
from ezored.mod import log


# -----------------------------------------------------------------------------
def run(params={}):
    log.info('Cleaning...')
    file.remove_dir(os.path.join(file.root_dir(), 'build'))
    file.purge_files(file.root_dir(), '*.pyc')
    file.purge_files(file.root_dir(), 'Thumbs.db')
    file.purge_files(file.root_dir(), '.DS_Store')
    file.purge_dirs(file.root_dir(), '__pycache__')
    log.ok('')


# -----------------------------------------------------------------------------
def help(params={}):
    return ''


# -----------------------------------------------------------------------------
def get_description(params={}):
    return 'Cleanup the workspace'
