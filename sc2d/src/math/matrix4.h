
//
// Created by maksim on 6/27/18.
//

#ifndef INC_2D_ENGINE_matrix4_H
#define INC_2D_ENGINE_matrix4_H

#include "vector4.h"

// clang-format off
namespace math {
    /// Four dimensional square matrix
    struct mat4 {
        float n[4][4];

        constexpr mat4() : n{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}} {};

        constexpr mat4(float _11, float _12, float _13, float _14,
             float _21, float _22, float _23, float _24,
             float _31, float _32, float _33, float _34,
             float _41, float _42, float _43, float _44)
             : n{{_11, _12, _13, _14},
                 {_21, _22, _23, _24},
                 {_31, _32, _33, _34},
                 {_41, _42, _43, _44}} {};

        constexpr mat4(const vec4 &a,
             const vec4 &b,
             const vec4 &c,
             const vec4 &d)
             : n{{a.x, a.y, a.z, a.w},
                 {b.x, b.y, b.z, b.w},
                 {c.x, c.y, c.z, c.w},
                 {d.x, d.y, d.z, d.w}} {};
        /**
         * Gets element value
         * @param i row number
         * @param j column number
         * @return matrix element 
         */
        float &operator()(int i, int j)
        {
            return n[i][j];
        }

        /**
         * Gets element value
         * @param i row number
         * @param j column number
         * @return matrix element 
         */
        const float &operator()(int i, int j) const
        {
            return n[j][i];
        }

        /**
         * Gets row as vector
         * @param j row number
         * @return row in vec4 representation  
         */
        vec4 &operator[](int j)
        {
            return (*reinterpret_cast<vec4 *>(n[j]));
        }

        /**
         * Gets row as vector
         * @param j row number
         * @return row in vec4 representation  
         */
        const vec4 &operator[](int j) const
        {
            return (*reinterpret_cast<const vec4 *>(n[j]));
        }

        /**
         * Multiplication by scalar
         * @param scalar 
         * @return calculated matrix
         */
        mat4 operator*(float scalar) const
        {
            mat4 result;
            result.n[0][0] = n[0][0] * scalar;
            result.n[0][1] = n[0][1] * scalar;
            result.n[0][2] = n[0][2] * scalar;
            result.n[0][3] = n[0][3] * scalar;

            result.n[1][0] = n[1][0] * scalar;
            result.n[1][1] = n[1][1] * scalar;
            result.n[1][2] = n[1][2] * scalar;
            result.n[1][3] = n[1][3] * scalar;

            result.n[2][0] = n[2][0] * scalar;
            result.n[2][1] = n[2][1] * scalar;
            result.n[2][2] = n[2][2] * scalar;
            result.n[2][3] = n[2][3] * scalar;

            result.n[3][0] = n[3][0] * scalar;
            result.n[3][1] = n[3][1] * scalar;
            result.n[3][2] = n[3][2] * scalar;
            result.n[3][3] = n[3][3] * scalar;
            return result;
        }

