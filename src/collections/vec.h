//
// Created by novasurfer on 3/1/19.
//

#ifndef INC_2D_GAME_VEC_H
#define INC_2D_GAME_VEC_H

#include "core/log2.h"
#include "memory/pool_allocator.h"
#include <cstring>
#include <iterator>
#include <type_traits>

// TODO:  ------------------- Write tests and benchmarks -------------------

namespace sc2d
{

    template <typename T>
    class vec
    {
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
        vec(vec<T>&&) noexcept;
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
        void reserve(size_type new_size);
        void shrink_to_fit();

        reference operator[](size_type index);
        const_reference operator[](size_type index) const;
        reference at(size_type index);
        const_reference at(size_type index) const;
        reference front();
        const_reference front() const;
        reference back();
        const_reference back() const;

        T* data() noexcept;
        const T* data() const noexcept;

        template <typename... Args>
        void emplace_back(Args&&... args);
        void push_back(const T& cref_data);
        void push_back(T&& lvref_data);
        void pop_back();

        template <typename... Args>
        iterator emplace(const_iterator c_iter, Args&&...);
        iterator insert(const_iterator c_iter, const T& cref_type);
        iterator insert(const_iterator c_iter, T&& uref_type);
        iterator insert(const_iterator pos, size_type count, const T& value);
        template <typename InputIter>
        iterator insert(const_iterator pos, InputIter first, InputIter last);
        iterator insert(const_iterator pos, std::initializer_list<T> ilist);
        iterator erase(const_iterator it);
        iterator erase(const_iterator fist, const_iterator last);
        void swap(vec<T>& other);
        void clear() noexcept;

        bool operator==(const vec<T>&) const;
        bool operator!=(const vec<T>&) const;
        bool operator<(const vec<T>&) const;
        bool operator<=(const vec<T>&) const;
        bool operator>(const vec<T>&) const;
        bool operator>=(const vec<T>&) const;

    private:
        inline void allocate();
        inline void update_array_address()
        {
            array = (T*)pool_alloc->p_start;
        }

        size_type initial_size = 1;
        T* array;
        std::unique_ptr<memory::pool_allocator> pool_alloc {
            std::make_unique<memory::pool_allocator>()};
    };

    template <typename T>
    void vec<T>::allocate()
    {
        pool_alloc->create(sizeof(T), initial_size << 1u, alignof(T*));
        update_array_address();
    }

    template <typename T>
    vec<T>::vec() noexcept
    {
        allocate();
    }

    template <typename T>
    vec<T>::vec(vec::size_type size)
        : initial_size(size)
    {
        allocate();
    }

    template <typename T>
    vec<T>::vec(vec::size_type size, const T& data)
        : initial_size(size)
    {
        allocate();
        for(size_t i = 0; i < size; ++i)
            push_back(data);
    }

    template <typename T>
    vec<T>::vec(typename vec<T>::iterator first, typename vec<T>::iterator last)
        : initial_size((last - first) >> 1u)
    {
        allocate();
        for(; first != last; ++first)
            push_back(*first);
    }

    template <typename T>
    vec<T>::vec(std::initializer_list<T> ilist)
        : initial_size(ilist.size())
    {
        allocate();
        for(const auto& i : ilist)
            push_back(i);
    }

    template <typename T>
    vec<T>::vec(const vec<T>& v)
        : initial_size(v.capacity() >> 1u)
    {
        allocate();
        for(size_t i = 0; i < v.initial_size; ++i)
            array[i] = v.array[i];
    }

    template <typename T>
    vec<T>::vec(vec<T>&& v) noexcept
        : initial_size(v.capacity() >> 1u)
    {
        allocate();
        for(size_t i = 0; i < v.size(); ++i)
            array[i] = std::move(v.array[i]);
    }

    template <typename T>
    vec<T>::~vec()
    {
        pool_alloc->destroy();
        pool_alloc.reset();
        array = nullptr;
    }

    template <typename T>
    vec<T>& vec<T>::operator=(const vec<T>& other)
    {
        if(size_t other_capacity = other.pool_alloc->num_of_blocks;
           other_capacity > pool_alloc->num_of_blocks) {
            pool_alloc->resize(other_capacity);
            update_array_address();
        }

        for(size_t i = 0; i < other.pool_alloc->num_of_initialized; ++i)
            array[i] = other[i];
    }

