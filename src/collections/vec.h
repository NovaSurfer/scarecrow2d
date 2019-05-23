//
// Created by novasurfer on 3/1/19.
//

#ifndef CPPTRAINING_vec_H
#define CPPTRAINING_vec_H

#include <iterator>
#include <type_traits>
#include <memory/pool_allocator.h>

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
        using IS_T_TRIVIAL = std::is_trivial<T>;

        vec() noexcept;
        explicit vec(size_type n);
        vec(size_type size, const T& data);
//        vec(size_type size, const memory::allocator& alloc);
        vec(typename vec<T>::iterator first, typename vec<T>::iterator last);
        vec(std::initializer_list<T> ilist);
        vec(const vec<T>& v);
        vec(vec<T> &&) noexcept;
        ~vec();

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
        void resize(size_type new_size);
        void resize(size_type new_size, const T& data);
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
        size_type vec_size = 0;
        T* array;
        std::unique_ptr<memory::pool_allocator> pool_alloc {std::make_unique<memory::pool_allocator>()};

        inline void allocate();
    };

    template<typename T>
    void vec<T>::allocate()
    {
        pool_alloc->create(sizeof(T), vec_size << 1, alignof(T));
        array = (T*)pool_alloc->get_start();
    }

    template <typename T>
    vec<T>::vec() noexcept
    {
        allocate();
    }

    template<typename T>
    vec<T>::vec(vec::size_type size) : vec_size{size}
    {
        allocate();
    }

    template<typename T>
    vec<T>::vec(vec::size_type size, const T& data) : vec_size{size}
    {
        allocate();
        for(size_t i = 0; i < size; ++i)
            push_back(data);
    }

    template<typename T>
    vec<T>::vec(typename vec<T>::iterator first, typename vec<T>::iterator last) : vec_size{(last - first) << 1}
    {
        allocate();
        for(size_t i = 0; i < vec_size; ++i, ++first)
            push_back(*first);
    }

    template<typename T>
    vec<T>::vec(std::initializer_list<T> ilist) : vec_size{ilist.size()}
    {
        allocate();
        for(const auto& i : ilist)
            push_back(i);
    }

    template<typename T>
    vec<T>::vec(const vec<T>& v) : vec_size{v.capacity() >> 1}
    {
        allocate();
        for(size_t i = 0; i < v.vec_size; ++i)
            array[i] = v.array[i];
    }

    template<typename T>
    vec<T>::vec(vec<T>&& v) noexcept : vec_size{v.capacity() >> 1}
    {
        allocate();
        for(size_t i = 0; i < v.size(); ++i)
            array[i] = std::move(v.array[i]);
    }

    template<typename T>
    vec<T>::~vec()
    {
        pool_alloc->destroy();
        pool_alloc.reset();
        array = nullptr;
    }

    template<typename T>
    vec<T>& vec<T>::operator=(const vec<T>& other)
    {
        for (size_t i = 0; i < other.vec_size; ++i)
            push_back(other[i]);
        vec_size = other.vec_size;
    }

    template<typename T>
    vec<T>& vec<T>::operator=(vec<T>&& other)
    {
        for(size_t i = 0; i < other.vec_size; ++i)
            push_back(std::move(other[i]));
        vec_size = other.vec_size;
    }

    template<typename T>
    vec<T>& vec<T>::operator=(std::initializer_list<T> ilist)
    {
        for(const auto& i : ilist)
            push_back(i);

    }

    template<typename T>
    void vec<T>::assign(vec::size_type size, const T& data)
    {
        for(size_t i = 0; i < size; ++i)
            push_back(data);
    }

    template<typename T>
    void vec<T>::assign(vec::iterator first, vec::iterator last)
    {
        size_t count = last - first;
        for(size_t i = 0; i < count; ++i, ++first)
            push_back(*first);
    }

    template<typename T>
    void vec<T>::assign(std::initializer_list<T> ilist)
    {
        for(const auto& i : ilist)
            push_back(i);
    }

    template<typename T>
    void vec<T>::push_back(const T& cref_type)
    {
        T* item = (T*)pool_alloc->allocate();
        *item = cref_type;
        array[pool_alloc->get_intialized_num()] = *item;
    }

    template<typename T>
    typename vec<T>::reference vec<T>::operator[](vec::size_type index)
    {
        return array[index];
    }

    template<typename T>
    typename vec<T>::size_type vec<T>::capacity() const noexcept
    {
        pool_alloc->get_num_of_blocks();
    }

    template<typename T>
    typename vec<T>::iterator vec<T>::begin() noexcept
    {
        return array;
    }

    template<typename T>
    typename vec<T>::iterator vec<T>::end() noexcept
    {
        return array + pool_alloc->get_num_of_blocks();
    }

    template<typename T>
    typename vec<T>::const_iterator vec<T>::cbegin() const noexcept
    {
        return array;
    }

    template<typename T>
    typename vec<T>::const_iterator vec<T>::cend() const noexcept
    {
        return array + pool_alloc->get_num_of_blocks();
    }

    template<typename T>
    typename vec<T>::reverse_iterator vec<T>::rbegin() noexcept
    {
        return reverse_iterator(array + pool_alloc->get_num_of_blocks());
    }

    template<typename T>
    typename vec<T>::reverse_iterator vec<T>::rend() noexcept
    {
        return reverse_iterator(array);
    }

    template<typename T>
    typename vec<T>::const_reverse_iterator vec<T>::crbegin() const noexcept
    {
        return reverse_iterator(array + pool_alloc->get_num_of_blocks());
    }

    template<typename T>
    typename vec<T>::const_reverse_iterator vec<T>::crend() const noexcept
    {
        return reverse_iterator(array);
    }

    template<typename T>
    bool vec<T>::empty() const noexcept
    {
        return vec_size == 0;
    }

    template<typename T>
    typename vec<T>::size_type vec<T>::size() const noexcept
    {
        return pool_alloc->get_intialized_num();
    }

    template<typename T>
    typename vec<T>::size_type vec<T>::max_size() const noexcept
    {
        return size_t(-1);
    }

    template<typename T>
    void vec<T>::resize(vec::size_type new_size)
    {
        // If new size is bigger than current size of vector
        if(new_size > pool_alloc->get_intialized_num())
        {
            // If new size if begger than current capacity of vector
            if(new_size > pool_alloc->get_num_of_blocks())
            {
                pool_alloc->resize(new_size);
            }
        } else {
            //  Reduce size to its first count elements
            for(size_t i = pool_alloc->get_intialized_num() - 1; i >= new_size; --i)
                pool_alloc->deallocate((void*)&array[i]);
        }
    }
}




#endif //CPPTRAINING_vec_H
