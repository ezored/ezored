"""Package target"""

import os

from pygemstones.io import file as f
from pygemstones.system import platform as p
from pygemstones.system import runner as r
from pygemstones.util import log as l

from files.config import target_android as config
from files.core import const, module


# -----------------------------------------------------------------------------
def run(params):
    proj_path = params["proj_path"]
    target_name = params["target_name"]
    target_config = config.run(proj_path, target_name, params)

    archs = target_config["archs"]
    build_types = target_config["build_types"]
    android_module_name = "library"

    l.i("Creating AAR library...")

    if archs and len(archs) > 0:
        if build_types and len(build_types) > 0:
            for build_type in build_types:
                l.i("Creating AAR library for: {0}...".format(build_type))

                build_dir = os.path.join(
                    proj_path, const.DIR_NAME_BUILD, target_name, build_type
                )

                # copy library project template
                android_library_build_dir = os.path.join(build_dir, "aar")

                f.recreate_dir(android_library_build_dir)

                android_project_dir = os.path.join(
                    proj_path,
                    const.DIR_NAME_FILES,
                    const.DIR_NAME_FILES_TARGETS,
                    target_name,
                    const.DIR_NAME_FILES_TARGET_SUPPORT,
                    "android-aar-project",
                )

                f.copy_dir(
                    android_project_dir,
                    android_library_build_dir,
                    symlinks=True,
                )

                # replace data
                build_gradle_file = os.path.join(
                    android_library_build_dir,
                    "library",
                    "build.gradle",
                )

                f.replace_in_file(
                    build_gradle_file, "{VERSION}", target_config["version"]
                )
                f.replace_in_file(
                    build_gradle_file, "{VERSION_CODE}", target_config["version_code"]
                )

                # copy support lib files
                gluecode_support_lib_dir = os.path.join(
                    proj_path,
                    const.DIR_NAME_FILES,
                    const.DIR_NAME_FILES_MODULES,
                    "support-lib",
                )

                f.copy_all(
                    os.path.join(gluecode_support_lib_dir, "java"),
                    os.path.join(
                        android_library_build_dir,
                        android_module_name,
                        "src",
                        "main",
                        "java",
                    ),
                )

                # copy all modules glue code files
                modules_dir = os.path.join(
                    proj_path,
                    const.DIR_NAME_FILES,
                    const.DIR_NAME_FILES_MODULES,
                )

                modules = module.get_list(proj_path)

                for m in modules:
                    module_dir = os.path.join(
                        modules_dir,
                        m,
                        const.DIR_NAME_GLUECODE,
                        "generated-src",
                        "java",
                    )

                    if f.dir_exists(module_dir):
                        f.copy_all(
                            module_dir,
                            os.path.join(
                                android_library_build_dir,
                                android_module_name,
                                "src",
                                "main",
                                "java",
                            ),
                        )

                # copy all modules implementation files
                modules_dir = os.path.join(
                    proj_path,
                    const.DIR_NAME_FILES,
                    const.DIR_NAME_FILES_MODULES,
                )

                modules = module.get_list(proj_path)

                for m in modules:
                    module_dir = os.path.join(
                        modules_dir,
                        m,
                        "implementation",
                        "java",
                    )

                    if f.dir_exists(module_dir):
                        f.copy_all(
                            module_dir,
                            os.path.join(
                                android_library_build_dir,
                                android_module_name,
                                "src",
                                "main",
                                "java",
                            ),
                        )

                # copy all native libraries
                for arch in archs:
                    compiled_arch_dir = os.path.join(
                        build_dir,
                        arch["conan_arch"],
                        const.DIR_NAME_BUILD_TARGET,
                        "lib",
                    )

                    target_arch_dir = os.path.join(
                        android_library_build_dir,
                        "library",
                        "src",
                        "main",
                        "jniLibs",
                        arch["arch"],
                    )

                    f.copy_all(compiled_arch_dir, target_arch_dir)

                # build aar
                android_module_dir = os.path.join(
                    android_library_build_dir,
                    android_module_name,
                )

                if p.is_windows():
                    run_args = [
                        os.path.join("..", "gradlew.bat"),
                        "bundle{0}Aar".format(build_type),
                    ]
                else:
                    run_args = [
                        os.path.join("..", "gradlew"),
                        "bundle{0}Aar".format(build_type),
                    ]

                r.run(run_args, cwd=android_module_dir)

                # copy files
                arr_dir = os.path.join(
                    android_library_build_dir,
                    android_module_name,
                    "build",
                    "outputs",
                    "aar",
                )

                dist_dir = os.path.join(
                    proj_path, const.DIR_NAME_DIST, target_name, build_type
                )

                f.remove_dir(dist_dir)

                f.copy_all(arr_dir, dist_dir)

            l.ok()
        else:
            l.i('Build type list for "{0}" is invalid or empty'.format(target_name))
    else:
        l.i('Arch list for "{0}" is invalid or empty'.format(target_name))
