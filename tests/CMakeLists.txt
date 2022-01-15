cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

project(sc2d_test)

set(TEST_SOURCES
        unit.cpp
        doctest/doctest.h
        ../sc2d/src/core/log2.h
        ../sc2d/src/core/log2.cpp
        ../sc2d/src/core/dbg/dbg_asserts.h
        ../sc2d/src/core/compiler.h
        test_data_types.h
        math_tests.cpp
        )

add_executable(sc2d_test ${TEST_SOURCES})
target_include_directories(sc2d_test PUBLIC ../sc2d/src/)

#ParseAndAddCatchTests(game_test)