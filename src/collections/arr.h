//
// Created by novasurfer on 4/20/20.
//

#ifndef SCARECROW2D_ARR_H
#define SCARECROW2D_ARR_H

#include "core/dbg/dbg_asserts.h"
#include "core/limits.h"
#include "core/types.h"
#include "memory/memory.h"
#include "vec.h"
#include <type_traits>

namespace sc2d
{
    //Stack based Array for POD types
    template <typename T, size_t SIZE>
    class arr
    {
        using IS_T_TRIVIAL = std::is_trivial<T>;

    public:
        inline arr();
        constexpr size_t size() const
        {
            return SIZE;
        }
        T& operator[](size_t index);
        const T& operator[](size_t index) const;
        void insert_at(const T* item, size_t index, size_t size);

    private:
        T data[SIZE];
    };

    template <typename T, size_t SIZE>
    inline arr<T, SIZE>::arr()
    {
        DBG_CONSTEXPR_FAIL_IF(SIZE >= limits::MAX_STACK_ARR_SIZE, "too huge for stack array");
        DBG_CONSTEXPR_FAIL_IF(!IS_T_TRIVIAL::value, "non-POD array is not supported");
    }

    template <typename T, size_t SIZE>
    inline T& arr<T, SIZE>::operator[](size_t index)
    {
        return data[index];
    }

    template <typename T, size_t SIZE>
    inline const T& arr<T, SIZE>::operator[](size_t index) const
    {
        return data[index];
    }

    template <typename T, size_t SIZE>
    inline void arr<T, SIZE>::insert_at(const T* item, size_t index, size_t size)
    {
        memcpy(&data[index], item, sizeof(T) * size);
    }

}

#endif //SCARECROW2D_ARR_H
