from pygemstones.system import platform as p


# -----------------------------------------------------------------------------
def run(proj_path, target_name, params):
    archs = []

    if p.is_windows():
        archs.append(
            {
                "arch": "x86_64",
                "conan_arch": "x86_64",
                "conan_profile": "ezored_windows_profile",
            }
        )
    elif p.is_linux():
        archs.append(
            {
                "arch": "x86_64",
                "conan_arch": "x86_64",
                "conan_profile": "ezored_linux_profile",
            }
        )
    elif p.is_macos():
        archs.append(
            {
                "arch": "x86_64",
                "conan_arch": "x86_64",
                "conan_profile": "ezored_macos_profile",
                "min_version": "10.9",
            }
        )

    return {
        "project_name": "tests",
        "version": "1.0.0",
        "build_types": ["Release"],
        "archs": archs,
    }
