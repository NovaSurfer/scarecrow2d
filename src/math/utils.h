//
// Created by maksim on 6/24/18.
//

#ifndef INC_2D_ENGINE_UTILS_H
#define INC_2D_ENGINE_UTILS_H

namespace math
{
    struct utils
    {
        constexpr inline static float red2deg (const float x) const
        {
            return x * 57.295754f;
        }

        constexpr inline static float deg2rag (const float x) const
        {
            return x * 0.0174533f;
        }
    };
}

#endif //INC_2D_ENGINE_UTILS_H
