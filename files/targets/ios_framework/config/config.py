def run(params={}):
    return {
        'project_name': 'Core',
        'bitcode': True,
        'min_version': '9.0',
        'enable_arc': True,
        'enable_visibility': True,
        'build_types': ['Debug', 'Release'],
        'archs': [
            {
                'arch': 'armv7',
                'conan_arch': 'armv7',
                'platform': 'OS',
                'conan_profile': 'ezored_ios_framework_profile',
            },
            {
                'arch': 'armv7s',
                'conan_arch': 'armv7s',
                'platform': 'OS',
                'conan_profile': 'ezored_ios_framework_profile',
            },
            {
                'arch': 'arm64',
                'conan_arch': 'armv8',
                'platform': 'OS64',
                'conan_profile': 'ezored_ios_framework_profile',
            },
            {
                'arch': 'arm64e',
                'conan_arch': 'armv8.3',
                'platform': 'OS64',
                'conan_profile': 'ezored_ios_framework_profile',
            },
            {
                'arch': 'x86_64',
                'conan_arch': 'x86_64',
                'platform': 'SIMULATOR64',
                'conan_profile': 'ezored_ios_framework_profile',
            },
        ],
        'install_headers': [
            {
                'type': 'dir',
                'path': 'files/djinni/app-domain/generated-src/objc',
            },
            {
                'type': 'dir',
                'path': 'files/djinni/app-core/generated-src/objc',
            },
            {
                'type': 'dir',
                'path': 'files/djinni/app-data-services/generated-src/objc',
            },
            {
                'type': 'dir',
                'path': 'files/djinni/app-system-services/generated-src/objc',
            },
            {
                'type': 'dir',
                'path': 'files/djinni/app-helpers/generated-src/objc',
            },
            {
                'type': 'dir',
                'path': 'files/djinni/datetime/generated-src/objc',
            },
            {
                'type': 'dir',
                'path': 'files/djinni/file-helper/generated-src/objc',
            },
            {
                'type': 'dir',
                'path': 'files/djinni/http-client/generated-src/objc',
            },
            {
                'type': 'dir',
                'path': 'files/djinni/shared-data/generated-src/objc',
            },
            {
                'type': 'dir',
                'path': 'files/djinni/logger/generated-src/objc',
            },
            {
                'type': 'dir',
                'path': 'files/djinni/string-helper/generated-src/objc',
            },
            {
                'type': 'dir',
                'path': 'files/src/file-helper/objc',
            },
            {
                'type': 'dir',
                'path': 'files/src/logger/objc',
            },
            {
                'type': 'dir',
                'path': 'files/src/shared-data/objc',
            },
        ]
    }
