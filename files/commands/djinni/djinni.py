"""Djinni manager tool"""

import os

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
    djinni_modules_dir = os.path.join(
        file.root_dir(),
        const.DIR_NAME_FILES,
        const.DIR_NAME_DJINNI,
    )

    modules = runner.run_external(
        path=djinni_modules_dir,
        module_name='modules',
        command_name='get_modules',
        command_params=params,
        show_log=False,
        show_error_log=True,
        throw_error=True,
    )

    if modules:
        log.info('Generating files for all modules...')

        for module in modules:
            djinni_module_dir = os.path.join(djinni_modules_dir, module)
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
def help(params={}):
    log.colored('Available actions:\n', log.PURPLE)
    log.normal('  - generate')


# -----------------------------------------------------------------------------
def get_description(params={}):
    return 'Djinni manager tool'
