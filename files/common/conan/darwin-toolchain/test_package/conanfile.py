from conans.model.conan_file import ConanFile
from conans import CMake
import os


class DefaultNameConan(ConanFile):
    name = "DefaultName"
    version = "1.0.0"
    settings = "os", "compiler", "arch", "build_type"
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        cmd = ".%sbin%shello" % (os.sep, os.sep)
        if self.settings.os != "Macos":
            # Ensure it fails
            try:
                self.run(cmd)
            except:
                pass
            else:
                raise Exception("Cross building failed!")
        else:
            self.run(cmd)