    template <typename T>
    vec<T>& vec<T>::operator=(vec<T>&& other)
    {
        if(size_t other_capacity = other.pool_alloc->num_of_blocks;
           other_capacity > pool_alloc->num_of_blocks) {
            pool_alloc->resize(other_capacity);
            update_array_address();
        }

        for(size_t i = 0; i < other.initial_size; ++i)
            array[i] = std::move(other[i]);
    }

    template <typename T>
    vec<T>& vec<T>::operator=(std::initializer_list<T> ilist)
    {
        if(size_t ilist_size = ilist.size(); ilist_size > pool_alloc->num_of_blocks) {
            pool_alloc->resize(ilist_size << 1u);
            update_array_address();
        }

        size_t i = 0;
        for(auto j = ilist.begin(); j != ilist.end(); ++j, ++i) {
            array[i] = *j;
        }
    }

    template <typename T>
    void vec<T>::assign(vec::size_type size, const T& data)
    {
        for(size_t i = 0; i < size; ++i)
            push_back(data);
    }

    template <typename T>
    void vec<T>::assign(vec::iterator first, vec::iterator last)
    {
        size_t count = last - first;
        for(size_t i = 0; i < count; ++i, ++first)
            push_back(*first);
    }

    template <typename T>
    void vec<T>::assign(std::initializer_list<T> ilist)
    {
        for(const auto& i : ilist)
            push_back(i);
    }

    template <typename T>
    typename vec<T>::size_type vec<T>::capacity() const noexcept
    {
        return pool_alloc->num_of_blocks;
    }

    template <typename T>
    typename vec<T>::iterator vec<T>::begin() noexcept
    {
        return array;
    }

    template <typename T>
    typename vec<T>::iterator vec<T>::end() noexcept
    {
        return array + pool_alloc->num_of_initialized;
    }

    template <typename T>
    typename vec<T>::const_iterator vec<T>::cbegin() const noexcept
    {
        return array;
    }

    template <typename T>
    typename vec<T>::const_iterator vec<T>::cend() const noexcept
    {
        return array + pool_alloc->num_of_initialized;
    }

    template <typename T>
    typename vec<T>::reverse_iterator vec<T>::rbegin() noexcept
    {
        return reverse_iterator(array + pool_alloc->num_of_initialized);
    }

    template <typename T>
    typename vec<T>::reverse_iterator vec<T>::rend() noexcept
    {
        return reverse_iterator(array);
    }

    template <typename T>
    typename vec<T>::const_reverse_iterator vec<T>::crbegin() const noexcept
    {
        return reverse_iterator(array + pool_alloc->num_of_initialized);
    }

    template <typename T>
    typename vec<T>::const_reverse_iterator vec<T>::crend() const noexcept
    {
        return reverse_iterator(array);
    }

    template <typename T>
    bool vec<T>::empty() const noexcept
    {
        return initial_size == 0;
    }

    template <typename T>
    typename vec<T>::size_type vec<T>::size() const noexcept
    {
        return pool_alloc->num_of_initialized;
    }

    template <typename T>
    typename vec<T>::size_type vec<T>::max_size() const noexcept
    {
        return size_t(-1);
    }

    template <typename T>
    void vec<T>::resize(vec::size_type new_size)
    {
        const size_t current_size = pool_alloc->num_of_initialized;

        // If new size is bigger than current size of vector
        if(new_size > current_size) {
            // If new size if bigger than current capacity of vector
            if(new_size > pool_alloc->num_of_blocks) {
                //                pool_alloc->num_of_free_blocks = new_size - pool_alloc->num_of_initialized;
                pool_alloc->resize(new_size);
            }
        } else {
            //  Reduce size to its first count elements
            for(size_t i = current_size - 1; i >= new_size; --i)
                pool_alloc->deallocate((void*)&array[i]);

            pool_alloc->num_of_blocks = new_size;
        }
        pool_alloc->num_of_initialized = new_size;
    }

