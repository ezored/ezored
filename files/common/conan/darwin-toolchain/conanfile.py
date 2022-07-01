from conans import ConanFile, tools
from conans.errors import ConanInvalidConfiguration


class DarwinToolchainConan(ConanFile):
    name = "darwin-toolchain"
    version = "1.0.0"
    license = "Apple"
    settings = "os", "arch", "build_type", "os_build", "compiler"
    options = {
        "enable_bitcode": [True, False, None],
        "enable_arc": [True, False, None],
        "enable_visibility": [True, False, None],
    }
    default_options = {
        "enable_bitcode": None,
        "enable_arc": None,
        "enable_visibility": None,
    }
    description = "Darwin toolchain to (cross) compile macOS/iOS/watchOS/tvOS"
    url = "https://github.com/ezored/ezored"
    build_policy = "missing"

    # -----------------------------------------------------------------------------
    def config_options(self):
        if self.settings.os == "Macos":
            self.options.enable_bitcode = None

        if self.settings.os == "watchOS":
            self.options.enable_bitcode = True

        if self.settings.os == "tvOS":
            self.options.enable_bitcode = True

    # -----------------------------------------------------------------------------
    def configure(self):
        if self.settings.os_build != "Macos":
            raise ConanInvalidConfiguration("Build machine must be Macos")

        if not tools.is_apple_os(self.settings.os):
            raise ConanInvalidConfiguration("OS must be an Apple OS")

        if self.settings.os in ["watchOS", "tvOS"] and not self.options.enable_bitcode:
            raise ConanInvalidConfiguration("Bitcode is required on watchOS/tvOS")

        if self.settings.os == "Macos" and self.settings.arch not in [
            "x86",
            "x86_64",
            "armv8",
        ]:
            raise ConanInvalidConfiguration(
                "macOS: Only supported archs: [x86, x86_64, armv8]"
            )

        if self.settings.os == "iOS" and self.settings.arch not in [
            "armv7",
            "armv7s",
            "armv8",
            "armv8.3",
            "x86",
            "x86_64",
        ]:
            raise ConanInvalidConfiguration(
                "iOS: Only supported archs: [armv7, armv7s, armv8, armv8.3, x86, x86_64]"
            )

        if self.settings.os == "tvOS" and self.settings.arch not in ["armv8", "x86_64"]:
            raise ConanInvalidConfiguration(
                "tvOS: Only supported archs: [armv8, x86_64]"
            )

        if self.settings.os == "watchOS" and self.settings.arch not in [
            "armv7k",
            "armv8_32",
            "x86",
            "x86_64",
        ]:
            raise ConanInvalidConfiguration(
                "watchOS: Only supported archs: [armv7k, armv8_32, x86, x86_64]"
            )

    # -----------------------------------------------------------------------------
    def package_info(self):
        # Settings
        settings_target = None

        if hasattr(self, "settings_target"):
            settings_target = self.settings_target
            self.output.info("Settings: Target")
        else:
            settings_target = self.settings
            self.output.info("Settings: Default")

        # Sysroot
        xcrun = tools.XCRun(settings_target)
        sysroot = xcrun.sdk_path

        self.cpp_info.sysroot = sysroot
        common_flags = ["-isysroot%s" % sysroot]

        self.env_info.CONAN_CMAKE_OSX_SYSROOT = sysroot
        self.env_info.SDKROOT = sysroot

        # Bitcode
        if self.options.enable_bitcode is None:
            self.output.info("Bitcode enabled: IGNORED")
        else:
            if self.options.enable_bitcode:
                self.output.info("Bitcode enabled: YES")

                self.env_info.CMAKE_XCODE_ATTRIBUTE_ENABLE_BITCODE = "YES"
                self.env_info.CMAKE_XCODE_ATTRIBUTE_BITCODE_GENERATION_MODE = "bitcode"

                build_type = settings_target.get_safe("build_type")

                if build_type.lower() == "debug":
                    common_flags.append("-fembed-bitcode-marker")
                else:
                    common_flags.append("-fembed-bitcode")
            else:
                self.output.info("Bitcode enabled: NO")

        # ARC
        if self.options.enable_arc is None:
            self.output.info("ObjC ARC enabled: IGNORED")
        else:
            if self.options.enable_arc:
                common_flags.append("-fobjc-arc")
                self.env_info.CMAKE_XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC = "YES"
                self.output.info("ObjC ARC enabled: YES")
            else:
                common_flags.append("-fno-objc-arc")
                self.env_info.CMAKE_XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC = "NO"
                self.output.info("ObjC ARC enabled: NO")

        # Visibility
        if self.options.enable_visibility is None:
            self.output.info("Visibility enabled: IGNORED")
        else:
            if self.options.enable_visibility:
                self.env_info.CMAKE_XCODE_ATTRIBUTE_GCC_SYMBOLS_PRIVATE_EXTERN = "NO"
                self.output.info("Visibility enabled: YES")
            else:
                common_flags.append("-fvisibility=hidden")
                self.env_info.CMAKE_XCODE_ATTRIBUTE_GCC_SYMBOLS_PRIVATE_EXTERN = "YES"
                self.output.info("Visibility enabled: NO")

        self.cpp_info.cflags.extend(common_flags)
        self.cpp_info.cxxflags.extend(common_flags)
        self.cpp_info.sharedlinkflags.extend(common_flags)
        self.cpp_info.exelinkflags.extend(common_flags)

        cflags_str = " ".join(self.cpp_info.cflags)
        cxxflags_str = " ".join(self.cpp_info.cxxflags)
        ldflags_str = " ".join(self.cpp_info.sharedlinkflags)

        self.env_info.CFLAGS = cflags_str
        self.env_info.ASFLAGS = cflags_str
        self.env_info.CPPFLAGS = cxxflags_str
        self.env_info.CXXFLAGS = cxxflags_str
        self.env_info.LDFLAGS = ldflags_str

    # -----------------------------------------------------------------------------
    def package_id(self):
        self.info.clear()
