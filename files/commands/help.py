"""List all commands"""

import sys

from pygemstones.util import log as l

from files.core import command
from files.core.command import ezored_command_list


# -----------------------------------------------------------------------------
def run(params):
    args = params["args"]

    l.colored(
        'Please use "python {0} <command>" where <command> is one of:\n'.format(
            sys.argv[0]
        ),
        l.MAGENTA,
    )

    command_key_list = ezored_command_list.keys()
    width = max(len(name) for name in command_key_list)

    for command_name in command_key_list:
        params = {"args": args, "command_name": command_name}

        description = command.run_method(command_name, "get_description", params)

        print(
            "  {name:{width}}  {descr}".format(
                name=command_name, width=width, descr=description
            )
        )


# -----------------------------------------------------------------------------
def show_help(params):
    """
    :type params: dict
    """
    pass


# -----------------------------------------------------------------------------
def get_description(params):
    """
    :type params: dict
    """
    return "List all commands"
