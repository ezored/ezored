def run(proj_path, target_name, params):
    return {
        "project_name": "ezored",
        "version": "1.0.0",
        "build_types": ["Debug", "Release"],
        "archs": [
            {
                "arch": "x86_64",
                "conan_arch": "x86_64",
                "conan_profile": "ezored_windows_profile",
            }
        ],
    }
