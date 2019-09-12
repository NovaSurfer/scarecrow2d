//
// Created by maksim on 7/12/18.
//

#ifndef INC_2D_GAME_GEOMETRY2D_H
#define INC_2D_GAME_GEOMETRY2D_H

#include "matrix2.h"
#include "transform.h"
#include "utils.h"
#include "vector2.h"

namespace math
{
    using point2d = vec2;

    struct line2d
    {
        point2d start;
        point2d end;

        line2d() = default;
        line2d(const point2d& start, const point2d& end)
            : start(start)
            , end(end) {};

        static float length(const line2d& line)
        {
            return math::magnitude(line.end - line.start);
        }

        static float lengthSq(const line2d& line)
        {
            return math::magnitudeSq(line.end - line.start);
        }
    };

    struct circle
    {
        point2d position;
        float radius;

        circle()
            : radius(1.0f)
        {}
        circle(const point2d& pos, const float radius)
            : position(pos)
            , radius(radius)
        {}
    };

    struct rect2d
    {
        point2d origin;
        vec2 size;

        rect2d()
            : size(1.0f, 1.0f)
        {}
        rect2d(const point2d& origin, const vec2& size)
            : origin(origin)
            , size(size)
        {}

        static vec2 get_min(const rect2d rect)
        {
            vec2 p1 = rect.origin;
            vec2 p2 = rect.origin + rect.size;

            return vec2(fminf(p1.x, p2.x), fminf(p1.y, p2.y));
        }

        static vec2 get_max(const rect2d rect)
        {
            vec2 p1 = rect.origin;
            vec2 p2 = rect.origin + rect.size;

            return vec2(fmaxf(p1.x, p2.x), fmaxf(p1.y, p2.y));
        }

        static rect2d from_min_max(const vec2& min, const vec2& max)
        {
            return rect2d(min, max - min);
        }
    };

    struct orrect2d
    {
        point2d position;
        vec2 half_extends;
        float rotation;

        orrect2d()
            : half_extends(vec2(0, 0))
            , rotation(0)
        {}
        orrect2d(const point2d& positon, const vec2& half_extends)
            : position(positon)
            , half_extends(half_extends)
            , rotation(0)
        {}
        orrect2d(const point2d& positon, const vec2& half_extends, float rotation)
            : position(positon)
            , half_extends(half_extends)
            , rotation(rotation)
        {}
    };

    struct interval2d
    {
        float min;
        float max;

        static interval2d get_interval(const rect2d& rect, const vec2& axis)
        {
            interval2d result {};
            // Find the min and max of the rectangle being tested
            vec2 min = rect2d::get_min(rect);
            vec2 max = rect2d::get_max(rect);
            // building a set of vertices
            vec2 verts[] {// get all vertices of rect
                          vec2(min.x, min.y), vec2(max.x, max.y)};
            // Project each vertex onto the axis, store the smallest and largest values
            result.min = result.max = dot(axis, verts[0]);
            for(int i = 0; i < 4; ++i) {
                float projection = dot(axis, verts[i]);
                if(projection < result.min) {
                    result.min = projection;
                }
                if(projection > result.max) {
                    result.max = projection;
                }
            }
            return result;
        }

        static interval2d get_interval(const orrect2d& orrect, const vec2& axis)
        {
            // construct a non-oriented rectangle
            rect2d rect(point2d(orrect.position - orrect.half_extends), orrect.half_extends * 2.0f);
            // find vertices of that triangle
            vec2 min = rect2d::get_min(rect);
            vec2 max = rect2d::get_max(rect);

            vec2 verts[] {min, max, min, max};

            // rotation matrix for oriented rectangle
            float theta = utils::deg2rad(orrect.rotation);
            mat2 z_rotation {cosf(theta), sinf(theta), -sinf(theta), cosf(theta)};

            // Rotate every vertex of the non oriented rectangle
            // with rotation matrix, in order to get verts positions in
            // world space
            vec2 rot_vec = verts[0] - orrect.position;
            rot_vec = multiply_vector(rot_vec, z_rotation);
            verts[0] = rot_vec + orrect.position;

            rot_vec = verts[1] - orrect.position;
            rot_vec = multiply_vector(rot_vec, z_rotation);
            verts[1] = rot_vec + orrect.position;

            rot_vec = verts[2] - orrect.position;
            rot_vec = multiply_vector(rot_vec, z_rotation);
            verts[2] = rot_vec + orrect.position;

            rot_vec = verts[3] - orrect.position;
            rot_vec = multiply_vector(rot_vec, z_rotation);
            verts[3] = rot_vec + orrect.position;

            interval2d result;
            // store the min & max points of every projected vertex as the
            // interval of the rectangle.
            result.min = result.max = dot(axis, verts[0]);
            float proj = dot(axis, verts[1]);
            result.min = proj < result.min ? proj : result.min;
            result.max = proj > result.max ? proj : result.max;

            proj = dot(axis, verts[2]);
            result.min = proj < result.min ? proj : result.min;
            result.max = proj > result.max ? proj : result.max;

            proj = dot(axis, verts[3]);
            result.min = proj < result.min ? proj : result.min;
            result.max = proj > result.max ? proj : result.max;

            return result;
        }
    };

