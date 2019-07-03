//
// Created by maksim on 6/27/18.
//

#ifndef INC_2D_ENGINE_MATRIX2_H
#define INC_2D_ENGINE_MATRIX2_H

#include "vector2.h"

// clang-format off
namespace math {
    /// Two dimensional square matrix
    struct mat2 {
        float n[2][2];

        mat2() : n{0, 0, 0, 0} {};

        mat2(float _11, float _12,
             float _21, float _22)
             : n{_11, _12,
                 _21, _22} {};

        mat2(const vec2 &a,
             const vec2 &b)
             : n{a.x, a.y,
                 b.x, b.y} {};
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
         * @return row in vec2 representation  
         */
        vec2 &operator[](int j)
        {
            return (*reinterpret_cast<vec2 *>(n[j]));
        }

        /**
         * Gets row as vector
         * @param j row number
         * @return row in vec2 representation  
         */
        const vec2 &operator[](int j) const
        {
            return (*reinterpret_cast<const vec2 *>(n[j]));
        }

        /**
         * Multiplication by scalar
         * @param scalar 
         * @return calculated matrix
         */
        mat2 operator*(float scalar) const
        {
            mat2 result;
            result.n[0][0] = n[0][0] * scalar;
            result.n[0][1] = n[0][1] * scalar;
            result.n[1][0] = n[1][0] * scalar;
            result.n[1][1] = n[1][1] * scalar;
            return result;
        }

        /**
         * Multiplication by other matrix2
         * @param other some matrix2 
         * @return calculated matrix
         * @details https://en.wikipedia.org/wiki/Matrix_multiplication
         */
        mat2 operator*(const mat2 &other) const
        {
            math::mat2 result;
            result.n[0][0] = n[0][0] * other.n[0][0] + n[0][1] * other.n[1][0];
            result.n[0][1] = n[0][0] * other.n[0][1] + n[0][1] * other.n[1][1];
            result.n[1][0] = n[1][0] * other.n[0][0] + n[1][1] * other.n[1][0];
            result.n[1][1] = n[1][0] * other.n[0][1] + n[1][1] * other.n[1][1];
            return result;
        }

        /**
         * Addition by other matrix2
         * @param other some matrix2 
         * @return calculated matrix 
         */
        mat2 operator+(const mat2 &other) const
        {
            math::mat2 result;
            result.n[0][0] = n[0][0] + other.n[0][0];
            result.n[0][1] = n[0][1] + other.n[0][1];
            result.n[1][0] = n[1][0] + other.n[1][0];
            result.n[1][1] = n[1][1] + other.n[1][1];
            return result;
        }
        
        /**
         * Multiplication by scalar
         * @param scalar 
         * @return calculated matrix
         */
        mat2 &operator*=(float scalar)
        {
            *this = *this * scalar;
            return *this;
        }
        
        /**
         * Multiplication by other matrix2
         * @param other some matrix2 
         * @return calculated matrix
         * @details https://en.wikipedia.org/wiki/Matrix_multiplication
         */
        mat2 &operator*=(const mat2 &other)
        {
            *this = *this * other;
            return *this;
        }

        /**
         * Addition by other matrix2
         * @param other some matrix2 
         * @return calculated matrix 
         */
        mat2 &operator+=(const mat2 &other)
        {
            *this = *this + other;
            return *this;
        }

        /**
         * Compare current matrix with other
         * @param other some matrix2
         * @return true if all elements are equal
         */
        bool operator==(const mat2 &other) const
        {
            return ( n[0][0] == other.n[0][0] &&
                     n[0][1] == other.n[0][1] &&
                     n[1][0] == other.n[1][0] &&
                     n[1][1] == other.n[1][1] );
        }

        /**
         * Compare current matrix with another
         * @param other some matrix2
         * @return true if one at least one element differ
         */
        bool operator!=(const mat2 &other) const
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
        friend std::ostream &operator<<(std::ostream &ostream, const mat2 &mat)
        {
            ostream << mat.n[0][0] << '\t' << mat.n[0][1] << '\n'
                    << mat.n[1][0] << '\t' << mat.n[1][1] << '\n';
            return ostream;
        }

        /**
         * Transoses matrix
         * @return transposed matrix
         * @detail https://en.wikipedia.org/wiki/Transpose
         */
        mat2 transpose() const
        {
            mat2 result;
            result.n[0][0] = n[0][0];
            result.n[0][1] = n[1][0];
            result.n[1][0] = n[0][1];
            result.n[1][1] = n[1][1];
            return result;
        }

        /**
         * Calculates matrix determinant
         * @return matrix determinant
         * @details https://en.wikipedia.org/wiki/Determinant
         */
        float determinant() const
        {
            return n[0][0] * n[1][1] -
                   n[0][1] * n[1][0];
        }

        /**
         * Calculates matrix minor
         * @return minor matrix
         * @details https://en.wikipedia.org/wiki/Minor_(linear_algebra)
         */
        mat2 minor() const
        {
            return mat2(n[1][1], n[1][0],
                        n[0][1], n[0][0]);
        }

        /**
         * Calculates matrix cofactor
         * @return calculation result
         * @details https://en.wikipedia.org/wiki/Minor_(linear_algebra)#Cofactor_expansion_of_the_determinant
         */
        mat2 cofactor() const
        {
            mat2 result;
            mat2 minor_mat = minor();
            result.n[0][0] =  minor_mat.n[0][0];
            result.n[0][1] = -minor_mat.n[0][1];
            result.n[1][0] = -minor_mat.n[1][0];
            result.n[1][1] =  minor_mat.n[1][1];
            return result;
        }

        /**
         * Adjugates current matrix
         * @return calculation result
         * @details https://en.wikipedia.org/wiki/Adjugate_matrix
         */
        mat2 adjugate() const
        {
            mat2 transposed = transpose();
            return transposed.cofactor();
        }

        /**
         * Inverses current matrix
         * @return inversed matrix
         * @details https://en.wikipedia.org/wiki/Invertible_matrix
         */
        mat2 inverse()
        {
            float det = determinant();
            if (utils::cmp(det, 0.0f))
                return mat2();
            return adjugate() * (1.0f / det);
        }
    };
}


#endif //INC_2D_ENGINE_MATRIX2_H
