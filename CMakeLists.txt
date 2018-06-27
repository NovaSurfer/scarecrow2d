cmake_minimum_required(VERSION 3.10)
project(2d_engine)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${2d_engine_SOURCE_DIR}/cmake/modules")

# create a bin (output) directory


#copy game config file
configure_file(${CMAKE_SOURCE_DIR}/cfg/config.ini ${CMAKE_BINARY_DIR} COPYONLY)


set(SOURCE_FILES
        src/main.cpp
        src/game.cpp
        src/game.h
        src/textureManager.cpp
        src/textureManager.h
        src/gameObject.cpp
        src/gameObject.h
        src/levelmap.cpp
        src/levelmap.h
        src/components/ecs.h
        src/components/components.h
        src/components/transform.cpp
        src/components/transform.h
        src/components/sprite.cpp
        src/components/sprite.h
        src/math/vector.h
        src/components/inputController.cpp
        src/components/inputController.h
        src/utils/ini_io.h
        src/utils/ini_io.cpp
        src/inputManager.cpp
        src/inputManager.h
        src/math/utils.h)


add_executable(2d_engine ${SOURCE_FILES})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR})

target_link_libraries(2d_engine ${SDL2_LIBRARY}
                                ${SDL2_IMAGE_LIBRARIES}
                                ${SDL2_TTF_LIBRARIES})

# copy game data folder to output path
add_custom_command(TARGET 2d_engine PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        ${CMAKE_BINARY_DIR}/data)
