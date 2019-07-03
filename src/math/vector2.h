//
// Created by Maksim Ruts on 25-Apr-18.
//

#ifndef INC_2D_ENGINE_VECTOR2_H
#define INC_2D_ENGINE_VECTOR2_H

#include "utils.h"
#include <ostream>

// clang-format off
namespace math {
    /// Two dimensional vector
    struct vec2 {
        float x, y;

        vec2() : x(0), y(0) {};

        vec2(float x, float y) : x(x), y(y) {}

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
        vec2 &operator*=(float s)
        {
            x *= s;
            y *= s;
            return (*this);
        }

        /**
         * Division by scalar
         * @param s scalar
         * @return current vector
         */
        vec2 &operator/=(float s)
        {
            s = 1.0f / s;
            x *= s;
            y *= s;
            return (*this);
        }

        /**
         * Addition by other vector2
         * @param v some vector2
         * @return current vector
         */
        vec2 &operator+=(const vec2 &v)
        {
            x += v.x;
            y += v.y;
            return (*this);
        }

        /**
         * Subtraction by other vector2
         * @param v some vector2
         * @return current vector
         */
        vec2 operator-=(const vec2 &v)
        {
            x -= v.x;
            y -= v.y;
            return (*this);
        }

        /**
         * Stream insertion
         * @param ostream output stream
         * @param v vector that will be putted to stream
         * @note will be removed
         * @return
         */
        friend std::ostream &operator<<(std::ostream &ostream, const vec2 &v)
        {
            ostream << "(" << v.x << "," << v.y << ")";
            return ostream;
        }
    };

    /**
     * Compares two vectors
     * @param a
     * @param b
     * @return true if vectors are equal
     */
    inline bool operator==(const vec2 &a, const vec2 &b)
    {
        return math::utils::cmp(a.x, b.x) && math::utils::cmp(a.y, b.y);
    }

    /**
     * Compares two vectors
     * @param a
     * @param b
     * @return true if vectors are not equal
     */
    inline bool operator!=(const vec2 &a, const vec2 &b)
    {
        return !(a == b);
    }

    /**
     * Multiplication of vector by scalar
     * @param v some vector2
     * @param s some scalar
     * @return copy of the calculation result
     */
    inline vec2 operator*(const vec2 &v, float s)
    {
        return (vec2(v.x * s, v.y * s));
    }

    /**
     * Regular multiplication
     * @param a
     * @param b
     * @return copy of the calculation result
     */
    inline vec2 operator*(const vec2 &a, const vec2 &b)
    {
        return (vec2(a.x * b.x, a.y * b.y));
    }

    /**
     * Division of vector by scalar
     * @param v some vector2
     * @param s some scalar
     * @return copy of the calculation result
     */
    inline vec2 operator/(const vec2 &v, float s)
    {
        s = 1.0f / s;
        return (vec2(v.x * s, v.y * s));
    }

    /**
     * The sum of vectors
     * @param a
     * @param b
     * @return copy of the calculation result
     */
    inline vec2 operator+(const vec2 &a, const vec2 &b)
    {
        return (vec2(a.x + b.x, a.y + b.y));
    }

    /**
     * The difference of two vectors
     * @param a
     * @param b
     * @return copy of the calculation result
     */
    inline vec2 operator-(const vec2 &a, const vec2 &b)
    {
        return (vec2(a.x - b.x, a.y - b.y));
    }

    /**
     * Scalar product between two vectors
     * @param a
     * @param b
     * @return scalar value
     * @details https://en.wikipedia.org/wiki/Dot_product
     */
    inline float dot(const vec2 &a, const vec2 &b)
    {
        return (a.x * b.x + a.y * b.y);
    }

    /**
     * Lenght of the vector
     * @param v
     * @return scalar value
     * @details https://en.wikipedia.org/wiki/Magnitude_(mathematics)#Vector_spaces
     */
    inline float magnitude(const vec2 &v)
    {
        return (std::sqrt(dot(v, v)));
    }

    /**
     * Square length of the vector
     * @param v
     * @return scalar value
     * @note avoids expensive square root operation
     */
    inline float magnitudeSq(const vec2 &v)
    {
        return dot(v, v);
    }

    /**
     * Calculates distance between two vectors
     * @param a
     * @param b
     * @return scalar value
     * @details https://en.wikipedia.org/wiki/Euclidean_distance#Two_dimensions
     */
    inline float distance(const vec2 &a, const vec2 &b)
    {
        vec2 t = a - b;
        return magnitude(t);
    }

    /**
     * Vector normalization
     * @param v vector that will be normalized
     * @return unit vector
     * @details https://en.wikipedia.org/wiki/Unit_vector
     */
    inline vec2 normalize(const vec2 &v)
    {
        return (v / magnitude(v));
    }

    /**
     * Calculates angle between two vectors
     * @param a
     * @param b
     * @return angle in radians
     * @details https://en.wikipedia.org/wiki/Inner_product_space#Norms_on_inner_product_spaces
     */
    inline float angle(const vec2 &a, const vec2 &b)
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
    inline vec2 project(const vec2 &len, const vec2 &dir)
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
    inline vec2 perpendicular(const vec2 &len, const vec2 &dir)
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
    inline vec2 reflection(const vec2 &v, const vec2 &normal)
    {
        float d = dot(v, normal);
        return v - normal * (d * 2.0f);
    }
};


#endif //INC_2D_ENGINE_VECTOR2_H