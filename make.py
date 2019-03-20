#!/usr/bin/env python

# Build script for ezored 

import sys

from ezored import colorama
from ezored.mod import command

# Entrypoint
if __name__ == '__main__':
    colorama.init()
    command.process_command(sys.argv[1:])
