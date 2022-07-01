"""Package target"""

import os

from pygemstones.io import file as f
from pygemstones.system import runner as r
from pygemstones.type import list as ls
from pygemstones.util import log as l

from files.config import target_ios as config
from files.core import const


# -----------------------------------------------------------------------------
def run(params):
    proj_path = params["proj_path"]
    target_name = params["target_name"]
    target_config = config.run(proj_path, target_name, params)
    archs = target_config["archs"]
    build_types = target_config["build_types"]

    no_framework = ls.list_has_value(params["args"], "--no-framework")
    no_xcframework = ls.list_has_value(params["args"], "--no-xcframework")

    # at least one need be generated
    if no_framework and no_xcframework:
        l.e("You need let generate framework or xcframework, but both are disabled")

    # remove dist folder for the target
    dist_dir = os.path.join(
        proj_path,
        const.DIR_NAME_DIST,
        target_name,
    )

    f.remove_dir(dist_dir)

    # generate framework
    if not no_framework:
        generate_framework(
            proj_path=proj_path,
            target_name=target_name,
            target_config=target_config,
            archs=archs,
            build_types=build_types,
        )

    # generate xcframework
    if not no_xcframework:
        generate_xcframework(
            proj_path=proj_path,
            target_name=target_name,
            target_config=target_config,
            archs=archs,
            build_types=build_types,
        )

    # add strip framework script (only required if final project use framework instead of xcframework)
    l.i("Adding strip framework script...")

    target_scripts_dir = os.path.join(
        const.DIR_NAME_FILES,
        const.DIR_NAME_FILES_TARGETS,
        target_name,
        const.DIR_NAME_SUPPORT,
        "scripts",
    )

    f.copy_dir(
        target_scripts_dir,
        os.path.join(
            const.DIR_NAME_DIST,
            target_name,
            "scripts",
        ),
        symlinks=True,
    )

    # cocoapods
    l.i("Adding cocoapods script...")

    pod_file_path = os.path.join(
        const.DIR_NAME_FILES,
        const.DIR_NAME_FILES_TARGETS,
        target_name,
        const.DIR_NAME_SUPPORT,
        "cocoapods",
        "{0}.podspec".format(target_config["project_name"]),
    )

    target_pod_file_path = os.path.join(
        const.DIR_NAME_DIST,
        target_name,
        "{0}.podspec".format(target_config["project_name"]),
    )

    f.copy_file(
        pod_file_path,
        target_pod_file_path,
    )

    # xcframework group dir
    if not no_xcframework:
        if build_types and len(build_types) > 0:
            for build_type in build_types:
                xcframework_dir = os.path.join(
                    dist_dir,
                    build_type,
                    "{0}.xcframework".format(target_config["project_name"]),
                )

                found_dirs = f.find_dirs(xcframework_dir, "*")

                if found_dirs:
                    first_group = os.path.basename(found_dirs[0])

                    f.replace_in_file(
                        target_pod_file_path,
                        "{XCFRAMEWORK_" + build_type.upper() + "_GROUP_DIR}",
                        first_group,
                    )

    f.replace_in_file(target_pod_file_path, "{NAME}", target_config["project_name"])
    f.replace_in_file(target_pod_file_path, "{VERSION}", target_config["version"])

    # finish
    l.ok()


