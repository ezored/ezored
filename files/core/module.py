"""Module: Module"""

from files.core import file
from files.core import const
import os

# -----------------------------------------------------------------------------
def get_list(proj_path):
    module_dir = os.path.join(
        proj_path, const.DIR_NAME_FILES, const.DIR_NAME_FILES_MODULES
    )

    modules_found = file.find_dirs_simple(module_dir, "*")
    modules = []

    for m in modules_found:
        module_dir_name = os.path.basename(m)

        if module_dir_name == "support-lib":
            # support lib already have their files
            continue

        modules.append(module_dir_name)

    return modules
