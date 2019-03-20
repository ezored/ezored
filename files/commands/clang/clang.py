"""Clang manager tool"""

import os
import subprocess

from ezored import constants as const
from ezored.mod import file
from ezored.mod import log
from ezored.mod import runner


# -----------------------------------------------------------------------------
def run(params={}):
    args = params['args']

    if len(args) > 0:
        action = args[0]

        if action:
            if action == 'format':
                clang_format(params)
            else:
                help(params)
        else:
            help(params)
    else:
        help(params)


# -----------------------------------------------------------------------------
def clang_format(params={}):
    check_clang_format()

    dir_list = [
        {
            'path': os.path.join(
                file.root_dir(),
                const.DIR_NAME_FILES,
                const.DIR_NAME_FILES_SRC,
            ),
            'patterns': ['*.cpp', '*.hpp']
        },
        {
            'path': os.path.join(
                file.root_dir(),
                const.DIR_NAME_PROJECTS,
            ),
            'patterns': ['*.cpp', '*.hpp']
        }
    ]

    if dir_list:
        log.info('Formating files...')

        for dir_item in dir_list:
            patterns = dir_item['patterns']

            for pattern_item in patterns:
                files = file.find_files(dir_item['path'], pattern_item)

                for file_item in files:
                    log.info('Formatting file "{0}"...'.format(
                        os.path.relpath(file_item)
                    ))

                    run_args = [
                        'clang-format',
                        '-style',
                        'file',
                        '-i',
                        file_item,
                    ]

                    runner.run(
                        run_args,
                        file.root_dir()
                    )

        log.ok()
    else:
        log.error('No djinni modules to generate')


# -----------------------------------------------------------------------------
def check_clang_format():
    """Checks if invoking supplied clang-format binary works."""
    try:
        subprocess.check_output(['clang-format', '--version'])
    except OSError:
        log.error('Clang-format is not installed')


# -----------------------------------------------------------------------------
def help(params={}):
    log.colored('Available actions:\n', log.PURPLE)
    log.normal('  - format')


# -----------------------------------------------------------------------------
def get_description(params={}):
    return 'Clang manager tool'
