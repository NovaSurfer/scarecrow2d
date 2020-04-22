set(BENCH_SOURCES
        bench.cpp
        picobench/picobench.hpp
        ../src/core/compiler.h
        ../src/memory/memory.h
        ../src/memory/pool_allocator.h
        ../src/memory/pool_allocator.cpp
        ../src/collections/vec.h)


add_executable(game_bench ${BENCH_SOURCES})
target_include_directories(game_bench PUBLIC ${CMAKE_SOURCE_DIR}/src)

