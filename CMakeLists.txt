cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(scarecrow2d)

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
	add_compile_options("-Wall" "-Wextra" "-Wshadow" "-Wnon-virtual-dtor" "-pedantic" "-Wpadded" "$<$<CONFIG:RELEASE>:-O2>")
	add_compile_options("-Wall" "-Wextra" "-Wshadow" "-Wnon-virtual-dtor" "-pedantic" "-Wpadded" "$<$<CONFIG:DEBUG>:-O0>")
endif()

	add_compile_options("-fno-exceptions")

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++")
endif()

file(GLOB_RECURSE SHADER_FILES CONFIGURE_DEPENDS
		${SRC_DIR}/shaders/*.frag
		${SRC_DIR}/shaders/*.vert)

# Adds raw string literal for each shader file
foreach(shader_file ${SHADER_FILES})
	file(STRINGS ${shader_file} shader_str NEWLINE_CONSUME)
	if(NOT ${shader_str} MATCHES "(R\"\)")
		set(SHADER ${shader_str})
		configure_file(shader_template.sc2d ${shader_file})
	endif()
endforeach()

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
		${SHADER_FILES}
		${SRC_DIR}/*.h
		${SRC_DIR}/*.cpp
		${SRC_DIR}/*.inl)

file(GLOB_RECURSE DEPS_FILES CONFIGURE_DEPENDS
		${LIB_DIR}/stb/stb_image.h	deps/stb/stb_image.c
		${LIB_DIR}/nlohmann/json.hpp
		${LIB_DIR}/miniz/miniz.c		deps/miniz/miniz.h
		${LIB_DIR}/base64/base64.h	deps/base64/base64.cpp)

file(GLOB_RECURSE SHADER_FILES CONFIGURE_DEPENDS
		${SRC_DIR}/shaders/*.frag
		${SRC_DIR}/shaders/*.vert)

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${DEPS_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

include(CTest)
add_subdirectory(tests)
add_subdirectory(benchmarks)

# GLFW
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
set(GLAD_PROFILE "core")
set(GLAD_API "gl=3.3")
set(GLAD_EXTENSIONS "GL_ARB_instanced_arrays, GL_ARB_bindless_texture, GL_ARB_buffer_storage")
set(GLAD_SPEC "gl")
add_subdirectory("${GLAD_DIR}")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")
target_compile_definitions(glad PUBLIC GLAD_GLAPI_EXPORT PRIVATE GLAD_GLAPI_EXPORT_BUILD)

# FREETYPE
set(FREETYPE_DIR "${LIB_DIR}/freetype2")
set(FREETYPE_INCLUDE_DIRS "${FREETYPE_DIR}")
find_package(Freetype REQUIRED)
target_link_libraries(${PROJECT_NAME} ${FREETYPE_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${FREETYPE_INCLUDE_DIRS})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "/")

# GLM
#set(GLM_DIR "${LIB_DIR}/glm")
#set(GLM_TEST_ENABLE OFF CACHE INTERNAL "Build GLM unit tests")
#add_subdirectory("${GLM_DIR}")
#target_link_libraries(${PROJECT_NAME} "${GLM_LIBRARIES}")

#copy game's config & resources files
configure_file(${CMAKE_SOURCE_DIR}/cfg/config.ini ${CMAKE_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/cfg/resources.json ${CMAKE_BINARY_DIR} COPYONLY)

# copy game data folder to output path
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data/
        ${CMAKE_BINARY_DIR}/data/)


#Docs
add_subdirectory ("docs")