        /**
         * Multiplication by other matrix4
         * @param o some matrix4
         * @return calculated matrix
         * @details https://en.wikipedia.org/wiki/Matrix_multiplication
         */
        mat4 operator*(const mat4 &o) const
        {
            math::mat4 result;
            result.n[0][0] = n[0][0] * o.n[0][0] + n[0][1] * o.n[1][0] + n[0][2] * o.n[2][0] + n[0][3] * o.n[3][0];
            result.n[0][1] = n[0][0] * o.n[0][1] + n[0][1] * o.n[1][1] + n[0][2] * o.n[2][1] + n[0][3] * o.n[3][1];
            result.n[0][2] = n[0][0] * o.n[0][2] + n[0][1] * o.n[1][2] + n[0][2] * o.n[2][2] + n[0][3] * o.n[3][2];
            result.n[0][3] = n[0][0] * o.n[0][3] + n[0][1] * o.n[1][3] + n[0][2] * o.n[2][3] + n[0][3] * o.n[3][3];

            result.n[1][0] = n[1][0] * o.n[0][0] + n[1][1] * o.n[1][0] + n[1][2] * o.n[2][0] + n[1][3] * o.n[3][0];
            result.n[1][1] = n[1][0] * o.n[0][1] + n[1][1] * o.n[1][1] + n[1][2] * o.n[2][1] + n[1][3] * o.n[3][1];
            result.n[1][2] = n[1][0] * o.n[0][2] + n[1][1] * o.n[1][2] + n[1][2] * o.n[2][2] + n[1][3] * o.n[3][2];
            result.n[1][3] = n[1][0] * o.n[0][3] + n[1][1] * o.n[1][3] + n[1][2] * o.n[2][3] + n[1][3] * o.n[3][3];

            result.n[2][0] = n[2][0] * o.n[0][0] + n[2][1] * o.n[1][0] + n[2][2] * o.n[2][0] + n[2][3] * o.n[3][0];
            result.n[2][1] = n[2][0] * o.n[0][1] + n[2][1] * o.n[1][1] + n[2][2] * o.n[2][1] + n[2][3] * o.n[3][1];
            result.n[2][2] = n[2][0] * o.n[0][2] + n[2][1] * o.n[1][2] + n[2][2] * o.n[2][2] + n[2][3] * o.n[3][2];
            result.n[2][3] = n[2][0] * o.n[0][3] + n[2][1] * o.n[1][3] + n[2][2] * o.n[2][3] + n[2][3] * o.n[3][3];

            result.n[3][0] = n[3][0] * o.n[0][0] + n[3][1] * o.n[1][0] + n[3][3] * o.n[2][0] + n[3][3] * o.n[3][0];
            result.n[3][1] = n[3][0] * o.n[0][1] + n[3][1] * o.n[1][1] + n[3][3] * o.n[2][1] + n[3][3] * o.n[3][1];
            result.n[3][2] = n[3][0] * o.n[0][2] + n[3][1] * o.n[1][2] + n[3][3] * o.n[2][2] + n[3][3] * o.n[3][2];
            result.n[3][3] = n[3][0] * o.n[0][3] + n[3][1] * o.n[1][3] + n[3][3] * o.n[2][3] + n[3][3] * o.n[3][3];
            return result;
        }

        /**
         * Addition by other matrix4
         * @param other some matrix4 
         * @return calculated matrix 
         */
        mat4 operator+(const mat4 &other) const
        {
            math::mat4 result;
            result.n[0][0] = n[0][0] + other.n[0][0];
            result.n[0][1] = n[0][1] + other.n[0][1];
            result.n[0][2] = n[0][2] + other.n[0][2];
            result.n[0][3] = n[0][3] + other.n[0][3];

            result.n[1][0] = n[1][0] + other.n[1][0];
            result.n[1][1] = n[1][1] + other.n[1][1];
            result.n[1][2] = n[1][2] + other.n[1][2];
            result.n[1][3] = n[1][3] + other.n[1][3];

            result.n[2][0] = n[2][0] + other.n[2][0];
            result.n[2][1] = n[2][1] + other.n[2][1];
            result.n[2][2] = n[2][2] + other.n[2][2];
            result.n[2][3] = n[2][3] + other.n[2][3];

            result.n[3][0] = n[3][0] + other.n[3][0];
            result.n[3][1] = n[3][1] + other.n[3][1];
            result.n[3][2] = n[3][2] + other.n[3][2];
            result.n[3][3] = n[3][3] + other.n[3][3];
            return result;
        }

        /**
         * Multiplication by scalar
         * @param scalar 
         * @return calculated matrix
         */
        mat4 &operator*=(float scalar)
        {
            *this = *this * scalar;
            return *this;
        }
        
        /**
         * Multiplication by other matrix4
         * @param other some matrix4 
         * @return calculated matrix
         * @details https://en.wikipedia.org/wiki/Matrix_multiplication
         */
        mat4 &operator*=(const mat4 &other)
        {
            *this = *this * other;
            return *this;
        }

        /**
         * Addition by other matrix4
         * @param other some matrix4 
         * @return calculated matrix 
         */
        mat4 &operator+=(const mat4 &other)
        {
            *this = *this + other;
            return *this;
        }

