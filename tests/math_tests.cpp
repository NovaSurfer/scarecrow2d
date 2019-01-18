//
// Created by maksim on 6/29/18.
//
#include <iostream>
#include "catch2/catch.hpp"
#include "../src/math/matrix2.h"
#include "../src/math/matrix3.h"
#include "../src/math/matrix4.h"
#include "../src/math/vector2.h"

using namespace math;

TEST_CASE("mat2d-operations", "[math]")
{
    mat2 matrix(1, 2, 3, 4);

    SECTION("is equal")
    {
        mat2 m(1, 2, 3, 4);
        REQUIRE(matrix == m);
    }

    SECTION("get value at position (i,j)")
    {
        REQUIRE(matrix(0, 0) == 1);
        REQUIRE(matrix(0, 1) == 2);
        REQUIRE(matrix(1, 0) == 3);
        REQUIRE(matrix(1, 1) == 4);

        SECTION("get values at position as const")
        {
            const mat2 const_matrix;
            REQUIRE(std::is_const<std::remove_reference<decltype(const_matrix(0, 0))>::type>::value);
        }
    }

    SECTION("get column values in vec2")
    {
        REQUIRE(typeid(matrix[0]) == typeid(vec2));

        SECTION("get column values as const")
        {
            const mat2 const_matrix;
            REQUIRE(std::is_const<std::remove_reference<decltype(const_matrix[0])>::type>::value);
        }
    }

    SECTION("scalar multiplication")
    {
        float scalar = 8;
        mat2 result = matrix * 8;

        REQUIRE(result == mat2(8, 16, 24, 32));

        SECTION("*= operator with scalar")
        {
            matrix *= 8;
            REQUIRE(matrix == mat2(8, 16, 24, 32));
        }
    }

    SECTION("matrix multiplication")
    {
        mat2 matrix2(1, 2, 3, 4);
        mat2 result = matrix * matrix2;
        REQUIRE(result == mat2(7, 10, 15, 22));

        SECTION("*= operator with matrix")
        {
            matrix *= matrix2;
            REQUIRE(matrix == mat2(7, 10, 15, 22));
        }
    }

    SECTION("matrix addition")
    {
        mat2 matrix2(1, 2, 3, 4);
        mat2 result = matrix + matrix2;
        REQUIRE(result == mat2(2, 4, 6, 8));

        SECTION("+= operator with matrix")
        {
            matrix += matrix2;
            REQUIRE(matrix == mat2(2, 4, 6, 8));
        }
    }

    SECTION("transpose")
    {
        REQUIRE(matrix.transpose() == mat2(1, 3, 2, 4));
    }

    SECTION("determinant")
    {
        REQUIRE(matrix.determinant() == -2);
    }

    SECTION("minor")
    {
        REQUIRE(matrix.minor() == mat2(4, 3, 2, 1));
    }

    SECTION("cofactor")
    {
        REQUIRE(matrix.cofactor() == mat2(4, -3, -2, 1));
    }

    SECTION("adjugate")
    {
        REQUIRE(matrix.adjugate() == mat2(4, -2, -3, 1));
    }

    SECTION("inverse")
    {
        REQUIRE(matrix * matrix.inverse() == mat2(1,0,0,1));
    }
}

// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------

