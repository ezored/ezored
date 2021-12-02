"""Module: Commands"""

import glob
import importlib
import os
from collections import OrderedDict

from files.core import const

ezored_command_list = OrderedDict()


# -----------------------------------------------------------------------------
def get_all_commands(proj_path, args):
    """
    Create command dictionary

    :param proj_path: project root path
    :param args: call arguments
    """
    # search on project path

    project_command_path = os.path.join(proj_path, const.DIR_NAME_FILES)

    command_list = glob.glob(
        os.path.join(project_command_path, const.DIR_NAME_FILES_COMMANDS, "*.py")
    )

    if command_list:
        for command_path in command_list:
            command_name = os.path.basename(command_path)
            command_name = os.path.splitext(command_name)[0]

            if command_name.startswith("__"):
                continue

            command_package = "{0}.{1}.{2}".format(
                const.DIR_NAME_FILES, const.DIR_NAME_FILES_COMMANDS, command_name
            )
            command_module = importlib.import_module(command_package)

            ezored_command_list[command_name] = command_module


# -----------------------------------------------------------------------------
def run_method(command_name, method, params):
    """Run target with verb"""

    if command_name in ezored_command_list.keys():
        method = getattr(ezored_command_list[command_name], method)
        return method(params)


# -----------------------------------------------------------------------------
def show_help(params):
    """
    Show help message of command

    :param params: parameters
    """
    params["command_name"] = "show_help"
    ezored_command_list["help"].run(params)


# -----------------------------------------------------------------------------
def process_command(proj_path, args):
    """
    Entrypoint to call commands

    :param proj_path: project root path
    :param args: call arguments
    """
    get_all_commands(proj_path, args)

    params = {"args": args, "proj_path": proj_path}

    if len(args) > 0:
        command_name = str(args[0])
        args.pop(0)

        if command_name in ezored_command_list.keys():
            params["command_name"] = command_name
            ezored_command_list[command_name].run(params)
        else:
            show_help(params)
    else:
        show_help(params)
