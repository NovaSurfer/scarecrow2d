//
// Created by Maksim Ruts on 25-Apr-18.
//

#ifndef INC_2D_ENGINE_VECTOR4_H
#define INC_2D_ENGINE_VECTOR4_H

#include "utils.h"
#include <ostream>

// clang-format off
namespace math {
    /// Four dimensional vector
    struct vec4 {
        float x, y, z, w;

        constexpr vec4() : x(0), y(0), z(0), w(0) {};

        constexpr vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

        /**
         * Gets element as array
         * @param i index
         * @return the element
         */
        float &operator[](int i)
        {
            return ((&x)[i]);
        }

        /**
         * Gets element as array
         * @param i index
         * @return the element
         */
        const float &operator[](int i) const
        {
            return ((&x)[i]);
        }

        /**
         * Multiplication by scalar
         * @param s scalar
         * @return current vector
         */
        vec4 &operator*=(float s)
        {
            x *= s;
            y *= s;
            z *= s;
            w *= s;
            return (*this);
        }

        /**
         * Division by scalar
         * @param s scalar
         * @return current vector
         */
        vec4 &operator/=(float s)
        {
            s = 1.0f / s;
            x *= s;
            y *= s;
            z *= s;
            w *= s;
            return (*this);
        }

        /**
         * Addition by other vector4
         * @param v some vector4
         * @return current vector
         */
        vec4 &operator+=(const vec4 &v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            w += v.w;
            return (*this);
        }

        /**
         * Subtraction by other vector4
         * @param v some vector4
         * @return current vector
         */
        vec4 operator-=(const vec4 &v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            w -= v.w;
            return (*this);
        }

        /**
         * Stream insertion
         * @param ostream output stream
         * @param v vector that will be putted to stream
         * @note will be removed
         * @return
         */
        friend std::ostream &operator<<(std::ostream &ostream, const vec4 &v)
        {
            ostream << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")\n";
            return ostream;
        }
    };

    /**
     * Compares two vectors
     * @param a
     * @param b
     * @return true if vectors are equal
     */
    inline bool operator==(const vec4 &a, const vec4 &b)
    {
        return math::utils::cmp(a.x, b.x) && math::utils::cmp(a.y, b.y)
        && math::utils::cmp(a.z, b.z) && math::utils::cmp(a.w, b.w);
    }

    /**
     * Compares two vectors
     * @param a
     * @param b
     * @return true if vectors are not equal
     */
    inline bool operator!=(const vec4 &a, const vec4 &b)
    {
        return !(a == b);
    }

    /**
     * Multiplication of vector by scalar
     * @param v some vector4
     * @param s some scalar
     * @return copy of the calculation result
     */
    inline vec4 operator*(const vec4 &v, float s)
    {
        return (vec4(v.x * s, v.y * s, v.z * s, v.w * s));
    }

    /**
     * Regular multiplication
     * @param a
     * @param b
     * @return copy of the calculation result
     */
    inline vec4 operator*(const vec4 &a, const vec4 &b)
    {
        return (vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w));
    }

    /**
     * Division of vector by scalar
     * @param v some vector4
     * @param s some scalar
     * @return copy of the calculation result
     */
    inline vec4 operator/(const vec4 &v, float s)
    {
        s = 1.0f / s;
        return (vec4(v.x * s, v.y * s, v.z * s, v.w * s));
    }

    /**
     * The sum of vectors
     * @param a
     * @param b
     * @return copy of the calculation result
     */
    inline vec4 operator+(const vec4 &a, const vec4 &b)
    {
        return (vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w));
    }

    /**
     * The difference of two vectors
     * @param a
     * @param b
     * @return copy of the calculation result
     */
    inline vec4 operator-(const vec4 &a, const vec4 &b)
    {
        return (vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w));
    }

    /**
     * Scalar product between two vectors
     * @param a
     * @param b
     * @return scalar value
     * @details https://en.wikipedia.org/wiki/Dot_product
     */
    inline float dot(const vec4 &a, const vec4 &b)
    {
        return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
    }

    /**
     * Lenght of the vector
     * @param v
     * @return scalar value
     * @details https://en.wikipedia.org/wiki/Magnitude_(mathematics)#Vector_spaces
     */
    inline float magnitude(const vec4 &v)
    {
        return (std::sqrt(dot(v, v)));
    }

    /**
     * Square length of the vector
     * @param v
     * @return scalar value
     * @note avoids expensive square root operation
     */
    inline float magnitudeSq(const vec4 &v)
    {
        return dot(v, v);
    }

    /**
     * Calculates distance between two vectors
     * @param a
     * @param b
     * @return scalar value
     * @details https://en.wikipedia.org/wiki/Euclidean_distance#Three_dimensions
     */
    inline float distance(const vec4 &a, const vec4 &b)
    {
        vec4 t = a - b;
        return magnitude(t);
    }

    /**
     * Vector normalization
     * @param v vector that will be normalized
     * @return unit vector
     * @details https://en.wikipedia.org/wiki/Unit_vector
     */
    inline vec4 normalize(const vec4 &v)
    {
        return (v / magnitude(v));
    }

    /**
     * Calculates vector that is perpendicular to both a and b
     * @param a
     * @param b
     * @return copy of the calculation result
     * @details https://en.wikipedia.org/wiki/Cross_product
     */
    inline vec4 cross(const vec4 &a, const vec4 &b)
    {
        vec4 result;
        result.x = a.y * b.z - a.z * b.y;
        result.y = a.z * b.x - a.x * b.z;
        result.z = a.x * b.y - a.y * b.x;
        // cross product for vec4 is not defined
        result.w = a.w;
        return result;
    }

    /**
     * Calculates angle between two vectors
     * @param a
     * @param b
     * @return angle in radians
     * @details https://en.wikipedia.org/wiki/Inner_product_space#Norms_on_inner_product_spaces
     */
    inline float angle(const vec4 &a, const vec4 &b)
    {
        float m = std::sqrt(magnitudeSq(a) * magnitudeSq(b));
        return std::acos(dot(a, b) / m);
    }

    /**
     * Project one vector onto another
     * @param len
     * @param dir
     * @return projected vector
     * @details https://en.wikipedia.org/wiki/Vector_projection#Vector_projection_2
     */
    inline vec4 project(const vec4 &len, const vec4 &dir)
    {
        float d = dot(len, dir);
        float magSq = magnitudeSq(dir);
        return dir * (d / magSq);
    }

    /**
     * Calculates perpendicular vector
     * @param len
     * @param dir
     * @return
     */
    inline vec4 perpendicular(const vec4 &len, const vec4 &dir)
    {
        return len - project(len, dir);
    }

    /**
     * Calculates reflected vector
     * @param v
     * @param normal
     * @return reflected vector v around normal
     * @details https://en.wikipedia.org/wiki/Reflection_(mathematics)
     */
    inline vec4 reflection(const vec4 &v, const vec4 &normal)
    {
        float d = dot(v, normal);
        return v - normal * (d * 2.0f);
    }
};


#endif //INC_2D_ENGINE_VECTOR4_H