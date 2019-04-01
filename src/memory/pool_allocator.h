//
// Created by maksim.ruts on 1.4.19.
//

#ifndef INC_2D_GAME_POOL_ALLOCATOR_H
#define INC_2D_GAME_POOL_ALLOCATOR_H

#include "allocator.h"

namespace sc2d::memory {

    class pool_allocator : public allocator {
    public:

        pool_allocator(size_t chunk_size, uint8_t chunk_alignment, size_t size, void* mem);

        ~pool_allocator();

        void* allocate(size_t size, uint8_t alignment) override;
        void deallocate(void* p) override;

    private:
        size_t chunk_size;
        uint8_t chunk_alignment;
        void**  pool_list = nullptr;
    };
}

#endif //INC_2D_GAME_POOL_ALLOCATOR_H
