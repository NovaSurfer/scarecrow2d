//
// Created by Maksim on 4/21/2019.
//

#ifndef INC_2D_GAME_DYNAMIC_LINEAR_ALLOCATOR_H
#define INC_2D_GAME_DYNAMIC_LINEAR_ALLOCATOR_H

#include "allocator.h"

// Reference: https://www.gamedev.net/articles/programming/general-and-gameplay-programming/c-custom-memory-allocation-r3010/

namespace sc2d::memory {

    class dynamic_linear_allocator : public allocator {
    public:
        dynamic_linear_allocator(allocator& backing_allocator, size_t block_size, uint8_t block_alignment);
        ~dynamic_linear_allocator() override = default;

        void* allocate(size_t size, uint8_t alignement = DEFAULT_ALIGNMENT) final;
        void  deallocate(void* p) final {};
        void rewind(void* mark);
        void clear();

    private:
        bool allocate_new_block(size_t size, uint8_t alignment);

        struct block_info;

        allocator& backing_allocator;
        void* current_pos;
        block_info* current_block;
        size_t block_size;
        uint8_t block_alignment;
    };
}
#endif //INC_2D_GAME_DYNAMIC_LINEAR_ALLOCATOR_H
