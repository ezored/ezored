"""Module: Target"""

import os

from pygemstones.io import file as f
from pygemstones.system import platform as p
from pygemstones.util import log as l

from files.core import const


# -----------------------------------------------------------------------------
def get_all_targets(proj_path):
    results = []

    targets_path = os.path.join(
        proj_path, const.DIR_NAME_FILES, const.DIR_NAME_FILES_TARGETS
    )

    if not os.path.isdir(targets_path):
        l.e("Target folder not exists: {0}".format(targets_path))

    targets = f.find_dirs(targets_path, "*")

    if targets:
        for target_path in targets:
            target_name = os.path.basename(target_path)

            if target_name:
                results.append(target_name)

    results.sort()

    return results


# -----------------------------------------------------------------------------
def get_all_target_verbs(proj_path, target_name):
    results = []

    target_verbs_list = f.find_files(
        os.path.join(
            proj_path,
            const.DIR_NAME_FILES,
            const.DIR_NAME_FILES_TARGETS,
            target_name,
            const.DIR_NAME_FILES_TARGET_VERBS,
        ),
        "*.py",
    )

    if target_verbs_list:
        for verb_file in target_verbs_list:
            verb_name = os.path.basename(verb_file)
            verb_name = os.path.splitext(verb_name)[0]

            if verb_name:
                results.append(verb_name)

    results.sort()
    return results


# -----------------------------------------------------------------------------
def get_build_profile():
    if p.is_windows():
        return const.PROFILE_BUILD_WINDOWS
    elif p.is_linux():
        return const.PROFILE_BUILD_LINUX
    elif p.is_macos():
        return const.PROFILE_BUILD_MACOS
    else:
        return const.PROFILE_BUILD_DEFAULT
