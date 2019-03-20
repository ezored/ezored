"""Conan manager tool"""

import os

from ezored import constants as const
from ezored.mod import file
from ezored.mod import log
from ezored.mod import target


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

    targets = target.get_all_targets()

    if targets:
        for target_item in targets:
            files = file.find_files(os.path.join(
                file.root_dir(),
                const.DIR_NAME_FILES,
                const.DIR_NAME_FILES_TARGETS,
                target_item,
                const.DIR_NAME_FILES_TARGET_CONAN,
                const.DIR_NAME_FILES_TARGET_CONAN_PROFILE,
            ), '*profile')

            if files:
                conan_profile_dir = os.path.join(
                    file.home_dir(),
                    const.DIR_NAME_HOME_CONAN,
                    const.DIR_NAME_HOME_CONAN_PROFILES
                )

                for item in files:
                    filename = os.path.basename(item)
                    log.info('Copying profile "{0}"...'.format(filename))

                    file.copy_file(item, os.path.join(
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
