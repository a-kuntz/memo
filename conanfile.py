from conans import ConanFile, CMake, tools


class MemorizerConan(ConanFile):
    name = "memorizer"
    version = "0.1"
    license = "MIT"
    author = "Andreas Kuntz <50048909+a-kuntz@users.noreply.github.com>"
    url = "https://github.com/a-kuntz/memo"
    description = "Simple c++ 17 function memorizer library"
    topics = ("memoizer", "memorizer",)
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    generators = "cmake"
    requires = "gtest/1.8.1"
    exports_sources = "lib/include/*"
    no_copy_source = True

    def source(self):
        self.run("git clone git@github.com:a-kuntz/memo.git")

    def build(self):
        cmake = CMake(self)
        cmake.verbose = True
        cmake.configure(source_folder="memo")
        cmake.build()
        cmake.test(output_on_failure=True)

    def package(self):
        self.copy("*.h", dst="include", src="lib/include")

    # def package_info(self):
    #     self.cpp_info.includedirs = ['include']  # Ordered list of include paths

    def package_id(self):
        self.info.header_only()