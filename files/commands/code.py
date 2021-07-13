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
        path_list = [
            {
                "path": os.path.join(
                    proj_path, const.DIR_NAME_FILES, const.DIR_NAME_FILES_MODULES
                ),
                "patterns": ["*.cpp", "*.hpp", "*.c", "*.h", "*.m", "*.mm"],
            },
            {
                "path": os.path.join(proj_path, const.DIR_NAME_PROJECTS, "others"),
                "patterns": ["*.cpp", "*.hpp", "*.c", "*.h", "*.m", "*.mm"],
            },
            {
                "path": os.path.join(proj_path, const.DIR_NAME_PROJECTS, "android"),
                "patterns": ["*.cpp", "*.hpp", "*.c", "*.h", "*.m", "*.mm"],
            },
            {
                "path": os.path.join(proj_path, const.DIR_NAME_PROJECTS, "ios"),
                "patterns": ["*.cpp", "*.hpp", "*.c", "*.h", "*.m", "*.mm"],
            },
        ]

        if path_list:
            log.info("Formating C++ files...")

            for path_list_item in path_list:
                patterns = path_list_item["patterns"]

                for pattern_item in patterns:
                    files = file.find_files(path_list_item["path"], pattern_item)

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
    has_tool = check_python_formatter()

    if has_tool:
        path_list = [
            {
                "path": os.path.join(proj_path, "make.py"),
            },
            {
                "path": os.path.join(proj_path, const.DIR_NAME_FILES),
                "patterns": ["*.py"],
            },
        ]

        if path_list:
            log.info("Formating Python files...")

            for path_list_item in path_list:
                patterns = (
                    path_list_item["patterns"] if "patterns" in path_list_item else None
                )

                if patterns:
                    for pattern_item in patterns:
                        files = file.find_files(path_list_item["path"], pattern_item)

                        for file_item in files:
                            log.info(
                                "Formatting file: {0}...".format(
                                    os.path.relpath(file_item)
                                )
                            )

                            run_args = ["black", "-q", file_item]

                            runner.run(run_args, proj_path)
                else:
                    file_item = (
                        path_list_item["path"] if "path" in path_list_item else None
                    )

                    if file_item:
                        log.info(
                            "Formatting file: {0}...".format(os.path.relpath(file_item))
                        )

                        run_args = ["black", "-q", file_item]

                        runner.run(run_args, proj_path)

            log.ok()
        else:
            log.error("No Python files found to format")

    # format cmake files
    has_tool = check_cmake_formatter()

    if has_tool:
        path_list = [
            {
                "path": os.path.join(proj_path, const.DIR_NAME_FILES),
                "patterns": ["*.cmake"],
            },
            {
                "path": os.path.join(proj_path, const.DIR_NAME_FILES),
                "patterns": ["CMakeLists.txt"],
            },
        ]

        if path_list:
            log.info("Formating CMake files...")

            for path_list_item in path_list:
                patterns = path_list_item["patterns"]

                for pattern_item in patterns:
                    files = file.find_files(path_list_item["path"], pattern_item)

                    for file_item in files:
                        log.info(
                            "Formatting file: {0}...".format(os.path.relpath(file_item))
                        )

                        run_args = [
                            "cmake-format",
                            "-c",
                            ".cmake-format",
                            "-i",
                            file_item,
                        ]

                        runner.run(run_args, proj_path)

            log.ok()
        else:
            log.error("No CMake files found to format")


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
def check_python_formatter():
    """Checks if invoking supplied black binary works."""
    try:
        subprocess.check_output(["black", "--version"])
        return True
    except OSError:
        log.info("Black is not installed, check: https://github.com/psf/black")
        return False


# -----------------------------------------------------------------------------
def check_cmake_formatter():
    """Checks if invoking supplied cmake-format binary works."""
    try:
        subprocess.check_output(["cmake-format", "--version"])
        return True
    except OSError:
        log.info(
            "Cmake-format is not installed, check: https://github.com/cheshirekow/cmake_format"
        )
        return False


# -----------------------------------------------------------------------------
def show_help(params):
    log.colored("Available actions:\n", log.PURPLE)
    log.normal("  - format")


# -----------------------------------------------------------------------------
def get_description(params):
    return "Code manager tool"
