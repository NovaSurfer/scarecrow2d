//
// Created by maksim on 6/27/18.
//

#ifndef INC_2D_ENGINE_MATRICES_H
#define INC_2D_ENGINE_MATRICES_H

#include "vector.h"

namespace math {
    struct mat2 {
        float n[2][2];

        mat2() : n{0, 0, 0, 0} {};

        mat2(float _11, float _12, float _21, float _22)
                : n{_11, _12,
                    _21, _22} {};

        mat2(const vec2& a, const vec2& b)
                : n{a.x, a.y,
                    b.x, b.y} {};

        float& operator()(int i, int j)
        {
            return n[i][j];
        }

        const float& operator()(int i, int j) const
        {
            return n[j][i];
        }

        vec2& operator[](int j)
        {
            return (*reinterpret_cast<vec2 *>(n[j]));
        }

        const vec2& operator[](int j) const
        {
            return (*reinterpret_cast<const vec2 *>(n[j]));
        }

        inline friend mat2 operator*(const mat2& matrix, float scalar)
        {
            mat2 result;
            for(int i = 0; i < 2; i++)
            {
                for(int j = 0; j < 2; j++)
                {
                    result.n[i][j] = matrix.n[i][j] * scalar;
                }
            }
            return result;
        }

        inline friend mat2 operator*(const mat2& mat1, const mat2& mat2)
        {
            math::mat2 result;
            for(int i = 0; i < 2; i++)
            {
                for(int j = 0; j < 2; j++)
                {
                    for(int k = 0; k < 2; k++)
                    {
                        result.n[i][j] += mat1.n[i][k] * mat2.n[k][j];
                    }
                }
            }
            return result;
        }

        inline friend std::ostream &operator<<(std::ostream &ostream, const mat2 &mat)
        {
            for(int i = 0; i < 2; i++)
            {
                for(int j = 0; j < 2; j++)
                {
                    ostream << mat.n[i][j] << ' ';
                }
                ostream << '\n';
            }
            return ostream;
        }

        mat2 transpose(const mat2& matrix)
        {
            mat2 result;
            for(int i = 0; i < 2; i++)
            {
                for(int j = 0; j < 2; j++)
                {
                    result.n[j][i] = matrix.n[i][j];
                }
            }
        }
    };
}


#endif //INC_2D_ENGINE_MATRICES_H
