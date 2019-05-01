//
// Created by Maksim on 4/28/2019.
//

#include "heap_allocator.h"
#include "aligners.h"

namespace sc2d::memory {

    void* heap_allocator::allocate(size_t size, uint8_t alignment) {
        assert(size != 0);
        uint8_t adjustment = align_forward_adjustment(current_pos, alignment);

        if(_used_memory + adjustment + size > _size) return nullptr;

        uint8_t aligned_address = (uintptr_t) current_pos + adjustment;
        current_pos = (void*)(aligned_address + size);
        _used_memory += size + adjustment;
        _num_allocations++;

        return (void*)aligned_address;
    }

    void heap_allocator::deallocate(void* p) {

    }

    void heap_allocator::clear() {
        _num_allocations = 0;
        _used_memory = 0;
        current_pos = _start;
    }
}