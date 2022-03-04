cd conan
conan install -s build_type=Debug conanfile.txt
cd ..
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .