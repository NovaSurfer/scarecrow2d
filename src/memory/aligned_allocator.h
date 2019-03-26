//
// Created by Maksim on 3/23/2019.
//

#ifndef INC_2D_GAME_ALIGNED_ALLOCATOR_H
#define INC_2D_GAME_ALIGNED_ALLOCATOR_H

#include <memory>

#if defined(__GLIBC__) && ((__GLIBC__>=2 && __GLIBC_MINOR__>=8) || __GLIBC__>2) \
 && defined(__LP64__)
    #define GLIBC_MALLOC_ALREADY_ALIGNED 1
#else
    #define GLIBC_MALLOC_ALREADY_ALIGNED 0
#endif

#if defined(__FreeBSD__) && !defined(__arm__) && !defined(__mips__)
    #define FREEBSD_MALLOC_ALREADY_ALIGNED 1
#else
    #define FREEBSD_MALLOC_ALREADY_ALIGNED 0
#endif

#if (defined(__APPLE__) \
 || defined(_WIN64) \
 || GLIBC_MALLOC_ALREADY_ALIGNED \
 || FREEBSD_MALLOC_ALREADY_ALIGNED)
    #define MALLOC_ALREADY_ALIGNED 1
#else
    #define MALLOC_ALREADY_ALIGNED 0
#endif

#if ((defined __QNXNTO__) || (defined _GNU_SOURCE) || ((defined _XOPEN_SOURCE) && (_XOPEN_SOURCE >= 600))) \
 && (defined _POSIX_ADVISORY_INFO) && (_POSIX_ADVISORY_INFO > 0)
    #define HAS_POSIX_MEMALIGN 1
#else
    #define HAS_POSIX_MEMALIGN 0
#endif

#if SSE_INSTR_SET > 0
    #define HAS_MM_MALLOC 1
#else
    #define HAS_MM_MALLOC 0
#endif

namespace sc2d::memory {

    void* _aligned_malloc(size_t size, size_t alignment);
    void* aligned_malloc(size_t size, size_t alignment);

    void _aligned_free(void* ptr);
    void aligned_free(void* ptr);

    template<typename T, size_t N>
    class aligned_allocator {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;
        using size_type = size_t;
        using difference_type = ptrdiff_t;

        template<typename U>
        struct rebind {
            using other = aligned_allocator<U, N>;
        };

        constexpr pointer address(reference r) const { return &r; }

        constexpr const_pointer address(const_reference r) const { return &r; }

        constexpr pointer allocate(size_type n, typename std::allocator<void>::const_pointer hint = nullptr) const;

        constexpr pointer deallocate(pointer p, size_type size) const;

        constexpr void construct(pointer p, const_reference value) const { new(p) value_type(value); }

        constexpr void destroy(pointer p) const { p->~value_type(); }

        constexpr size_type max_size() const noexcept { return size_type(-1) / sizeof(T); }

        constexpr bool operator==(const aligned_allocator&) const { return true; }

        constexpr bool operator!=(const aligned_allocator& rhs) const { return !operator == (rhs); }

    };

    template<class T, size_t N>
    constexpr typename aligned_allocator<T, N>::pointer
    aligned_allocator<T, N>::allocate(size_type n, typename std::allocator<void>::const_pointer hint) const
    {
        pointer res = reinterpret_cast<pointer>(sc2d::memory::aligned_malloc(sizeof(T) * n, N));
        if (res==0)
            throw std::bad_alloc();
        return res;
    }

    template<class T, size_t N>
    constexpr typename aligned_allocator<T, N>::pointer
    aligned_allocator<T, N>::deallocate(pointer p, size_type size) const
    {
        sc2d::memory::aligned_free(p);
    }
}

#endif //INC_2D_GAME_ALIGNED_ALLOCATOR_H
