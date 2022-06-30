"""Gluecode manager tool"""

import importlib
import os
import stat

from pygemstones.io import file as f
from pygemstones.io import net as n
from pygemstones.system import platform as p
from pygemstones.system import runner as r
from pygemstones.type import list as ls
from pygemstones.util import log as l

from files.config import gluecode as config
from files.core import const, gluecode


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
    version = ls.get_arg_list_value(params["args"], "--version")

    if not version or len(version) == 0:
        version = const.GLUECODE_TOOL_VERSION

    l.i("Glue code tool version: {0}".format(version))

    # check tool folder
    tool_dir = os.path.join(proj_path, const.DIR_NAME_BUILD, const.DIR_NAME_GLUECODE)

    f.recreate_dir(tool_dir)

    # prepare tool data
    tool_file_path = gluecode.get_tool_path(params)

    if p.is_windows():
        file_url = "https://github.com/cross-language-cpp/djinni-generator/releases/download/v{0}/djinni.bat".format(
            version
        )
    else:
        file_url = "https://github.com/cross-language-cpp/djinni-generator/releases/download/v{0}/djinni".format(
            version
        )

    # prepare tool data
    try:
        n.download(file_url, tool_file_path)

        # add executable permission
        st = os.stat(tool_file_path)
        os.chmod(tool_file_path, st.st_mode | stat.S_IEXEC)
    except Exception as e:
        l.e("Error when download file {0}: {1}".format(file_url, e))

    l.ok()


# -----------------------------------------------------------------------------
def generate(params):
    proj_path = params["proj_path"]

    # check modules folder
    modules_path = os.path.join(
        proj_path, const.DIR_NAME_FILES, const.DIR_NAME_FILES_MODULES
    )

    if not os.path.isdir(modules_path):
        l.e("Modules folder not exists: {0}".format(modules_path))

    # get gluecode modules
    gluecode_config = config.run(proj_path, None, params)
    modules = gluecode_config["modules"]

    if modules:
        l.i("Generating files for all modules...")

        for m in modules:
            if not os.path.isdir(
                os.path.join(modules_path, m, const.DIR_NAME_GLUECODE)
            ):
                l.i('Module "{0}" was skipped'.format(m))
                continue

            l.i('Generating glue code files for "{0}"...'.format(m))

            func_path = "files.modules.{0}.gluecode.generate.run".format(m)
            mod_name, func_name = func_path.rsplit(".", 1)
            mod = importlib.import_module(mod_name)
            func = getattr(mod, func_name)
            func(params)

        l.ok()
    else:
        l.e("No modules to generate")


# -----------------------------------------------------------------------------
def version(params):
    tool_path = gluecode.get_tool_path(params)

    if not os.path.isfile(tool_path):
        l.e("Glue code tool was not found: {0}".format(tool_path))

    r.run("{0} --version".format(tool_path), cwd=os.getcwd(), shell=True)


# -----------------------------------------------------------------------------
def show_help(params):
    l.colored("Available actions:\n", l.MAGENTA)
    l.m("  - setup")
    l.m("  - generate")
    l.m("  - version")


# -----------------------------------------------------------------------------
def get_description(params):
    return "Glue code manager tool"
