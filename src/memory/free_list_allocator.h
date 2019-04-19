//
// Created by Maksim on 4/13/2019.
//

#ifndef INC_2D_GAME_FREE_LIST_ALLOCATOR_H
#define INC_2D_GAME_FREE_LIST_ALLOCATOR_H

#include "allocator.h"

// Reference: https://www.gamedev.net/articles/programming/general-and-gameplay-programming/c-custom-memory-allocation-r3010/

namespace sc2d::memory {

    class free_list_allocator : public allocator {
    public:
        free_list_allocator(size_t size, void* start);
        ~free_list_allocator() override = default;

        void* allocate(size_t size, uint8_t alignment) override;
        void deallocate(void* p) override;

    private:
        struct allocation_header
        {
            size_t size;
            uint8_t adjustment;
        };

        struct free_block
        {
            size_t size;
            free_block* next;
        };

        static_assert(sizeof(allocation_header) >= sizeof(free_block), "sizeof(allocation_header) < sizeof(free_block)");

        free_block* free_blocks;
    };
}

#endif //INC_2D_GAME_FREE_LIST_ALLOCATOR_H
