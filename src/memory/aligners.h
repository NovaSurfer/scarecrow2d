//
// Created by Maksim on 3/31/2019.
//

#ifndef INC_2D_GAME_ALIGNERS_H
#define INC_2D_GAME_ALIGNERS_H

#include <cstdint>

// Reference: https://www.gamedev.net/articles/programming/general-and-gameplay-programming/c-custom-memory-allocation-r3010/

namespace sc2d::memory
{
    inline void* align_forward(void* address, uint8_t alignment)
    {
        return reinterpret_cast<void*>(
            (reinterpret_cast<uintptr_t>(address) + static_cast<uintptr_t>(alignment - 1)) &
            static_cast<uintptr_t>(~(alignment - 1)));
    }

    inline uint8_t align_forward_adjustment(const void* address, uint8_t alignment)
    {
        uint8_t adjustment = alignment - (reinterpret_cast<uintptr_t>(address) +
                                          static_cast<uintptr_t>(alignment - 1));
        if(adjustment == alignment)
            return 0;

        return adjustment;
    }

    inline uint8_t align_forward_adjustment_with_header(const void* address, uint8_t alignment,
                                                        uint8_t header_size)
    {
        uint8_t adjustment = align_forward_adjustment(address, alignment);
        uint8_t needed_space = header_size;

        if(adjustment < needed_space) {
            needed_space -= adjustment;

            adjustment += alignment * (needed_space / alignment);

            if(needed_space % alignment > 0)
                adjustment += alignment;
        }
        return adjustment;
    }

    inline bool is_aligned(const void* address, uint8_t alignment)
    {
        return align_forward_adjustment(address, alignment) == 0;
    }
}

#endif //INC_2D_GAME_ALIGNERS_H
