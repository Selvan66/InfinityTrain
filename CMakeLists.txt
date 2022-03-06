cmake_minimum_required(VERSION 3.1)
project(InfinityTrain)

set(CMAKE_CXX_STANDARD 17)

set(CODE_DIR ${CMAKE_SOURCE_DIR}/code)
set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)
set(CONAN_DIR ${CMAKE_SOURCE_DIR}/conan)

include(${CONAN_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

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
    doxygen_add_docs(
        doxygen
        ${CODE_DIR}
        COMMENT "Generate docs")
else(DOXYGEN_FOUND)
    message("Doxygen not found, need to be installed to generate the doxygen")
endif(DOXYGEN_FOUND)