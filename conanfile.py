from conans import ConanFile, CMake

class TypeLiteConan(ConanFile):
    version = "0.0.0"
    name = "type-lite"
    description = "Strong types for C++98, C++11 and later in a single-file header-only library"
    license = "Boost Software License - Version 1.0. http://www.boost.org/LICENSE_1_0.txt"
    url = "https://github.com/martinmoene/type-lite.git"
    exports_sources = "include/nonstd/*", "CMakeLists.txt", "cmake/*", "LICENSE.txt"
    settings = "compiler", "build_type", "arch"
    build_policy = "missing"
    author = "Martin Moene"

    def build(self):
        """Avoid warning on build step"""
        pass

    def package(self):
        """Run CMake install"""
        cmake = CMake(self)
        cmake.definitions["TYPE_LITE_OPT_BUILD_TESTS"] = "OFF"
        cmake.definitions["TYPE_LITE_OPT_BUILD_EXAMPLES"] = "OFF"
        cmake.configure()
        cmake.install()

    def package_info(self):
        self.info.header_only()
