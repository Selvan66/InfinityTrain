#!/bin/sh

if [ "$#" -eq 0 ]; then
  echo "No build type specified. Please specifiy 'debug' or 'release'"
  exit 1
fi

if [ "$1" == "debug" ]; then
  conan install . --build=missing --output-folder build --settings=build_type=Debug
  cmake --preset conan-debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1
  cmake --build build -j8
elif [ "$1" == "release" ]; then
  conan install . --build=missing --output-folder build --settings=build_type=Release
  cmake --preset conan-release -DCMAKE_EXPORT_COMPILE_COMMANDS=1
  cmake --build build -j8
else
  echo "Wrong build type. Please specifiy 'debug' or 'release'"
  exit 1
fi
