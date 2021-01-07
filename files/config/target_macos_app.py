def run(proj_path, target_name, params):
    return {
        "project_name": "ezored",
        "build_types": ["Debug", "Release"],
        "archs": [
            {
                "arch": "x86_64",
                "conan_arch": "x86_64",
                "conan_profile": "ezored_macos_app_profile",
                "min_version": "10.9",
            }
        ],
    }
