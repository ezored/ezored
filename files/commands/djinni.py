"""Djinni manager tool"""

import os

from ezored.app import const
from ezored.modules import file
from ezored.modules import log
from ezored.modules import runner
from files.config import djinni as config


# -----------------------------------------------------------------------------
def run(params):
    args = params['args']

    if len(args) > 0:
        action = args[0]

        if action:
            if action == 'generate':
                generate(params)
            else:
                show_help(params)
        else:
            show_help(params)
    else:
        show_help(params)


# -----------------------------------------------------------------------------
def generate(params):
    proj_path = params['proj_path']

    # check djinni folder
    djinni_modules_path = os.path.join(
        proj_path,
        const.DIR_NAME_FILES,
        const.DIR_NAME_DJINNI,
    )

    if not os.path.isdir(djinni_modules_path):
        log.error('Djinni modules folder not exists: {0}'.format(
            djinni_modules_path
        ))

    # get djinni modules
    djinni_config = config.run(proj_path, None, params)
    modules = djinni_config['modules']

    if modules:
        log.info('Generating files for all modules...')

        for module in modules:
            djinni_module_dir = os.path.join(djinni_modules_path, module)
            djinni_module_file = os.path.join(djinni_module_dir, 'generate.py')

            if file.file_exists(djinni_module_file):
                log.info('Generating djinni files for "{0}"...'.format(
                    module
                ))

                runner.run(['python', 'generate.py'], djinni_module_dir)

        log.ok()
    else:
        log.error('No djinni modules to generate')


# -----------------------------------------------------------------------------
def show_help(params):
    log.colored('Available actions:\n', log.PURPLE)
    log.normal('  - generate')


# -----------------------------------------------------------------------------
def get_description(params):
    return 'Djinni manager tool'
