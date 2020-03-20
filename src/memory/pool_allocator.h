//
// Created by maksim.ruts on 1.4.19.
//

#ifndef INC_2D_GAME_POOL_ALLOCATOR_H
#define INC_2D_GAME_POOL_ALLOCATOR_H

//#include "allocator.h"
//#include "aligned_allocator.h"
#include <memory>

namespace sc2d
{

    // Forward declaring vec<T> class
    template <typename T>
    class vec;

    namespace memory
    {
        enum class is_resized
        {
            NO,
            YES
        };

        struct alloc_result
        {
            const void* ptr = nullptr;
            is_resized resized = is_resized::NO;
        };

        class pool_allocator
        {

            template <typename T>
            friend class sc2d::vec;

        public:
            ~pool_allocator()
            {
                destroy();
            }

            void create(size_t block_size, size_t num_of_blocks, size_t alignment);
            void destroy();
            alloc_result allocate();
            void resize(size_t new_size);
            void deallocate(void* ptr);

            unsigned char* get_start() const
            {
                return p_start;
            }
            size_t get_intialized_num() const
            {
                return num_of_initialized;
            }
            size_t get_num_of_blocks() const
            {
                return num_of_blocks;
            }

        private:
            unsigned char* addr_from_index(size_t index) const;
            size_t index_from_addr(const unsigned char* ptr) const;

            size_t num_of_blocks = 0;
            size_t size_of_block = 0;
//            size_t num_of_free_blocks = 0;
            size_t num_of_initialized = 0;
            unsigned char* p_start = nullptr;
            unsigned char* p_next = nullptr;
        };
    }
}

#endif //INC_2D_GAME_POOL_ALLOCATOR_H
