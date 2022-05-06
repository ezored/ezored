import os

from files.core import const
from files.config import gluecode as config


def run(proj_path, target_name, params):
    return {
        "project_name": "ezored",
        "version": "1.0.0",
        "build_types": ["Debug", "Release"],
        "archs": [
            {
                "arch": "armv7",
                "conan_arch": "armv7",
                "conan_profile": "ezored_ios_profile",
                "min_version": "9.0",
                "supported_platform": "iPhoneOS",
                "enable_bitcode": True,
                "group": "ios",
            },
            {
                "arch": "arm64",
                "conan_arch": "armv8",
                "conan_profile": "ezored_ios_profile",
                "min_version": "9.0",
                "supported_platform": "iPhoneOS",
                "enable_bitcode": True,
                "group": "ios",
            },
            {
                "arch": "x86_64",
                "conan_arch": "x86_64",
                "conan_profile": "ezored_ios_profile",
                "min_version": "9.0",
                "supported_platform": "iPhoneSimulator",
                "enable_bitcode": False,
                "group": "ios_simulator",
            },
            {
                "arch": "x86_64",
                "conan_arch": "x86_64",
                "conan_profile": "ezored_catalyst_profile",
                "min_version": "10.15",
                "supported_platform": "MacOSX",
                "enable_bitcode": False,
                "group": "ios_catalyst",
                "subsystem_ios_version": "13.1",
            },
            {
                "arch": "arm64",
                "conan_arch": "armv8",
                "conan_profile": "ezored_catalyst_profile",
                "min_version": "10.15",
                "supported_platform": "MacOSX",
                "enable_bitcode": True,
                "group": "ios_catalyst",
                "subsystem_ios_version": "13.1",
            },
            {
                "arch": "arm64",
                "conan_arch": "armv8",
                "conan_profile": "ezored_tvos_profile",
                "min_version": "11.0",
                "supported_platform": "AppleTVOS",
                "enable_bitcode": True,
                "group": "tvos",
            },
            {
                "arch": "x86_64",
                "conan_arch": "x86_64",
                "conan_profile": "ezored_tvos_profile",
                "min_version": "11.0",
                "supported_platform": "AppleTVSimulator",
                "enable_bitcode": False,
                "group": "tvos_simulator",
            },
            {
                "arch": "armv7k",
                "conan_arch": "armv7k",
                "conan_profile": "ezored_watchos_profile",
                "min_version": "5.0",
                "supported_platform": "WatchOS",
                "enable_bitcode": True,
                "group": "watchos",
            },
            {
                "arch": "arm64_32",
                "conan_arch": "armv8_32",
                "conan_profile": "ezored_watchos_profile",
                "min_version": "5.0",
                "supported_platform": "WatchOS",
                "enable_bitcode": True,
                "group": "watchos",
            },
            {
                "arch": "x86_64",
                "conan_arch": "x86_64",
                "conan_profile": "ezored_watchos_profile",
                "min_version": "5.0",
                "supported_platform": "WatchSimulator",
                "enable_bitcode": False,
                "group": "watchos_simulator",
            },
        ],
        "umbrella_header": "Ezored.h",
        "install_headers": get_header_dir_list(
            proj_path,
            target_name,
            params,
        ),
    }


def get_header_dir_list(proj_path, target_name, params):
    result = []
    filter_gen_src = []
    filter_impl_src = []

    # check modules folder
    modules_path = os.path.join(
        proj_path, const.DIR_NAME_FILES, const.DIR_NAME_FILES_MODULES
    )

    if os.path.isdir(modules_path):
        gluecode_config = config.run(proj_path, None, params)
        modules = gluecode_config["modules"]

        if modules:
            for m in modules:
                gluecode_dir = os.path.join(
                    modules_path,
                    m,
                    const.DIR_NAME_GLUECODE,
                )

                module_gen_dir = os.path.join(
                    gluecode_dir,
                    "generated-src",
                    "objc",
                )
                module_impl_dir = os.path.join(
                    modules_path,
                    m,
                    "implementation",
                    "objc",
                )

                # generated src
                if m not in filter_gen_src:
                    if os.path.isdir(module_gen_dir):
                        result.append(
                            {
                                "type": "dir",
                                "path": module_gen_dir,
                            }
                        )

                # implementation
                if m not in filter_impl_src:
                    if os.path.isdir(module_impl_dir):
                        result.append(
                            {
                                "type": "dir",
                                "path": module_impl_dir,
                            }
                        )

    return result
