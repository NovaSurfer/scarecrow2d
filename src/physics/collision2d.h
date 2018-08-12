//
// Created by maksim on 8/10/18.
//

#ifndef INC_2D_GAME_COLLISION2D_H
#define INC_2D_GAME_COLLISION2D_H

#include "../math/geometry2d.h"

namespace physics
{

    struct collision2d {

        bool circle_circle(const math::circle &c1, const math::circle &c2)
        {
            math::line2d line(c1.position, c2.position);
            float radiiSum = c1.radius + c2.radius;
            return math::line2d::lengthSq(line) <= radiiSum * radiiSum;
        }

        bool circle_rectangle(const math::circle &circle, const math::rect2d &rect)
        {
            math::vec2 min = math::rect2d::get_min(rect);
            math::vec2 max = math::rect2d::get_max(rect);

            math::point2d closest_point = circle.position;

            math::utils::clamp(circle.position.x, min.x, max.x);
            math::utils::clamp(circle.position.y, min.y, max.y);

            math::line2d line(circle.position, closest_point);
            return math::line2d::lengthSq(line) <= circle.radius * circle.radius;
        }

        bool rectangle_rectangle(const math::rect2d &rect1, const math::rect2d &rect2)
        {
            math::vec2 amin = math::rect2d::get_min(rect1);
            math::vec2 amax = math::rect2d::get_max(rect1);

            math::vec2 bmin = math::rect2d::get_min(rect2);
            math::vec2 bmax = math::rect2d::get_max(rect2);

            bool over_x = ((bmin.x <= amax.x) && (amin.x <= bmax.x));
            bool over_y = ((bmin.y <= amax.y) && (amin.y <= bmax.y));

            return over_x && over_y;
        }
        /*!
         * Tests if two intervals overlap
         */
        bool overlap_on_axis(const math::rect2d &rect1,
                const math::rect2d &rect2, const math::vec2 &axis)
        {
            math::interval2d a = math::interval2d::get_interval(rect1, axis);
            math::interval2d b = math::interval2d::get_interval(rect2, axis);
            return ((b.min <= a.max) && (a.min <= b.max));
        }

        bool rectange_rectange_sat(const math::rect2d &rect1, const math::rect2d &rect2)
        {
            math::vec2 axis_to_test[] = {math::vec2(1,0), math::vec2(0,1)};

            for(int i = 0; i < 2; ++i)
            {
                // Intervals don't overlap, separating axis found
                if(!overlap_on_axis(rect1, rect2, axis_to_test[i]))
                {
                    return false; // No collision has taken place
                }
            }
            // All intervals overlapped, separation axis not found.
            return true;
        };
    };
};

#endif //INC_2D_GAME_COLLISION2D_H
