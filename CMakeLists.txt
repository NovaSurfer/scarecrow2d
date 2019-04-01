# cmake ../ -DCMAKE_SH="CMAKE_SH-NOT_FOUND" -DCMAKE_BUILD_TYPE="Debug" -G "MinGW Makefiles"
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(2d_game)

set(CMAKE_CXX_STANDARD 17)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Bindind sources & dependencies
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps)

if(MSVC)
	add_compile_options("/W4" "$<$<CONFIG:RELEASE>:/O2>")
	add_compile_options("/W4" "$<$<CONFIG:DEBUG>:/O0>")
else()
	add_compile_options("-Wall" "-Wextra" "-Wshadow" "-Wnon-virtual-dtor" "-pedantic" "$<$<CONFIG:RELEASE>:-O2>")
	add_compile_options("-Wall" "-Wextra" "-Wshadow" "-Wnon-virtual-dtor" "-pedantic" "$<$<CONFIG:DEBUG>:-O0>")
endif()

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++")
endif()

set(SOURCE_FILES
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/core/shader.h                     ${SRC_DIR}/core/shader.cpp
        ${SRC_DIR}/core/texture.h                    ${SRC_DIR}/core/texture.cpp
        ${SRC_DIR}/filesystem/resourceHolder.h       ${SRC_DIR}/filesystem/resourceHolder.cpp
        ${SRC_DIR}/filesystem/configLoader.h         ${SRC_DIR}/filesystem/configLoader.cpp
        ${SRC_DIR}/filesystem/configNames.h          ${SRC_DIR}/filesystem/configNames.cpp
        ${LIB_DIR}/stb/stb_image.h                   ${LIB_DIR}/stb/stb_image.c
        ${LIB_DIR}/nlohmann/json.hpp
        ${SRC_DIR}/core/window.h                     ${SRC_DIR}/core/window.cpp
        ${SRC_DIR}/math/size2d.h
        ${SRC_DIR}/math/vector2.h
        ${SRC_DIR}/math/vector3.h
        ${SRC_DIR}/math/vector4.h
        ${SRC_DIR}/math/matrix2.h
        ${SRC_DIR}/math/matrix3.h
        ${SRC_DIR}/math/matrix4.h
        ${SRC_DIR}/math/geometry2d.h
        ${SRC_DIR}/math/transform.h                  ${SRC_DIR}/math/transform.cpp
        ${SRC_DIR}/math/utils.h
        ${SRC_DIR}/core/log2.h                       ${SRC_DIR}/core/log2.cpp
        ${SRC_DIR}/core/sprite.h                     ${SRC_DIR}/core/sprite.cpp
		${SRC_DIR}/memory/aligned_allocator.h 		 ${SRC_DIR}/memory/aligned_allocator.cpp
		${SRC_DIR}/memory/allocator.h 			     ${SRC_DIR}/memory/allocator.cpp
		${SRC_DIR}/memory/pool_allocator.cpp  		 ${SRC_DIR}/memory/pool_allocator.h)
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

set(GLFW_DIR "${LIB_DIR}/glfw")
set(BUILD_SHARED_LIBS ON CACHE INTERNAL "Build the GLFW DLL / shared library / dynamic library")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PUBLIC "${GLFW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PUBLIC "GLFW_INCLUDE_NONE")

# GLAD
set(GLAD_DIR "${LIB_DIR}/glad")
add_subdirectory("${GLAD_DIR}")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")
target_compile_definitions(glad PUBLIC GLAD_GLAPI_EXPORT PRIVATE GLAD_GLAPI_EXPORT_BUILD)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "/")

# GLM
set(GLM_DIR "${LIB_DIR}/glm")
set(GLM_TEST_ENABLE OFF CACHE INTERNAL "Build GLM unit tests")
add_subdirectory("${GLM_DIR}")
target_link_libraries(${PROJECT_NAME} "${GLM_LIBRARIES}")

#copy game's config & resources files
configure_file(${CMAKE_SOURCE_DIR}/cfg/config.ini ${CMAKE_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/cfg/resources.json ${CMAKE_BINARY_DIR} COPYONLY)

# copy game data folder to output path
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data/
        ${CMAKE_BINARY_DIR}/data/)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/shaders/
        ${CMAKE_BINARY_DIR}/data/shaders/)