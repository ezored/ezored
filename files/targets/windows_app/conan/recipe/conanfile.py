from conans import ConanFile, CMake


class TargetConan(ConanFile):
    name = "windows_app"
    version = "1.0.0"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {
        "shared": False,
        "fPIC": True,
        "sqlite3:threadsafe": 1,
        "poco:enable_xml": False,
        "poco:enable_json": False,
        "poco:enable_mongodb": False,
        "poco:enable_pdf": False,
        "poco:enable_data": False,
        "poco:enable_data_sqlite": False,
        "poco:enable_data_mysql": False,
        "poco:enable_data_odbc": False,
        "poco:enable_sevenzip": False,
        "poco:enable_zip": False,
        "poco:enable_apacheconnector": False,
        "poco:enable_cppparser": False,
        "poco:enable_pocodoc": False,
        "poco:enable_pagecompiler": False,
        "poco:enable_pagecompiler_file2page": False,
        "poco:enable_tests": False,
        "poco:poco_unbundled": False,
        "poco:cxx_14": False,
    }
    exports_sources = "*"
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.definitions["CMAKE_BUILD_TYPE"] = self.settings.build_type
        cmake.definitions["PROJECT_CONFIG_ARCH"] = self.settings.arch
        cmake.configure()
        cmake.build()

    def imports(self):
        self.copy("*.dll", dst="bin", keep_path=False)

    def requirements(self):
        self.requires("sqlite3/3.31.1")
        self.requires("rapidjson/1.1.0")
        self.requires("poco/1.10.1")
        self.requires("openssl/1.1.1c")
        self.requires("sqlitecpp/2.5.0")