        /**
         * Compare current matrix with other
         * @param other some matrix4
         * @return true if all elements are equal
         */
        bool operator==(const mat4 &other) const
        {
            return (n[0][0] == other.n[0][0] &&
                    n[0][1] == other.n[0][1] &&
                    n[0][2] == other.n[0][2] &&
                    n[0][3] == other.n[0][3] &&

                    n[1][0] == other.n[1][0] &&
                    n[1][1] == other.n[1][1] &&
                    n[1][2] == other.n[1][2] &&
                    n[1][3] == other.n[1][3] &&

                    n[2][0] == other.n[2][0] &&
                    n[2][1] == other.n[2][1] &&
                    n[2][2] == other.n[2][2] &&
                    n[2][3] == other.n[2][3] &&

                    n[3][0] == other.n[3][0] &&
                    n[3][1] == other.n[3][1] &&
                    n[3][2] == other.n[3][2] &&
                    n[3][3] == other.n[3][3] );
        }

        /**
         * Compare current matrix with another
         * @param other some matrix4
         * @return true if one at least one element differ
         */
        bool operator!=(const mat4 &other) const
        {
            return !(*this == other);
        }

        /**
         * Stream insertion
         * @param ostream output stream
         * @param mat matrix that will be putted to stream
         * @note will be removed
         * @return
         */
        friend std::ostream &operator<<(std::ostream &ostream, const mat4 &mat)
        {
            ostream << mat.n[0][0] << '\t' << mat.n[0][1] << '\t' << mat.n[0][2] << '\t' << mat.n[0][3] << '\n'
                    << mat.n[1][0] << '\t' << mat.n[1][1] << '\t' << mat.n[1][2] << '\t' << mat.n[1][3] << '\n'
                    << mat.n[2][0] << '\t' << mat.n[2][1] << '\t' << mat.n[2][2] << '\t' << mat.n[2][3] << '\n'
                    << mat.n[3][0] << '\t' << mat.n[3][1] << '\t' << mat.n[3][2] << '\t' << mat.n[3][3] << '\n';
            return ostream;
        }

        /**
         * Transoses matrix
         * @return transposed matrix
         * @detail https://en.wikipedia.org/wiki/Transpose
         */
        [[nodiscard]] mat4 transpose() const
        {
            mat4 result;
            result.n[0][0] = n[0][0];
            result.n[0][1] = n[1][0];
            result.n[0][2] = n[2][0];
            result.n[0][3] = n[3][0];

            result.n[1][0] = n[0][1];
            result.n[1][1] = n[1][1];
            result.n[1][2] = n[2][1];
            result.n[1][3] = n[3][1];

            result.n[2][0] = n[0][2];
            result.n[2][1] = n[1][2];
            result.n[2][2] = n[2][2];
            result.n[2][3] = n[3][2];

            result.n[3][0] = n[0][3];
            result.n[3][1] = n[1][3];
            result.n[3][2] = n[2][3];
            result.n[3][3] = n[3][3];
            return result;
        }

        /**
         * Calculates matrix determinant
         * @return matrix determinant
         * @details https://en.wikipedia.org/wiki/Determinant
         * @note for 3x3 matrix determinant 
         * I've used new method discribed here (Scheme 5): http://m-hikari.com/ija/ija-password-2009/ija-password5-8-2009/hajrizajIJA5-8-2009.pdf
         */
        [[nodiscard]] float determinant() const
        {
            return
            n[0][0] * (n[1][3] * n[2][1] * n[3][2] + n[1][1] * n[2][2] * n[3][3] +
                        n[1][2] * n[2][3] * n[3][1] - n[3][3] * n[2][1] * n[1][2] -
                        n[3][1] * n[2][2] * n[1][3] - n[3][2] * n[2][3] * n[1][1])

            -n[0][1] * (n[1][3] * n[2][0] * n[3][2] + n[1][0] * n[2][2] * n[3][3] +
                        n[1][2] * n[2][3] * n[3][0] - n[3][3] * n[2][0] * n[1][2] -
                        n[3][0] * n[2][2] * n[1][3] - n[3][2] * n[2][3] * n[1][0])

            +n[0][2] * (n[1][3] * n[2][0] * n[3][1] + n[1][0] * n[2][1] * n[3][3] +
                        n[1][1] * n[2][3] * n[3][0] - n[1][1] * n[2][0] * n[3][3] -
                        n[1][3] * n[2][1] * n[3][0] - n[3][1] * n[2][3] * n[1][0])

            -n[0][3] * (n[1][2] * n[2][0] * n[3][1] + n[1][0] * n[2][1] * n[3][2] +
                        n[1][1] * n[2][2] * n[3][0] - n[3][2] * n[2][0] * n[1][1] -
                        n[3][0] * n[2][1] * n[1][2] - n[3][1] * n[2][2] * n[1][0]);
        }

