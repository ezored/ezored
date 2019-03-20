"""Module: Target"""

import os

from ezored import constants as const
from ezored.mod import file
from ezored.mod import runner


# -----------------------------------------------------------------------------
def get_all_targets():
    results = []

    target_dir_list = file.find_dirs_simple(os.path.join(
        file.root_dir(),
        const.DIR_NAME_FILES,
        const.DIR_NAME_FILES_TARGETS,
    ), '*')

    if target_dir_list:
        for target_dir in target_dir_list:
            target_name = os.path.basename(target_dir)

            if target_name:
                results.append(target_name)

    results.sort()
    return results


# -----------------------------------------------------------------------------
def get_all_target_verbs(target_name):
    results = []

    target_verbs_list = file.find_files_simple(os.path.join(
        file.root_dir(),
        const.DIR_NAME_FILES,
        const.DIR_NAME_FILES_TARGETS,
        target_name,
        const.DIR_NAME_FILES_TARGET_VERBS,
    ), '*.py')

    if target_verbs_list:
        for verb_file in target_verbs_list:
            verb_name = os.path.basename(verb_file)
            verb_name = os.path.splitext(verb_name)[0]

            if verb_name:
                results.append(verb_name)

    results.sort()
    return results


# -----------------------------------------------------------------------------
def get_target_config(target_name):
    target_folder = os.path.join(
        file.root_dir(),
        const.DIR_NAME_FILES,
        const.DIR_NAME_FILES_TARGETS,
        target_name,
        const.DIR_NAME_FILES_TARGET_CONFIG,
    )

    target_config_file = os.path.join(
        target_folder,
        const.FILE_NAME_FILES_TARGET_CONFIG,
    )

    if file.file_exists(target_config_file):
        return runner.run_external(
            path=target_folder,
            module_name=const.COMMAND_NAME_CONFIG,
            command_name='run',
            command_params={},
            show_log=False,
            show_error_log=True,
            throw_error=True,
        )

    return {}