    template <typename T>
    void vec<T>::resize(vec::size_type new_size, const T& data)
    {
        const size_t current_size = pool_alloc->num_of_initialized;
        if(new_size > current_size) {
            if(new_size > pool_alloc->num_of_blocks) {
                pool_alloc->resize(new_size);
            }

            for(size_t i = current_size; i < new_size; ++i)
                array[i] = data;

        } else {
            for(size_t i = current_size - 1; i >= new_size; --i)
                pool_alloc->deallocate((void*)&array[i]);

            pool_alloc->num_of_blocks = new_size;
        }
        pool_alloc->num_of_initialized = new_size;
    }

    template <typename T>
    void vec<T>::reserve(vec::size_type new_size)
    {
        if(new_size > pool_alloc->num_of_blocks) {
            pool_alloc->resize(new_size);
        }
    }

    template <typename T>
    void vec<T>::shrink_to_fit()
    {
        resize(pool_alloc->num_of_initialized);
    }

    template <typename T>
    typename vec<T>::reference vec<T>::operator[](vec::size_type index)
    {
        return array[index];
    }

    template <typename T>
    typename vec<T>::const_reference vec<T>::operator[](vec::size_type index) const
    {
        return array[index];
    }

    template <typename T>
    typename vec<T>::reference vec<T>::at(vec::size_type index)
    {
        if(index < pool_alloc->num_of_initialized)
            return array[index];

        // TODO: Deal with this exception
        //        throw std::out_of_range("Vector's index out of range!");
    }

    template <typename T>
    typename vec<T>::const_reference vec<T>::at(vec::size_type index) const
    {
        if(index < pool_alloc->get_intialized_num())
            return array[index];

        // TODO: Deal with this exception
        //        throw std::out_of_range("Vector's index out of range");
    }

    template <typename T>
    typename vec<T>::reference vec<T>::front()
    {
        return array[0];
    }

    template <typename T>
    typename vec<T>::const_reference vec<T>::front() const
    {
        return array[0];
    }

    template <typename T>
    typename vec<T>::reference vec<T>::back()
    {
        return array[pool_alloc->num_of_initialized - 1];
    }

    template <typename T>
    typename vec<T>::const_reference vec<T>::back() const
    {
        return array[pool_alloc->num_of_initialized - 1];
    }

    template <typename T>
    T* vec<T>::data() noexcept
    {
        return array;
    }

    template <typename T>
    const T* vec<T>::data() const noexcept
    {
        return array;
    }

    template <typename T>
    void vec<T>::push_back(const T& cref_data)
    {
        const memory::alloc_result res = pool_alloc->allocate();
        T& item = *(T*)res.ptr;
        item = cref_data;

        if(res.resized == memory::is_resized::YES)
            update_array_address();
    }

    template <typename T>
    void vec<T>::push_back(T&& lvref_data)
    {
        memory::alloc_result res = pool_alloc->allocate();
        T& item = *(T*)res.ptr;
        item = std::move(lvref_data);

        if(res.resized == memory::is_resized::YES)
            update_array_address();
    }

    template <typename T>
    template <typename... Args>
    void vec<T>::emplace_back(Args&&... args)
    {
        memory::alloc_result res = pool_alloc->allocate();
        T& item = *(T*)res.ptr;
        item = std::move(T(std::forward<Args>(args)...));

        if(res.resized == memory::is_resized::YES)
            update_array_address();
    }

    template <typename T>
    void vec<T>::pop_back()
    {
        pool_alloc->deallocate((void*)&array[pool_alloc->num_of_initialized - 1]);
    }

    template <typename T>
    template <typename... Args>
    typename vec<T>::iterator vec<T>::emplace(vec::const_iterator c_iter, Args&&... args)
    {
        if((ptrdiff_t)(pool_alloc->num_of_blocks - pool_alloc->num_of_initialized) <= 0)
            pool_alloc->resize(pool_alloc->num_of_blocks << 1u);

        iterator iter = &array[c_iter - array];
        // Bug for non-POD types
        size_t sz = (pool_alloc->num_of_initialized - (c_iter - array)) * sizeof(T);
        if(sz > 0)
            memmove(iter + 1, iter, sz);
        (*iter) = std::move(T(std::forward<Args>(args)...));
        pool_alloc->num_of_initialized++;
        return iter;
    }

