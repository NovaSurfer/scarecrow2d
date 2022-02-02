cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
include("cmake/HunterGate.cmake")
HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.300.tar.gz"
        SHA1 "1151d539465d9cdbc880ee30f794864aec11c448"
)

project(scarecrow2d)

option(SC2D_BUILD_TESTS "Enables tests build" OFF)

set(CMAKE_CXX_STANDARD 17)
set(sc2d_root ${CMAKE_CURRENT_SOURCE_DIR})
set(sc2d_binary ${PROJECT_BINARY_DIR}/sc2d_engine)


add_subdirectory(sc2d)
add_subdirectory(sc2d_client)

if(SC2D_BUILD_TESTS)
    add_subdirectory(tests)
endif()
#add_subdirectory(sc2d_editor)
#add_subdirectory(sc2d_deps)
