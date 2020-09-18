//
// Created by novasurfer on 4/20/20.
//

#ifndef SCARECROW2D_ARR_H
#define SCARECROW2D_ARR_H

#include "core/dbg/dbg_asserts.h"
#include "core/limits.h"
#include "core/types.h"
#include "memory/memory.h"
#include <type_traits>

namespace sc2d
{
    template <typename T, size_t SIZE>
    class arr
    {
        using IS_T_TRIVIAL = std::is_trivial<T>;

    public:
        constexpr size_t size() const
        {
            return SIZE;
        }
        T& operator[](size_t index);
        const T& operator[](size_t index) const;
        void insert_at(const T* item, size_t index, size_t size);
        T* get();
        const T* get() const;


    private:
        T data[SIZE];
    };

    template <typename T, size_t SIZE>
    forceinline T& arr<T, SIZE>::operator[](size_t index)
    {
        return data[index];
    }

    template <typename T, size_t SIZE>
    forceinline const T& arr<T, SIZE>::operator[](size_t index) const
    {
        return data[index];
    }

    template <typename T, size_t SIZE>
    forceinline void arr<T, SIZE>::insert_at(const T* item, size_t index, size_t size)
    {
        DBG_CONSTEXPR_FAIL_IF(!IS_T_TRIVIAL::value, "insert_at for non-POD array is not supported");
        memcpy(&data[index], item, sizeof(T) * size);
    }

    template <typename T, size_t SIZE>
    forceinline const T* arr<T, SIZE>::get() const
    {
        return data;
    }

    template <typename T, size_t SIZE>
    forceinline T* arr<T, SIZE>::get()
    {
        return data;
    }
}

#endif //SCARECROW2D_ARR_H
