"""Djinni manager tool"""

import os

import ezored.functions as fn
import ezored.logging as log
from ezored import constants as const


# -----------------------------------------------------------------------------
def run(params={}):
    args = params['args']

    if len(args) > 0:
        action = args[0]

        if action:
            if action == 'generate':
                generate(params)
            else:
                help(params)
        else:
            help(params)
    else:
        help(params)


# -----------------------------------------------------------------------------
def generate(params={}):
    dirs = fn.find_dirs_simple(os.path.join(
        fn.root_dir(),
        const.DIR_NAME_FILES,
        const.DIR_NAME_DJINNI),
        '*'
    )

    if dirs:
        log.info('Generating files for all modules...')
        dirs.sort()

        for item in dirs:
            if fn.file_exists(os.path.join(item, 'generate.py')):
                dir_name = os.path.basename(item)
                log.info('Generating djinni files for "{0}"...'.format(dir_name))
                fn.run_simple(['python', 'generate.py'], item)

        log.ok()
    else:
        log.error('No djinni modules to generate')


# -----------------------------------------------------------------------------
def help(params={}):
    log.colored('Available actions:\n', log.PURPLE)
    log.normal('  - generate')


# -----------------------------------------------------------------------------
def get_description(params={}):
    return 'Djinni manager tool'
