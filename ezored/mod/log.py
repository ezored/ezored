"""Module: Log"""

import sys

# log colors
RED = '\033[31m'
GREEN = '\033[32m'
YELLOW = '\033[33m'
BLUE = '\033[1;36m'
PURPLE = '\033[95m'
ENDC = '\033[39m'


# -----------------------------------------------------------------------------
def error(msg, fatal=True):
    """
    Print error message and exit with error code 10 
    unless 'fatal' is False.

    :param msg:     string message
    :param fatal:   exit program with error code 10 if True (default is true)
    """
    print('{0}[ERROR]{1} {2}'.format(RED, ENDC, msg))

    if fatal:
        sys.exit(10)


# -----------------------------------------------------------------------------
def warn(msg):
    """
    Print a warning message

    :param msg:     string message
    """
    print('{0}[WARNING]{1} {2}'.format(YELLOW, ENDC, msg))


# -----------------------------------------------------------------------------
def ok(msg=''):
    """
    Print a green 'ok' message

    :param msg:     string message
    """
    print('{0}[OK]{1} {2}'.format(GREEN, ENDC, msg))


# -----------------------------------------------------------------------------
def fail(msg='', fatal=True):
    """
    Print a red 'fail' message

    :param msg:     string message
    """
    print('{0}[FAIL]{1} {2}'.format(RED, ENDC, msg))

    if fatal:
        sys.exit(10)


# -----------------------------------------------------------------------------
def failed(msg):
    """
    Print a red 'fail' message

    :param msg:     string message
    """
    print('{0}[FAILED]{1} {2}'.format(RED, ENDC, msg))


# -----------------------------------------------------------------------------
def info(msg):
    """
    Print a yellow 'info' message

    :param msg:     string message
    """
    print('{0}[INFO]{1} {2}'.format(YELLOW, ENDC, msg))


# -----------------------------------------------------------------------------
def normal(msg):
    """
    Print a normal log message

    :param msg:     string message
    """
    print(msg)


# -----------------------------------------------------------------------------
def colored(msg, color):
    """
    Print a colored log message

    :param msg:     text message
    :param color:   color escape sequence (e.g. log.YELLOW)
    """
    print('{}{}{}'.format(color, msg, ENDC))
