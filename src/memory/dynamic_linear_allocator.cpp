//
// Created by Maksim on 4/21/2019.
//

#include "dynamic_linear_allocator.h"
#include "aligners.h"

// Reference: https://www.gamedev.net/articles/programming/general-and-gameplay-programming/c-custom-memory-allocation-r3010/

namespace sc2d::memory
{
    struct dynamic_linear_allocator::block_info
    {
        void* start;
        block_info* prev_block;
        size_t size;
        size_t used_memory;
    };

    dynamic_linear_allocator::dynamic_linear_allocator
    (allocator& backing_allocator, size_t block_size, uint8_t block_alignment)
        : allocator(1, nullptr), backing_allocator{backing_allocator}, block_size{block_size}, block_alignment{block_alignment}
    {
        _size = 0; // little hack, because "can't" create allocator with size 0
    }

    void* dynamic_linear_allocator::allocate(size_t size, uint8_t alignment)
    {
        assert(_size != 0 && alignment != 0);

        if(current_block == nullptr)
            allocate_new_block(size, alignment);

        uint8_t adjustment = align_forward_adjustment(current_pos, alignment);

        if(current_block->used_memory + adjustment + size > current_block->size)
        {
            allocate_new_block(size, alignment);

            adjustment = align_forward_adjustment(current_pos, alignment);
        }

        void* aligned_address = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(current_pos) + adjustment);
        size_t total_size = adjustment + size;
        current_pos = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(current_pos) + total_size);

        current_block->used_memory += total_size;
        _used_memory += total_size;

        return aligned_address;
    }

    void dynamic_linear_allocator::rewind(void* mark)
    {
        if(mark == current_pos)
            return;

        assert(current_block != nullptr);

        while(mark <= current_block + 1 || mark >
                reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(current_block->start) + current_block->size))
        {
            _size -= current_block->size;
            _used_memory -= current_block->used_memory;

            block_info* temp = current_block->prev_block;

            backing_allocator.deallocate(current_block->start);

            current_block = temp;

            // Check if previous block is not empty
            if(current_block != nullptr)
            {
                // reduce allocator used memory
                _used_memory -= current_block->size - current_block->used_memory;
            }
            else
            {
                assert(mark == nullptr);
                current_pos = nullptr;
                return;
            }
        }

        assert(mark != nullptr);

        assert(mark > current_block + 1 &&
        mark <=reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(current_block->start) + current_block->used_memory));

        size_t k = current_block->used_memory - ((uintptr_t)mark - (uintptr_t)current_block->start);
        current_block->used_memory -= k;
        _used_memory -= k;
        current_pos = mark;
    }

    void dynamic_linear_allocator::clear()
    {
        rewind(nullptr);

        assert(_used_memory == 0		&&
                _size == 0				&&
                _num_allocations == 0	&&
                _start == nullptr		&&
                current_pos == nullptr	&&
                current_block == nullptr);
    }

    bool dynamic_linear_allocator::allocate_new_block(size_t size, uint8_t alignment)
    {
        // Some space might be wasted but KISS
        size_t total_size = size + alignment + sizeof(block_info) + alignof(block_info);
        size_t num_blocks = total_size / block_size;

        if(total_size % block_size != 0)
            num_blocks++;

        size_t new_block_size = num_blocks * block_size;

        void* new_block = backing_allocator.allocate(new_block_size, block_alignment);

        if(new_block == nullptr)
            return false;

        uintptr_t new_block_info_adjustment = align_forward_adjustment(new_block, alignof(block_info));
        block_info* new_block_info =
                reinterpret_cast<block_info*>(reinterpret_cast<uintptr_t>(new_block) + new_block_info_adjustment);

        new_block_info->start = new_block;
        new_block_info->prev_block = current_block;
        new_block_info->size = new_block_size;
        new_block_info->used_memory = sizeof(block_info) + new_block_info_adjustment;

        if(current_block !=nullptr)
        {
            _used_memory += current_block->size - current_block->used_memory;
        }

        _used_memory += new_block_info->used_memory;
        current_block = new_block_info;
        current_pos = current_block + 1;
        _size += new_block_size;

        return true;
    }
}
