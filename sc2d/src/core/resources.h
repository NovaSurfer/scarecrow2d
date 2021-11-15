//
// Created by novasurfer on 4/24/20.
//

#ifndef SCARECROW2D_RESOURCES_H
#define SCARECROW2D_RESOURCES_H

#include "result.h"

namespace sc2d
{

    struct Resources
    {
        static ResultBool load_all();
        static void clean_all();
    };
}

#endif //SCARECROW2D_RESOURCES_H
