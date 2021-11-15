//
// Created by novasurfer on 9/2/20.
//

#ifndef SCARECROW2D_ARRHEAP_H
#define SCARECROW2D_ARRHEAP_H

#include "core/dbg/dbg_asserts.h"
#include "core/types.h"
#include "memory/memory.h"
#include <type_traits>

namespace sc2d
{

    // TODO: add tests and custom allocator support
    template <typename T>
    class arrheap
    {
    public:
        constexpr explicit arrheap(size_t length);
        ~arrheap();
        constexpr explicit arrheap(const arrheap<T>& other);
        constexpr explicit arrheap(const arrheap<T>&& other);
        constexpr T& operator[](size_t i) const;
        arrheap<T>& operator=(const arrheap<T>& other) const;
        arrheap<T>& operator=(const arrheap<T>&& other) const;

    private:
        T* data;
        size_t length;
    };

    template <typename T>
    constexpr arrheap<T>::arrheap(size_t length)
        : length(length)
    {
        data = new T[length];
    }

    template <typename T>
    arrheap<T>::~arrheap()
    {
        delete[] data;
        data = nullptr;
        length = 0;
    }

    template <typename T>
    constexpr arrheap<T>::arrheap(const arrheap<T>& other)
        : length(other.length)
    {
        data = new T[length];
        for(size_t i = 0; i < length; ++i) {
            data[i] = other[i];
        }
    }

    template <typename T>
    constexpr T& arrheap<T>::operator[](size_t i) const
    {
        return data[i];
    }

    template <typename T>
    constexpr arrheap<T>::arrheap(const arrheap<T>&& other)
        : length(other.length)
        , data(std::exchange(other.data, nullptr))
    {
        other.length = 0;
    }

    template <typename T>
    arrheap<T>& arrheap<T>::operator=(const arrheap<T>& other) const
    {
        if(this != other) {
            if(data != nullptr) {
                delete[] data;
            }
            data = other.data;
            length = other.length;
        }

        return *this;
    }

    template <typename T>
    arrheap<T>& arrheap<T>::operator=(const arrheap<T>&& other) const
    {
        if(this != other) {
            if(data != nullptr) {
                delete[] data;
            }
            data = other.data;
            length = other.length;
        }

        return *this;
    }

}

#endif //SCARECROW2D_ARRHEAP_H