# -----------------------------------------------------------------------------
def generate_framework(proj_path, target_name, target_config, archs, build_types):
    l.i("Packaging framework...")

    if archs and len(archs) > 0:
        if build_types and len(build_types) > 0:
            for build_type in build_types:
                l.i("Copying for: {0}...".format(build_type))

                # copy first folder for base
                framework_dir = os.path.join(
                    proj_path,
                    const.DIR_NAME_BUILD,
                    target_name,
                    build_type,
                    archs[0]["group"],
                    archs[0]["conan_arch"],
                    const.DIR_NAME_BUILD_TARGET,
                    "lib",
                    "{0}.framework".format(target_config["project_name"]),
                )

                dist_dir = os.path.join(
                    proj_path,
                    const.DIR_NAME_DIST,
                    target_name,
                    build_type,
                    "{0}.framework".format(target_config["project_name"]),
                )

                f.remove_dir(dist_dir)

                f.copy_dir(
                    framework_dir,
                    dist_dir,
                    symlinks=True,
                )

                # update info plist file
                plist_path = os.path.join(
                    proj_path,
                    const.DIR_NAME_DIST,
                    target_name,
                    build_type,
                    "{0}.framework".format(target_config["project_name"]),
                    "Info.plist",
                )

                if os.path.exists(plist_path):
                    # remove supported platforms inside plist
                    r.run(
                        [
                            "plutil",
                            "-remove",
                            "CFBundleSupportedPlatforms",
                            plist_path,
                        ],
                        cwd=proj_path,
                    )

                # lipo
                lipo_archs_args = []

                for arch in archs:
                    if is_valid_group(arch["group"]):
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
                                "{0}.framework".format(target_config["project_name"]),
                                target_config["project_name"],
                            )
                        )

                lipo_args = [
                    "lipo",
                    "-create",
                    "-output",
                ]

                if f.dir_exists(
                    os.path.join(
                        dist_dir,
                        "Versions",
                    )
                ):
                    lipo_args.extend(
                        [
                            os.path.join(
                                dist_dir,
                                "Versions",
                                "A",
                                target_config["project_name"],
                            ),
                        ]
                    )
                else:
                    lipo_args.extend(
                        [
                            os.path.join(
                                dist_dir,
                                target_config["project_name"],
                            ),
                        ]
                    )

                lipo_args.extend(lipo_archs_args)
                r.run(lipo_args, cwd=proj_path)

                # check file
                l.i("Checking file for: {0}...".format(build_type))

                r.run(
                    ["file", os.path.join(dist_dir, target_config["project_name"])],
                    cwd=proj_path,
                )
        else:
            l.i('Build type list for "{0}" is invalid or empty'.format(target_name))
    else:
        l.i('Arch list for "{0}" is invalid or empty'.format(target_name))


# -----------------------------------------------------------------------------
def generate_xcframework(proj_path, target_name, target_config, archs, build_types):
    l.i("Packaging xcframework...")

    if archs and len(archs) > 0:
        if build_types and len(build_types) > 0:
            for build_type in build_types:
                l.i("Generating for: {0}...".format(build_type))

                # generate group list
                groups = []
                groups_command = []

                for arch in archs:
                    if not arch["group"] in groups:
                        groups.append(arch["group"])

                if len(groups) == 0:
                    l.e(
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
                        l.e("Group framework was not found: {0}".format(group))

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

                    f.remove_dir(group_xcframework_dir)
                    f.copy_all(
                        framework_dir,
                        group_xcframework_dir,
                    )

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
                    ]

                    if f.dir_exists(
                        os.path.join(
                            group_xcframework_dir,
                            "Versions",
                        )
                    ):
                        lipo_args.extend(
                            [
                                os.path.join(
                                    group_xcframework_dir,
                                    "Versions",
                                    "A",
                                    target_config["project_name"],
                                ),
                            ]
                        )
                    else:
                        lipo_args.extend(
                            [
                                os.path.join(
                                    group_xcframework_dir,
                                    target_config["project_name"],
                                ),
                            ]
                        )

                    lipo_args.extend(lipo_archs_args)
                    r.run(lipo_args, cwd=proj_path)

                    # add final framework to group
                    groups_command.append("-framework")
                    groups_command.append(group_xcframework_dir)

                # generate xcframework
                xcframework_dir = os.path.join(
                    proj_path,
                    const.DIR_NAME_DIST,
                    target_name,
                    build_type,
                    "{0}.xcframework".format(target_config["project_name"]),
                )

                f.remove_dir(xcframework_dir)

                xcodebuild_command = ["xcodebuild", "-create-xcframework"]
                xcodebuild_command += groups_command
                xcodebuild_command += ["-output", xcframework_dir]

                r.run(xcodebuild_command, cwd=proj_path)

                # check file
                l.i("Checking file for: {0}...".format(build_type))

                r.run(["ls", xcframework_dir], cwd=proj_path)
        else:
            l.i('Build type list for "{0}" is invalid or empty'.format(target_name))
    else:
        l.i('Arch list for "{0}" is invalid or empty'.format(target_name))


# -----------------------------------------------------------------------------
def is_valid_group(group):
    return True
