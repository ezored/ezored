"""Create universal xcframework"""

import os

from files.modules import const
from files.modules import file
from files.modules import log
from files.modules import runner
from files.config import target_ios_framework as config


# -----------------------------------------------------------------------------
def run(params):
    proj_path = params["proj_path"]
    target_name = params["target_name"]
    target_config = config.run(proj_path, target_name, params)

    archs = target_config["archs"]
    build_types = target_config["build_types"]

    log.info("Packaging universal xcframework...")

    if archs and len(archs) > 0:
        if build_types and len(build_types) > 0:
            for build_type in build_types:
                log.info("Generating for: {0}...".format(build_type))

                # generate group list
                groups = []
                groups_command = []

                for arch in archs:
                    if not arch["group"] in groups:
                        groups.append(arch["group"])

                        groups_command.append("-framework")
                        groups_command.append(
                            os.path.join(
                                proj_path,
                                const.DIR_NAME_BUILD,
                                target_name,
                                build_type,
                                arch["group"],
                                "xcframework",
                                "{0}.framework".format(target_config["project_name"]),
                            )
                        )

                if len(groups) == 0:
                    log.error(
                        "Group list are empty, make sure you have defined group name for each arch in config file for this target"
                    )

                # generate framework for each group
                for group in groups:
                    # get first framework data for current group
                    base_framework_arch = None

                    for arch in archs:
                        if arch["group"] == group:
                            base_framework_arch = arch

                    if not base_framework_arch:
                        log.error("Group framework was not found: {0}".format(group))

                    # copy base framework
                    framework_dir = os.path.join(
                        proj_path,
                        const.DIR_NAME_BUILD,
                        target_name,
                        build_type,
                        base_framework_arch["group"],
                        base_framework_arch["conan_arch"],
                        const.DIR_NAME_BUILD_TARGET,
                        "lib",
                        "{0}.framework".format(target_config["project_name"]),
                    )

                    group_xcframework_dir = os.path.join(
                        proj_path,
                        const.DIR_NAME_BUILD,
                        target_name,
                        build_type,
                        group,
                        "xcframework",
                        "{0}.framework".format(target_config["project_name"]),
                    )

                    file.remove_dir(group_xcframework_dir)
                    file.copy_dir(framework_dir, group_xcframework_dir, symlinks=True)

                    # generate single framework for group
                    lipo_archs_args = []

                    for arch in archs:
                        if arch["group"] == group:
                            lipo_archs_args.append(
                                os.path.join(
                                    proj_path,
                                    const.DIR_NAME_BUILD,
                                    target_name,
                                    build_type,
                                    arch["group"],
                                    arch["conan_arch"],
                                    const.DIR_NAME_BUILD_TARGET,
                                    "lib",
                                    "{0}.framework".format(
                                        target_config["project_name"]
                                    ),
                                    target_config["project_name"],
                                )
                            )

                    lipo_args = [
                        "lipo",
                        "-create",
                        "-output",
                        os.path.join(
                            group_xcframework_dir, target_config["project_name"]
                        ),
                    ]

                    lipo_args.extend(lipo_archs_args)

                    runner.run(lipo_args, proj_path)

                # generate xcframework
                xcframework_dir = os.path.join(
                    proj_path,
                    const.DIR_NAME_DIST,
                    target_name,
                    build_type,
                    "{0}.xcframework".format(target_config["project_name"]),
                )

                file.remove_dir(xcframework_dir)

                xcodebuild_command = ["xcodebuild", "-create-xcframework"]

                xcodebuild_command += groups_command

                xcodebuild_command += ["-output", xcframework_dir]

                runner.run(xcodebuild_command, proj_path)

                # check file
                log.info("Checking file for: {0}...".format(build_type))

                runner.run(["ls", xcframework_dir], proj_path)

            log.ok()
        else:
            log.info(
                'Build type list for "{0}" is invalid or empty'.format(target_name)
            )
    else:
        log.info('Arch list for "{0}" is invalid or empty'.format(target_name))
