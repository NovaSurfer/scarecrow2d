set(TEST_SOURCES
        catch2/catch.hpp
        unit.cpp
        math_tests.cpp)

add_executable(game_test ${TEST_SOURCES})
target_link_libraries(game_test lib)

ParseAndAddCatchTests(game_test)