TEST_CASE("mat3d-operations", "[math]")
{
    mat3 matrix(1, 1, 1, 2, 2, 2, 3, 3, 3);
    mat3 matx3(1, 1, 1, 2, 5, 8, 9, 3, 3);
    
    SECTION("is equal")
    {
        mat3 m(1, 1, 1, 2, 2, 2, 3, 3, 3);
        REQUIRE(matrix == m);
    }

    SECTION("get value at position (i,j)")
    {
        REQUIRE(matrix(0, 0) == 1);
        REQUIRE(matrix(0, 1) == 1);
        REQUIRE(matrix(0, 2) == 1);

        REQUIRE(matrix(1, 0) == 2);
        REQUIRE(matrix(1, 1) == 2);
        REQUIRE(matrix(1, 2) == 2);

        REQUIRE(matrix(2, 0) == 3);
        REQUIRE(matrix(2, 1) == 3);
        REQUIRE(matrix(2, 2) == 3);


        SECTION("get values at position as const")
        {
            const mat3 const_matrix;
            REQUIRE(std::is_const<std::remove_reference<decltype(const_matrix(0, 0))>::type>::value);
        }
    }

    SECTION("get column values in vec3")
    {
        REQUIRE(typeid(matrix[0]) == typeid(vec3));

        SECTION("get column values as const")
        {
            const mat3 const_matrix;
            REQUIRE(std::is_const<std::remove_reference<decltype(const_matrix[0])>::type>::value);
        }
    }

    SECTION("scalar multiplication")
    {
        float scalar = 8;
        mat3 result = matrix * 8;

        REQUIRE(result == mat3(8, 8, 8, 16, 16, 16, 24, 24, 24));

        SECTION("*= operator with scalar")
        {
            matrix *= 8;
            REQUIRE(matrix == mat3(8, 8, 8, 16, 16, 16, 24, 24, 24));
        }
    }

    SECTION("matrix multiplication")
    {
        mat3 matrix2(1, 1, 1, 2, 2, 2, 3, 3, 3);
        mat3 result = matrix * matrix2;
        REQUIRE(result == mat3(6, 6, 6, 12, 12, 12, 18, 18, 18));

        SECTION("*= operator with matrix")
        {
            matrix *= matrix2;
            REQUIRE(matrix == mat3(6, 6, 6, 12, 12, 12, 18, 18, 18));
        }
    }

    SECTION("matrix addition")
    {
        mat3 matrix2(1, 1, 1, 2, 2, 2, 3, 3, 3);
        mat3 result = matrix + matrix2;
        REQUIRE(result == mat3(2, 2, 2, 4, 4, 4, 6, 6, 6));

        SECTION("+= operator with matrix")
        {
            matrix += matrix2;
            REQUIRE(matrix == mat3(2, 2, 2, 4, 4, 4, 6, 6, 6));
        }
    }

    SECTION("transpose")
    {
        REQUIRE(matrix.transpose() == mat3(1, 2, 3, 1, 2, 3, 1, 2, 3));
    }

    SECTION("determinant")
    {
        REQUIRE(matx3.determinant() == 18);
    }

    SECTION("minor")
    {
        REQUIRE(matx3.minor() == mat3(-9, -66, -39, 0, -6, -6, 3, 6, 3));
    }

    SECTION("cofactor")
    {
        REQUIRE(matx3.cofactor() == mat3(-9, 66, -39, -0, -6, 6, 3, -6, 3));
    }

    SECTION("adjugate")
    {
        REQUIRE(matx3.adjugate() == mat3(-9, 0, 3, 66, -6, -6, -39, 6, 3));
    }
    // TODO:
    // SECTION("inverse")
    // {
    //     mat3 matrix2(1, 1, 1, 2, 5, 8, 9, 3, 3);
    //     std::cout << matrix2.inverse();
    //     REQUIRE(matrix2 * matrix2.inverse() == mat3(1, 0, 0, 0, 1, 0, 0, 0, 1));
    // }
}

// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------

TEST_CASE("mat4d-operations", "[math]")
{
    mat4 matrix(1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 5, 8, 9, 4, 4, 4);
    mat4 matx3(1, 1, 2, 1, 2, 4, 2, 2, 2, 5, 5, 8, 9, 4, 4, 4);

    SECTION("is equal")
    {
        mat4 m(1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 5, 8, 9, 4, 4, 4);
        REQUIRE(matrix == m);
    }

    SECTION("get value at position (i,j)")
    {
        REQUIRE(matrix(0, 0) == 1);
        REQUIRE(matrix(0, 1) == 1);
        REQUIRE(matrix(0, 2) == 1);
        REQUIRE(matrix(0, 3) == 1);

        REQUIRE(matrix(1, 0) == 2);
        REQUIRE(matrix(1, 1) == 2);
        REQUIRE(matrix(1, 2) == 2);
        REQUIRE(matrix(1, 3) == 2);

        REQUIRE(matrix(2, 0) == 3);
        REQUIRE(matrix(2, 1) == 3);
        REQUIRE(matrix(2, 2) == 5);
        REQUIRE(matrix(2, 3) == 8);

        REQUIRE(matrix(3, 0) == 9);
        REQUIRE(matrix(3, 1) == 4);
        REQUIRE(matrix(3, 2) == 4);
        REQUIRE(matrix(3, 3) == 4);

        SECTION("get values at position as const")
        {
            const mat4 const_matrix;
            REQUIRE(std::is_const<std::remove_reference<decltype(const_matrix(0, 0))>::type>::value);
        }
    }

    SECTION("get column values in vec4")
    {
        REQUIRE(typeid(matrix[0]) == typeid(vec4));

        SECTION("get column values as const")
        {
            const mat4 const_matrix;
            REQUIRE(std::is_const<std::remove_reference<decltype(const_matrix[0])>::type>::value);
        }
    }

    SECTION("scalar multiplication")
    {
        float scalar = 8;
        mat4 result = matrix * 8;

        REQUIRE(result == mat4(8,8,8,8,16,16,16,16,24,24,40,64,72,32,32,32));

        SECTION("*= operator with scalar")
        {
            matrix *= 8;
            REQUIRE(matrix == mat4(8,8,8,8,16,16,16,16,24,24,40,64,72,32,32,32));
        }
    }

    SECTION("matrix multiplication")
    {
        mat4 matrix2(1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4);
        mat4 result = matrix * matrix2;
        REQUIRE(result == mat4(10,10,10,10,20,20,20,20,56,56,56,56,45,45,45,45));

        SECTION("*= operator with matrix")
        {
            matrix *= matrix2;
            REQUIRE(matrix == mat4(10,10,10,10,20,20,20,20,56,56,56,56,45,45,45,45));
        }
    }

    SECTION("matrix addition")
    {
        mat4 matrix2(1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4);
        mat4 result = matrix + matrix2;
        REQUIRE(result == mat4(2, 2, 2, 2, 4, 4, 4, 4, 6, 6, 8, 11, 13, 8, 8, 8));

        SECTION("+= operator with matrix")
        {
            matrix += matrix2;
            REQUIRE(matrix == mat4(2, 2, 2, 2, 4, 4, 4, 4, 6, 6, 8, 11, 13, 8, 8, 8));
        }
    }

    SECTION("transpose")
    {
        REQUIRE(matrix.transpose() == mat4(1, 2, 3, 9, 1, 2, 3, 4, 1, 2, 5, 4, 1, 2, 8, 4));
    }
// TODO:
//    SECTION("determinant")
//    {
//        REQUIRE(matx3.determinant() == 188);
//    }

    SECTION("minor")
    {
        REQUIRE(matx3.minor() == mat4(-24, 30, 158, 74, 12, 79, 15, -37, -8, 10, -10, -38, -28, -12, 12, 8));
    }

    SECTION("cofactor")
    {
        REQUIRE(matx3.cofactor() == mat4(-24, -30, 158, -74, -12, 79, -15, -37, -8, -10, -10, 38, 28, -12, -12, 8));
    }

    SECTION("adjugate")
    {
        REQUIRE(matx3.adjugate() == mat4(-24, -12, -8, 28, -30, 79, -10, -12, 158, -15, -10, -12, -74, -37, 38, 8));
    }

    // SECTION("inverse")
    // {
    //     mat3 matrix2(1, 1, 1, 2, 5, 8, 9, 3, 3);
    //     std::cout << matrix2.inverse();
    //     REQUIRE(matrix2 * matrix2.inverse() == mat3(1, 0, 0, 0, 1, 0, 0, 0, 1));
    // }
}


