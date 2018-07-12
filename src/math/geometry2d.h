//
// Created by maksim on 7/12/18.
//

#ifndef INC_2D_GAME_GEOMETRY2D_H
#define INC_2D_GAME_GEOMETRY2D_H

#include "vector.h"

namespace math
{
    using point2d = vec2;

    struct line2d {
        point2d start;
        point2d end;

        inline line2d() = default;
        inline line2d(const point2d& start, const point2d& end) : start(start), end(end){};

        inline float length(const line2d &line)
        {
            return math::vec2::magnitude(line.end - line.start);
        }

        inline float lengthSq(const line2d &line)
        {
            return math::vec2::magnitudeSq(line.end - line.start);
        }
    };

    struct circle {
        point2d position;
        float radius;

        inline circle() : radius(1.0f) {}
        inline circle(const point2d &pos, const float radius) : position(pos), radius(radius) {}

    };

    struct rect2d {
        point2d origin;
        vec2 size;

        inline rect2d() : size(1.0f,1.0f) {}
        inline rect2d(const point2d& origin, const vec2 &size) : origin(origin), size(size) {}

        inline vec2 get_min(const rect2d rect)
        {
            vec2 p1 = rect.origin;
            vec2 p2 = rect.origin + rect.size;

            return vec2(fminf(p1.x, p2.x), fminf(p1.y, p2.y));
        }

        inline vec2 get_max(const rect2d rect)
        {
            vec2 p1 = rect.origin;
            vec2 p2 = rect.origin + rect.size;

            return vec2(fmaxf(p1.x, p2.x), fmaxf(p1.y, p2.y));
        }

        inline rect2d from_min_max(const vec2 &min, const vec2 &max)
        {
            return rect2d(min, max-min);
        }
    };
};

#endif //INC_2D_GAME_GEOMETRY2D_H
