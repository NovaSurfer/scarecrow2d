//
// Created by maksim.ruts on 1.4.19.
//

#include "pool_allocator.h"
#include "aligners.h"

// Reference: https://www.gamedev.net/articles/programming/general-and-gameplay-programming/c-custom-memory-allocation-r3010/?page=2
// Game Engine Architecture by Jason Gregory, 3rd edition: chapter 6.2

namespace sc2d::memory {

    pool_allocator::pool_allocator
            (size_t chunk_size, uint8_t chunk_alignment, size_t size, void *mem) :
            allocator{size, mem}, chunk_size{chunk_size}, chunk_alignment{chunk_alignment}
    {
        assert(chunk_size >= sizeof(void*));

        const uint8_t adjustment = align_forward_adjustment(mem, chunk_alignment);
        pool_list = (void**)(reinterpret_cast<uintptr_t>(mem) + adjustment);
        const size_t chunks_count = (size - adjustment) / chunk_size - 1;

        void** list = pool_list;

        for(size_t i = 0; i < chunks_count; ++i)
        {
            list = (void**)(reinterpret_cast<uintptr_t>(list) + chunk_size);
            list = (void**) *list;
        }

        *list = nullptr;
    }

    pool_allocator::~pool_allocator()
    {
        pool_list = nullptr;
    }

    void *pool_allocator::allocate(size_t size, uint8_t alignment)
    {
        assert(size == chunk_size && alignment == chunk_alignment);

        if(pool_list == nullptr)
            return nullptr;

        void* v_ptr = pool_list;
        pool_list = (void**) *pool_list;
        _used_memory += size;
        _num_allocations++;

        return v_ptr;
    }

    void pool_allocator::deallocate(void *p)
    {
        *((void**)p) = pool_list;
        pool_list = (void**)p;
        _used_memory -= chunk_size;
        _num_allocations--;
    }
}
