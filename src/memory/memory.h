//
// Created by Maksim on 4/8/2019.
//

#ifndef INC_2D_GAME_MEMORY_H
#define INC_2D_GAME_MEMORY_H

class allocator;

namespace sc2d::memory
{
    allocator& default_allocator();

    namespace main
    {
        void init();
        void destroy();
    }
}

#endif //INC_2D_GAME_MEMORY_H
