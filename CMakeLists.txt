cmake_minimum_required(VERSION 3.1)
project(InfinityTrain)

# Compiler
if (MSVC)
    add_compile_options(/bigobj)
else ()
    add_compile_options(-Wa, -mbig-obj)
endif()

# Cmake
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 17)


# Conan
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake"
                TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(CONANFILE conanfile.txt
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Setup
set(CODE_DIR ${CMAKE_SOURCE_DIR}/code)
set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)
set(DOCS_DIR ${CMAKE_SOURCE_DIR}/docs)

file(GLOB_RECURSE SOURCE LIST_DIRECTORY true ${CODE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CODE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CONAN_INCLUDE_DIRS})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_DIR}/ $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# Doxygen
option(BUILD_DOC "Build documentation" ON)
find_package(Doxygen REQUIRED dot)
if (DOXYGEN_FOUND)
    set(README ${CMAKE_SOURCE_DIR}/README.md)
    set(DOXYGEN_OUTPUT_DIRECTORY ${DOCS_DIR})
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE ${README})
    
    doxygen_add_docs(
        doxygen
        ${CODE_DIR} ${README}
        COMMENT "Generate docs")
else(DOXYGEN_FOUND)
    message("Doxygen not found, need to be installed to generate the doxygen")
endif(DOXYGEN_FOUND)