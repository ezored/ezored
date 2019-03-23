#!/usr/bin/env python

import os
import subprocess
import sys

ezored_path = os.path.dirname(os.path.abspath(__file__))
proj_path = ezored_path
ezored_path = os.path.join(ezored_path, 'ezored')

if not os.path.isdir(ezored_path):
    print("\033[93m[INFO] Cloning ezored to '{0}':\033[0m".format(ezored_path))

    subprocess.call([
        'git',
        'clone',
        'https://github.com/ezored/ezored-core.git',
        ezored_path
    ])

sys.path.insert(0, ezored_path)

try:
    from mod import ezored
except ImportError:
    error_msg = "\033[91m[ERROR]\033[0m Failed to initialize ezored in '{0}'"
    print(error_msg.format(proj_path))
    sys.exit(10)

if __name__ == '__main__':
    ezored.run(ezored_path, proj_path, sys.argv)
