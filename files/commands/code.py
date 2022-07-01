"""Code manager tool"""

import os
import subprocess

from pygemstones.io import file as f
from pygemstones.system import runner as r
from pygemstones.util import log as l

from files.core import const, target


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
    targets = target.get_all_targets(proj_path)

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
                "path": os.path.join(
                    proj_path, const.DIR_NAME_PROJECTS, "ios", "Sample", "Sample"
                ),
                "patterns": ["*.cpp", "*.hpp", "*.c", "*.h", "*.m", "*.mm"],
            },
        ]

        if path_list:
            l.i("Formating C++ files...")

            for path_list_item in path_list:
                patterns = path_list_item["patterns"]

                for pattern_item in patterns:
                    files = f.find_files(
                        path_list_item["path"], pattern_item, recursive=True
                    )

                    for file_item in files:
                        l.i(
                            "Formatting file: {0}...".format(os.path.relpath(file_item))
                        )

                        run_args = ["clang-format", "-style", "file", "-i", file_item]

                        r.run(run_args, cwd=proj_path)

            l.ok()
        else:
            l.e("No C++ files found to format")

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
            l.i("Formating Python files...")

            for path_list_item in path_list:
                patterns = (
                    path_list_item["patterns"] if "patterns" in path_list_item else None
                )

                if patterns:
                    for pattern_item in patterns:
                        files = f.find_files(
                            path_list_item["path"], pattern_item, recursive=True
                        )

                        for file_item in files:
                            l.i(
                                "Formatting file: {0}...".format(
                                    os.path.relpath(file_item)
                                )
                            )

                            run_args = ["black", "-q", file_item]

                            r.run(run_args, cwd=proj_path)
                else:
                    file_item = (
                        path_list_item["path"] if "path" in path_list_item else None
                    )

                    if file_item:
                        l.i(
                            "Formatting file: {0}...".format(os.path.relpath(file_item))
                        )

                        run_args = ["black", "-q", file_item]

                        r.run(run_args, cwd=proj_path)

            l.ok()
        else:
            l.e("No Python files found to format")

    # format cmake files
    has_tool = check_cmake_formatter()

    if has_tool:
        path_list = [
            {
                "path": os.path.join(
                    proj_path, const.DIR_NAME_FILES, const.DIR_NAME_FILES_MODULES
                ),
                "patterns": ["*.cmake"],
            },
            {
                "path": os.path.join(
                    proj_path, const.DIR_NAME_FILES, const.DIR_NAME_FILES_MODULES
                ),
                "patterns": ["CMakeLists.txt"],
            },
            {
                "path": os.path.join(
                    proj_path, const.DIR_NAME_FILES, const.DIR_NAME_FILES_COMMON
                ),
                "patterns": ["*.cmake"],
            },
            {
                "path": os.path.join(
                    proj_path, const.DIR_NAME_FILES, const.DIR_NAME_FILES_COMMON
                ),
                "patterns": ["CMakeLists.txt"],
            },
        ]

        for target_name in targets:
            path_list.extend(
                [
                    {
                        "path": os.path.join(
                            proj_path,
                            const.DIR_NAME_FILES,
                            const.DIR_NAME_FILES_TARGETS,
                            target_name,
                            const.DIR_NAME_FILES_TARGET_CMAKE,
                        ),
                        "patterns": ["*.cmake"],
                    },
                    {
                        "path": os.path.join(
                            proj_path,
                            const.DIR_NAME_FILES,
                            const.DIR_NAME_FILES_TARGETS,
                            target_name,
                            const.DIR_NAME_FILES_TARGET_CMAKE,
                        ),
                        "patterns": ["CMakeLists.txt"],
                    },
                    {
                        "path": os.path.join(
                            proj_path,
                            const.DIR_NAME_FILES,
                            const.DIR_NAME_FILES_TARGETS,
                            target_name,
                            const.DIR_NAME_FILES_TARGET_CONAN,
                        ),
                        "patterns": ["*.cmake"],
                    },
                    {
                        "path": os.path.join(
                            proj_path,
                            const.DIR_NAME_FILES,
                            const.DIR_NAME_FILES_TARGETS,
                            target_name,
                            const.DIR_NAME_FILES_TARGET_CONAN,
                        ),
                        "patterns": ["CMakeLists.txt"],
                    },
                    {
                        "path": os.path.join(
                            proj_path,
                            const.DIR_NAME_FILES,
                            const.DIR_NAME_FILES_TARGETS,
                            target_name,
                            const.DIR_NAME_FILES_TARGET_SUPPORT,
                        ),
                        "patterns": ["*.cmake"],
                    },
                    {
                        "path": os.path.join(
                            proj_path,
                            const.DIR_NAME_FILES,
                            const.DIR_NAME_FILES_TARGETS,
                            target_name,
                            const.DIR_NAME_FILES_TARGET_SUPPORT,
                        ),
                        "patterns": ["CMakeLists.txt"],
                    },
                    {
                        "path": os.path.join(
                            proj_path,
                            const.DIR_NAME_FILES,
                            const.DIR_NAME_FILES_TARGETS,
                            target_name,
                            const.DIR_NAME_FILES_TARGET_VERBS,
                        ),
                        "patterns": ["*.cmake"],
                    },
                    {
                        "path": os.path.join(
                            proj_path,
                            const.DIR_NAME_FILES,
                            const.DIR_NAME_FILES_TARGETS,
                            target_name,
                            const.DIR_NAME_FILES_TARGET_VERBS,
                        ),
                        "patterns": ["CMakeLists.txt"],
                    },
                ]
            )

        if path_list:
            l.i("Formating CMake files...")

            for path_list_item in path_list:
                patterns = path_list_item["patterns"]

                for pattern_item in patterns:
                    files = f.find_files(
                        path_list_item["path"], pattern_item, recursive=True
                    )

                    for file_item in files:
                        l.i(
                            "Formatting file: {0}...".format(os.path.relpath(file_item))
                        )

                        run_args = [
                            "cmake-format",
                            "-c",
                            ".cmake-format",
                            "-i",
                            file_item,
                        ]

                        r.run(run_args, cwd=proj_path)

            l.ok()
        else:
            l.e("No CMake files found to format")


# -----------------------------------------------------------------------------
def check_cpp_formatter():
    """Checks if invoking supplied clang-format binary works."""
    try:
        subprocess.check_output(["clang-format", "--version"])
        return True
    except OSError:
        l.i(
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
        l.i("Black is not installed, check: https://github.com/psf/black")
        return False


# -----------------------------------------------------------------------------
def check_cmake_formatter():
    """Checks if invoking supplied cmake-format binary works."""
    try:
        subprocess.check_output(["cmake-format", "--version"])
        return True
    except OSError:
        l.i(
            "Cmake-format is not installed, check: https://github.com/cheshirekow/cmake_format"
        )
        return False


# -----------------------------------------------------------------------------
def show_help(params):
    l.colored("Available actions:\n", l.MAGENTA)
    l.m("  - format")


# -----------------------------------------------------------------------------
def get_description(params):
    return "Code manager tool"
