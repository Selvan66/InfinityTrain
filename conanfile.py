from conan import ConanFile


class ConanBuild(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def build_requirements(self):
        self.tool_requires("cmake/[>=3.10]")

    def requirements(self):
        self.requires("ogg/1.3.5")
        self.requires("sfml/2.5.1")
        self.requires("nlohmann_json/3.10.5")
        self.requires("exprtk/0.0.1")
        self.requires("spdlog/1.13.0")
