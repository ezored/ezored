"""Module: Runner"""

import importlib
import os
import subprocess
import sys

from files.modules import log


# -----------------------------------------------------------------------------
def run_external(
    path,
    module_name,
    command_name,
    command_params,
    show_log=False,
    show_error_log=False,
    throw_error=False,
):
    """
    Execute external command inside path and return the command result.
    :param path: path where python file is located
    :param module_name: module name
    :param command_name: command name
    :param command_params: command params
    :param show_log: show log
    :param show_error_log: show log if exception
    :param throw_error: throw error if exception
    :return: command result
    """
    result = None

    sys_path = list(sys.path)
    original_cwd = os.getcwd()

    target_module = None
    command = None

    try:
        sys.path.insert(0, path)

        target_module = importlib.import_module(module_name)
        command = getattr(target_module, command_name)

        result = command(params=command_params)

        if show_log:
            log.normal('Command "{0}" finished with success'.format(command_name))
    except Exception as e:
        if show_error_log:
            log.error(
                'Error while call "{0}" on module "{1}": {2}'.format(
                    command_name, module_name, e
                ),
                fatal=(not throw_error),
            )

        if throw_error:
            raise

    finally:
        if module_name in sys.modules:
            del sys.modules[module_name]

        if target_module is not None:
            del target_module

        if command is not None:
            del command

        sys.path = sys_path
        os.chdir(original_cwd)

    return result


# -----------------------------------------------------------------------------
def run(args, cwd):
    ret = subprocess.call(args, cwd=cwd)

    if ret > 0:
        log.normal(
            "{2}COMMAND:{3} {0}\n"
            "{4}WORKING DIR:{5} {1}".format(
                " ".join(args), cwd, log.YELLOW, log.ENDC, log.YELLOW, log.ENDC
            )
        )

        log.error("Command execution has failed")