        /**
         * Calculates matrix minor
         * @return minor matrix
         * @details https://en.wikipedia.org/wiki/Minor_(linear_algebra)
         */
        [[nodiscard]] mat4 minor() const
        {               // M (0,0)
            return mat4(n[1][1] * n[2][2] * n[3][3] + n[1][2] * n[2][3] * n[3][1] +
                        n[1][3] * n[2][1] * n[3][2] - n[1][3] * n[2][2] * n[3][1] -
                        n[1][2] * n[2][1] * n[3][3] - n[1][1] * n[2][3] * n[3][2] ,
                        // M (0,1)
                        n[1][0] * n[2][2] * n[3][3] + n[1][2] * n[2][3] * n[3][0] +
                        n[1][3] * n[2][0] * n[3][2] - n[1][3] * n[2][2] * n[3][0] -
                        n[1][2] * n[2][0] * n[3][3] - n[1][0] * n[2][3] * n[3][2] ,
                        // M (0,2)
                        n[1][0] * n[2][1] * n[3][3] + n[1][1] * n[2][3] * n[3][0] +
                        n[1][3] * n[2][0] * n[3][1] - n[1][3] * n[2][1] * n[3][0] -
                        n[1][1] * n[2][0] * n[3][3] - n[1][0] * n[2][3] * n[3][1] ,
                        // M (0,3)
                        n[1][0] * n[2][1] * n[3][2] + n[1][1] * n[2][2] * n[3][0] +
                        n[1][2] * n[2][0] * n[3][1] - n[1][2] * n[2][1] * n[3][0] -
                        n[1][1] * n[2][0] * n[3][2] - n[1][0] * n[2][2] * n[3][1] ,
                        // --------------------------------------------------------
                        // M (1,0)
                        n[0][1] * n[2][2] * n[3][3] + n[0][2] * n[2][3] * n[3][1] +
                        n[0][3] * n[2][1] * n[3][2] - n[0][3] * n[2][2] * n[3][1] -
                        n[0][2] * n[2][1] * n[3][3] - n[0][1] * n[2][3] * n[3][2] ,
                        // M (1,1)
                        n[0][0] * n[2][2] * n[3][3] + n[0][2] * n[2][3] * n[3][0] +
                        n[0][3] * n[2][0] * n[3][2] - n[0][3] * n[2][2] * n[3][0] -
                        n[0][2] * n[2][0] * n[3][3] - n[0][0] * n[2][3] * n[3][2] ,
                        // M (1,2)
                        n[0][0] * n[2][1] * n[3][3] + n[0][1] * n[2][3] * n[3][0] +
                        n[0][3] * n[2][0] * n[3][1] - n[0][3] * n[2][1] * n[3][0] -
                        n[0][1] * n[2][0] * n[3][3] - n[0][0] * n[2][3] * n[3][1] ,
                        // M (1,3)
                        n[0][0] * n[2][1] * n[3][2] + n[0][1] * n[2][2] * n[3][0] +
                        n[0][2] * n[2][0] * n[3][1] - n[0][2] * n[2][1] * n[3][0] -
                        n[0][1] * n[2][0] * n[3][2] - n[0][0] * n[2][2] * n[3][1] ,
                        // --------------------------------------------------------
                        // M (2,0)
                        n[0][1] * n[1][2] * n[3][3] + n[0][2] * n[1][3] * n[3][1] +
                        n[0][3] * n[1][1] * n[3][2] - n[0][3] * n[1][2] * n[3][1] -
                        n[0][2] * n[1][1] * n[3][3] - n[0][1] * n[1][3] * n[3][2] ,
                        // M (2,1)
                        n[0][0] * n[1][2] * n[3][3] + n[0][2] * n[1][3] * n[3][0] +
                        n[0][3] * n[1][0] * n[3][2] - n[0][3] * n[1][2] * n[3][0] -
                        n[0][2] * n[1][0] * n[3][3] - n[0][0] * n[1][3] * n[3][2] ,
                        // M (2,2)
                        n[0][0] * n[1][1] * n[3][3] + n[0][1] * n[1][3] * n[3][0] +
                        n[0][3] * n[1][0] * n[3][1] - n[0][3] * n[1][1] * n[3][0] -
                        n[0][1] * n[1][0] * n[3][3] - n[0][0] * n[1][3] * n[3][1] ,
                        // M (2,3)
                        n[0][0] * n[1][1] * n[3][2] + n[0][1] * n[1][2] * n[3][0] +
                        n[0][2] * n[1][0] * n[3][1] - n[0][2] * n[1][1] * n[3][0] -
                        n[0][1] * n[1][0] * n[3][2] - n[0][0] * n[1][2] * n[3][1] ,
                        // --------------------------------------------------------
                        // M (3,0)
                        n[0][1] * n[1][2] * n[2][3] + n[0][2] * n[1][3] * n[2][1] +
                        n[0][3] * n[1][1] * n[2][2] - n[0][3] * n[1][2] * n[2][1] -
                        n[0][2] * n[1][1] * n[2][3] - n[0][1] * n[1][3] * n[2][2] ,
                        // M (3,1)
                        n[0][0] * n[1][2] * n[2][3] + n[0][2] * n[1][3] * n[2][0] +
                        n[0][3] * n[1][0] * n[2][2] - n[0][3] * n[1][2] * n[2][0] -
                        n[0][2] * n[1][0] * n[2][3] - n[0][0] * n[1][3] * n[2][2] ,
                        // M (3,2)
                        n[0][0] * n[1][1] * n[2][3] + n[0][1] * n[1][3] * n[2][0] +
                        n[0][3] * n[1][0] * n[2][1] - n[0][3] * n[1][1] * n[2][0] -
                        n[0][1] * n[1][0] * n[2][3] - n[0][0] * n[1][3] * n[2][1] ,
                        // M (3,3)
                        n[0][0] * n[1][1] * n[2][2] + n[0][1] * n[1][2] * n[2][0] +
                        n[0][2] * n[1][0] * n[2][1] - n[0][2] * n[1][1] * n[2][0] -
                        n[0][1] * n[1][0] * n[2][2] - n[0][0] * n[1][2] * n[2][1]);
        }

