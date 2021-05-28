"""Gluecode manager tool"""

import os
import stat
import importlib

from files.core import const
from files.core import file
from files.core import log
from files.core import runner
from files.core import util
from files.core import net
from files.core import gluecode
from files.core import module


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

    # check modules folder
    modules_path = os.path.join(
        proj_path, const.DIR_NAME_FILES, const.DIR_NAME_FILES_MODULES
    )

    if not os.path.isdir(modules_path):
        log.error("Modules folder not exists: {0}".format(modules_path))

    # get gluecode modules
    modules = module.get_list(proj_path)

    if modules:
        log.info("Generating files for all modules...")

        for m in modules:
            if not os.path.isdir(
                os.path.join(modules_path, m, const.DIR_NAME_GLUECODE)
            ):
                log.info('Module "{0}" was skipped'.format(m))
                continue

            log.info('Generating glue code files for "{0}"...'.format(m))

            func_path = "files.modules.{0}.gluecode.generate.run".format(m)
            mod_name, func_name = func_path.rsplit(".", 1)
            mod = importlib.import_module(mod_name)
            func = getattr(mod, func_name)
            func(params)

        log.ok()
    else:
        log.error("No modules to generate")


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
