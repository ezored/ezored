def run(params={}):
    return {
        'project_name': 'Core',
        'bitcode': True,
        'min_version': '9.0',
        'enable_arc': True,
        'enable_visibility': True,
        'conan_profile': 'ezored_ios_framework_profile',
        'archs': [
            {'arch': 'armv7', 'conan_arch': 'armv7', 'platform': 'OS'},
            {'arch': 'armv7s', 'conan_arch': 'armv7s', 'platform': 'OS'},
            {'arch': 'arm64', 'conan_arch': 'armv8', 'platform': 'OS64'},
            {'arch': 'arm64e', 'conan_arch': 'armv8.3', 'platform': 'OS64'},
            {'arch': 'x86_64', 'conan_arch': 'x86_64', 'platform': 'SIMULATOR64'},
        ],
        'build_types': ['Debug', 'Release'],
        'install_headers': [
            {
                'type': 'dir',
                'path': 'files/djinni/001-app-domain/generated-src/objc',
            },
            {
                'type': 'dir',
                'path': 'files/djinni/002-app-core/generated-src/objc',
            },
            {
                'type': 'dir',
                'path': 'files/djinni/003-app-data-services/generated-src/objc',
            },
            {
                'type': 'dir',
                'path': 'files/djinni/004-app-system-service/generated-src/objc',
            },
            {
                'type': 'dir',
                'path': 'files/djinni/005-app-helpers/generated-src/objc',
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
                'path': 'files/djinni/httpclient/generated-src/objc',
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
                'path': 'files/src/httpclient/objc',
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
