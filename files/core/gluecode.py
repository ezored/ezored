"""Module: Glue code"""

import os

from files.core import const
from files.core import file
from files.core import log
from files.core import runner
from files.core import util

# -----------------------------------------------------------------------------


def get_tool_path(params):
    proj_path = params["proj_path"]

    if util.is_windows_platform():
        tool_file_path = os.path.join(
            proj_path, const.DIR_NAME_BUILD, const.DIR_NAME_GLUECODE, "djinni.bat"
        )
    else:
        tool_file_path = os.path.join(
            proj_path, const.DIR_NAME_BUILD, const.DIR_NAME_GLUECODE, "djinni"
        )

    return tool_file_path


# -----------------------------------------------------------------------------
def generate(params):
    proj_path = params["proj_path"]
    module_data = params["module_data"]

    if not module_data:
        log.error("Module data is invalid")

    # check required tool
    gluecode_tool_path = get_tool_path(params)

    if not os.path.isfile(gluecode_tool_path):
        log.error(
            "Glue code tool was not found: {0}".format(
                gluecode_tool_path,
            )
        )

    # module data
    module_name = module_data["name"]
    tool_params = module_data["tool_params"]

    module_dir = os.path.join(
        proj_path,
        const.DIR_NAME_FILES,
        const.DIR_NAME_FILES_MODULES,
        module_name,
        const.DIR_NAME_GLUECODE,
    )

    # clean old generated src
    file.remove_dir(os.path.join(module_dir, "generated-src"))
    file.remove_dir(os.path.join(module_dir, "yaml"))

    # run
    runner_args = []
    runner_args.extend([gluecode_tool_path])
    runner_args.extend(tool_params)

    runner.run_as_shell(
        args=" ".join(runner_args),
        cwd=module_dir,
    )
