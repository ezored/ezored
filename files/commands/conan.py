"""Conan manager tool"""

import os

from files.modules import const
from files.modules import file
from files.modules import log
from files.modules import target


# -----------------------------------------------------------------------------
def run(params):
    args = params["args"]

    if len(args) > 0:
        action = args[0]

        if action:
            if action == "install_profiles":
                install_profiles(params)
            else:
                show_help(params)
        else:
            show_help(params)
    else:
        show_help(params)


# -----------------------------------------------------------------------------
def install_profiles(params):
    proj_path = params["proj_path"]
    targets = target.get_all_targets(proj_path)

    log.info("Copying files...")

    if targets:
        for target_item in targets:
            files = file.find_files(
                os.path.join(
                    proj_path,
                    const.DIR_NAME_FILES,
                    const.DIR_NAME_FILES_TARGETS,
                    target_item,
                    const.DIR_NAME_FILES_TARGET_CONAN,
                    const.DIR_NAME_FILES_TARGET_CONAN_PROFILE,
                ),
                "*profile",
            )

            if files:
                conan_profile_dir = os.path.join(
                    file.home_dir(),
                    const.DIR_NAME_HOME_CONAN,
                    const.DIR_NAME_HOME_CONAN_PROFILES,
                )

                for item in files:
                    filename = os.path.basename(item)
                    log.info('Copying profile "{0}"...'.format(filename))

                    file.copy_file(item, os.path.join(conan_profile_dir, filename))

    log.ok()


# -----------------------------------------------------------------------------
def show_help(params):
    log.colored("Available actions:\n", log.PURPLE)
    log.normal("  - install_profiles")


# -----------------------------------------------------------------------------
def get_description(params):
    return "Conan manager tool"