TEST_CASE("vec2d-operations", "[math]")
{
    vec2 vector(1, 2);

    SECTION("is equal")
    {
        vec2 v(1, 2);
        REQUIRE(vector == v);
    }

    SECTION("get element as array")
    {
        REQUIRE(vector[0] == 1);
        REQUIRE(vector[1] == 2);

        SECTION("get element as const")
        {
            const vec2 const_v;
            REQUIRE(std::is_const<std::remove_reference<decltype(const_v[0])>::type>::value);
        }
    }

    SECTION("scalar multiplication")
    {
        float scalar = 8;
        vec2 result = vector * 8;

        REQUIRE(result == vec2(8, 16));

        SECTION("*= operator with scalar")
        {
            vector *= 8;
            REQUIRE(vector == vec2(8, 16));
        }
    }

    SECTION("scalar division")
    {
        float scalar = 2;
        vec2 result = vector / 2;

        REQUIRE(result == vec2(0.5f, 1.0f));

        SECTION("/= operator with scalar")
        {
            vector /= 2;
            REQUIRE(vector == vec2(0.5f, 1.0f));
        }
    }

    SECTION("vector addition")
    {
        vec2 v(1, 2);
        vec2 result = vector + v;

        REQUIRE(result == vec2(2, 4));

        SECTION("+= operator")
        {
            vector += v;
            REQUIRE(vector == vec2(2, 4));
        }
    }

    SECTION("vector subtraction")
    {
        vec2 v(1, 2);
        vec2 result = vector - v;

        REQUIRE(result == vec2());

        SECTION("-= operator")
        {
            vector -= v;
            REQUIRE(vector == vec2());
        }
    }

    SECTION("dot product")
    {
        vec2 v(2, 4);
        float result = dot(vector, v);
        REQUIRE(result == 10.0f);
    };

    SECTION("magnitude")
    {
        float result = magnitude(vector);
        REQUIRE(result == Approx(2.236067f));
    }

    SECTION("squire magnitude")
    {
        REQUIRE(magnitudeSq(vector) == 5.0f);
    }

    SECTION("distance")
    {
        REQUIRE(distance(vec2(4, 6), vector) == 5.0f);
    }

    SECTION("normalize")
    {
        //  FAILED:
        //  REQUIRE( magnitude(normalize(vector)) == 1.0f )
        //  with expansion:
        //  1.0f == 1.0f
        REQUIRE(magnitude(normalize(vector)) == Approx(1.0f));
    }

    SECTION("get angle")
    {
        REQUIRE(angle(vector, vector) == 0.0f);
    }

    SECTION("projection")
    {
        vec2 v(3, 6);
        REQUIRE(project(vector, v) == vec2(1, 2));
    }

    SECTION("perpendicular")
    {
        vec2 v(3, 6);
        REQUIRE(perpendicular(vector, v) == vec2());
    }

    SECTION("reflection")
    {
        REQUIRE(reflection(vector, normalize(vector)) == vec2(-1,-2));
    }
}