    template <typename T>
    typename vec<T>::iterator vec<T>::insert(vec::const_iterator c_iter, const T& cref_type)
    {
        if((ptrdiff_t)(pool_alloc->num_of_blocks - pool_alloc->num_of_initialized) <= 0)
            pool_alloc->resize(pool_alloc->num_of_blocks << 1u);

        iterator iter = &array[c_iter - array];
        // Bug for non-POD types
        size_t sz = (pool_alloc->num_of_initialized - (c_iter - array)) * sizeof(T);
        if(sz > 0)
            memmove(iter + 1, iter, sz);
        *iter = cref_type;
        pool_alloc->num_of_initialized++;
        return iter;
    }

    template <typename T>
    typename vec<T>::iterator vec<T>::insert(vec::const_iterator c_iter, T&& uref_type)
    {
        if((ptrdiff_t)(pool_alloc->num_of_blocks - pool_alloc->num_of_initialized) <= 0)
            pool_alloc->resize(pool_alloc->num_of_blocks << 1u);

        iterator iter = &array[c_iter - array];
        // Bug for non-POD types
        size_t sz = (pool_alloc->num_of_initialized - (c_iter - array)) * sizeof(T);
        if(sz > 0)
            memmove(iter + 1, iter, sz);
        *iter = std::move(uref_type);
        pool_alloc->num_of_initialized++;
        return iter;
    }

    template <typename T>
    typename vec<T>::iterator vec<T>::insert(vec::const_iterator pos, vec::size_type count,
                                             const T& value)
    {
        iterator iter = &array[pos - array];
        if(count <= 0)
            return iter;

        if((ptrdiff_t)(pool_alloc->num_of_blocks - pool_alloc->num_of_initialized - count) <= 0)
            pool_alloc->resize((pool_alloc->num_of_blocks + count) << 1u);

        // Bug for non-POD types
        size_t sz = (pool_alloc->num_of_initialized - (pos - array)) * sizeof(T);
        if(sz > 0)
            memmove(iter + count, iter, sz);
        for(iterator i = iter; count--; ++i)
            (*i) = value;
        pool_alloc->num_of_initialized += count;
        return iter;
    }

    template <typename T>
    template <typename InputIter>
    typename vec<T>::iterator vec<T>::insert(vec::const_iterator pos, InputIter first,
                                             InputIter last)
    {
        iterator iter = &array[pos - array];
        ptrdiff_t count = last - first;
        if(count <= 0)
            return iter;

        if((ptrdiff_t)(pool_alloc->num_of_blocks - pool_alloc->num_of_initialized - count) <= 0)
            pool_alloc->resize((pool_alloc->num_of_blocks + count) << 1u);

        // Bug for non-POD types
        size_t sz = (pool_alloc->num_of_initialized - (pos - array)) * sizeof(T);
        if(sz > 0)
            memmove(iter + count, iter, sz);
        size_t j = 0;
        for(iterator i = iter; first != last; ++i, ++first, ++j){
            (*i) = (*first);
        }
        pool_alloc->num_of_initialized += count;
        return nullptr;
    }

    template <typename T>
    typename vec<T>::iterator vec<T>::insert(vec::const_iterator pos,
                                             std::initializer_list<T> ilist)
    {
        size_t count = ilist.size();
        iterator iter = &array[pos - array];
        if(count <= 0)
            return iter;

        if((ptrdiff_t)(pool_alloc->num_of_blocks - pool_alloc->num_of_initialized - count) <= 0)
            pool_alloc->resize((pool_alloc->num_of_blocks + count) << 1u);

        // Bug for non-POD types
        size_t sz = (pool_alloc->num_of_initialized - (pos - array)) * sizeof(T);
        if(sz > 0)
            memmove(iter + count, iter, sz);
        iterator i = iter;
        for(auto& item : ilist) {
            (*i) = item;
            ++i;
        }
        pool_alloc->num_of_initialized += count;
        return i;
    }

