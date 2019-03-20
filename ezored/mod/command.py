"""Module: Command"""

import os

from ezored import constants as const
from ezored.mod import file
from ezored.mod import runner


# -----------------------------------------------------------------------------
def get_all_commands():
    results = []

    command_list = file.find_dirs_simple(os.path.join(
        file.root_dir(),
        const.DIR_NAME_FILES,
        const.DIR_NAME_FILES_COMMANDS,
    ), '*')

    if command_list:
        for command_dir in command_list:
            command_name = os.path.basename(command_dir)

            if command_name:
                results.append(command_name)

    results.sort()
    return results


# -----------------------------------------------------------------------------
def run_method(command_name, method, params):
    """Run target with verb"""

    commands = get_all_commands()

    if command_name in commands:
        command_folder = os.path.join(
            file.root_dir(),
            const.DIR_NAME_FILES,
            const.DIR_NAME_FILES_COMMANDS,
            command_name,
        )

        return runner.run_external(
            path=command_folder,
            module_name=command_name,
            command_name=method,
            command_params=params,
            show_log=False,
            show_error_log=True,
            throw_error=True,
        )


# -----------------------------------------------------------------------------
def help(args):
    """
    Show help message of command

    :param args:    call arguments
    """
    command_name = 'help'
    params = {
        'args': args,
        'command_name': command_name,
    }

    run_method(command_name, 'run', params)


# -----------------------------------------------------------------------------
def process_command(args):
    """
    Entrypoint to call commands

    :param args:    call arguments
    """
    commands = get_all_commands()

    if len(args) > 0:
        command_name = str(args[0])
        args.pop(0)

        if command_name in commands:
            params = {
                'args': args,
                'command_name': command_name,
            }

            run_method(command_name, 'run', params)
        else:
            help(args)
    else:
        help(args)
