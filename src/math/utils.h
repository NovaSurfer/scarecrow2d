//
// Created by maksim on 6/24/18.
//

#ifndef INC_2D_ENGINE_UTILS_H
#define INC_2D_ENGINE_UTILS_H

#include <cmath>
#include <cfloat>

namespace math
{
    struct utils
    {
        /**
         * Comparing floating point numbers
         */
        static bool cmp(const float x, const float y)
        {
            return fabsf(x - y) <=FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y)));
        }

        /**
         * Absolute tolerance test.
         * Fails when the numbers being compared are large.
         */
        static float absolute(const float x, const float y)
        {
            return fabsf(x - y) <= FLT_EPSILON;
        }

        /**
         * Relative tolerance test.
         * Fails when the numbers being compared are small.
         */
        static float relative(const float x, const float y)
        {
            return fabsf(x - y) <= FLT_EPSILON * fmaxf(fabsf(x), fabsf(y));
        }

        /**
         * Converting radians to degrees
         */
        constexpr static float rad2deg(const float x)
        {
            return x * 57.295754f;
        }

        /**
         * Converting degrees to radians
         */
        constexpr static float deg2rad(const float x)
        {
            return x * 0.0174533f;
        }

        constexpr static void clamp(float number, const float min, const float max)
        {
            number = (number < min) ? min : ((number > max) ? max : number);
        }
    };
}

#endif //INC_2D_ENGINE_UTILS_H
