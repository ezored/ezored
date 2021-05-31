from files.core import util


def run(proj_path, target_name, params):
    archs = []

    if util.is_windows_platform():
        archs.append(
            {
                "arch": "x86_64",
                "conan_arch": "x86_64",
                "conan_profile": "ezored_windows_profile",
            }
        )
    elif util.is_linux_platform():
        archs.append(
            {
                "arch": "x86_64",
                "conan_arch": "x86_64",
                "conan_profile": "ezored_linux_profile",
            }
        )
    elif util.is_macos_platform():
        archs.append(
            {
                "arch": "x86_64",
                "conan_arch": "x86_64",
                "conan_profile": "ezored_macos_profile",
                "min_version": "10.9",
            }
        )

    return {
        "project_name": "test",
        "version": "1.0.0",
        "build_types": ["Release"],
        "archs": archs,
    }
