from conans import ConanFile, CMake


class TargetConan(ConanFile):
    name = 'ios_framework'
    version = '1.0.0'
    settings = 'os', 'compiler', 'build_type', 'arch'
    options = {
        'shared': [True, False],
        'fPIC': [True, False],
        'ios_arch': 'ANY',
        'ios_platform': 'ANY',
        'ios_deployment_target': 'ANY',
        'enable_bitcode': 'ANY',
        'enable_arc': 'ANY',
        'enable_visibility': 'ANY',
        'cmake_toolchain_file': 'ANY',
    }
    default_options = {
        'shared': False,
        'fPIC': True,
        'ios_arch': 'ANY',
        'ios_platform': 'ANY',
        'ios_deployment_target': 'ANY',
        'enable_bitcode': 'ANY',
        'enable_arc': 'ANY',
        'enable_visibility': 'ANY',
        'cmake_toolchain_file': 'ANY',
    }
    exports_sources = '*'
    generators = 'cmake'

    def build(self):
        cmake = CMake(self)
        cmake.definitions['CMAKE_BUILD_TYPE'] = self.settings.build_type
        cmake.definitions['CMAKE_TOOLCHAIN_FILE'] = self.options.cmake_toolchain_file
        cmake.definitions['CMAKE_BUILD_TYPE'] = self.settings.build_type
        cmake.definitions['PROJECT_CONFIG_ARCH'] = self.settings.arch        
        cmake.definitions['IOS_ARCH'] = self.options.ios_arch
        cmake.definitions['IOS_PLATFORM'] = self.options.ios_platform
        cmake.definitions['IOS_DEPLOYMENT_TARGET'] = self.options.ios_deployment_target
        cmake.definitions['ENABLE_BITCODE'] = self.options.enable_bitcode
        cmake.definitions['ENABLE_ARC'] = self.options.enable_arc
        cmake.definitions['ENABLE_VISIBILITY'] = self.options.enable_visibility
        cmake.configure()
        cmake.build()

    def requirements(self):
        self.requires('sqlite3/3.27.2@bincrafters/stable')
        self.requires('sqlitecpp/2.3.0@bincrafters/stable')
        self.requires('rapidjson/1.1.0@bincrafters/stable')
