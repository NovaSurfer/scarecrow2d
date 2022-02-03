cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(sc2d_client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/)
#add_subdirectory(../sc2d/ ${CMAKE_CURRENT_BINARY_DIR}/sc2d/)

set(HEADERS
        "src/game_main.h"
        )

set(SOURCES
        "src/game_main.cpp"
        "src/main.cpp"
        )


set(all_src ${HEADERS} ${SOURCES})

add_executable (sc2d_client ${all_src})
target_include_directories(sc2d_base
        PUBLIC ../sc2d/src/)
target_link_libraries(sc2d_client sc2d_base)


# ASSETS COPYING

#copy game's config & resources files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cfg/config.ini ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cfg/resources.json ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

# copy game data folder to output path
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/data/
        ${CMAKE_CURRENT_BINARY_DIR}/data/)
