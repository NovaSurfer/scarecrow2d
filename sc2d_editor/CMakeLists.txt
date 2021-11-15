cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(sc2d_editor)

set(HEADERS
        "src/game_main.h"
        "src/menu.h"
        )

set(SOURCES
        "src/game_main.cpp"
        "src/menu.cpp"
        )


set(all_src ${HEADERS} ${SOURCES})

add_executable (sc2d_editor ${all_src})
target_link_libraries(sc2d_editor sc2d)
