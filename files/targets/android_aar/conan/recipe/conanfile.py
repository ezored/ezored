from conans import ConanFile, CMake


class TargetConan(ConanFile):
    name = 'android_aar'
    version = '1.0.0'
    settings = 'os', 'compiler', 'build_type', 'arch'
    options = {
        'shared': [True, False],
        'fPIC': [True, False],
    }
    default_options = {
        'shared': False,
        'fPIC': True,
    }
    exports_sources = '*'
    generators = 'cmake'

    def build(self):
        cmake = CMake(self)
        cmake.definitions['CMAKE_BUILD_TYPE'] = self.settings.build_type
        cmake.definitions['PROJECT_CONFIG_ARCH'] = self.settings.arch        
        cmake.configure()
        cmake.build()

    def requirements(self):
        self.requires('sqlite3/3.27.2@bincrafters/stable')
        self.requires('sqlitecpp/2.3.0@bincrafters/stable')
        self.requires('rapidjson/1.1.0@bincrafters/stable')
