//
// Created by novasurfer on 3/29/20.
//

#ifndef SCARECROW2D_MEMORY_H
#define SCARECROW2D_MEMORY_H

#include "core/compiler.h"

namespace sc2d
{

#if COMPILER_GCC || COMPILER_CLANG
#    include <cstdlib>
#    define malloc_aligned(bytes, alignment) aligned_alloc(alignment, bytes)
#    define free_aligned(ptr) free(ptr)
#elif COMPILER_MVC
#    include <malloc.h>
#    define malloc_aligned(bytes, alignment) _aligned_malloc(bytes, alignment)
#    define free_aligned(ptr) _aligned_free(ptr)
#    define realloc_aligned(ptr, bytes, alignment) _aligned_realloc(ptr, bytes, alignment)
#endif
}

#endif //SCARECROW2D_MEMORY_H
