"""Conan manager tool"""

import os

from files.modules import const
from files.modules import file
from files.modules import log
from files.modules import runner
from files.modules import target


# -----------------------------------------------------------------------------
def run(params):
    args = params["args"]

    if len(args) > 0:
        action = args[0]

        if action:
            if action == "setup":
                setup(params)
            else:
                show_help(params)
        else:
            show_help(params)
    else:
        show_help(params)


# -----------------------------------------------------------------------------
def setup(params):
    proj_path = params["proj_path"]
    targets = target.get_all_targets(proj_path)

    log.info("Creating default profile...")

    # create default profile
    runner.run(
        [
            "conan",
            "profile",
            "new",
            "default",
            "--detect",
            "--force",
        ],
        cwd=os.getcwd(),
    )

    # copy all targets profile
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

    # add darwin toolchain
    log.info("Adding darwin toolchain repository...")

    runner.run(
        [
            "conan",
            "remote",
            "add",
            "darwin-toolchain",
            "https://api.bintray.com/conan/ezored/conan-darwin-toolchain",
            "--force",
        ],
        cwd=os.getcwd(),
    )

    log.ok()


# -----------------------------------------------------------------------------
def show_help(params):
    log.colored("Available actions:\n", log.PURPLE)
    log.normal("  - setup")


# -----------------------------------------------------------------------------
def get_description(params):
    return "Conan manager tool"
