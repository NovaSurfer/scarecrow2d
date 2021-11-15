//
// Created by novasurfer on 8/31/20.
//

#ifndef SCARECROW2D_ALLOCATOR_H
#define SCARECROW2D_ALLOCATOR_H

enum class is_resized
{
    NO,
    YES
};

struct alloc_result
{
    const unsigned char* ptr = nullptr;
    is_resized resized = is_resized::NO;
};

struct allocator
{
    alloc_result allocate();
    void deallocate(void* ptr);
};


#endif //SCARECROW2D_ALLOCATOR_H
