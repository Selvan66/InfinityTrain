conan install . --build=missing --output-folder build
cmake --preset conan-release -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cmake --build build
