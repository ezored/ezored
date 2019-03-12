def run(params={}):
    return {
        'project_name': 'Sample',
        'min_version': '10.9',
        'conan_profile': 'ezored_macos_app_profile',
        'archs': [
            {'arch': 'x86_64', 'conan_arch': 'x86_64'},
        ],
        'build_types': ['Debug', 'Release']
    }
