"""Cleanup the workspace"""

import os

import ezored.functions as fn
import ezored.logging as log


# -----------------------------------------------------------------------------
def run(params={}):
    log.info('Cleaning...')
    fn.remove_dir(os.path.join(fn.root_dir(), 'build'))
    fn.purge_files(fn.root_dir(), '*.pyc')
    fn.purge_files(fn.root_dir(), 'Thumbs.db')
    fn.purge_files(fn.root_dir(), '.DS_Store')
    fn.purge_dirs(fn.root_dir(), '__pycache__')
    log.ok('')


# -----------------------------------------------------------------------------
def help(params={}):
    return ''


# -----------------------------------------------------------------------------
def get_description(params={}):
    return 'Cleanup the workspace'
