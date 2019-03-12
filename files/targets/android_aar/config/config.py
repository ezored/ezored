def run(params={}):
    return {
        'project_name': 'core',
        'conan_profile': 'ezored_android_aar_profile',
        'archs': [
            {'arch': 'armeabi-v7a', 'conan_arch': 'armv7'},
            {'arch': 'arm64-v8a', 'conan_arch': 'armv8'},
            {'arch': 'x86', 'conan_arch': 'x86'},
            {'arch': 'x86_64', 'conan_arch': 'x86_64'},
        ],
        'build_types': ['Debug', 'Release']
    }
