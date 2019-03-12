"""List all commands"""

import sys

import ezored.functions as fn
import ezored.logging as log


# -----------------------------------------------------------------------------
def run(params={}):
    args = params['args']

    log.colored('Please use "{0} <command>" where <command> is one of:\n'.format(
        sys.argv[0]), log.PURPLE)

    commands = fn.get_all_commands()
    width = max(len(name) for name in commands)

    for command in commands:
        params = {
            'args': args,
            'command_name': command,
        }

        description = fn.run_command(command, 'get_description', params)

        print('  {name:{width}}  {descr}'.format(
            name=command, width=width, descr=description))


# -----------------------------------------------------------------------------
def help(params={}):
    pass


# -----------------------------------------------------------------------------
def get_description(params={}):
    return 'List all commands'
