"""Cleanup the workspace"""

import os

from files.modules import file
from files.modules import log


# -----------------------------------------------------------------------------
def run(params):
    log.info("Cleaning...")

    proj_path = params["proj_path"]

    file.remove_dir(os.path.join(proj_path, "build"))

    file.purge_files(proj_path, "*.pyc")
    file.purge_files(proj_path, "*.zip")
    file.purge_files(proj_path, "*.tar")
    file.purge_files(proj_path, "*.tar.gz")
    file.purge_files(proj_path, "Thumbs.db")
    file.purge_files(proj_path, ".DS_Store")

    file.purge_dirs(proj_path, "__pycache__")

    log.ok("")


# -----------------------------------------------------------------------------
def show_help(params):
    return ""


# -----------------------------------------------------------------------------
def get_description(params):
    return "Cleanup the workspace"
