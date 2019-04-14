//
// Created by maksim.ruts on 28.3.19.
//

#ifndef INC_2D_GAME_ALLOCATOR_H
#define INC_2D_GAME_ALLOCATOR_H

#include <stddef.h>
#include <cassert>
#include <cstdint>
#include <utility>

// Reference: https://www.gamedev.net/articles/programming/general-and-gameplay-programming/c-custom-memory-allocation-r3010/

namespace sc2d::memory {

    constexpr uint8_t DEFAULT_ALIGNMENT = 8;

    class allocator {
    public:
        allocator(size_t size, void *start) :
                _start{start}, _size{size}, _used_memory{0}, _num_allocations{0} {}

        virtual ~allocator() {
            assert(_num_allocations == 0 && _used_memory == 0);
            _start = nullptr;
            _size = 0;
        }

        virtual void *allocate(size_t size, uint8_t alignment = DEFAULT_ALIGNMENT) = 0;
        virtual void deallocate(void* p) = 0;

        void* get_start() const { return _start; }
        size_t get_size() const { return _size; }
        size_t get_used_memory() const { return _used_memory; }
        size_t get_num_allocation() const { return _num_allocations; }

    protected:
        void *_start;
        size_t _size;
        size_t _used_memory;
        size_t _num_allocations;
    };

    namespace allocs {

        template<typename T, typename... Args>
        inline T *allocate_new(allocator &alloc, Args &&... args);

        template<typename T>
        inline void deallocate_delete(allocator &alloc, T &obj);

        template<typename T>
        inline T *allocate_array(allocator &alloc, size_t length);

        template<typename T>
        inline T *allocate_array_no_construct(allocator &alloc, size_t length);

        template<typename T>
        inline void deallocate_array(allocator &alloc, T *array);

        template<typename T>
        inline void deallocate_array_no_destuct(allocator &alloc, T *array);
    }
#include "allocator.inl"
}

#endif //INC_2D_GAME_ALLOCATOR_H
