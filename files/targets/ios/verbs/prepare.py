"""Prepare target files and dependencies"""

import os

from pygemstones.io import file as f
from pygemstones.system import runner as r
from pygemstones.util import log as l

from files.config import target_ios as config
from files.core import const, target


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
                    arch["group"],
                    arch["conan_arch"],
                    const.DIR_NAME_BUILD_CONAN,
                )

                f.recreate_dir(build_dir)

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
                    "-pr:b",
                    target.get_build_profile(),
                    "-pr:h",
                    arch["conan_profile"],
                    "-s:h",
                    "arch={0}".format(arch["conan_arch"]),
                    "-s:h",
                    "build_type={0}".format(build_type),
                    "-s:h",
                    "os.version={0}".format(arch["min_version"]),
                    "-o",
                    "ezored_arch={0}".format(arch["conan_arch"]),
                    "-o",
                    "ezored_name={0}".format(target_config["project_name"]),
                    "-o",
                    "ezored_version={0}".format(target_config["version"]),
                    "-o",
                    "ezored_group={0}".format(arch["group"]),
                ]

                # extra run args
                if "enable_bitcode" in arch:
                    run_args.append("-o:h")
                    run_args.append(
                        "darwin-toolchain:enable_bitcode={0}".format(
                            arch["enable_bitcode"]
                        )
                    )

                if "enable_arc" in arch:
                    run_args.append("-o:h")
                    run_args.append(
                        "darwin-toolchain:enable_arc={0}".format(arch["enable_arc"])
                    )

                if "enable_visibility" in arch:
                    run_args.append("-o:h")
                    run_args.append(
                        "darwin-toolchain:enable_visibility={0}".format(
                            arch["enable_visibility"]
                        )
                    )

                if "subsystem_ios_version" in arch:
                    run_args.append("-s:h")
                    run_args.append(
                        "os.subsystem.ios_version={0}".format(
                            arch["subsystem_ios_version"]
                        )
                    )

                # final run args
                run_args.append("--build=missing")
                run_args.append("--update")

                r.run(run_args, cwd=build_dir)

        l.ok()
    else:
        l.e('Arch list for "{0}" is invalid or empty'.format(target_name))
