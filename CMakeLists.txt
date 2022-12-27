cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
include("cmake/HunterGate.cmake")
HunterGate(
        URL "https://github.com/NovaSurfer/hunter/archive/refs/tags/v0.25.0.tar.gz"
        SHA1 "7acf0b72a34243aee2acbb44c773c0af1f807240"
)

project(scarecrow2d)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(SC2D_BUILD_TESTS "Enables tests build" OFF)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(sc2d)
add_subdirectory(sc2d_client)

if(SC2D_BUILD_TESTS)
    add_subdirectory(tests)
endif()
#add_subdirectory(sc2d_editor)
#add_subdirectory(sc2d_deps)
