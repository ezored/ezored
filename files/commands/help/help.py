"""List all commands"""

import sys

from ezored.mod import command
from ezored.mod import log


# -----------------------------------------------------------------------------
def run(params={}):
    args = params['args']

    log.colored('Please use "{0} <command>" where <command> is one of:\n'.format(
        sys.argv[0]), log.PURPLE
    )

    commands = command.get_all_commands()
    width = max(len(name) for name in commands)

    for command_item in commands:
        params = {
            'args': args,
            'command_name': command_item,
        }

        description = command.run_method(command_item, 'get_description', params)

        print('  {name:{width}}  {descr}'.format(
            name=command_item,
            width=width,
            descr=description
        ))


# -----------------------------------------------------------------------------
def help(params={}):
    pass


# -----------------------------------------------------------------------------
def get_description(params={}):
    return 'List all commands'
