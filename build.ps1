
param(
    [string]$BuildType
)

if (-not $BuildType) {
    Write-Host "No build type specified. Please specify 'debug' or 'release'"
    exit 1
}

switch ($BuildType) {
    "debug" {
        conan install . --build=missing --output-folder build --settings=build_type=Debug
        cmake --preset conan-debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1
        cmake --build build
    }
    "release" {
        conan install . --build=missing --output-folder build --settings=build_type=Release
        cmake --preset conan-release -DCMAKE_EXPORT_COMPILE_COMMANDS=1
        cmake --build build
    }
    default {
        Write-Host "Wrong build type. Please specify 'debug' or 'release'"
        exit 1
    }
}
