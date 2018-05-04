cmake_minimum_required(VERSION 3.10)
project(2d_engine)

set(CMAKE_CXX_STANDARD 17)

#set(SDL2_PATH "E:\\SDL\\SDL2-devel-2.0.8-mingw.tar\\SDL2-devel-2.0.8-mingw\\SDL2-2.0.8\\x86_64-w64-mingw32")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${2d_engine_SOURCE_DIR}/cmake/modules")
# create a bin folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)



#set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${SDL2_SOURCE_DIR}/cmake/configs")

#file(COPY ${2d_engine_SOURCE_DIR}/res DESTINATION ${2d_engine_SOURCE_DIR}/bin)
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
        src/components/inputController.h)


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
