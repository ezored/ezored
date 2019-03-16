def run(params={}):
    return {
        'project_name': 'core',
        'build_types': ['Debug', 'Release'],
        'archs': [
            {
                'arch': 'armeabi-v7a',
                'conan_arch': 'armv7',
                'conan_profile': 'ezored_android_aar_profile',
            },
            {
                'arch': 'arm64-v8a',
                'conan_arch': 'armv8',
                'conan_profile': 'ezored_android_aar_profile',
            },
            {
                'arch': 'x86',
                'conan_arch': 'x86',
                'conan_profile': 'ezored_android_aar_profile',
            },
            {
                'arch': 'x86_64',
                'conan_arch': 'x86_64',
                'conan_profile': 'ezored_android_aar_profile',
            },
        ],
    }
