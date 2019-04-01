//
// Created by novasurfer on 3/1/19.
//

#ifndef CPPTRAINING_vec_H
#define CPPTRAINING_vec_H

#include <iterator>
//#include "../memory/allocator.h"

#include "../memory/aligned_allocator.h"
#include <iostream>

namespace sc2d {

    template <typename T>
    class vec {
    public:

        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;
        using iterator = T*;
        using const_iterator = const T*;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = const std::reverse_iterator<iterator>;
        using difference_type = ptrdiff_t;
        using size_type = size_t;

        vec() noexcept;
//        explicit vec(sc2d::memory::allocator& alloc);
        explicit vec(size_type n);
        vec(size_type size, const T& data);
        vec(typename vec<T>::iterator first, typename vec<T>::iterator last);
        vec(std::initializer_list<T> ilist);
        vec(const vec<T>& v);
        vec(vec<T> &&) noexcept;
        ~vec() = default;

        vec<T>& operator=(const vec<T>& v);
        vec<T>& operator=(vec<T>&& v);
        vec<T>& operator=(std::initializer_list<T> ilist);

        void assign(size_type size, const T& data);
        void assign(typename vec<T>::iterator first, typename vec<T>::iterator last);
        void assign(std::initializer_list<T> ilist);

        iterator begin() noexcept;
        iterator end() noexcept;
        const_iterator cbegin() const noexcept;
        const_iterator cend() const noexcept;
        reverse_iterator rbegin() noexcept;
        reverse_iterator rend() noexcept;
        const_reverse_iterator crbegin() const noexcept;
        const_reverse_iterator crend() const noexcept;

        bool empty() const noexcept;
        size_type size() const noexcept;
        size_type max_size() const noexcept;
        size_type capacity() const noexcept;
        void resize(size_type size);
        void resize(size_type size, const T& data);
        void reverse(size_type size);
        void shrink_to_fit();

        reference operator[](size_type size);
        const_reference operator[](size_type size) const;
        reference at(size_type size);
        const_reference at(size_type size) const;
        reference front();
        const_reference front() const;
        reference back();
        const_reference back() const;

        T* data() noexcept;
        const T* data() const noexcept;

        template <typename... Args>
        void emplace_back(Args&& ...args);
        void push_back(const T& cref_type);
        void push_back(T&& type);
        void pop_back();

        template<typename... Args>
        iterator emplace(const_iterator c_iter, Args&&...);
        iterator insert(const_iterator c_iter, const T& cref_type);
        iterator insert(const_iterator c_iter, T&& uref_type);
        iterator insert(const_iterator c_iter, size_type size, const T& cref_type);
        template<typename InputIter>
        iterator insert(const_iterator c_iter, InputIter first, InputIter last);
        iterator insert(const_iterator c_iter, std::initializer_list<T> ilist);
        iterator erase(const_iterator elm);
        iterator erase(const_iterator fist, const_iterator last);
        void swap(vec<T>& other);
        void clear() noexcept;

        bool operator == (const vec<T> &) const;
        bool operator != (const vec<T> &) const;
        bool operator < (const vec<T> &) const;
        bool operator <= (const vec<T> &) const;
        bool operator > (const vec<T> &) const;
        bool operator >= (const vec<T> &) const;

    private:
        size_type reserved_size = 4;
        size_type vec_size = 0;
        T* array;

        inline void reallocate();
    };


    template <typename T>
    vec<T>::vec() noexcept
    {
        array = reinterpret_cast<T*>(sc2d::memory::aligned_malloc(sizeof(T) * reserved_size, 16));
    }
}




#endif //CPPTRAINING_vec_H
