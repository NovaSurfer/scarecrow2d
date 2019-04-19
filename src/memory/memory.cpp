// Copyright (C) 2012 Bitsquid AB
// License: https://bitbucket.org/bitsquid/foundation/src/default/LICENCSE

#include <malloc.h>
#include <new>

#include "allocator.h"
#include "memory.h"
#include "free_list_allocator.h"


namespace sc2d::memory::main
{
    constexpr size_t _memory_size = 1024 * 1024 * 31; // 32,5 MB
    static void* _buffer;
    static free_list_allocator* _main_allocator;

    void init()
    {
        _buffer = malloc(_memory_size);
        _main_allocator = new (_buffer) free_list_allocator(_memory_size - sizeof(free_list_allocator),
                        reinterpret_cast<void *>(reinterpret_cast<uintptr_t>(_buffer) + sizeof(free_list_allocator)));
    }

    void destroy()
    {
        _main_allocator->~allocator();
    }
}