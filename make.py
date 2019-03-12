#!/usr/bin/env python

# Build script for ezored 

import sys

from ezored import colorama
from ezored import commands

# Entrypoint
if __name__ == '__main__':
    colorama.init()
    commands.process_command(sys.argv[1:])
