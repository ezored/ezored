"""Create final executable"""

import os

import ezored.app.const as const
from ezored.modules import file
from ezored.modules import log
from files.config import target_linux_app as config


# -----------------------------------------------------------------------------
def run(params):
    proj_path = params["proj_path"]
    target_name = params["target_name"]
    target_config = config.run(proj_path, target_name, params)

    archs = target_config["archs"]
    build_types = target_config["build_types"]

    log.info("Packaging...")

    if archs and len(archs) > 0:
        for arch in archs:
            for build_type in build_types:
                log.info(
                    "Copying for: {0}/{1}...".format(arch["conan_arch"], build_type)
                )

                # create folders
                dist_dir = os.path.join(
                    proj_path,
                    const.DIR_NAME_DIST,
                    target_name,
                    build_type,
                    arch["conan_arch"],
                )

                file.remove_dir(dist_dir)
                file.create_dir(dist_dir)

                build_dir = os.path.join(
                    proj_path,
                    const.DIR_NAME_BUILD,
                    target_name,
                    build_type,
                    arch["conan_arch"],
                    const.DIR_NAME_BUILD_TARGET,
                    "bin",
                )

                # copy files
                file.copy_all_inside(build_dir, dist_dir)
    else:
        log.error('Arch list for "{0}" is invalid or empty'.format(target_name))