    template <typename T>
    typename vec<T>::iterator vec<T>::erase(vec::const_iterator it)
    {
        iterator iter = &array[it - array];
        //        (*iter).~T();
        pool_alloc->deallocate(iter);
        //        memmove(iter, iter + 1, (pool_alloc->num_of_initialized - (it - array) - 1) * sizeof(T));
        //        pool_alloc->num_of_initialized--;
        //        pool_alloc->num_of_free_blocks++;
        return iter;
    }

    template <typename T>
    typename vec<T>::iterator vec<T>::erase(vec::const_iterator first, vec::const_iterator last)
    {
        iterator iter = &array[first - array];
        if(first == last)
            return iter;

        while(first != last) {
            ++first;
            //            (*first).~T();
            pool_alloc->deallocate(first);
        }

        memmove(iter, last, (pool_alloc->num_of_initialized - (last - array)) * sizeof(T));
        pool_alloc->num_of_initialized -= last - first;
        //        pool_alloc->num_of_free_blocks -= last - first;

        return iter;
    }

    template <typename T>
    void vec<T>::swap(vec<T>& other)
    {
        std::swap(*array, *other.array);
        pool_alloc.swap(other.pool_alloc);
    }

    template <typename T>
    void vec<T>::clear() noexcept
    {
        for(size_t i = 0; i < pool_alloc->num_of_initialized; ++i) {
            pool_alloc->deallocate(array[i]);
        }
    }

    template <typename T>
    bool vec<T>::operator==(const vec<T>& other) const
    {
        if(pool_alloc->num_of_initialized != other.pool_alloc->num_of_initialized)
            return false;

        for(size_t i = 0; i < pool_alloc->num_of_initialized; ++i) {
            if(array[i] != other.array[i]) {
                return false;
            }
        }

        return true;
    }

    template <typename T>
    bool vec<T>::operator!=(const vec<T>& other) const
    {
        if(pool_alloc->num_of_initialized != other.pool_alloc->num_of_initialized)
            return true;

        for(size_t i = 0; i < pool_alloc->num_of_initialized; ++i) {
            if(array[i] != other.array[i])
                return true;
        }
        return false;
    }

    template <typename T>
    bool vec<T>::operator<(const vec<T>& other) const
    {
        for(size_t i = 0,
                   size = pool_alloc->num_of_initialized < other.pool_alloc->num_of_initialized
                              ? pool_alloc->num_of_initialized
                              : other.pool_alloc->num_of_initialized;
            i < size; ++i) {
            if(array[i] != other.array[i])
                return array[i] < other.array[i];
        }

        return pool_alloc->num_of_initialized < other.pool_alloc->num_of_initialized;
    }

    template <typename T>
    bool vec<T>::operator<=(const vec<T>& other) const
    {
        for(size_t i = 0,
                   size = pool_alloc->num_of_initialized < other.pool_alloc->num_of_initialized
                              ? pool_alloc->num_of_initialized
                              : other.pool_alloc->num_of_initialized;
            i < size; ++i) {
            if(array[i] != other.array[i])
                return array[i] < other.array[i];
        }

        return pool_alloc->num_of_initialized <= other.pool_alloc->num_of_initialized;
    }

    template <typename T>
    bool vec<T>::operator>(const vec<T>& other) const
    {
        for(size_t i = 0,
                   size = pool_alloc->num_of_initialized < other.pool_alloc->num_of_initialized
                              ? pool_alloc->num_of_initialized
                              : other.pool_alloc->num_of_initialized;
            i < size; ++i) {
            if(array[i] != other.array[i])
                return array[i] > other.array[i];
        }

        return pool_alloc->num_of_initialized > other.pool_alloc->num_of_initialized;
    }

    template <typename T>
    bool vec<T>::operator>=(const vec<T>& other) const
    {
        for(size_t i = 0,
                   size = pool_alloc->num_of_initialized < other.pool_alloc->num_of_initialized
                              ? pool_alloc->num_of_initialized
                              : other.pool_alloc->num_of_initialized;
            i < size; ++i) {
            if(array[i] != other.array[i])
                return array[i] > other.array[i];
        }

        return pool_alloc->num_of_initialized >= other.pool_alloc->num_of_initialized;
    }
}

#endif //INC_2D_GAME_VEC_H
