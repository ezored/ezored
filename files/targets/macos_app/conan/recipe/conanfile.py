from conans import ConanFile, CMake


class TargetConan(ConanFile):
    name = "macos_app"
    version = "1.0.0"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {
        "shared": False,
        "fPIC": True,
        "sqlite3:threadsafe": 1,
        "sqlite3:build_executable": False,
        "poco:enable_xml": True,
        "poco:enable_json": True,
        "poco:enable_jwt": False,
        "poco:enable_util": True,
        "poco:enable_mongodb": False,
        "poco:enable_pdf": False,
        "poco:enable_data": False,
        "poco:enable_data_sqlite": False,
        "poco:enable_data_mysql": False,
        "poco:enable_data_odbc": False,
        "poco:enable_data_postgresql": False,
        "poco:enable_sevenzip": False,
        "poco:enable_zip": False,
        "poco:enable_apacheconnector": False,
        "poco:enable_cppparser": False,
        "poco:enable_pocodoc": False,
        "poco:enable_pagecompiler": False,
        "poco:enable_pagecompiler_file2page": False,
    }
    exports_sources = "*"
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.definitions["CMAKE_BUILD_TYPE"] = self.settings.build_type
        cmake.definitions["PROJECT_CONFIG_ARCH"] = self.settings.arch
        cmake.definitions["CMAKE_OSX_DEPLOYMENT_TARGET"] = self.settings.get_safe(
            "os.version"
        )
        cmake.configure()
        cmake.build()

    def requirements(self):
        self.requires("sqlite3/3.34.0")
        self.requires("rapidjson/1.1.0")
        self.requires("poco/1.9.4")
        self.requires("openssl/1.1.1i")
        self.requires("sqlitecpp/2.5.0")
