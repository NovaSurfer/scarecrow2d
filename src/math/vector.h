//
// Created by Maksim Ruts on 25-Apr-18.
//

#ifndef INC_2D_ENGINE_VECTOR_H
#define INC_2D_ENGINE_VECTOR_H

#include <cmath>

namespace math
{
    // Two dimensional vector
    struct vec2
    {
        float x, y;

        vec2() = default;
        vec2(float x, float y): x(x), y(y) {}

        float& operator [](int i)
        {
            return ((&x)[i]);
        }

        const float& operator [](int i) const
        {
            return ((&x)[i]);
        }

        vec2& operator *=(float s)
        {
            x *= s;
            y *= s;
            return (*this);
        }

        vec2& operator /=(float s)
        {
            s = 1.0f / s;
            x *= s;
            y *= s;
            return (*this);
        }

    };

    inline vec2 operator *(const vec2& v, float s)
    {
        return (vec2(v.x * s, v.y * s));
    }

    inline vec2 operator /(const vec2& v, float s)
    {
        s = 1.0f / s;
        return (vec2(v.x * s, v.y * s));
    }

    inline vec2 operator -(const vec2& v)
    {
        return (vec2(-v.x, -v.y));
    }

    // Pythagorean theorem in 2 dimensions
    inline float magnitude(const vec2& v)
    {
        return (std::sqrt(v.x*v.x + v.y*v.y));
    }

    // Returns unit vector
    inline vec2 normalize(const vec2& v)
    {
        return (v / magnitude(v));
    }
};


#endif //INC_2D_ENGINE_VECTOR_H
