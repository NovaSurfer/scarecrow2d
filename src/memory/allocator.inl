//
// Created by maksim.ruts on 28.3.19.
//
#ifndef INC_2D_GAME_ALLOCATOR_INL
#define INC_2D_GAME_ALLOCATOR_INL

namespace allocs {

    template <typename T, typename... Args>
    inline T* allocate_new(allocator& alloc, Args&&... args)
    {
        return new (alloc.allocate(sizeof(T), alignof(T))) T(std::forward<Args>(args)...);
    }

    template <typename T>
    inline void deallocate_delete(allocator& alloc, T& obj)
    {
        obj.~T();
        alloc.deallocate(&obj);
    }

    template <typename T>
    inline T* allocate_array(allocator& alloc, size_t length)
    {
        assert(length != 0);
        size_t header_size = sizeof(size_t) / sizeof(T);

        if(sizeof(size_t) % sizeof(T) > 0)
            header_size += 1;

        T* p = reinterpret_cast<T*>(alloc.allocate(sizeof(T) * (header_size + length), alignof(T))) + header_size;
        *(reinterpret_cast<size_t *>(p) - 1) = length;

        for(size_t i = 0; i < length; ++i)
        {
            new (&p[i]) T;
        }

        return p;
    }

    template <typename T>
    inline T* allocate_array_no_construct(allocator& alloc, size_t length)
    {
        assert(length != 0);
        size_t header_size = sizeof(size_t) / sizeof(T);

        if(sizeof(size_t) % sizeof(T) > 0)
            header_size += 1;

        T* p = reinterpret_cast<T*>(alloc.allocate(sizeof(T) * (header_size + length), alignof(T))) + header_size;
        *(reinterpret_cast<size_t *>(p) - 1) = length;

        return p;
    }

    template <typename T>
    inline void deallocate_array(allocator& alloc, T* array)
    {
        assert(array != nullptr);

        size_t lenght = *(reinterpret_cast<size_t *>(array) -1);

        for(size_t i = lenght; --i;)
        {
            array[i].~T();
        }

        size_t header_size = sizeof(size_t) / sizeof(T);

        if(sizeof(size_t) % sizeof(T) > 0)
            header_size += 1;

        alloc.deallocate(array - header_size);
    }

    template<typename T>
    inline void deallocate_array_no_destuct(allocator& alloc, T* array)
    {
        assert(array != nullptr);

        size_t header_size = sizeof(size_t) /sizeof(T);

        if(sizeof(size_t) % sizeof(T) > 0)
            header_size += 1;

        alloc.deallocate(array - header_size);
    }
}
#endif //INC_2D_GAME_ALLOCATOR_INL
