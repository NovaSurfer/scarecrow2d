cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(2d_game)

set(CMAKE_CXX_STANDARD 17)
# Cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
# Bindind sources & dependencies
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps)
# GCC compilation flags
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(GCC_COMPILE_FLAGS "-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic")
endif()

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++")
endif()


set(SOURCE_FILES
        ${SRC_DIR}/oglMain.cpp
        ${SRC_DIR}/shader.h
        ${SRC_DIR}/shader.cpp
        ${SRC_DIR}/texture.h
        ${SRC_DIR}/texture.cpp
        ${SRC_DIR}/filesystem/resourceHolder.h
        ${SRC_DIR}/filesystem/resourceHolder.cpp
        ${SRC_DIR}/filesystem/configLoader.h
        ${SRC_DIR}/filesystem/configLoader.cpp
        ${SRC_DIR}/filesystem/configNames.h
        ${SRC_DIR}/filesystem/configNames.cpp
        ${LIB_DIR}/stb/stb_image.h
        ${LIB_DIR}/stb/stb_image.c
        ${LIB_DIR}/nlohmann/json.hpp
        ${SRC_DIR}/window.cpp
        ${SRC_DIR}/window.h)
#        ${SRC_DIR}/game2.cpp
#        ${SRC_DIR}/game2.h)
#        ${SRC_DIR}/textureManager.cpp
#        ${SRC_DIR}/textureManager.h
#        ${SRC_DIR}/gameObject.cpp
#        ${SRC_DIR}/gameObject.h
#        ${SRC_DIR}/levelmap.cpp
#        ${SRC_DIR}/levelmap.h
#        ${SRC_DIR}/components/ecs.h
#        ${SRC_DIR}/components/components.h
#        ${SRC_DIR}/components/transform.cpp
#        ${SRC_DIR}/components/transform.h
#        ${SRC_DIR}/components/sprite.cpp
#        ${SRC_DIR}/components/sprite.h
#        ${SRC_DIR}/math/vector.h
#        ${SRC_DIR}/components/inputController.cpp
#        ${SRC_DIR}/components/inputController.h
#        ${SRC_DIR}/utils/ini_io.h
#        ${SRC_DIR}/utils/ini_io.cpp
#        ${SRC_DIR}/inputManager.cpp
#        ${SRC_DIR}/inputManager.h
#        ${SRC_DIR}/math/utils.h
#        ${SRC_DIR}/math/matrices.h
#        ${SRC_DIR}/math/geometry2d.h
#        ${SRC_DIR}/physics/collision2d.h
#        ${LIB_DIR}/stb/stb_image.h
#        ${LIB_DIR}/stb/stb_image.c)

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

include(CTest)
include(ParseAndAddCatchTests)

add_subdirectory(tests)

# -------------- WILL BE REMOVED -------------- #
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR})

target_link_libraries (${PROJECT_NAME}
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES})
# -------------- /WILL BE REMOVED -------------- #

# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")
set(BUILD_SHARED_LIBS ON CACHE INTERNAL "Build the GLFW DLL / shared library / dynamic library")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

# GLAD
set(GLAD_DIR "${LIB_DIR}/glad")
add_subdirectory("${GLAD_DIR}")
#add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")
target_compile_definitions(glad PUBLIC GLAD_GLAPI_EXPORT PRIVATE GLAD_GLAPI_EXPORT_BUILD)


# GLM
set(GLM_DIR "${LIB_DIR}/glm")
add_subdirectory("${GLM_DIR}")
target_link_libraries(${PROJECT_NAME} "${GLM_LIBRARIES}")


#copy game config file
configure_file(${CMAKE_SOURCE_DIR}/cfg/config.ini ${CMAKE_BINARY_DIR} COPYONLY)
if(WIN32)
    configure_file(${CMAKE_BINARY_DIR}/deps/glad/libglad.dll ${CMAKE_BINARY_DIR} COPYONLY)
    configure_file(${CMAKE_BINARY_DIR}/deps/glfw/src/glfw3.dll ${CMAKE_BINARY_DIR} COPYONLY)
endif()

if (UNIX AND NOT APPLE)
    configure_file(${CMAKE_BINARY_DIR}/deps/glad/libglad.so ${CMAKE_BINARY_DIR} COPYONLY)
    configure_file(${CMAKE_BINARY_DIR}/deps/glfw/src/glfw3.so ${CMAKE_BINARY_DIR} COPYONLY)
endif()
# copy game data folder to output path
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data/
        ${CMAKE_BINARY_DIR}/data/)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/shaders
        ${CMAKE_BINARY_DIR}/data/shaders)