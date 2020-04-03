//
// Created by maksim.ruts on 1.4.19.
//

#include "pool_allocator.h"
#include "core/log2.h"
#include "memory.h"
#include <cstring>

//Pool allocator reference: http://www.thinkmind.org/download.php?articleid=computation_tools_2012_1_10_80006

namespace sc2d::memory
{

    void pool_allocator::create(size_t block_size, size_t blocks_numb, size_t alignment)
    {
        size_of_block = block_size;
        num_of_blocks = blocks_numb;
        this->alignment = alignment;
        p_start = reinterpret_cast<unsigned char*>(
            malloc_aligned(block_size * blocks_numb, this->alignment));
        p_next = p_start;
    }

    void pool_allocator::destroy()
    {
        free_aligned(p_start);
        p_start = nullptr;
    }

    alloc_result pool_allocator::allocate()
    {
        alloc_result result;

        if(num_of_initialized < num_of_blocks) {
            size_t* ptr = (size_t*)addr_from_index(num_of_initialized);
            *ptr = num_of_initialized + 1;
            ++num_of_initialized;

            result.ptr = (void*)p_next;
            if(num_of_blocks - num_of_initialized > 0) {
                p_next = addr_from_index(*(size_t*)p_next);
            }
        } else {
            resize(num_of_blocks << 1u);
            result.resized = is_resized::YES;
            result.ptr = addr_from_index(num_of_initialized);
            ++num_of_initialized;
            p_next = addr_from_index(num_of_initialized);
        }

        return result;
    }

    void pool_allocator::resize(size_t new_size)
    {
#if COMPILER_GCC || COMPILER_CLANG
        if(void* p_new_start = malloc_aligned(size_of_block * new_size, alignment)) {
            if(!(memcpy(p_new_start, p_start, size_of_block * num_of_blocks))) {
                // TODO: throw error;
            }
            free_aligned(p_start);
            p_start = reinterpret_cast<unsigned char*>(p_new_start);
        }
#elif COMPILER_MVC
        if(void* p_new_start = realloc_aligned(p_start, size_of_block * new_size, alignment))
            p_start = reinterpret_cast<unsigned char*>(p_new_start);
#endif
        else {
            // TODO: Error handling.
        }
        num_of_blocks = new_size;
    }

    void pool_allocator::deallocate(void* ptr)
    {
        if(p_next != nullptr) {
            (*(size_t*)ptr) = index_from_addr(p_next);
            p_next = (unsigned char*)ptr;
        } else {
            (*(size_t*)ptr) = num_of_blocks;
            p_next = (unsigned char*)ptr;
        }
        --num_of_initialized;
    }

    unsigned char* pool_allocator::addr_from_index(size_t index) const
    {
        return p_start + index * size_of_block;
    }

    size_t pool_allocator::index_from_addr(const unsigned char* ptr) const
    {
        return ((size_t)(ptr - p_start) / size_of_block);
    }
}
