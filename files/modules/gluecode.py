"""Module: Glue code"""

import os

from files.modules import const
from files.modules import file
from files.modules import log
from files.modules import runner
from files.modules import util

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

        tool_file_path = "{0}".format(tool_file_path)

    return tool_file_path


# -----------------------------------------------------------------------------
def generate(params):
    proj_path = params["proj_path"]
    module_data = params["module_data"]

    if not module_data:
        log.error("Module data is invalid")

    # module data
    module_name = module_data["name"]
    tool_params = module_data["tool_params"]

    module_dir = os.path.join(
        proj_path, const.DIR_NAME_FILES, const.DIR_NAME_GLUECODE, module_name
    )

    # clean old generated src
    file.remove_dir(os.path.join(module_dir, "generated-src"))
    file.remove_dir(os.path.join(module_dir, "yaml"))

    # run
    gluecode_tool_path = get_tool_path(params)

    runner_args = []
    runner_args.extend([gluecode_tool_path])
    runner_args.extend(tool_params)

    runner.run_as_shell(
        args=[" ".join(runner_args)],
        cwd=module_dir,
    )
