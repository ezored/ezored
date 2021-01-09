"""Gluecode manager tool"""

import os
import stat
import importlib

from files.modules import const
from files.modules import file
from files.modules import log
from files.modules import runner
from files.modules import util
from files.modules import net
from files.modules import gluecode
from files.config import gluecode as config


# -----------------------------------------------------------------------------
def run(params):
    args = params["args"]

    if len(args) > 0:
        action = args[0]

        if action:
            if action == "setup":
                setup(params)
            elif action == "generate":
                generate(params)
            elif action == "version":
                version(params)
            else:
                show_help(params)
        else:
            show_help(params)
    else:
        show_help(params)


# -----------------------------------------------------------------------------
def setup(params):
    proj_path = params["proj_path"]

    # version
    version = util.get_arg_value("--version", params["args"])

    if not version or len(version) == 0:
        version = const.GLUECODE_TOOL_VERSION

    log.info("Glue code tool version: {0}".format(version))

    # check tool folder
    tool_dir = os.path.join(proj_path, const.DIR_NAME_BUILD, const.DIR_NAME_GLUECODE)

    file.remove_dir(tool_dir)
    file.create_dir(tool_dir)

    # prepare tool data
    tool_file_path = gluecode.get_tool_path(params)

    if util.is_windows_platform():
        file_url = "https://github.com/cross-language-cpp/djinni-generator/releases/download/v{0}/djinni.bat".format(
            version
        )
    else:
        file_url = "https://github.com/cross-language-cpp/djinni-generator/releases/download/v{0}/djinni".format(
            version
        )

    # prepare tool data
    try:
        net.download(file_url, tool_file_path)

        # add executable permission
        st = os.stat(tool_file_path)
        os.chmod(tool_file_path, st.st_mode | stat.S_IEXEC)
    except Exception as e:
        log.error("Error when download file {0}: {1}".format(file_url, e))

    log.ok()


# -----------------------------------------------------------------------------
def generate(params):
    proj_path = params["proj_path"]

    # check gluecode folder
    gluecode_modules_path = os.path.join(
        proj_path, const.DIR_NAME_FILES, const.DIR_NAME_GLUECODE
    )

    if not os.path.isdir(gluecode_modules_path):
        log.error(
            "Glue code modules folder not exists: {0}".format(gluecode_modules_path)
        )

    # get gluecode modules
    gluecode_config = config.run(proj_path, None, params)
    modules = gluecode_config["modules"]

    if modules:
        log.info("Generating files for all modules...")

        for module in modules:
            log.info('Generating glue code files for "{0}"...'.format(module))

            func_path = "files.gluecode.{0}.generate.run".format(module)
            mod_name, func_name = func_path.rsplit(".", 1)
            mod = importlib.import_module(mod_name)
            func = getattr(mod, func_name)
            func(params)

        log.ok()
    else:
        log.error("No glue code modules to generate")


# -----------------------------------------------------------------------------
def version(params):
    tool_path = gluecode.get_tool_path(params)

    if not os.path.isfile(tool_path):
        log.error("Glue code tool was not found: {0}".format(tool_path))

    runner.run_as_shell("{0} --version".format(tool_path), cwd=os.getcwd())


# -----------------------------------------------------------------------------
def show_help(params):
    log.colored("Available actions:\n", log.PURPLE)
    log.normal("  - setup")
    log.normal("  - generate")
    log.normal("  - version")


# -----------------------------------------------------------------------------
def get_description(params):
    return "Glue code manager tool"
