//
// Created by Maksim Ruts on 25-Apr-18.
//

#ifndef INC_2D_ENGINE_VECTOR_H
#define INC_2D_ENGINE_VECTOR_H

#include "utils.h"
#include <ostream>

namespace math {
    // Two dimensional vector
    struct vec2 {
        float x, y;

        vec2() : x(0), y(0) {};

        vec2(float x, float y) : x(x), y(y) {}

        float &operator[](int i)
        {
            return ((&x)[i]);
        }

        const float &operator[](int i) const
        {
            return ((&x)[i]);
        }

        vec2 &operator*=(float s)
        {
            x *= s;
            y *= s;
            return (*this);
        }

        vec2 &operator/=(float s)
        {
            s = 1.0f / s;
            x *= s;
            y *= s;
            return (*this);
        }

        vec2 &operator+=(const vec2 &v)
        {
            x += v.x;
            y += v.y;
            return (*this);
        }

        vec2 operator-=(const vec2 &v)
        {
            x -= v.x;
            y -= v.y;
            return (*this);
        }

        friend std::ostream &operator<<(std::ostream &ostream, const vec2 &v)
        {
            ostream << "(" << v.x << "," << v.y << ")";
            return ostream;
        }
    };

    inline bool operator==(const vec2 &a, const vec2 &b)
    {
        return math::utils::cmp(a.x, b.x) && math::utils::cmp(a.y, b.y);
    }

    inline bool operator!=(const vec2 &a, const vec2 &b)
    {
        return !(a == b);
    }

    inline vec2 operator*(const vec2 &v, float s)
    {
        return (vec2(v.x * s, v.y * s));
    }

    inline vec2 operator/(const vec2 &v, float s)
    {
        s = 1.0f / s;
        return (vec2(v.x * s, v.y * s));
    }

    inline vec2 operator+(const vec2 &a, const vec2 &b)
    {
        return (vec2(a.x + b.x, a.y + b.y));
    }

    inline vec2 operator-(const vec2 &a, const vec2 &b)
    {
        return (vec2(a.x - b.x, a.y - b.y));
    }

    inline float dot(const vec2 &a, const vec2 &b)
    {
        return (a.x * b.x + a.y * b.y);
    }

    inline float magnitude(const vec2 &v)
    {
        return (std::sqrt(dot(v, v)));
    }

    inline float magnitudeSq(const vec2 &v)
    {
        return dot(v, v);
    }

    inline float distance(const vec2 &a, const vec2 &b)
    {
        vec2 t = a - b;
        return magnitude(t);
    }

    inline vec2 normalize(const vec2 &v)
    {
        return (v / magnitude(v));
    }

    inline float angle(const vec2 &a, const vec2 &b)
    {
        float m = std::sqrt(magnitudeSq(a) * magnitudeSq(b));
        return std::acos(dot(a, b) / m);
    }

    inline vec2 project(const vec2 &len, const vec2 &dir)
    {
        float d = dot(len, dir);
        float magSq = magnitudeSq(dir);
        return dir * (d / magSq);
    }

    inline vec2 perpendicular(const vec2 &len, const vec2 &dir)
    {
        return len - project(len, dir);
    }

    inline vec2 reflection(const vec2 &v, const vec2 &normal)
    {
        float d = dot(v, normal);
        return v - normal * (d * 2.0f);
    }
};


#endif //INC_2D_ENGINE_VECTOR_H