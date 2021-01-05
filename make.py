#!/usr/bin/env python

import os
import subprocess
import sys

from files.modules import ezored

proj_path = os.path.dirname(os.path.abspath(__file__))


if __name__ == "__main__":
    ezored.run(proj_path, sys.argv)