        /**
         * Calculates matrix cofactor
         * @return calculation result
         * @details https://en.wikipedia.org/wiki/Minor_(linear_algebra)#Cofactor_expansion_of_the_determinant
         */
        [[nodiscard]] mat4 cofactor() const
        {
            mat4 result;
            mat4 minor_mat = minor();
            result.n[0][0] =  minor_mat.n[0][0];
            result.n[0][1] = -minor_mat.n[0][1];
            result.n[0][2] =  minor_mat.n[0][2];
            result.n[0][3] = -minor_mat.n[0][3];

            result.n[1][0] = -minor_mat.n[1][0];
            result.n[1][1] =  minor_mat.n[1][1];
            result.n[1][2] = -minor_mat.n[1][2];
            result.n[1][3] =  minor_mat.n[1][3];

            result.n[2][0] =  minor_mat.n[2][0];
            result.n[2][1] = -minor_mat.n[2][1];
            result.n[2][2] =  minor_mat.n[2][2];
            result.n[2][3] = -minor_mat.n[2][3];

            result.n[3][0] = -minor_mat.n[3][0];
            result.n[3][1] =  minor_mat.n[3][1];
            result.n[3][2] = -minor_mat.n[3][2];
            result.n[3][3] =  minor_mat.n[3][3];
            return result;
        }

        /**
         * Adjugates current matrix
         * @return calculation result
         * @details https://en.wikipedia.org/wiki/Adjugate_matrix
         */
        [[nodiscard]] mat4 adjugate() const
        {
            mat4 transposed = transpose();
            return transposed.cofactor();
        }

        /**
         * Inverses current matrix
         * @return inversed matrix
         * @details https://en.wikipedia.org/wiki/Invertible_matrix
         */
        mat4 inverse()
        {
            float det = determinant();
            if (utils::cmp(det, 0.0f))
                return mat4();
            return adjugate() * (1.0f / det);
        }
    };
}


#endif //INC_2D_ENGINE_matrix4_H