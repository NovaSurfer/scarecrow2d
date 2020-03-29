set(TEST_SOURCES
        doctest/doctest.h
        ../src/memory/pool_allocator.cpp
        unit.cpp
        math_tests.cpp
        vec_tests.cpp ../src/memory/memory.h)

add_executable(game_test ${TEST_SOURCES})
target_include_directories(game_test PUBLIC ${CMAKE_SOURCE_DIR}/src)

#ParseAndAddCatchTests(game_test)