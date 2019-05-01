//
// Created by Maksim on 4/28/2019.
//

#ifndef INC_2D_GAME_HEAP_ALLOCATOR_H
#define INC_2D_GAME_HEAP_ALLOCATOR_H

#include "allocator.h"

namespace sc2d::memory {

    class heap_allocator : public allocator {
    public:
        heap_allocator(size_t size, void* start) : allocator(size, start), _start(start), current_pos(start)
        {
            assert(size > 0);
        }
        ~heap_allocator()
        {
            current_pos = nullptr;
        }

        void* allocate(size_t size, uint8_t alignment) override;
        void deallocate(void* p) override;
        void clear();

    protected:
        void* _start;
        void* current_pos;

    };
}

#endif //INC_2D_GAME_HEAP_ALLOCATOR_H
