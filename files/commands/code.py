"""Code manager tool"""

import os
import subprocess

from files.core import const
from files.core import file
from files.core import log
from files.core import runner


# -----------------------------------------------------------------------------
def run(params):
    args = params["args"]

    if len(args) > 0:
        action = args[0]

        if action:
            if action == "format":
                code_format(params)
            else:
                show_help(params)
        else:
            show_help(params)
    else:
        show_help(params)


# -----------------------------------------------------------------------------
def code_format(params):
    proj_path = params["proj_path"]

    # format c++ files
    has_tool = check_cpp_formatter()

    if has_tool:
        dir_list = [
            {
                "path": os.path.join(
                    proj_path, const.DIR_NAME_FILES, const.DIR_NAME_FILES_MODULES
                ),
                "patterns": ["*.cpp", "*.hpp"],
            },
            {
                "path": os.path.join(proj_path, const.DIR_NAME_PROJECTS),
                "patterns": ["*.cpp", "*.hpp"],
            },
        ]

        if dir_list:
            log.info("Formating C++ files...")

            for dir_item in dir_list:
                patterns = dir_item["patterns"]

                for pattern_item in patterns:
                    files = file.find_files(dir_item["path"], pattern_item)

                    for file_item in files:
                        log.info(
                            "Formatting file: {0}...".format(os.path.relpath(file_item))
                        )

                        run_args = ["clang-format", "-style", "file", "-i", file_item]

                        runner.run(run_args, proj_path)

            log.ok()
        else:
            log.error("No C++ files found to format")

    # format python files
    has_tool = check_php_formatter()

    if has_tool:
        dir_list = [
            {"path": proj_path, "patterns": ["make.py"]},
            {
                "path": os.path.join(proj_path, const.DIR_NAME_FILES),
                "patterns": ["*.py"],
            },
        ]

        if dir_list:
            log.info("Formating Python files...")

            for dir_item in dir_list:
                patterns = dir_item["patterns"]

                for pattern_item in patterns:
                    files = file.find_files(dir_item["path"], pattern_item)

                    for file_item in files:
                        log.info(
                            "Formatting file: {0}...".format(os.path.relpath(file_item))
                        )

                        run_args = ["black", "-q", file_item]

                        runner.run(run_args, proj_path)

            log.ok()
        else:
            log.error("No Python files found to format")


# -----------------------------------------------------------------------------
def check_cpp_formatter():
    """Checks if invoking supplied clang-format binary works."""
    try:
        subprocess.check_output(["clang-format", "--version"])
        return True
    except OSError:
        log.info(
            "Clang-format is not installed, check: https://clang.llvm.org/docs/ClangFormat.html"
        )
        return False


# -----------------------------------------------------------------------------
def check_php_formatter():
    """Checks if invoking supplied black binary works."""
    try:
        subprocess.check_output(["black", "--version"])
        return True
    except OSError:
        log.info("Black is not installed, check: https://github.com/psf/black")
        return False


# -----------------------------------------------------------------------------
def show_help(params):
    log.colored("Available actions:\n", log.PURPLE)
    log.normal("  - format")


# -----------------------------------------------------------------------------
def get_description(params):
    return "Code manager tool"
