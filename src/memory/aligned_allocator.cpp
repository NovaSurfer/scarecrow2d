//
// Created by Maksim on 3/23/2019.
//
#include "aligned_allocator.h"

namespace sc2d::memory {

    void* _aligned_malloc(size_t size, size_t alignment)
    {
        void* res = nullptr;
        void* ptr = malloc(size + alignment);
        if (ptr!=nullptr) {
            res = reinterpret_cast<void*>((reinterpret_cast<size_t>(ptr) & ~(size_t(alignment-1))) + alignment);
            *(reinterpret_cast<void**>(res) - 1) = ptr;
        }
        return res;
    }

    void* aligned_malloc(size_t size, size_t alignment)
    {
#if MALLOC_ALREADY_ALIGNED
        return malloc(size);
#elif HAS_MM_MALLOC
        return _mm_malloc(size, alignment);
#endif
    }

    void _aligned_free(void* ptr)
    {
        if (ptr != nullptr)
            free(*(reinterpret_cast<void**>(ptr) - 1));
    }

    void aligned_free(void* ptr)
    {
#if MALLOC_ALREADY_ALIGNED
        free(ptr);
#elif HAS_MM_MALLOC
        _mm_free(ptr);
#endif
    }
}