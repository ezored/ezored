"""Cleanup the workspace"""

import os

from pygemstones.io import file as f
from pygemstones.util import log as l


# -----------------------------------------------------------------------------
def run(params):
    l.i("Cleaning...")

    proj_path = params["proj_path"]

    f.remove_dir(os.path.join(proj_path, "build"))

    f.remove_files(proj_path, "*.pyc", recursive=True)
    f.remove_files(proj_path, "*.zip", recursive=True)
    f.remove_files(proj_path, "*.tar", recursive=True)
    f.remove_files(proj_path, "*.tar.gz", recursive=True)
    f.remove_files(proj_path, "Thumbs.db", recursive=True)
    f.remove_files(proj_path, ".DS_Store", recursive=True)

    f.remove_dirs(proj_path, "__pycache__", recursive=True)

    l.ok()


# -----------------------------------------------------------------------------
def show_help(params):
    return ""


# -----------------------------------------------------------------------------
def get_description(params):
    return "Cleanup the workspace"
