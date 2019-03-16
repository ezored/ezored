"""Conan manager tool"""

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
            if action == 'install_profiles':
                install_profiles(params)
            else:
                help(params)
        else:
            help(params)
    else:
        help(params)


# -----------------------------------------------------------------------------
def install_profiles(params={}):
    log.info('Copying files...')

    targets = fn.get_all_targets()

    if targets:
        for target in targets:
            files = fn.find_files(os.path.join(
                fn.root_dir(),
                const.DIR_NAME_FILES,
                const.DIR_NAME_FILES_TARGETS,
                target,
                const.DIR_NAME_FILES_TARGET_CONAN,
                const.DIR_NAME_FILES_TARGET_CONAN_PROFILE,
            ), '*profile')

            if files:
                conan_profile_dir = os.path.join(
                    fn.home_dir(),
                    const.DIR_NAME_HOME_CONAN,
                    const.DIR_NAME_HOME_CONAN_PROFILES
                )

                for item in files:
                    filename = os.path.basename(item)
                    log.info('Copying profile "{0}"...'.format(filename))

                    fn.copy_file(item, os.path.join(
                        conan_profile_dir,
                        filename
                    ))

    log.ok()


# -----------------------------------------------------------------------------
def help(params={}):
    log.colored('Available actions:\n', log.PURPLE)
    log.normal('  - install_profiles')


# -----------------------------------------------------------------------------
def get_description(params={}):
    return 'Conan manager tool'
