cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

project(sc2d_base)

hunter_add_package(aglet)
find_package(aglet CONFIG REQUIRED)

hunter_add_package(nlohmann_json)
find_package(nlohmann_json CONFIG REQUIRED)

hunter_add_package(freetype)
find_package(freetype CONFIG REQUIRED)

hunter_add_package(glfw)
find_package(glfw3 REQUIRED)

hunter_add_package(miniz)
find_package(miniz CONFIG REQUIRED)

#hunter_add_package(stb)
#find_package(stb CONFIG REQUIRED)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${SRC_DIR})
file(GLOB_RECURSE SHADER_FILES CONFIGURE_DEPENDS
        ${SRC_DIR}/shaders/*.frag
        ${SRC_DIR}/shaders/*.vert)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
        ${SHADER_FILES}
        ${SRC_DIR}/*.h
        )

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        ${SRC_DIR}/*.cpp
        ${SRC_DIR}/*.c
        ${SRC_DIR}/*.inl
        )

set(all_src ${HEADERS} ${SOURCES})
add_library(sc2d_base STATIC ${all_src})

# use external libs
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../deps ${PROJECT_BINARY_DIR}/deps)

target_link_libraries(sc2d_base PUBLIC aglet::aglet nlohmann_json::nlohmann_json freetype::freetype miniz::miniz glfw)
#target_link_libraries(sc2d PRIVATE sc2d_deps)

#target_include_directories(sc2d
#        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../deps
#        PRIVATE "${SRC_DIR}")


