"""Prepare target files and dependencies"""

import os

from pygemstones.io import file as f
from pygemstones.system import platform as p
from pygemstones.system import runner as r
from pygemstones.util import log as l

from files.config import target_tests as config
from files.core import const


# -----------------------------------------------------------------------------
def run(params):
    proj_path = params["proj_path"]
    target_name = params["target_name"]
    target_config = config.run(proj_path, target_name, params)

    archs = target_config["archs"]
    build_types = target_config["build_types"]

    if archs and len(archs) > 0:
        for arch in archs:
            for build_type in build_types:
                l.i("Building for: {0}/{1}...".format(arch["conan_arch"], build_type))

                # conan install
                build_dir = os.path.join(
                    proj_path,
                    const.DIR_NAME_BUILD,
                    target_name,
                    build_type,
                    arch["conan_arch"],
                    const.DIR_NAME_BUILD_CONAN,
                )

                f.recreate_dir(build_dir)

                # main run args
                run_args = [
                    "conan",
                    "install",
                    os.path.join(
                        proj_path,
                        const.DIR_NAME_FILES,
                        const.DIR_NAME_FILES_TARGETS,
                        target_name,
                        const.DIR_NAME_FILES_TARGET_CONAN,
                        const.DIR_NAME_FILES_TARGET_CONAN_RECIPE,
                        const.FILE_NAME_FILES_TARGET_CONAN_RECIPE_CONANFILE_PY,
                    ),
                    "--profile",
                    arch["conan_profile"],
                    "-s",
                    "arch={0}".format(arch["conan_arch"]),
                    "-s",
                    "build_type={0}".format(build_type),
                    "-o",
                    "ezored_arch={0}".format(arch["conan_arch"]),
                    "-o",
                    "ezored_name={0}".format(target_config["project_name"]),
                    "-o",
                    "ezored_version={0}".format(target_config["version"]),
                ]

                # extra run args
                if p.is_macos():
                    run_args.append("-s"),
                    run_args.append("os.version={0}".format(arch["min_version"]))

                # final run args
                run_args.append("--build=missing")
                run_args.append("--update")

                r.run(run_args, cwd=build_dir)

        l.ok()
    else:
        l.e('Arch list for "{0}" is invalid or empty'.format(target_name))
