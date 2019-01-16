//
// Created by maksim on 6/27/18.
//

#ifndef INC_2D_ENGINE_MATRIX3_H
#define INC_2D_ENGINE_MATRIX3_H

#include "vector3.h"

namespace math {
    /// Three dimensional square matrix
    struct mat3 {
        float n[3][3];

        mat3() : n{0, 0, 0, 0, 0, 0, 0, 0, 0} {};

        mat3(float _11, float _12, float _13,
             float _21, float _22, float _23,
             float _31, float _32, float _33)
             : n{_11, _12, _13,
                 _21, _22, _23,
                 _31, _32, _33} {};

        mat3(const vec3 &a,
             const vec3 &b,
             const vec3 &c)
             : n{a.x, a.y, a.z,
                 b.x, b.y, b.z,
                 c.x, b.y, b.z} {};
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
         * @return row in vec3 representation  
         */
        vec3 &operator[](int j)
        {
            return (*reinterpret_cast<vec3 *>(n[j]));
        }

        /**
         * Gets row as vector
         * @param j row number
         * @return row in vec3 representation  
         */
        const vec3 &operator[](int j) const
        {
            return (*reinterpret_cast<const vec3 *>(n[j]));
        }

        /**
         * Multiplication by scalar
         * @param scalar 
         * @return calculated matrix
         */
        mat3 operator*(float scalar) const
        {
            mat3 result;
            result.n[0][0] = n[0][0] * scalar;
            result.n[0][1] = n[0][1] * scalar;
            result.n[0][2] = n[0][2] * scalar;

            result.n[1][0] = n[1][0] * scalar;
            result.n[1][1] = n[1][1] * scalar;
            result.n[1][2] = n[1][2] * scalar;

            result.n[2][0] = n[2][0] * scalar;
            result.n[2][1] = n[2][1] * scalar;
            result.n[2][2] = n[2][2] * scalar;
            return result;
        }

        /**
         * Multiplication by other matrix3
         * @param o some matrix3 
         * @return calculated matrix
         * @details https://en.wikipedia.org/wiki/Matrix_multiplication
         */
        mat3 operator*(const mat3 &o) const
        {
            math::mat3 result;
            result.n[0][0] = n[0][0] * o.n[0][0] + n[0][1] * o.n[1][0] + n[0][2] * o.n[2][0];
            result.n[0][1] = n[0][0] * o.n[0][1] + n[0][1] * o.n[1][1] + n[0][2] * o.n[2][1];
            result.n[0][2] = n[0][0] * o.n[0][2] + n[0][1] * o.n[1][2] + n[0][2] * o.n[2][2];

            result.n[1][0] = n[1][0] * o.n[0][0] + n[1][1] * o.n[1][0] + n[1][2] * o.n[2][0];
            result.n[1][1] = n[1][0] * o.n[0][1] + n[1][1] * o.n[1][1] + n[1][2] * o.n[2][1];
            result.n[1][2] = n[1][0] * o.n[0][2] + n[1][1] * o.n[1][2] + n[1][2] * o.n[2][2];

            result.n[2][0] = n[2][0] * o.n[0][0] + n[2][1] * o.n[1][0] + n[2][2] * o.n[2][0];
            result.n[2][1] = n[2][0] * o.n[0][1] + n[2][1] * o.n[1][1] + n[2][2] * o.n[2][1];
            result.n[2][2] = n[2][0] * o.n[0][2] + n[2][1] * o.n[1][2] + n[2][2] * o.n[2][2];
            return result;
        }

        /**
         * Addition by other matrix3
         * @param other some matrix3 
         * @return calculated matrix 
         */
        mat3 operator+(const mat3 &other) const
        {
            math::mat3 result;
            result.n[0][0] = n[0][0] + other.n[0][0];
            result.n[0][1] = n[0][1] + other.n[0][1];
            result.n[0][2] = n[0][2] + other.n[0][2];

            result.n[1][0] = n[1][0] + other.n[1][0];
            result.n[1][1] = n[1][1] + other.n[1][1];
            result.n[1][2] = n[1][2] + other.n[1][2];

            result.n[2][0] = n[2][0] + other.n[2][0];
            result.n[2][1] = n[2][1] + other.n[2][1];
            result.n[2][2] = n[2][2] + other.n[2][2];
            return result;
        }

        /**
         * Multiplication by scalar
         * @param scalar 
         * @return calculated matrix
         */
        mat3 &operator*=(float scalar)
        {
            *this = *this * scalar;
            return *this;
        }
        
        /**
         * Multiplication by other matrix3
         * @param other some matrix3 
         * @return calculated matrix
         * @details https://en.wikipedia.org/wiki/Matrix_multiplication
         */
        mat3 &operator*=(const mat3 &other)
        {
            *this = *this * other;
            return *this;
        }

