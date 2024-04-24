cmake_minimum_required(VERSION 3.25)

project(
    Database_Benchmark
    VERSION 0.0.1
    DESCRIPTION "A simple benchmark project for several database management systems"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "Error: CMAKE_TOOLCHAIN_FILE is not set. Make sure to set it to the path of vcpkg.cmake")
endif()

include(${CMAKE_SOURCE_DIR}/cmake/dependencies.cmake)
find_packages()


add_subdirectory(src)


