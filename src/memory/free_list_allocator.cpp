//
// Created by Maksim on 4/13/2019.
//

#include "free_list_allocator.h"
#include "aligners.h"

// Reference: https://www.gamedev.net/articles/programming/general-and-gameplay-programming/c-custom-memory-allocation-r3010/

namespace sc2d::memory {

    free_list_allocator::free_list_allocator(size_t size, void* start)
        : allocator{size, start}, free_blocks{(free_block*)start}
    {
        free_blocks->size = size;
        free_blocks->next = nullptr;
    }

    void* free_list_allocator::allocate(size_t size, uint8_t alignment)
    {
        assert(size != 0 && alignment != 0);

        free_block* prev_free_block = nullptr;
        free_block* curr_free_block = free_blocks;

        free_block* prev_best_fit = nullptr;
        free_block* best_fit = nullptr;
        uint8_t best_fit_adjustment = 0;
        size_t best_fit_total_size = 0;

        // Find best fit
        while(curr_free_block != nullptr)
        {
            // Calculate adjustment needed to keep object correctly aligned
            uint8_t adjustment = align_forward_adjustment_with_header(curr_free_block,
                    alignment, sizeof(allocation_header));

            size_t total_size = size + adjustment;

            // If its an exact match use this free block
            if(curr_free_block->size == total_size)
            {
                prev_best_fit = prev_free_block;
                best_fit = curr_free_block;
                best_fit_adjustment = adjustment;
                best_fit_total_size = total_size;

                break;
            }

            // If its a better fit switch
            if(curr_free_block->size > total_size && (best_fit == nullptr || curr_free_block->size < best_fit->size))
            {
                prev_best_fit = prev_free_block;
                best_fit = curr_free_block;
                best_fit_adjustment = adjustment;
                best_fit_total_size = total_size;
            }

            prev_free_block = curr_free_block;
            curr_free_block = curr_free_block->next;
        }

        if(best_fit == nullptr)
            return nullptr;

        // If allocations in the remaining memory will be impossible
        if(best_fit->size - best_fit_total_size <= sizeof(allocation_header))
        {
            // Increase memory allocation instead of creating new free_block
            best_fit_total_size = best_fit->size;

            if(prev_best_fit != nullptr)
            {
                prev_best_fit->next = best_fit->next;

            } else {
                free_blocks = best_fit->next;
            }

        }
        else
        {
            // Prevent new block from overwriting best fit block info
            assert(best_fit_total_size > sizeof(free_block));

            // Else create a new free_block containing remaining memory
            free_block* new_block  = (free_block*) (reinterpret_cast<uintptr_t>(best_fit) + best_fit_total_size);
            new_block->size = best_fit->size - best_fit_total_size;
            new_block->next = best_fit->next;

            if(prev_best_fit != nullptr)
            {
                prev_best_fit->next = best_fit->next;

            } else {
                free_blocks = best_fit->next;
            }
        }

        uintptr_t aligned_address = (uintptr_t)best_fit + best_fit_adjustment;

        allocation_header* header = (allocation_header*)(aligned_address - sizeof(allocation_header));
        header->size = best_fit_total_size;
        header->adjustment = best_fit_adjustment;

        assert(is_aligned(header, alignment));

        _used_memory += best_fit_total_size;
        _num_allocations++;

        return (void*)aligned_address;

    }
}