        /**
         * Addition by other matrix3
         * @param other some matrix3 
         * @return calculated matrix 
         */
        mat3 &operator+=(const mat3 &other)
        {
            *this = *this + other;
            return *this;
        }

        /**
         * Compare current matrix with other
         * @param other some matrix3
         * @return true if all elments are equal 
         */
        bool operator==(const mat3 &other) const
        {
            return (n[0][0] == other.n[0][0] &&
                    n[0][1] == other.n[0][1] &&
                    n[0][2] == other.n[0][2] &&

                    n[1][0] == other.n[1][0] &&
                    n[1][1] == other.n[1][1] &&
                    n[1][2] == other.n[1][2] &&

                    n[2][0] == other.n[2][0] &&
                    n[2][1] == other.n[2][1] &&
                    n[2][2] == other.n[2][2] );
        }

        /**
         * Compare current matrix with another
         * @param other some matrix3
         * @return true if one at least one lement differ 
         */
        bool operator!=(const mat3 &other) const
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
        friend std::ostream &operator<<(std::ostream &ostream, const mat3 &mat)
        {
            ostream << mat.n[0][0] << '\t' << mat.n[0][1] << '\t' << mat.n[0][2] << '\n'
                    << mat.n[1][0] << '\t' << mat.n[1][1] << '\t' << mat.n[1][2] << '\n'
                    << mat.n[2][0] << '\t' << mat.n[2][1] << '\t' << mat.n[2][2] << '\n';
            return ostream;
        }

        /**
         * Transoses matix
         * @return transposed matrix
         * @detail https://en.wikipedia.org/wiki/Transpose
         */
        mat3 transpose() const
        {
            mat3 result;
            result.n[0][0] = n[0][0];
            result.n[0][1] = n[1][0];
            result.n[0][2] = n[2][0];

            result.n[1][0] = n[0][1];
            result.n[1][1] = n[1][1];
            result.n[1][2] = n[2][1];

            result.n[2][0] = n[0][2];
            result.n[2][1] = n[1][2];
            result.n[2][2] = n[2][2];
            return result;
        }

        /**
         * Calculates matrix determinant
         * @return matrix determinant
         * @details https://en.wikipedia.org/wiki/Determinant
         */
        float determinant() const
        {
            return n[0][0] * (n[1][1] * n[2][2] - n[1][2] * n[2][1]) -
                   n[0][1] * (n[1][0] * n[2][2] - n[1][2] * n[2][0]) +
                   n[0][2] * (n[1][0] * n[2][1] - n[1][1] * n[2][0]);

        }

        /**
         * Calculates matrix minor
         * @return minor matrix
         * @details https://en.wikipedia.org/wiki/Minor_(linear_algebra)
         */
        mat3 minor() const
        {
            return mat3(n[1][1] * n[2][2] - n[1][2] * n[2][1],
                        n[1][0] * n[2][2] - n[1][2] * n[2][0],
                        n[1][0] * n[2][1] - n[1][1] * n[2][0],

                        n[0][1] * n[2][2] - n[0][2] * n[2][1],
                        n[0][0] * n[2][2] - n[0][2] * n[2][0],
                        n[0][0] * n[2][1] - n[0][1] * n[2][0],

                        n[0][1] * n[1][2] - n[0][2] * n[1][1],
                        n[0][0] * n[1][2] - n[0][2] * n[1][0],
                        n[0][0] * n[1][1] - n[0][1] * n[1][0]);
        }

        /**
         * Calculates matrix cofactor
         * @return calculation result
         * @details https://en.wikipedia.org/wiki/Minor_(linear_algebra)#Cofactor_expansion_of_the_determinant
         */
        mat3 cofactor() const
        {
            mat3 result;
            mat3 minor_mat = minor();
            result.n[0][0] =  minor_mat.n[0][0];
            result.n[0][1] = -minor_mat.n[0][1];
            result.n[0][2] =  minor_mat.n[0][2];

            result.n[1][0] = -minor_mat.n[1][0];
            result.n[1][1] =  minor_mat.n[1][1];
            result.n[1][2] = -minor_mat.n[1][2];

            result.n[2][0] =  minor_mat.n[2][0];
            result.n[2][1] = -minor_mat.n[2][1];
            result.n[2][2] =  minor_mat.n[2][2];
            return result;
        }

        /**
         * Adjugates current matrix
         * @return calculation result
         * @details https://en.wikipedia.org/wiki/Adjugate_matrix
         */
        mat3 adjugate() const
        {
            mat3 transposed = transpose();
            return transposed.cofactor();
        }

        /**
         * Inverses current matrix
         * @return inversed matix
         * @details https://en.wikipedia.org/wiki/Invertible_matrix
         */
        mat3 inverse()
        {
            float det = determinant();
            if (utils::cmp(det, 0.0f))
                return mat3();
            return adjugate() * (1.0f / det);
        }
    };
}


#endif //INC_2D_ENGINE_MATRIX3_H
