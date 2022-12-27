//
// Created by max on 12/13/22.
//

#ifndef SCARECROW2D_UTILS_H
#define SCARECROW2D_UTILS_H

#include <stdlib.h>
#include "vulkan/vulkan.h"

static void VK_ASSERT(bool check)
{
    if(!check)
        exit(EXIT_FAILURE);
}

#define VK_CHECK(value)                                                                            \
    if(value != VK_SUCCESS) {                                                                      \
        VK_ASSERT(false);                                                                          \
        return false;                                                                              \
    }
#define VK_CHECK_RET(value)                                                                        \
    if(value != VK_SUCCESS) {                                                                      \
        VK_ASSERT(false);                                                                          \
        return value;                                                                              \
    }

#endif //SCARECROW2D_UTILS_H
