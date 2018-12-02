from conans import ConanFile, tools
import os

build_dir = os.getenv("BUILD_DIR", "build")

def lookup(name, default = None):
    v = default
    if os.path.exists(build_dir + "/" + name):
        v = tools.load(build_dir + "/" + name)
    return os.getenv("CONAN_" + name, v)

class arbiter_example(ConanFile):
    name = lookup("NAME")
    version = lookup("VERSION", "snapshot")
    settings = "os", "compiler", "build_type", "arch"
    url = "https://someurl.here"
    generators = "cmake"
    requires = "gtest/1.8.0@bincrafters/stable"

    def package(self):
        self.copy("*.so", src="src", dst="lib")
        self.copy("*.hpp", src="src", dst="include")

    def package_info(self):
        self.cpp_info.libs = self.collect_libs()
