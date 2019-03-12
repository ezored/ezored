def run(params={}):
    return {
        'project_name': 'Sample',
        'conan_profile': 'ezored_windows_app_profile',
        'archs': [
            {'arch': 'x86_64', 'conan_arch': 'x86_64'},
        ],
        'build_types': ['Debug', 'Release']
    }
