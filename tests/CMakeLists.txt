set(TEST_SOURCES
        unit.cpp
        doctest/doctest.h
        ../src/core/log2.h
        ../src/core/log2.cpp
        ../src/memory/pool_allocator.cpp
        ../src/memory/memory.h
        ../src/collections/arr.h
        test_data_types.h
        math_tests.cpp
        vec_tests.cpp
        arr_tests.cpp test_data_types.h)

add_executable(game_test ${TEST_SOURCES})
target_include_directories(game_test PUBLIC ${CMAKE_SOURCE_DIR}/src)

#ParseAndAddCatchTests(game_test)