    /***
     * @details <a href="https://en.wikipedia.org/wiki/Slope#Algebra_and_geometry">Slope-intercept form</a>
     * @param point
     * @param line
     * @return
     */
    bool point_on_line(const point2d& point, const line2d& line)
    {
        // Find slope
        float dy = line.end.y - line.start.y;
        float dx = line.end.x - line.start.x;
        float m = dy / dx;
        // Find the Y-Intercept
        float b = line.start.y - m * line.start.x;
        // Check line equation
        return utils::cmp(point.y, m * point.x + b);
    }

    /***
     * @details A point is inside a circle if the length of a line from the center of the circle to the point being
     *          tested is less than the radius of the circle. Finding the length of a line involves a square root
     *          operation, we can avoid this by checking the square length of the line against the square
     *          radius of the circle.
     * @param point
     * @param c
     * @return
     */
    bool point_in_circle(const point2d& point, const circle& c)
    {
        line2d line(point, c.position);
        return line2d::lengthSq(line) >= c.radius * c.radius;
    }

    bool point_in_rect(const point2d& point, const rect2d rect)
    {
        vec2 min = rect2d::get_min(rect);
        vec2 max = rect2d::get_max(rect);
        return min.x <= point.x && min.y <= point.y && point.x <= max.x && point.y <= max.y;
    }

    bool point_in_orrect(const point2d& point, const orrect2d rect)
    {
        rect2d local_rect {point2d(), rect.half_extends * 2.0f};
        vec2 rot_vec = point - rect.position;
        float theta = -utils::deg2rad(rect.rotation);
        mat2 z_rotation {cosf(theta), sinf(theta), -sinf(theta), cosf(theta)};

        rot_vec = multiply_vector(rot_vec, z_rotation);
        vec2 local_point = rot_vec + rect.half_extends;

        return point_in_rect(local_point, local_rect);
    }

    bool line_circle(const line2d& line, const circle& circle)
    {
        vec2 ab = line.end - line.start;
        float t = dot(circle.position - line.start, ab) / magnitudeSq(ab);
        if(t < 0.0f || t > 1.0f) {
            return false;
        }
        point2d closest_point = line.start + ab * t;
        line2d circle_to_closest(circle.position, closest_point);
        return line2d::lengthSq(circle_to_closest) < circle.radius * circle.radius;
    }

    bool line_rect(const line2d& line, const rect2d& rect)
    {
        if(point_in_rect(line.start, rect) || point_in_rect(line.end, rect)) {
            return true;
        }
        vec2 norm = normalize(line.end - line.start);
        norm.x = (norm.x != 0) ? 1.0f / norm.x : 0;
        norm.y = (norm.y != 0) ? 1.0f / norm.y : 0;
        vec2 min = (rect2d::get_min(rect) - line.start) * norm;
        vec2 max = (rect2d::get_max(rect) - line.end) * norm;

        float tmin = fmaxf(fminf(min.x, max.x), fmaxf(min.y, max.y));

        float tmax = fminf(fmaxf(min.x, max.x), fmaxf(min.y, max.y));

        if(tmax < 0 || tmin > tmax)
            return false;

        float t = (tmin < 0.0f) ? tmax : tmin;
        return t > 0.0f && t * t < line2d::lengthSq(line);
    }

    bool line_orrect(const line2d& line, const orrect2d& orrect)
    {
        float theta = -utils::deg2rad(orrect.rotation);
        mat2 z_rotation {cosf(theta), sinf(theta), -sinf(theta), cosf(theta)};
        line2d local_line;

        vec2 rot_vector = line.start - orrect.position;
        rot_vector = multiply_vector(rot_vector, z_rotation);
        local_line.start = rot_vector + orrect.half_extends;

        rot_vector = line.end - orrect.position;
        rot_vector = multiply_vector(rot_vector, z_rotation);
        local_line.end = rot_vector + orrect.half_extends;

        rect2d local_rect {point2d(), orrect.half_extends * 2.0f};

        return line_rect(local_line, local_rect);
    };

    bool overlap_on_axis(const math::rect2d& rect1, const math::rect2d& rect2,
                                const math::vec2& axis)
    {
        interval2d a = interval2d::get_interval(rect1, axis);
        interval2d b = interval2d::get_interval(rect2, axis);
        return ((b.min <= a.max) && (a.min <= b.max));
    }

    bool overlap_on_axis(const math::rect2d& rect1, const math::orrect2d& rect2,
                         const math::vec2& axis)
    {
        interval2d a = interval2d::get_interval(rect1, axis);
        interval2d b = interval2d::get_interval(rect2, axis);
        return ((b.min <= a.max) && (a.min <= b.max));
    }
};

#endif //INC_2D_GAME_GEOMETRY2D_H
