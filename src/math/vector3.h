//
// Created by Maksim Ruts on 25-Apr-18.
//

#ifndef INC_2D_ENGINE_VECTOR_H
#define INC_2D_ENGINE_VECTOR_H

#include "utils.h"
#include <ostream>

namespace math {
    // Two dimensional vector
    struct vec3 {
        float x, y, z;

        vec3() : x(0), y(0), z(0){};

        vec3(float x, float y, float z) : x(x), y(y), z(z) {}

        float &operator[](int i)
        {
            return ((&x)[i]);
        }

        const float &operator[](int i) const
        {
            return ((&x)[i]);
        }

        vec3 &operator*=(float s)
        {
            x *= s;
            y *= s;
            z *= s;
            return (*this);
        }

        vec3 &operator/=(float s)
        {
            s = 1.0f / s;
            x *= s;
            y *= s;
            z *= s;
            return (*this);
        }

        vec3 &operator+=(const vec3 &v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return (*this);
        }

        vec3 operator-=(const vec3 &v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return (*this);
        }

        friend std::ostream &operator<<(std::ostream &ostream, const vec3 &v)
        {
            ostream << "(" << v.x << "," << v.y << "," << v.z << ")\n";
            return ostream;
        }
    };

    inline bool operator==(const vec3 &a, const vec3 &b)
    {
        return math::utils::cmp(a.x, b.x) && math::utils::cmp(a.y, b.y) && math::utils::cmp(a.z, b.z);
    }

    inline bool operator!=(const vec3 &a, const vec3 &b)
    {
        return !(a == b);
    }

    inline vec3 operator*(const vec3 &v, float s)
    {
        return (vec3(v.x * s, v.y * s, v.z));
    }

    inline vec3 operator/(const vec3 &v, float s)
    {
        s = 1.0f / s;
        return (vec3(v.x * s, v.y * s, v.z * s));
    }

    inline vec3 operator+(const vec3 &a, const vec3 &b)
    {
        return (vec3(a.x + b.x, a.y + b.y, a.z + b.z));
    }

    inline vec3 operator-(const vec3 &a, const vec3 &b)
    {
        return (vec3(a.x - b.x, a.y - b.y, a.z - b.z));
    }

    inline float dot(const vec3 &a, const vec3 &b)
    {
        return (a.x * b.x + a.y * b.y + a.z * b.z);
    }

    inline float magnitude(const vec3 &v)
    {
        return (std::sqrt(dot(v, v)));
    }

    inline float magnitudeSq(const vec3 &v)
    {
        return dot(v, v);
    }

    inline float distance(const vec3 &a, const vec3 &b)
    {
        vec3 t = a - b;
        return magnitude(t);
    }

    inline vec3 normalize(const vec3 &v)
    {
        return (v / magnitude(v));
    }

    inline vec3 cross(const vec3 &a, const vec3 &b)
    {
        vec3 result;
        result.x = a.y * b.z - a.z * b.y;
        result.y = a.z * b.x - a.x * b.z;
        result.z = a.x * b.y - a.y * b.x;
        return result;
    }

    inline float angle(const vec3 &a, const vec3 &b)
    {
        float m = std::sqrt(magnitudeSq(a) * magnitudeSq(b));
        return std::acos(dot(a, b) / m);
    }

    inline vec3 project(const vec3 &len, const vec3 &dir)
    {
        float d = dot(len, dir);
        float magSq = magnitudeSq(dir);
        return dir * (d / magSq);
    }

    inline vec3 perpendicular(const vec3 &len, const vec3 &dir)
    {
        return len - project(len, dir);
    }

    inline vec3 reflection(const vec3 &v, const vec3 &normal)
    {
        float d = dot(v, normal);
        return v - normal * (d * 2.0f);
    }
};


#endif //INC_2D_ENGINE_VECTOR_H