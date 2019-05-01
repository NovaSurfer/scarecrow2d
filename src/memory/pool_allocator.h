//
// Created by maksim.ruts on 1.4.19.
//

#ifndef INC_2D_GAME_POOL_ALLOCATOR_H
#define INC_2D_GAME_POOL_ALLOCATOR_H

#include "allocator.h"
#include "aligned_allocator.h"

namespace sc2d::memory {

    class pool_allocator {
    public:
        ~pool_allocator() {destroy();}

        void create(size_t block_size, size_t num_of_blocks, size_t alignment);
        void destroy();
        void* allocate();
        void deallocate(void* ptr);

        size_t num_of_blocks = 0;
        size_t size_of_block = 0;
        size_t num_of_free_blocks = 0;
        size_t num_of_initialized = 0;
        unsigned char* p_start = nullptr;
        unsigned char* p_next = nullptr;
    private:
        void* addr_from_index(size_t index) const;

        size_t index_from_addr(const unsigned char* ptr) const;
    };

}

#endif //INC_2D_GAME_POOL_ALLOCATOR_H
