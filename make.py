#!/usr/bin/env python

import os
import subprocess
import sys

ezored_path = os.path.dirname(os.path.abspath(__file__))
proj_path = ezored_path
ezored_path = os.path.join(ezored_path, 'ezored')

if not os.path.isdir(ezored_path):
    print("Cloning ezored-core to '{0}'".format(ezored_path))

    subprocess.call([
        'git',
        'clone',
        'https://github.com/ezored/ezored-core.git',
        ezored_path
    ])

sys.path.insert(0, ezored_path)

try:
    from ezored.modules import ezored
except ImportError:
    error_msg = "[ERROR] Failed to initialize ezored-core in '{0}'"
    print(error_msg.format(proj_path))
    sys.exit(10)

if __name__ == '__main__':
    ezored.run(ezored_path, proj_path, sys.argv)
