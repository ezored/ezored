#!/usr/bin/env python

import os
import sys

from files.core import bootstrap

proj_path = os.path.dirname(os.path.abspath(__file__))


# -----------------------------------------------------------------------------
if __name__ == "__main__":
    bootstrap.run(proj_path, sys.argv)
