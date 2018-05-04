//
// Created by Maksim Ruts on 25-Apr-18.
//

#ifndef INC_2D_ENGINE_VECTOR_H
#define INC_2D_ENGINE_VECTOR_H

#include <cmath>
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

        inline friend vec2 operator*(const vec2 &v, float s)
        {
            return (vec2(v.x * s, v.y * s));
        }

        inline friend vec2 operator/(const vec2 &v, float s)
        {
            s = 1.0f / s;
            return (vec2(v.x * s, v.y * s));
        }

        inline friend vec2 operator-(const vec2 &v)
        {
            return (vec2(-v.x, -v.y));
        }

        inline friend vec2 operator+(const vec2 &a, const vec2 &b)
        {
            return (vec2(a.x + b.x, a.y + b.y));
        }

        inline friend vec2 operator-(const vec2 &a, const vec2 &b)
        {
            return (vec2(a.x - b.x, a.y - b.y));
        }

        // Pythagorean theorem in 2 dimensions
        inline friend float magnitude(const vec2 &v)
        {
            return (std::sqrt(v.x * v.x + v.y * v.y));
        }

        // Returns unit vector
        inline friend vec2 normalize(const vec2 &v)
        {
            return (v / magnitude(v));
        }

        inline friend std::ostream &operator<<(std::ostream &ostream, const vec2 &v)
        {
            ostream << "(" << v.x << "," << v.y << ")";
            return ostream;
        }
    };
};


#endif //INC_2D_ENGINE_VECTOR_H
