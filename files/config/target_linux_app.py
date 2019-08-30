def run(proj_path, target_name, params):
    return {
        "project_name": "Sample",
        "build_types": ["Debug", "Release"],
        "archs": [
            {
                "arch": "x86",
                "conan_arch": "x86",
                "conan_profile": "ezored_linux_app_profile",
            },
            {
                "arch": "x86_64",
                "conan_arch": "x86_64",
                "conan_profile": "ezored_linux_app_profile",
            },
        ],
    }
