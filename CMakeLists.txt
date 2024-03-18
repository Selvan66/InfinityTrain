cmake_minimum_required(VERSION 3.1)
project(InfinityTrain)

# Compiler
if (MSVC)
  add_compile_options(
    /bigobj 
    /Wall 
    /sdl 
    /guard:cf 
    /guard:ehcont 
    /CETCOMPAT 
    /fsanitize=address 
    /analyze
  )
else()
  add_compile_options(
    -Wall 
    -Wextra 
    -Wfloat-equal 
    -Wundef 
    -Wshadow 
    -Wpointer-arith 
    -Wcast-align 
    -Wstrict-overflow=5
    -Wwrite-strings
    -Wcast-qual
    -Wswitch-default
    -Wconversion
    -Wunreachable-code
  )
endif()

# Cmake
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 17)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif (NOT CMAKE_BUILD_TYPE)

# Setup
set(CODE_DIR ${CMAKE_SOURCE_DIR}/code)
set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)
set(DOCS_DIR ${CMAKE_SOURCE_DIR}/docs)

file(GLOB_RECURSE SOURCE LIST_DIRECTORY true ${CODE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})

target_include_directories(${PROJECT_NAME} PRIVATE ${CODE_DIR})

# Copy assets to build folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_DIR}/ $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# Packages
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics windows audio system REQUIRED)
find_package(Ogg)
find_package(nlohmann_json)
find_package(exprtk)
target_link_libraries(${PROJECT_NAME} sfml::sfml Ogg::ogg nlohmann_json::nlohmann_json exprtk::exprtk)
target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_INCLUDE_DIR} ${exprtk_INCLUDE_DIR} ${nlohmann_json_INCLUDE_DIR} ${Ogg_INCLUDE_DIR})

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
