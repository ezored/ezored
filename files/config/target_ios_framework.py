def run(proj_path, target_name, params):
    return {
        'project_name': 'Ezored',
        'build_types': ['Debug'],
        'archs': [
            {
                'arch': 'armv7',
                'conan_arch': 'armv7',
                'platform': 'OS',
                'conan_profile': 'ezored_ios_framework_profile',
                'min_version': '9.0',
            },
            {
                'arch': 'armv7s',
                'conan_arch': 'armv7s',
                'platform': 'OS',
                'conan_profile': 'ezored_ios_framework_profile',
                'min_version': '9.0',
            },
            {
                'arch': 'arm64',
                'conan_arch': 'armv8',
                'platform': 'OS64',
                'conan_profile': 'ezored_ios_framework_profile',
                'min_version': '9.0',
            },
            {
                'arch': 'arm64e',
                'conan_arch': 'armv8.3',
                'platform': 'OS64',
                'conan_profile': 'ezored_ios_framework_profile',
                'min_version': '9.0',
            },
            {
                'arch': 'x86_64',
                'conan_arch': 'x86_64',
                'platform': 'SIMULATOR64',
                'conan_profile': 'ezored_ios_framework_profile',
                'min_version': '9.0',
            },
        ],
        'install_headers': [
            {
                'type': 'dir',
                'path': 'files/djinni/app-domain/generated-src/objc',
            },
            {
                'type': 'dir',
                'path': 'files/djinni/app-enums/generated-src/objc',
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
