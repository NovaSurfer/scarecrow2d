//
// Created by maksim on 6/27/18.
//

#ifndef INC_2D_ENGINE_MATRICES_H
#define INC_2D_ENGINE_MATRICES_H

#include "vector.h"

namespace math {
    struct mat2 {
        float n[2][2];

        inline mat2() : n{0, 0, 0, 0} {};

        inline mat2(float _11, float _12,
                    float _21, float _22) :
                n{_11, _12,
                  _21, _22} {};

        inline mat2(const vec2 &a,
                    const vec2 &b) :
                n{a.x, a.y,
                  b.x, b.y} {};

        inline float &operator()(int i, int j)
        {
            return n[i][j];
        }

        inline const float &operator()(int i, int j) const
        {
            return n[j][i];
        }

        inline vec2 &operator[](int j)
        {
            return (*reinterpret_cast<vec2 *>(n[j]));
        }

        inline const vec2 &operator[](int j) const
        {
            return (*reinterpret_cast<const vec2 *>(n[j]));
        }

        inline mat2 operator*(float scalar) const
        {
            mat2 result;
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    result.n[i][j] = n[i][j] * scalar;
                }
            }
            return result;
        }

        inline mat2 operator*(const mat2 &other) const
        {
            math::mat2 result;
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    for (int k = 0; k < 2; k++)
                    {
                        result.n[i][j] += n[i][k] * other.n[k][j];
                    }
                }
            }
            return result;
        }

        inline mat2 &operator*=(float scalar)
        {
            *this = *this * scalar;
            return *this;
        }

        inline mat2 &operator*=(const mat2 &other)
        {
            *this = *this * other;
            return *this;
        }

        inline bool operator==(const mat2 &other) const
        {
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    if (this->n[i][j] != other.n[i][j])
                        return false;
                }
            }
            return true;
        }

        inline bool operator !=(const mat2 &other) const
        {
            return !(*this == other);
        }

        inline friend std::ostream &operator<<(std::ostream &ostream, const mat2 &mat)
        {
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    ostream << mat.n[i][j] << ' ';
                }
                ostream << '\n';
            }
            return ostream;
        }

        inline mat2 transpose() const
        {
            mat2 result;
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    result.n[i][j] = n[j][i];
                }
            }
            return result;
        }

        inline float determinant() const
        {
            return n[0][0] * n[1][1] -
                   n[0][1] * n[1][0];
        }

        inline mat2 minor() const
        {
            return mat2(n[1][1], n[1][0],
                        n[0][1], n[0][0]);
        }

        inline mat2 cofactor() const
        {
            mat2 result;
            mat2 minor_mat = minor();

            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    float sign = powf(-1.0f, i + j);
                    result[i][j] = sign * minor_mat.n[i][j];
                }
            }
            return result;
        }

        inline mat2 adjugate() const
        {
            mat2 transposed = transpose();
            return transposed.cofactor();
        }
    };
}


#endif //INC_2D_ENGINE_MATRICES_H
