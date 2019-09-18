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
        "Poco:enable_xml": False,
        "Poco:enable_json": False,
        "Poco:enable_mongodb": False,
        "Poco:enable_pdf": False,
        "Poco:enable_data": False,
        "Poco:enable_data_sqlite": False,
        "Poco:enable_data_mysql": False,
        "Poco:enable_data_odbc": False,
        "Poco:enable_sevenzip": False,
        "Poco:enable_zip": False,
        "Poco:enable_apacheconnector": False,
        "Poco:enable_cppparser": False,
        "Poco:enable_pocodoc": False,
        "Poco:enable_pagecompiler": False,
        "Poco:enable_pagecompiler_file2page": False,
        "Poco:enable_tests": False,
        "Poco:poco_unbundled": False,
        "Poco:cxx_14": False,
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
        self.requires("sqlite3/3.29.0@bincrafters/stable")
        self.requires("sqlitecpp/2.4.0@bincrafters/stable")
        self.requires("rapidjson/1.1.0@bincrafters/stable")
        self.requires("Poco/1.9.4@pocoproject/stable")
        self.requires("OpenSSL/1.1.1c@conan/stable")
