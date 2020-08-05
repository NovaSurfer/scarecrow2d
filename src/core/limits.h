//
// Created by novasurfer on 4/20/20.
//

#ifndef SCARECROW2D_LIMITS_H
#define SCARECROW2D_LIMITS_H

#include "types.h"
#include <cstddef>

namespace sc2d::limits
{
    constexpr size_t MAX_STACK_ARR_SIZE = 1'000'000;
    // Rendering
    constexpr u32 DRAWCALL_QUADS = 1024;
    constexpr u32 DRAWCALL_VERTICES = DRAWCALL_QUADS * 4;
    constexpr u32 DRAWCALL_INDICES = DRAWCALL_QUADS * 6;
}

#endif //SCARECROW2D_LIMITS_H
