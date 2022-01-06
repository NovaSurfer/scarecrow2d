set(TEST_SOURCES
        unit.cpp
        doctest/doctest.h
        ../sc2d/src/core/log2.h
        ../sc2d/src/core/log2.cpp
        ../sc2d/src/core/dbg/dbg_asserts.h
        ../sc2d/src/core/compiler.h
        test_data_types.h
        math_tests.cpp
        test_data_types.h)

add_executable(sc2d_test ${TEST_SOURCES})
target_include_directories(sc2d_test PUBLIC ${CMAKE_SOURCE_DIR}/src)

#ParseAndAddCatchTests(game_test)