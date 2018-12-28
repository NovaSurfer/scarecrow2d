//
// Created by maksim on 6/27/18.
//

#ifndef INC_2D_ENGINE_MATRICES_H
#define INC_2D_ENGINE_MATRICES_H

#include "vector2.h"

namespace math {
    struct mat2 {
        float n[2][2];

        mat2() : n{0, 0, 0, 0} {};

        mat2(float _11, float _12,
                    float _21, float _22) :
                n{_11, _12,
                  _21, _22} {};

        mat2(const vec2 &a,
                    const vec2 &b) :
                n{a.x, a.y,
                  b.x, b.y} {};

        float &operator()(int i, int j)
        {
            return n[i][j];
        }

        const float &operator()(int i, int j) const
        {
            return n[j][i];
        }

        vec2 &operator[](int j)
        {
            return (*reinterpret_cast<vec2 *>(n[j]));
        }

        const vec2 &operator[](int j) const
        {
            return (*reinterpret_cast<const vec2 *>(n[j]));
        }

        mat2 operator*(float scalar) const
        {
            mat2 result;
            result.n[0][0] = n[0][0] * scalar;
            result.n[0][1] = n[0][1] * scalar;
            result.n[1][0] = n[1][0] * scalar;
            result.n[1][1] = n[1][1] * scalar;
            return result;
        }

        mat2 operator*(const mat2 &other) const
        {
            math::mat2 result;
            result.n[0][0] = n[0][0] * other.n[0][0] + n[0][1] * other.n[1][0];
            result.n[0][1] = n[0][0] * other.n[0][1] + n[0][1] * other.n[1][1];
            result.n[1][0] = n[1][0] * other.n[0][0] + n[1][1] * other.n[1][0];
            result.n[1][1] = n[1][0] * other.n[0][1] + n[1][1] * other.n[1][1];
            return result;
        }

        mat2 operator+(const mat2 &other) const
        {
            math::mat2 result;
            result.n[0][0] = n[0][0] + other.n[0][0];
            result.n[0][1] = n[0][1] + other.n[0][1];
            result.n[1][0] = n[1][0] + other.n[1][0];
            result.n[1][1] = n[1][1] + other.n[1][1];
            return result;
        }

        mat2 &operator*=(float scalar)
        {
            *this = *this * scalar;
            return *this;
        }

        mat2 &operator*=(const mat2 &other)
        {
            *this = *this * other;
            return *this;
        }

        mat2 &operator+=(const mat2 &other)
        {
            *this = *this + other;
            return *this;
        }

        bool operator==(const mat2 &other) const
        {
            return ( n[0][0] == other.n[0][0] &&
                     n[0][1] == other.n[0][1] &&
                     n[1][0] == other.n[1][0] &&
                     n[1][1] == other.n[1][1] );
        }

        bool operator!=(const mat2 &other) const
        {
            return !(*this == other);
        }

        friend std::ostream &operator<<(std::ostream &ostream, const mat2 &mat)
        {
            ostream << mat.n[0][0] << '\t' << mat.n[0][1] << '\n'
                    << mat.n[1][0] << '\t' << mat.n[1][1] << '\n';
            return ostream;
        }

        mat2 transpose() const
        {
            mat2 result;
            result.n[0][0] = n[0][0];
            result.n[0][1] = n[1][0];
            result.n[1][0] = n[0][1];
            result.n[1][1] = n[1][1];
            return result;
        }

        float determinant() const
        {
            return n[0][0] * n[1][1] -
                   n[0][1] * n[1][0];
        }

        mat2 minor() const
        {
            return mat2(n[1][1], n[1][0],
                        n[0][1], n[0][0]);
        }

        mat2 cofactor() const
        {
            mat2 result;
            mat2 minor_mat = minor();
            result.n[0][0] = minor_mat.n[0][0];
            result.n[0][1] = minor_mat.n[0][1] * -1.0f;
            result.n[1][0] = minor_mat.n[1][0] * -1.0f;
            result.n[1][1] = minor_mat.n[1][1];
            return result;
        }

        mat2 adjugate() const
        {
            mat2 transposed = transpose();
            return transposed.cofactor();
        }

        mat2 inverse()
        {
            float det = n[0][0] * n[1][1] - n[0][1] * n[1][0];

            if (utils::cmp(det, 0.0f)) return mat2();

            mat2 result;

            // To avoid excessive division
            float i_det = 1.0f / det;

            // Do reciprocal multiplication
            result.n[0][0] =  n[1][1] * i_det;
            result.n[0][1] = -n[0][1] * i_det;
            result.n[1][0] = -n[1][0] * i_det;
            result.n[1][1] =  n[0][0] * i_det;
            return result;
        }
    };
}


#endif //INC_2D_ENGINE_MATRICES_H
