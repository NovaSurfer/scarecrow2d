//
// Created by maksim.ruts on 1.4.19.
//

#include "pool_allocator.h"

// Reference: http://www.thinkmind.org/download.php?articleid=computation_tools_2012_1_10_80006

namespace sc2d::memory {

    void pool_allocator::create(size_t block_size, size_t blocks_numb, size_t alignment)
    {
        size_of_block = block_size;
        num_of_blocks = blocks_numb;
        p_start = reinterpret_cast<unsigned char*>(aligned_malloc(block_size * blocks_numb, alignment));
        num_of_free_blocks = num_of_blocks;
        p_next = p_start;
    }

    void pool_allocator::destroy()
    {
        aligned_free(p_start);
        p_start = nullptr;
    }

    void* pool_allocator::allocate()
    {
        if(num_of_initialized < num_of_free_blocks)
        {
            unsigned char* ptr = (unsigned char*)addr_from_index(num_of_initialized);
            *ptr = num_of_initialized + 1;
            num_of_initialized++;
        }

        void* ptr = nullptr;
        if(num_of_free_blocks > 0)
        {
            ptr = (void*)p_next;
            --num_of_free_blocks;
            if(num_of_free_blocks != 0)
            {
                p_next = (unsigned char*)addr_from_index(*(size_t*)p_next);
            }
            else
            {
                p_next = nullptr;
            }
        }

        return ptr;
    }

    void pool_allocator::deallocate(void* ptr)
    {
        if(p_next != nullptr)
        {
            (*(size_t*)ptr) = index_from_addr(p_next);
            p_next = (unsigned char*)ptr;
        }
        else
        {
            (*(size_t*)ptr) = num_of_blocks;
            p_next = (unsigned char*)ptr;
        }
        num_of_free_blocks++;
    }

    void* pool_allocator::addr_from_index(size_t index) const
    {
        return reinterpret_cast<void*>(p_start + (index * size_of_block));
    }

    size_t pool_allocator::index_from_addr(const unsigned char* ptr) const
    {
        return ((size_t)(ptr - p_start) / size_of_block);
    }
}
