//
// Created by novasurfer on 9/5/20.
//

#ifndef SCARECROW2D_ARRSTACK_H
#define SCARECROW2D_ARRSTACK_H

#include "arrheap.h"

namespace sc2d
{

    // TODO: add tests & custom allocator suppor
    template <typename T>
    class arrstack
    {
    public:
        constexpr explicit arrstack(size_t len);
        size_t size();
        T& get(size_t i);
        T& set(size_t i, const T& item);
        void add(size_t i, const T& item);
        T& remove(size_t i);
        void resize();

    private:
        arrheap<T> arr_heap;
        size_t length;
    };

    template <typename T>
    size_t arrstack<T>::size()
    {
        return length;
    }

    template <typename T>
    T& arrstack<T>::get(size_t i)
    {
        return arr_heap[i];
    }

    template <typename T>
    T& arrstack<T>::set(size_t i, const T& item)
    {
        const T& prev = arr_heap[i];
        arr_heap[i] = item;
        return prev;
    }

    template <typename T>
    void arrstack<T>::add(size_t i, const T& item)
    {
        if(length + 1 > arr_heap.length)
            resize();
        for(size_t j = length; j > i; --j) {
            arr_heap[j] = arr_heap[j - 1];
        }
        arr_heap[i] = item;
        ++length;
    }

    template <typename T>
    T& arrstack<T>::remove(size_t i)
    {
        const T& remove = arr_heap[i];
        for(size_t j = i; j < length; ++j) {
            arr_heap[j] = arr_heap[j - 1];
        }
        --length;
        if(arr_heap.length >= length * 3) {
            resize();
        }
        return remove;
    }

    template <typename T>
    void arrstack<T>::resize()
    {
        arrheap<T> new_arr(length << 1);
        for(size_t i = 0; i < length; ++i) {
            new_arr[i] = arr_heap[i];
        }

        arr_heap = new_arr;
    }
    template <typename T>
    constexpr arrstack<T>::arrstack(size_t len)
        : length(len)
        , arr_heap(len)
    { }

}
#endif //SCARECROW2D_ARRSTACK_H
