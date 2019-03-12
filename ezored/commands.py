"""Commands entrypoint"""

from ezored import functions as fn


# -----------------------------------------------------------------------------
def help(args):
    """
    Show help message of command
    
    :param args:    call arguments
    """
    command = 'help'
    params = {
        'args': args,
        'command_name': command,
    }

    fn.run_command(command, 'run', params)


# -----------------------------------------------------------------------------
def process_command(args):
    """
    Entrypoint to call commands
    
    :param args:    call arguments
    """
    commands = fn.get_all_commands()

    if len(args) > 0:
        command = str(args[0])
        args.pop(0)

        if command in commands:
            params = {
                'args': args,
                'command_name': command,
            }

            fn.run_command(command, 'run', params)
        else:
            help(args)
    else:
        help(args)
