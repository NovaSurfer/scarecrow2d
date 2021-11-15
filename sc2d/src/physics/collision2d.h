//
// Created by maksim on 8/10/18.
//

#ifndef INC_2D_GAME_COLLISION2D_H
#define INC_2D_GAME_COLLISION2D_H

#include "../math/geometry2d.h"

namespace physics::collision2d
{
    bool circle_circle(const math::circle& c1, const math::circle& c2)
    {
        math::line2d line(c1.position, c2.position);
        float radiiSum = c1.radius + c2.radius;
        return math::line2d::lengthSq(line) <= radiiSum * radiiSum;
    }

    bool circle_rectangle(const math::circle& circle, const math::rect2d& rect)
    {
        math::vec2 min = math::rect2d::get_min(rect);
        math::vec2 max = math::rect2d::get_max(rect);

        math::point2d closest_point = circle.position;

        math::utils::clamp(circle.position.x, min.x, max.x);
        math::utils::clamp(circle.position.y, min.y, max.y);

        math::line2d line(circle.position, closest_point);
        return math::line2d::lengthSq(line) <= circle.radius * circle.radius;
    }

    bool rectangle_rectangle(const math::rect2d& rect1, const math::rect2d& rect2)
    {
        math::vec2 amin = math::rect2d::get_min(rect1);
        math::vec2 amax = math::rect2d::get_max(rect1);

        math::vec2 bmin = math::rect2d::get_min(rect2);
        math::vec2 bmax = math::rect2d::get_max(rect2);

        bool over_x = ((bmin.x <= amax.x) && (amin.x <= bmax.x));
        bool over_y = ((bmin.y <= amax.y) && (amin.y <= bmax.y));

        return over_x && over_y;
    }

    bool rectange_rectange_sat(const math::rect2d& rect1, const math::rect2d& rect2)
    {
        return overlap_on_axis(rect1, rect2, math::vec2(1, 0)) &&
               overlap_on_axis(rect1, rect2, math::vec2(0, 1));
    }

    bool rectange_orrectangle(const math::rect2d& rect, const math::orrect2d& orrect)
    {
        float theta = math::utils::deg2rad(orrect.rotation);
        math::vec2 axis_to_test[] {{1, 0},
                                   {0, 1},
                                   math::normalize({orrect.half_extends.x, 0}),
                                   math::normalize({0, orrect.half_extends.y})};
        math::mat2 z_rotation {cosf(theta), sinf(theta), -sinf(theta), cosf(theta)};

        axis_to_test[2] = math::multiply_vector(axis_to_test[2], z_rotation);
        axis_to_test[3] = math::multiply_vector(axis_to_test[3], z_rotation);

        return math::overlap_on_axis(rect, orrect, axis_to_test[0]) &&
               math::overlap_on_axis(rect, orrect, axis_to_test[1]) &&
               math::overlap_on_axis(rect, orrect, axis_to_test[2]) &&
               math::overlap_on_axis(rect, orrect, axis_to_test[3]);
    };

//    bool orrectangle_orrectangle(const math::orrect2d& orrect1, const math::orrect2d& orrect2)
//    {
//        math::rect2d rect {math::point2d(), orrect1.half_extends * 2.0f};
//
//    }
};

#endif //INC_2D_GAME_COLLISION2D_H
