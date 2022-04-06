cd conan
conan install -s build_type=Debug -s compiler.version=16 -s arch=x86_64 conanfile.txt --build=missing
cd ..
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .