cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

project(sc2d_base)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

hunter_add_package(aglet)
find_package(aglet CONFIG REQUIRED)

hunter_add_package(Assimp)
find_package(Assimp CONFIG REQUIRED)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)

hunter_add_package(Vulkan-Headers)
find_package(VulkanHeaders CONFIG REQUIRED)

hunter_add_package(nlohmann_json)
find_package(nlohmann_json CONFIG REQUIRED)

hunter_add_package(freetype)
find_package(freetype CONFIG REQUIRED)

hunter_add_package(glfw)
find_package(glfw3 REQUIRED)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

if(ANDROID)
    target_compile_definitions(sc2d_base PRIVATE GLFW_INCLUDE_ES32)
endif()


hunter_add_package(miniz)
find_package(miniz CONFIG REQUIRED)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${SRC_DIR})

file(GLOB_RECURSE SHADER_FILES CONFIGURE_DEPENDS
        ${SRC_DIR}/shaders/*.frag
        ${SRC_DIR}/shaders/*.vert)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
        ${SHADER_FILES}
        ${SRC_DIR}/core/*.h
        ${SRC_DIR}/filesystem/*.h
        ${SRC_DIR}/math/*.h
        ${SRC_DIR}/physics/*.h
        ${SRC_DIR}/utils/*.h
        )

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        ${SRC_DIR}/core/*.cpp
        ${SRC_DIR}/core/*.inl
        ${SRC_DIR}/filesystem/*.cpp
        ${SRC_DIR}/filesystem/*.inl
        ${SRC_DIR}/math/*.cpp
        ${SRC_DIR}/math/*.inl
        ${SRC_DIR}/physics/*.cpp
        ${SRC_DIR}/physics/*.inl
        ${SRC_DIR}/utils/*.cpp
        ${SRC_DIR}/utils/*.inl
        ${SRC_DIR}/stb_image.c
        )

set(all_src ${HEADERS} ${SOURCES})

add_subdirectory(${SRC_DIR}/base)
add_library(sc2d_base STATIC ${all_src})

target_link_libraries(sc2d_base PUBLIC
        Assimp::assimp
        sc_base
        aglet::aglet
        Vulkan::Headers
        nlohmann_json::nlohmann_json
        freetype::freetype
        miniz::miniz
        glfw)



