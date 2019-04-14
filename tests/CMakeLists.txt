set(TEST_SOURCES
        catch2/catch.hpp
        unit.cpp
        math_tests.cpp vec_tests.cpp)

add_executable(game_test ${TEST_SOURCES})
target_include_directories(game_test PRIVATE ${CMAKE_SOURCE_DIR}/src)

ParseAndAddCatchTests(game_test)